#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
bool ROI_AddImage(){
    Mat srcImagel = imread("1.jpg");
	Mat logoImage = imread("2.jpg");
	if(!srcImagel.data){
		printf("cannot read the src image!!!");
		return false;
	}
	if(!logoImage.data){
		printf("cannot read the logo image!!!");
		return false;
	}
	Mat imageROI = srcImagel(Rect(100,150,logoImage.cols,logoImage.rows));
	Mat mask = imread("2.jpg",0);
    logoImage.copyTo(imageROI,mask);
	namedWindow("ROI table");
	imshow("ROI table",srcImagel);
	waitKey(0);
	return true;

}

bool LinearBlending(){
	double alphaValue = 0.5;
	double betaValue;
	Mat srcImage2,srcImage3,dstImage;
	srcImage2 = imread("1.jpg");
	srcImage3 = imread("2.jpg");
	if(!srcImage2.data){
		printf("cannot read the logo image!!!");
		return false;
	}
	if(!srcImage3.data){
		printf("cannot read the logo image!!!");
		return false;
	}
    betaValue = 0.3;//(1.0 - alphaValue);
	addWeighted(srcImage2,alphaValue,srcImage3,betaValue,0.0,dstImage);
	namedWindow("LinearBlending",1);
	imshow("LinearBlending",srcImage2);
	namedWindow("LinearBlending2",1);
	imshow("LinearBlending",dstImage);
	waitKey(0);
	return true;
}

bool ROI_LinearBlending(){
	Mat srcImage4 = imread("1.jpg",1);
	Mat logoImage = imread("22.jpg");
	if(!srcImage4.data){
		return false;
	}
	if(!logoImage.data){
		return false;
	}
	Mat  imageROI;
	imageROI = srcImage4(Rect(5,10,logoImage.cols,logoImage.rows));
	addWeighted(imageROI,0.5,logoImage,0.3,0.0,imageROI);
	namedWindow("ROI_LinearBlending");
	imshow("ROI_LinearBlending",srcImage4);
	waitKey(0);
	return true;
}
int main()
{
//
//	Mat girl = imread("1.jpg");
//	namedWindow("tu1");
//	imshow("tu1",girl);

//	Mat image = imread("1.jpg",199);
//	Mat logo= imread("2.png");
//
//	Mat imageROI;
//	imageROI = image(Rect(200,150,logo.cols,logo.rows));
//	addWeighted(imageROI,0.5,logo,0.3,0.,imageROI);
//	namedWindow("imageROI");
//	imshow("imageROI",image);
//	imwrite("imageROI.jpg",image);
//	waitKey(0);
//	return 0;
//    ROI_AddImage();
//	LinearBlending();
    ROI_LinearBlending();
	return 0;
}

