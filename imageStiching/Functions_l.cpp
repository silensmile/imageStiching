#include "header.h"

extern RNG g_rng;

//“从”函数_将边缘轮廓打断成【直】线段
vector<vector<Point>> lClusters(Mat srcImage)
{
	//提取边缘轮廓
	vector<vector<Point>>contours;
	vector<Vec4i> hierarchy;
	vector<vector<Point>> contours_poly(contours.size());
	findContours(srcImage, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
	//多边形近似提取分割点
	contours_poly.resize(contours.size());
	for (unsigned int i = 0; i < contours.size(); i++)
		approxPolyDP(Mat(contours[i]), contours_poly[i], 5, false);
	//作图观察
	Mat drawing = Mat::zeros(srcImage.size(), CV_8UC3);
	for (unsigned int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
	}
	contours_poly.resize(contours.size());
	for (int i = 0; i < contours_poly.size(); i = i + 1)
	{
		for (int j = 0; j < contours_poly[i].size(); j++)
		{
			circle(drawing, contours_poly[i][j], 2, CV_RGB(0, 0, 255), 2);
		}
	}
	namedWindow("轮廓", WINDOW_AUTOSIZE);
	imshow("轮廓", drawing);
	return contours_poly;
}

//进一步封装多边形近似，返回以两点组成的线段为单元进行储存的向量
vector<vector<vector<Point>>> lcluster2p(vector<vector<Point>>contours_poly, vector<vector<vector<Point>>> lcluster)
{
	vector<vector<Point>> vec;
	vector<Point> vec0;
	for (unsigned int i = 0; i < contours_poly.size(); i++)
	{
		vec.clear();
		for (unsigned int j = 0; j < contours_poly[i].size() - 1; j++)
		{
			vec0.clear();
			vec0.push_back(contours_poly[i][j]);
			vec0.push_back(contours_poly[i][j + 1]);
			vec.push_back(vec0);
		}
		lcluster.push_back(vec);
	}
	return lcluster;
}