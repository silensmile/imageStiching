#include "header.h"

//匹配分数计算函数	matchingScore
//************************************************************************************
//linecharacter 直线近似特征向量
//pairNum 初步匹配标号阵
//lcluster_2p 直线段“丛”近似轮廓
//bCenter 轮廓重心特征向量
//threshold_bc 重心距离阈值
//alpha w计算时权重系数，新版函数该参数已失效
//基本功能：根据初步筛选的标号阵
//************************************************************************************
vector<Vec3d> matchingScore(vector<vector<Vec2i>> lineCharacter, vector<Vec4i> pairNum, vector<vector<Point>> bCenter, vector<vector<vector<Point>>>lcluster_2p, int threshold_bc, int alpha)
{
	double wCalculate(vector<Vec2i> vec1, vector<Vec2i> vec2, vector<Vec2i>PairNum, int a);
	vector<Vec2i> transMatchingNum(vector<vector<Point>> bCenter, vector<vector<vector<Point>>>lcluster_2p, int c1Num, int c1_segmentNum, int c2Num, int c2_segmentNum, double Threshold);
	vector<Vec3d> matchingScore;
	matchingScore.clear();
	for (unsigned int i = 0; i < pairNum.size(); i++)
	{
		//计算按当前组合旋转下，有多少线段匹配上了
		vector<Vec2i> Num = transMatchingNum(bCenter, lcluster_2p, pairNum[i][0], pairNum[i][1], pairNum[i][2], pairNum[i][3], threshold_bc);
		//根据匹配上的线段标号，计算该种旋转组合的w值，结果顺序存在w向量里
		double w = 0;
		if (Num.size() != 0)
			w = wCalculate(lineCharacter[pairNum[i][0]], lineCharacter[pairNum[i][2]], Num, alpha);
		matchingScore.push_back(Vec3d(pairNum[i][1], pairNum[i][3], w));
	}
	return matchingScore;
}