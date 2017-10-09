#include <iostream>
#include <vector>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

Mat img;
int threshval = 160;

static void on_trackbar(int,void*){
	Mat bw = threshval<128?(img<threshval):(img>threshval);
	vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(bw,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE);
    Mat dst = Mat::zeros(img.size(),CV_8UC3);
    if(!contours.empty() && !hierarchy.empty()){
        int idx = 0;
        for(;idx>=0;idx=hierarchy[idx][0]){
            Scalar color((rand()&255),(rand()&255),(rand()&255));
            drawContours(dst,contours,idx,color,CV_FILLED,8,hierarchy);
        }
    }
    imshow("Connected Components",dst);
}

int main(){
    img = imread("1.jpg",0);
    if(!img.data){
        printf("Oh,no,the img can not be read\n");
        return 1;
    }
    namedWindow("image",1);
    imshow("image",img);
    namedWindow("Connected Components",1);
    createTrackbar("Threshold","Connected Components",&threshval,255,on_trackbar);
    on_trackbar(threshval,0);
    waitKey(0);
    return 0;
}
