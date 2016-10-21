#include "header.h"

//旋转组合标号阵（初步筛选标号阵）
//标号阵―匹配轮廓1中segment_i和轮廓2中segment_j的标号，组合成初步筛选的标号阵
vector<Vec4i> vpairNum(vector<vector<Vec2i>> lineCharacter, int dlThreshold, int daThreshold)
{
	vector<Vec4i> pairNum;
	for (int i = 0; i < lineCharacter.size() - 1; i++)
	{
		for (int m = i + 1; m < lineCharacter.size(); m++)
		{
			for (int j = 0; j < lineCharacter[i].size(); j++)
			{
				for (int n = 0; n < lineCharacter[m].size(); n++)
				{
					int diff_a = abs(lineCharacter[m][n][1] - lineCharacter[i][j][1]);
					int diff_l = abs(lineCharacter[m][n][0] - lineCharacter[i][j][0]);
					if ((diff_a <= daThreshold) && (diff_l <= dlThreshold))
						pairNum.push_back(Vec4i(i, j, m, n));
				}
			}
		}
	}
	return pairNum;
}