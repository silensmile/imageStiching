#include "header.h"

extern Mat g_srcImage;
extern vector<vector<Point>> bCenter;

//计算直线中点坐标
Point lineBaryCenter(Point a, Point b);

//点旋转函数	rotatePoint
//src 待旋转点坐标
//angle 待旋转角度，旋转轴为原点
Point rotatePoint(const Point src, double angle)
{
	Point dst;
	int x = (src.x)*cos(angle) - (src.y)*sin(angle);
	int y = (src.x)*sin(angle) + (src.y)*cos(angle);
	dst.x = x;
	dst.y = y;
	return dst;
}

//矢量旋转角计算
//a_2p 由两点组成的向量a
//b_2p 由两点组成的向量b
double vecRotateTheta(vector<Point> a_2p, vector<Point> b_2p)
{
	Point lineBaryCenter(Point a, Point b);
	//向量r1
	int r1_x = a_2p[1].x - a_2p[0].x;
	int r1_y = a_2p[1].y - a_2p[0].y;
	//向量r2
	int r2_x = b_2p[0].x - b_2p[1].x;
	int r2_y = b_2p[0].y - b_2p[1].y;
	int dot_r1r2 = r1_x*r2_x + r1_y*r2_y; //点乘
	double modr1 = sqrt(r1_x*r1_x + r1_y*r1_y);//取摸
	double modr2 = sqrt(r2_x*r2_x + r2_y*r2_y);
	double theta = acos(dot_r1r2 / (modr1*modr2));
	//叉乘
	double cross_r1r2 = r1_x*r2_y - r1_y*r2_x;
	if (cross_r1r2 >= 0) theta = -theta;
	return theta;
}
//旋转轮廓重心阵i
//Segment2p_1 线段1，两点向量表示
//Segment2p_2 线段2，两点向量表示
//bc_i 待旋转重心阵
//基本功能：根据线段1和线段2，将轮廓阵旋转至对应位置，得到旋转后轮廓重心阵坐标。注意，bCenter包含多个轮廓的重心阵，
//本函数传入参数仅为单一轮廓的重心阵。
vector<Point> rotateVecBcenter(vector<Point> Segment2p_1, vector<Point> Segment2p_2, vector<Point> bc_i)
{
	Mat drawing1 = Mat::zeros(g_srcImage.size(), CV_8UC3);
	vector<Point> bc_d;
	int endNum_a = Segment2p_1.size() - 1;
	int endNum_b = Segment2p_2.size() - 1;
	Point mid_a = lineBaryCenter(Segment2p_1[0], Segment2p_1[endNum_a]);
	Point mid_b = lineBaryCenter(Segment2p_2[0], Segment2p_2[endNum_b]);
	double dtheta = vecRotateTheta(Segment2p_1, Segment2p_2);
	for (unsigned int j = 0; j < bc_i.size(); j++)
	{
		Point temp = bc_i[j] - mid_b;
		Point bc = rotatePoint(temp, dtheta);
		bc = bc + mid_a;
		bc_d.push_back(bc);
	}
	//实验观察用，正式版可注释掉相应部分
	for (int i = 0; i < bc_d.size(); i++)
		circle(drawing1, bc_d[i], 2, CV_RGB(255, 0, 0), 2);
	for (unsigned int j = 0; j < bCenter.size(); j++)
		for (unsigned int i = 0; i < bCenter[j].size(); i++)
			circle(drawing1, bCenter[j][i], 2, CV_RGB(0, 255, 0), 2);
	namedWindow("zhongxin", 0);
	imshow("zhongxin", drawing1);
	return bc_d;
}