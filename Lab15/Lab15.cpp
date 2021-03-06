#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

Mat src, src_gray;

void cornerHarris_demo(int, void*)
{
	Mat dst, dst_norm, dst_norm_scaled;
	dst = Mat::zeros(src.size(), CV_32FC1);

	int blockSize = 2;
	int apertureSize = 3;
	double k = 0.04;

	cornerHarris(src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT);

	normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(dst_norm, dst_norm_scaled);

	for (int j = 0; j < dst_norm.rows; j++)
	{
		for (int i = 0; i < dst_norm.cols; i++)
		{
			if ((int)dst_norm.at<float>(j, i) > 200)
			{
				circle(dst_norm_scaled, Point(i, j), 5, Scalar(0), 2, 8, 0);
			}
		}
	}

	namedWindow("Corners", CV_WINDOW_AUTOSIZE);
	imshow("Corners", dst_norm_scaled);
}

int main(int argc, char** argv)
{
	src = imread(argv[1], 1);
	cvtColor(src, src_gray, CV_BGR2GRAY);

	cornerHarris_demo(0, 0);

	waitKey(0);
	return(0);
}

