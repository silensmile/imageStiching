#include "header.h"
#include "function.h"


int main()
{
	Mat original;
	g_srcImage = imread("../img/3.jpg", 1);
	const Mat src = g_srcImage;
	g_srcImage.copyTo(original);		//将原始图像保留到Original
	if (!g_srcImage.data)
	{
		printf("error,no image is found\n");
		return false;
	}
	g_srcImage = PreProcess(g_srcImage);
	Mat temp_g_srcImage;
	g_srcImage.copyTo(temp_g_srcImage);
	vector<vector<vector<Point>>>g_cluster = cClusters(g_srcImage);
	vector<vector<Point>>g_lcluster = lClusters(g_srcImage);
	lcluster_2p = lcluster2p(g_lcluster, lcluster_2p);
	vector<vector<Vec2i>>g_charalcluster = lineCharacter(g_lcluster, original);
	pairNum = vpairNum(g_charalcluster, 10, 10);
	bCenter = vBarycenter(lcluster_2p, bCenter);
	ms = matchingScore(g_charalcluster, pairNum, bCenter, lcluster_2p, 20, 5);
	//int maxnum = 0;
	//for (unsigned int i = 0; i < ms.size(); i++)
	//	if (ms[i][2] >= ms[maxnum][2])
	//		maxnum = i;
	//int maxw = ms[maxnum][2];
	//std::cout << maxnum << " " << maxw << std::endl;
	//rotateVecBcenter(lcluster_2p[0][ms[maxnum][0]], lcluster_2p[1][ms[maxnum][1]], bCenter[1]);
	//Mat output = selectAndStiching(src, temp_g_srcImage, lcluster_2p[ pairNum[maxnum][0] ][ms[maxnum][0]], lcluster_2p[pairNum[maxnum][2] ][ms[maxnum][1]]);
	Mat output = selectAndStiching(src, temp_g_srcImage);
	namedWindow("output", 0);
	imshow("output", output);
	imwrite("../img/output.png", output);
	waitKey(0);
	return 0;
}