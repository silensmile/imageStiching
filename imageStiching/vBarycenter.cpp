#include "header.h"

Point lineBaryCenter(Point a, Point b);

//��������������
//lcluster_2p ��������ϴ�ŵ����������
//bCenter �����������ŵ�����
vector<vector<Point>> vBarycenter(vector<vector<vector<Point>>>lcluster_2p, vector<vector<Point>> bCenter)
{
	vector<Point> vec;
	for (int i = 0; i < lcluster_2p.size(); i++)
	{
		vec.clear();
		for (int j = 0; j < lcluster_2p[i].size(); j++)
		{
			Point bc = lineBaryCenter(lcluster_2p[i][j][0], lcluster_2p[i][j][1]);
			vec.push_back(bc);
		}
		bCenter.push_back(vec);
	}
	return bCenter;
}