#include "header.h"

//ƥ��������㺯��	matchingScore
//************************************************************************************
//linecharacter ֱ�߽�����������
//pairNum ����ƥ������
//lcluster_2p ֱ�߶Ρ��ԡ���������
//bCenter ����������������
//threshold_bc ���ľ�����ֵ
//alpha w����ʱȨ��ϵ�����°溯���ò�����ʧЧ
//�������ܣ����ݳ���ɸѡ�ı����
//************************************************************************************
vector<Vec3d> matchingScore(vector<vector<Vec2i>> lineCharacter, vector<Vec4i> pairNum, vector<vector<Point>> bCenter, vector<vector<vector<Point>>>lcluster_2p, int threshold_bc, int alpha)
{
	double wCalculate(vector<Vec2i> vec1, vector<Vec2i> vec2, vector<Vec2i>PairNum, int a);
	vector<Vec2i> transMatchingNum(vector<vector<Point>> bCenter, vector<vector<vector<Point>>>lcluster_2p, int c1Num, int c1_segmentNum, int c2Num, int c2_segmentNum, double Threshold);
	vector<Vec3d> matchingScore;
	matchingScore.clear();
	for (unsigned int i = 0; i < pairNum.size(); i++)
	{
		//���㰴��ǰ�����ת�£��ж����߶�ƥ������
		vector<Vec2i> Num = transMatchingNum(bCenter, lcluster_2p, pairNum[i][0], pairNum[i][1], pairNum[i][2], pairNum[i][3], threshold_bc);
		//����ƥ���ϵ��߶α�ţ����������ת��ϵ�wֵ�����˳�����w������
		double w = 0;
		if (Num.size() != 0)
			w = wCalculate(lineCharacter[pairNum[i][0]], lineCharacter[pairNum[i][2]], Num, alpha);
		matchingScore.push_back(Vec3d(pairNum[i][1], pairNum[i][3], w));
	}
	return matchingScore;
}