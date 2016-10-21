#include "header.h"

int lineLength(Point a, Point b);

//旋转匹配直线标号函数	transMatchingNum
//c1Num 轮廓1的标号
//c2Num 轮廓2的标号
//c1_segmentNum 轮廓1的线段标号
//c2_segmentNum 轮廓2的线段标号
//Threshold 旋转后轮廓2重心和轮廓1重心之间的欧氏距离应小于的阈值
//基本功能：根据初步筛选结果，筛选出按当前直线段组合旋转后，满足1.重心距离小于一定阈值 2.夹角小于一定阈值 的线段组合，返回旋转后直线段匹配的组合标号
vector<Vec2i> transMatchingNum(vector<vector<Point>> bCenter, vector<vector<vector<Point>>>lcluster_2p, int c1Num, int c1_segmentNum, int c2Num, int c2_segmentNum, double Threshold)
{
	vector<Point> rotateVecBcenter(vector<Point> Segment2p_1, vector<Point> Segment2p_2, vector<Point> bc_i);
	vector<Vec2i> Num;
	vector<Point> bCenter_c2Num = rotateVecBcenter(lcluster_2p[c1Num][c1_segmentNum], lcluster_2p[c2Num][c2_segmentNum], bCenter[c2Num]);
	vector<Point> rotateVecBcenter(vector<Point> Segment2p_1, vector<Point> Segment2p_2, vector<Point> bc_i);
	double lineDirection(Point a, Point b);
	double Thresholdtheta = CV_PI / 36;
	for (unsigned int i = 0; i < bCenter[c1Num].size(); i++)
	{
		for (unsigned int j = 0; j < bCenter_c2Num.size(); j++)
		{
			int bc_dist = lineLength(bCenter[c1Num][i], bCenter_c2Num[j]);
			if (lineLength(bCenter[c1Num][i], bCenter_c2Num[j]) < Threshold)
			{
				vector<Point> temp;
				temp = rotateVecBcenter(lcluster_2p[c1Num][c1_segmentNum], lcluster_2p[c2Num][c2_segmentNum], lcluster_2p[c2Num][j]);
				double theta1 = lineDirection(lcluster_2p[c1Num][i][0], lcluster_2p[c1Num][i][1]);
				double theta2 = lineDirection(temp[0], temp[1]);
				double diff_theta = abs(theta1 - theta2);
				if (diff_theta<Thresholdtheta)
					Num.push_back(Vec2i(i, j));
			}
		}
	}
	return Num;
}