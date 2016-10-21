#include "header.h"

//计算matchin的w值
//vec1 轮廓i的小线段特征矢量
//vec2 轮廓j的小线段特征矢量，其中ij为旋转组合标号对
//PairNum 根据ij旋转组合标号得到的【旋转匹配直线标号】组合
double wCalculate(vector<Vec2i> vec1, vector<Vec2i> vec2, vector<Vec2i>PairNum, int a)
{
	double w1 = 0, w2 = 0, w3 = 0;
	for (unsigned int k = 0; k < PairNum.size(); k++)
	{
		for (unsigned int i = 0; i < vec1.size(); i++)
		{
			for (unsigned int j = 0; j < vec2.size(); j++)
			{
				if ((i == PairNum[k][0]) && (j == PairNum[k][1]))
				{
					int da = abs(vec1[i][1] - vec2[j][1]);
					if (da == 0) da = 1;
					w1 = w1 + 0.5*(vec1[i][0] + vec2[j][0]);
					//w2 = w2 + 0.5*(vec1[i][0] + vec2[j][0])*da;
					w3++;
				}
			}
		}
	}
	//新版w值计算为匹配上线段组的平均长度和匹配数量的组合
	double w = sqrt(w1)*w3;
	return w;
}