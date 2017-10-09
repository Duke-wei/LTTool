/*************************************************************************
    > File Name: main.cpp
    > Author: Duke-wei
    > Mail: 13540639584@163.com 
    > Created Time: 2016年12月27日 星期二 22时48分57秒
 ************************************************************************/
#include <opencv2/opencv.hpp>
#include<iostream>
using namespace std;
IplImage *g_pSrcImage=NULL;
IplImage *g_pBinaryImage = NULL;
const char *pstrWindowsBinaryTitle= "binary check";
void on_trackbar(int pos){
	//cvThreshold(g_pSrcImage,g_pBinaryImage,pos,255,CV_THRESH_BINARY);
	cvThreshold(g_pSrcImage,g_pBinaryImage,pos,255,CV_THRESH_OTSU);
	cvShowImage(pstrWindowsBinaryTitle,g_pBinaryImage);
}
int main(){
	const char* pstrImageName="1.jpg";
	const char* pstrWindowsSrcTitle="Source Image";
	const char *pstrWindowsToolBar="Threshold";
	IplImage *pSrcImage = cvLoadImage(pstrImageName,CV_LOAD_IMAGE_UNCHANGED);
	g_pSrcImage = cvCreateImage(cvGetSize(pSrcImage),IPL_DEPTH_8U,1);
	cvCvtColor(pSrcImage,g_pSrcImage,CV_BGR2GRAY);
	g_pBinaryImage = cvCreateImage(cvGetSize(g_pSrcImage),IPL_DEPTH_8U,1);

	cvNamedWindow(pstrWindowsSrcTitle,CV_WINDOW_AUTOSIZE);
	cvShowImage(pstrWindowsSrcTitle,pSrcImage);

	cvNamedWindow(pstrWindowsBinaryTitle,CV_WINDOW_AUTOSIZE);
	int nThreshold= 0;
	cvCreateTrackbar(pstrWindowsToolBar,pstrWindowsBinaryTitle,&nThreshold,254,on_trackbar);

	on_trackbar(1);
	cvWaitKey(0);
	cvDestroyWindow(pstrWindowsSrcTitle);
	cvDestroyWindow(pstrWindowsBinaryTitle);
	cvReleaseImage(&pSrcImage);
	cvReleaseImage(&g_pSrcImage);
	cvReleaseImage(&g_pBinaryImage);
	return 0;
}

