/*************************************************************************
    > File Name: main.cpp
    > Author: Duke-wei
    > Mail: 13540639584@163.com 
    > Created Time: 2016年12月27日 星期二 22时48分57秒
 ************************************************************************/
#include <opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

IplImage *g_pGrayImage = NULL;
const char *pstrWindowsBinaryTitle="binarytitle";
const char *pstrWindowsOutLineTitle="outlinetitle";

CvSeq *g_pcvSeq = NULL;

void on_trackbar(int pos){
	IplImage *pBinaryImage = cvCreateImage(cvGetSize(g_pGrayImage),IPL_DEPTH_8U,1);
	cvThreshold(g_pGrayImage,pBinaryImage,pos,255,CV_THRESH_BINARY);
	cvShowImage(pstrWindowsBinaryTitle,pBinaryImage);
	CvMemStorage* cvMemStorage = cvCreateMemStorage();
	IplImage *pOutlineImage = cvCreateImage(cvGetSize(g_pGrayImage),IPL_DEPTH_8U,3);
	int _levels = 5;
	cvZero(pOutlineImage);
	cvDrawContours(pOutlineImage,g_pcvSeq,CV_RGB(255,0,0),CV_RGB(0,255,0),_levels);
	cvShowImage(pstrWindowsOutLineTitle,pOutlineImage);
	cvReleaseMemStorage(&cvMemStorage);
	cvReleaseImage(&pBinaryImage);
	cvReleaseImage(&pOutlineImage);
}

int main(){
	const char *pstrWindowsSrcTitle = "SrcTitle";
	const char *pstrWindowsToolBarName = "BinaryImage";
	IplImage *pSrcImage = cvLoadImage("1.jpg",CV_LOAD_IMAGE_UNCHANGED);
	cvNamedWindow(pstrWindowsSrcTitle,CV_WINDOW_AUTOSIZE);
	cvShowImage(pstrWindowsSrcTitle,pSrcImage);

	g_pGrayImage = cvCreateImage(cvGetSize(pSrcImage),IPL_DEPTH_8U,1);
	cvCvtColor(pSrcImage,g_pGrayImage,CV_BGR2GRAY);
	cvNamedWindow(pstrWindowsBinaryTitle,CV_WINDOW_AUTOSIZE);
	cvNamedWindow(pstrWindowsBinaryTitle,CV_WINDOW_AUTOSIZE);

	int nThreshold = 0;
	cvCreateTrackbar(pstrWindowsToolBarName,pstrWindowsBinaryTitle,&nThreshold,254,on_trackbar);
	on_trackbar(1);
	cvWaitKey(0);
	cvDestroyWindow(pstrWindowsSrcTitle);
	cvDestroyWindow(pstrWindowsBinaryTitle);
	cvDestroyWindow(pstrWindowsOutLineTitle);
	cvReleaseImage(&pSrcImage);
	cvReleaseImage(&g_pGrayImage);
	return 0;
}


