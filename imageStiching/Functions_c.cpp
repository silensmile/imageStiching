#include "header.h"

extern RNG g_rng;

//���ӡ�����_����Ե������ϳɡ������߶�
vector<vector<vector<Point>>> cClusters(Mat srcImage)
{
	//��ȡ��Ե����
	vector<vector<Point>>contours;
	vector<Vec4i> hierarchy;
	vector<vector<Point>> contours_poly(contours.size());
	findContours(srcImage, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
	//����ν�����ȡ�ָ��
	contours_poly.resize(contours.size());
	for (unsigned int i = 0; i < contours.size(); i++)
		approxPolyDP(Mat(contours[i]), contours_poly[i], 5, false);
	//���ն���ν��Ʒָ���������������Ƭ��װ��cluster
	vector<vector<vector<Point>>> vec_cluster;
	vector<Point> vecp;
	vector<vector<Point>> vecl;
	for (int i = 0; i < contours.size(); i++)
	{
		vecl.clear();
		unsigned int  k = 0;
		unsigned int j = 1;
		for (j; j < contours_poly[i].size(); j++)
		{
			vecp.clear();
			for (k; k < contours[i].size(); k++)
			{
				if (contours[i][k] != contours_poly[i][j])
					vecp.push_back(contours[i][k]);
				else
				{
					vecp.push_back(contours[i][k]);
					break;
				}
			}
			vecl.push_back(vecp);
		}
		vec_cluster.push_back(vecl);
	}
	//��ͼ�۲�
	Mat drawing = Mat::zeros(srcImage.size(), CV_8UC3);
	for (unsigned int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
	}
	for (int i = 0; i < contours_poly.size(); i = i + 1)
	{
		for (int j = 0; j < contours_poly[i].size(); j++)
		{
			circle(drawing, contours_poly[i][j], 2, CV_RGB(0, 0, 255), 2);
		}
	}
	contours_poly.resize(contours.size());
	namedWindow("����", 0);
	imshow("����", drawing);
	return vec_cluster;
}

//����ƽ���Ҷ�
int cAvGscale(Mat srcImage, vector<Point> segment)
{
	int i = 0;
	int AveGscale = 0;
	for (i; i < segment.size(); i++)
	{
		AveGscale = AveGscale + srcImage.at<uchar>(segment[i]);
	}
	return AveGscale;
}

//��������
Point cBaryCenter(vector<Point>segment)
{
	Moments mom = moments(Mat(segment));
	Point cBcenter = Point(mom.m10 / mom.m00, mom.m01 / mom.m00);
	return cBcenter;
}