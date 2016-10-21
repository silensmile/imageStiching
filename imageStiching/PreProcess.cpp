#include "header.h"

extern Mat g_srcImage;
extern int g_nThresh;
extern int g_nThresh_Max;

//Ô¤´¦Àíº¯Êý
Mat PreProcess(Mat srcImage)
{
	Mat grayImage;
	Mat binaryImage;
	Mat dstImage;
	cvtColor(g_srcImage, grayImage, COLOR_BGR2GRAY);
	threshold(grayImage, binaryImage, 235, 255, CV_THRESH_BINARY);
	medianBlur(binaryImage, binaryImage, 9);
	Canny(binaryImage, dstImage, g_nThresh, g_nThresh_Max);
	return dstImage;
}