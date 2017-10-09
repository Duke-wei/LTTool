#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat girl = imread("1.jpg");
	namedWindow("tu1");
	imshow("tu1",girl);

	Mat image = imread("1.jpg",199);
	Mat logo= imread("2.png");
	
	Mat imageROI;
	imageROI = image(Rect(200,150,logo.cols,logo.rows));
	addWeighted(imageROI,0.5,logo,0.3,0.,imageROI);
	namedWindow("imageROI");
	imshow("imageROI",image);
	imwrite("imageROI.jpg",image);
	waitKey(0);
	return 0;
} 

