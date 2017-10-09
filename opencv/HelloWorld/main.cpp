/*************************************************************************
    > File Name: main.cpp
    > Author: Duke-wei
    > Mail: 13540639584@163.com 
    > Created Time: 2016年12月27日 星期二 22时48分57秒
 ************************************************************************/
#include <opencv2/opencv.hpp>
#include<iostream>
using namespace std;
//using namespace opencv2;

int main(){
	const char* pstrImageName="1.jpg";
	const char* pstrWindowsTitle="first opencv program";
	IplImage *pImage = cvLoadImage(pstrImageName,CV_LOAD_IMAGE_UNCHANGED);
	cvNamedWindow(pstrWindowsTitle,CV_WINDOW_AUTOSIZE);
	cvShowImage(pstrWindowsTitle,pImage);
	cvWaitKey();
	cvDestroyWindow(pstrWindowsTitle);
	cvReleaseImage(&pImage);
	return 0;
}

