#include "header.h"


extern vector<Vec4i> pairNum;
extern vector<Vec3d> ms;
extern vector<vector<vector<Point>>>lcluster_2p;

//重心
Point cBaryCenter(vector<Point>segment);
//计算直线中点坐标
Point lineBaryCenter(Point a, Point b);
//矢量旋转角计算
//a_2p 由两点组成的向量a
//b_2p 由两点组成的向量b
double vecRotateTheta(vector<Point> a_2p, vector<Point> b_2p);

Mat selectAndStiching(const Mat src, Mat PreProcessedImage)
{
	vector<vector<Point>>contours;
	vector<Vec4i> hierarchy;
	Rect ccomp;
	findContours(PreProcessedImage, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

	Mat* pieceMask = new Mat[contours.size()];
	Mat* piece = new Mat[contours.size()];
	Point seedPoint;
	//提取分离的单独碎片准备旋转合成
	for (int i = 0; i < contours.size(); i++)
	{
		pieceMask[i].create(src.size(), src.type());
		drawContours(pieceMask[i], contours, i, Scalar(255, 255, 255), 1, 8, vector<Vec4i>(), 0, Point());
		seedPoint = cBaryCenter(contours[i]);
		floodFill(pieceMask[i], seedPoint, Scalar(255, 255, 255), &ccomp, Scalar(0, 0, 0), Scalar(50, 50, 50));
		floodFill(pieceMask[i], Point(0, 0), Scalar(0, 0, 0), &ccomp, Scalar(50, 50, 50), Scalar(0, 0, 0));
		src.copyTo(piece[i], pieceMask[i]);
	}

	int* maxnum = new int[(contours.size()*(contours.size()-1))/2];
	int index = 0;
	for (int k = 0;k<contours.size() - 1;k++)
	{
		for (int j = k+1 ; j < contours.size(); j++,index++)
		{
			maxnum[index] = 0;
			for (unsigned int i = 0; i < ms.size(); i++)
			{
				if (ms[i][2] > 30 && ms[i][2] >= ms[maxnum[index]][2] && pairNum[i][0] == k && pairNum[i][2] == j)
					maxnum[index] = i;
			}
		}
	}
	int maxnummax = 0;
	for (unsigned int i = 0; i < (contours.size()*(contours.size() - 1))/2; i++)
		if (ms[maxnum[i]][2] >= ms[maxnum[maxnummax]][2])
			maxnummax = i;

	Mat* outputAll = new Mat[(contours.size()*(contours.size() - 1)) / 2];
	for (int i = 0; i < (contours.size()*(contours.size() - 1)) / 2; i++)
	{

		vector<Point> Segment2p_1 = lcluster_2p[pairNum[maxnum[i]][0]][ms[maxnum[i]][0]];
		vector<Point> Segment2p_2 = lcluster_2p[pairNum[maxnum[i]][2]][ms[maxnum[i]][1]];
		/*------------------平移旋转部分------------------*/
		Mat temppiece1, temppiece2;
		piece[pairNum[maxnum[i]][2]].copyTo(temppiece1);
		piece[pairNum[maxnum[i]][0]].copyTo(temppiece2);
		IplImage* piece1 = &IplImage(temppiece1);
		Point centerP0 = lineBaryCenter(Segment2p_1[0], Segment2p_1[1]),
			centerP1 = lineBaryCenter(Segment2p_2[0], Segment2p_2[1]);
		//计算二维旋转的仿射变换矩阵  P1->P0
		float m1[6] = { 1,0,(float)(centerP0.x - centerP1.x),0,1,(float)(centerP0.y - centerP1.y) };
		CvMat M1 = cvMat(2, 3, CV_32F, m1);
		//平移图像，并用黑色填充其余值  
		cvWarpAffine(piece1, piece1, &M1, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS, cvScalarAll(0));

		//旋转中心 
		CvPoint2D32f center;
		center.x = float(centerP0.x);
		center.y = float(centerP0.y);
		//旋转角度
		double dtheta = vecRotateTheta(Segment2p_1, Segment2p_2);
		float m2[6];
		CvMat M2 = cvMat(2, 3, CV_32F, m2);
		cv2DRotationMatrix(center, dtheta, 1, &M2);
		//旋转图像，并用黑色填充其余值  
		cvWarpAffine(piece1, piece1, &M2, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS, cvScalarAll(0));
		/*-------------------------------------------*/

		outputAll[i].create(src.size(), src.type());
		addWeighted(temppiece2, 1, temppiece1, 1, 0, outputAll[i]);
	}
	Mat output = outputAll[maxnummax];
	return output;
}