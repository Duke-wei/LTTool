/*************************************************************************
    > File Name: main.cpp
    > Author: Duke-wei
    > Mail: 13540639584@163.com 
    > Created Time: 2016年12月27日 星期二 22时48分57秒
 ************************************************************************/
#include <opencv2/opencv.hpp>
#include<iostream>
using namespace std;

int main(){
	const char* pstrImageName="1.jpg";
	const char* pstrSaveImageName="1_bu.jpg";
	const char* pstrWindowsSrcTitle="before resize";
	const char* pstrWindowsDstTitle="after resize";
	double fScale = 0.314;
	CvSize czSize;
	IplImage *pSrcImage = cvLoadImage(pstrImageName,CV_LOAD_IMAGE_UNCHANGED);
	IplImage *pDstImage = NULL;
	czSize.width = pSrcImage->width * fScale;
	czSize.height = pSrcImage->height * fScale;

	pDstImage = cvCreateImage(czSize,pSrcImage->depth,pSrcImage->nChannels);
	cvResize(pSrcImage,pDstImage,CV_INTER_AREA);

	cvNamedWindow(pstrWindowsSrcTitle,CV_WINDOW_AUTOSIZE);
	cvNamedWindow(pstrWindowsDstTitle,CV_WINDOW_AUTOSIZE);
	cvShowImage(pstrWindowsSrcTitle,pSrcImage);
	cvShowImage(pstrWindowsDstTitle,pDstImage);
	cvWaitKey();
	cvSaveImage(pstrSaveImageName,pDstImage);
	cvDestroyWindow(pstrWindowsSrcTitle);
	cvDestroyWindow(pstrWindowsDstTitle);
	cvReleaseImage(&pSrcImage);
	cvReleaseImage(&pDstImage);
	return 0;
}

