#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "videoprocessor.h"

void draw(cv::Mat& img, cv::Mat& out) {

	img.copyTo(out);
	cv::circle(out, cv::Point(100,100),5,cv::Scalar(255,0,0),2);
}

void canny(cv::Mat& img, cv::Mat& out) {

	// Convert to gray
	cv::cvtColor(img,out,CV_BGR2GRAY);
	// Compute Canny edges
	cv::Canny(out,out,100,200);
	// Invert the image
	cv::threshold(out,out,128,255,cv::THRESH_BINARY_INV);
}

int main()
{
	// Open the video file
    cv::VideoCapture capture(0);
	// check if video successfully opened
	if (!capture.isOpened())
		return 1;

	cv::Mat frame; // current video frame
	cv::Mat outImage;
	cv::namedWindow("Extracted Frame");

	while (true) 
	{
		if (!capture.read(frame))
			break;

		canny(frame, outImage);

		cv::imshow("Extracted Frame", outImage);

		cv::waitKey(50);

	}

	// Close the video file
	capture.release();

	cv::waitKey();

	return 0;
}