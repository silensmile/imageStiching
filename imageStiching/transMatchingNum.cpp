#include "header.h"

int lineLength(Point a, Point b);

//��תƥ��ֱ�߱�ź���	transMatchingNum
//c1Num ����1�ı��
//c2Num ����2�ı��
//c1_segmentNum ����1���߶α��
//c2_segmentNum ����2���߶α��
//Threshold ��ת������2���ĺ�����1����֮���ŷ�Ͼ���ӦС�ڵ���ֵ
//�������ܣ����ݳ���ɸѡ�����ɸѡ������ǰֱ�߶������ת������1.���ľ���С��һ����ֵ 2.�н�С��һ����ֵ ���߶���ϣ�������ת��ֱ�߶�ƥ�����ϱ��
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