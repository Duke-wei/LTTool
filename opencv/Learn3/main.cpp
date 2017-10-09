/*************************************************************************
    > File Name: main.cpp
    > Author: Duke-wei
    > Mail: 13540639584@163.com 
    > Created Time: 2016年12月27日 星期二 22时48分57秒
 ************************************************************************/
#include <opencv2/opencv.hpp>
#include<iostream>
using namespace std;
IplImage *g_pSrcImage,*g_pCannyImg;
const char *pstrWindowsCannyTitle = "canny check";
void on_trackbar(int threshold){
	cvCanny(g_pSrcImage,g_pCannyImg,threshold,threshold*3,3);
	cvShowImage(pstrWindowsCannyTitle,g_pCannyImg);
}
int main(){
	const char* pstrImageName="1.jpg";
	const char* pstrWindowsSrcTitle="Source Image";
	const char *pstrWindowsToolBar="Threshold";
	g_pSrcImage = cvLoadImage(pstrImageName,CV_LOAD_IMAGE_GRAYSCALE);
	g_pCannyImg = cvCreateImage(cvGetSize(g_pSrcImage),IPL_DEPTH_8U,1);

	cvNamedWindow(pstrWindowsSrcTitle,CV_WINDOW_AUTOSIZE);
	cvNamedWindow(pstrWindowsCannyTitle,CV_WINDOW_AUTOSIZE);
	int nThresholdEdge = 1;
	cvCreateTrackbar(pstrWindowsToolBar,pstrWindowsCannyTitle,&nThresholdEdge,100,on_trackbar);

	cvShowImage(pstrWindowsSrcTitle,g_pSrcImage);
	on_trackbar(1);
	cvWaitKey();
	cvDestroyWindow(pstrWindowsSrcTitle);
	cvDestroyWindow(pstrWindowsCannyTitle);
	cvReleaseImage(&g_pSrcImage);
	cvReleaseImage(&g_pCannyImg);
	return 0;
}

