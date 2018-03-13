// Summary: 对OpenCV库中的stitching.cpp修改和添加注释
// Author:  Amusi
// Date:    2018-03-01
// Reference:
//		[1]Stitcher class: https://docs.opencv.org/master/d2/d8d/classcv_1_1Stitcher.html
//		[2]stitching tutorial: https://docs.opencv.org/master/d8/d19/tutorial_stitcher.html

// Note: 此程序不使用GPU加速

// C++库文件
#include<iostream>

// OpenCV库文件
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
	// 读取图像
	vector<Mat> imgs;
	Mat pano;
	Mat img_temp;

#if 1
	// 命令行输入参数
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
	// 固定参数
	img_temp = imread("0001.jpg");
	imgs.push_back(img_temp);
	img_temp = imread("0002.jpg");
	imgs.push_back(img_temp);
	img_temp = imread("0003.jpg");
	imgs.push_back(img_temp);
#endif

	// 设置Stitcher参数
	bool try_use_gpu = false;					// true: 使用GPU; false: 使用CPU
	bool divide_images = true;					// true: false:
	Stitcher::Mode mode = Stitcher::PANORAMA;	// Mode: PANORAMA=0 创建全景图 panoramo; SCANS=1 创建扫描图

	// 图像拼接计时
	double time_start = static_cast<double>(getTickCount());

#if 1
	// 创建指向Stitcher类的智能指针Ptr
	Ptr<Stitcher> stitcher = Stitcher::create(mode, try_use_gpu);
	// 图像拼接
	Stitcher::Status status = stitcher->stitch(imgs, pano);

#else
	// 创建Stitcher类对象
	Stitcher stitcher = Stitcher::createDefault(try_use_gpu);
	// 图像拼接
	Stitcher::Status status = stitcher.stitch(imgs, pano);
#endif

	// 判断拼接状态
	if (status != Stitcher::OK)
	{
		cerr << "Can't stitch images, error code = " << static_cast<int>(status) << endl;
		return -1;
	}

	// 计算图像拼接耗时
	cout << "Cost time: " << static_cast<double>((getTickCount()-time_start) / getTickFrequency()) << " sec"<<endl;

	// 显示并保存全景图
	namedWindow("Panoramo", WINDOW_NORMAL);
	imshow("Panoramo", pano);
	imwrite("panoramo.jpg", pano);
	waitKey(0);

	return 0;
}