// Summary: Use OpenCV library to complete simple image stitching
// Author:  Amusi
// Date:    2018-03-01
// Reference:
//		[1]Stitcher class: https://docs.opencv.org/master/d2/d8d/classcv_1_1Stitcher.html
//		[2]stitching.cpp: https://docs.opencv.org/master/d8/d19/tutorial_stitcher.html

// Note: not use GPU


// C++ head
#include<iostream>
// OpenCV head
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
	// load images
	vector<Mat> imgs;
	Mat pano;
	Mat img_temp;

	img_temp = imread("0001.jpg");
	imgs.push_back(img_temp);
	img_temp = imread("0002.jpg");
	imgs.push_back(img_temp);
	img_temp = imread("0003.jpg");
	imgs.push_back(img_temp);

	// set Stitcher parameters
	bool try_use_gpu = false;					// true: use GPU; false: use CPU
	bool divide_images = true;					// true: false:
	Stitcher::Mode mode = Stitcher::PANORAMA;	// Mode: PANORAMA=0 create panoramo; SCANS=1 create scan

	double time_start = static_cast<double>(getTickCount());

#if 1
	// create Stitcher instance with smart pointer
	Ptr<Stitcher> stitcher = Stitcher::create(mode, try_use_gpu);
	// stitch
	Stitcher::Status status = stitcher->stitch(imgs, pano);

#else
	// create Stitcher instance
	Stitcher stitcher = Stitcher::createDefault(try_use_gpu);
	// stitch
	Stitcher::Status status = stitcher.stitch(imgs, pano);
#endif

	// judge the stitching status
	if (status != Stitcher::OK)
	{
		cerr << "Can't stitch images, error code = " << static_cast<int>(status) << endl;
		return -1;
	}

	cout << "Cost time: " << static_cast<double>((getTickCount()-time_start) / getTickFrequency()) << "s"<<endl;

	// show and save panoramo
	namedWindow("Panoramo", WINDOW_NORMAL);
	imshow("Panoramo", pano);
	imwrite("panoramo.jpg", pano);
	waitKey(0);

	return 0;
}