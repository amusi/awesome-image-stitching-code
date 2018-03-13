// Summary: ��OpenCV���е�stitching.cpp�޸ĺ����ע��
// Author:  Amusi
// Date:    2018-03-01
// Reference:
//		[1]Stitcher class: https://docs.opencv.org/master/d2/d8d/classcv_1_1Stitcher.html
//		[2]stitching tutorial: https://docs.opencv.org/master/d8/d19/tutorial_stitcher.html

// Note: �˳���ʹ��GPU����

// C++���ļ�
#include<iostream>

// OpenCV���ļ�
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
	// ��ȡͼ��
	vector<Mat> imgs;
	Mat pano;
	Mat img_temp;

#if 1
	// �������������
	if(argc < 2)
	{
		cerr << "Please input images name..." << endl;
		cerr << "Such as: *.exe img1 img2 img3 ... " << endl;
		return -1;
	}
	for(int i = 1; i < argc; ++i)
	{
		img_temp = imread(argv[i]);
		imgs.push_back(img_temp);
	}
#else
	// �̶�����
	img_temp = imread("0001.jpg");
	imgs.push_back(img_temp);
	img_temp = imread("0002.jpg");
	imgs.push_back(img_temp);
	img_temp = imread("0003.jpg");
	imgs.push_back(img_temp);
#endif

	// ����Stitcher����
	bool try_use_gpu = false;					// true: ʹ��GPU; false: ʹ��CPU
	bool divide_images = true;					// true: false:
	Stitcher::Mode mode = Stitcher::PANORAMA;	// Mode: PANORAMA=0 ����ȫ��ͼ panoramo; SCANS=1 ����ɨ��ͼ

	// ͼ��ƴ�Ӽ�ʱ
	double time_start = static_cast<double>(getTickCount());

#if 1
	// ����ָ��Stitcher�������ָ��Ptr
	Ptr<Stitcher> stitcher = Stitcher::create(mode, try_use_gpu);
	// ͼ��ƴ��
	Stitcher::Status status = stitcher->stitch(imgs, pano);

#else
	// ����Stitcher�����
	Stitcher stitcher = Stitcher::createDefault(try_use_gpu);
	// ͼ��ƴ��
	Stitcher::Status status = stitcher.stitch(imgs, pano);
#endif

	// �ж�ƴ��״̬
	if (status != Stitcher::OK)
	{
		cerr << "Can't stitch images, error code = " << static_cast<int>(status) << endl;
		return -1;
	}

	// ����ͼ��ƴ�Ӻ�ʱ
	cout << "Cost time: " << static_cast<double>((getTickCount()-time_start) / getTickFrequency()) << " sec"<<endl;

	// ��ʾ������ȫ��ͼ
	namedWindow("Panoramo", WINDOW_NORMAL);
	imshow("Panoramo", pano);
	imwrite("panoramo.jpg", pano);
	waitKey(0);

	return 0;
}