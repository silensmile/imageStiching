#include "header.h"

using namespace std;
using namespace cv;

Mat g_srcImage;
Mat g_grayImage;
Mat g_binaryImage;
Mat g_dstImage1;
Mat g_dstImage2;
Mat tempImage;
int g_nThresh = 230;
int g_nThresh_Max = 245;
RNG g_rng(12345);
vector<vector<Point>> bCenter;
vector<Vec4i> pairNum;
vector<Vec3d> ms;
vector<vector<vector<Point>>>lcluster_2p;

int max(int *a);

//Ԥ������
Mat PreProcess(Mat srcImage);

//���ӡ�����_����Ե������ϳɡ������߶�
vector<vector<vector<Point>>> cClusters(Mat srcImage);

//���ӡ�����_����Ե������ϳɡ�ֱ���߶�
vector<vector<Point>> lClusters(Mat srcImage);

//�߶γ��Ⱥ���_ŷ����þ���
int lineLength(Point a, Point b);

//ֱ��ƽ���ҶȺ���
int lineAveGscale(Mat srcImage, Point a, Point b);

//����ֱ���е�����
Point lineBaryCenter(Point a, Point b);

//С�߶�����ʸ������
vector<vector<Vec2i>> lineCharacter(vector<vector<Point>> Clusters, Mat srcImage);

//����matchin��wֵ
//vec1 ����i��С�߶�����ʸ��
//vec2 ����j��С�߶�����ʸ��������ijΪ��ת��ϱ�Ŷ�
//PairNum ����ij��ת��ϱ�ŵõ��ġ���תƥ��ֱ�߱�š����
double wCalculate(vector<Vec2i> vec1, vector<Vec2i> vec2, vector<Vec2i> PairNum, int a);

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
vector<Vec3d> matchingScore(vector<vector<Vec2i>> lineCharacter, vector<Vec4i> pairNum, vector<vector<Point>> bCenter, vector<vector<vector<Point>>>lcluster_2p, int threshold_bc, int alpha);

//��������
Point cBaryCenter(vector<Point>segment);

//��ת��ϱ���󣨳���ɸѡ�����
//�����Dƥ������1��segment_i������2��segment_j�ı�ţ���ϳɳ���ɸѡ�ı����
vector<Vec4i> vpairNum(vector<vector<Vec2i>> lineCharacter, int dlThreshold, int daThreshold);

//��������������
//lcluster_2p ��������ϴ�ŵ����������
//bCenter �����������ŵ�����
vector<vector<Point>> vBarycenter(vector<vector<vector<Point>>> lcluster_2p, vector<vector<Point>> bCenter);

//��ת����������i
//Segment2p_1 �߶�1������������ʾ
//Segment2p_2 �߶�2������������ʾ
//bc_i ����ת������
//�������ܣ������߶�1���߶�2������������ת����Ӧλ�ã��õ���ת���������������ꡣע�⣬bCenter�������������������
//���������������Ϊ��һ������������
vector<Point> rotateVecBcenter(vector<Point> Segment2p_1, vector<Point> Segment2p_2, vector<Point> bc_i);

//��һ����װ����ν��ƣ�������������ɵ��߶�Ϊ��Ԫ���д��������
vector<vector<vector<Point>>> lcluster2p(vector<vector<Point>>contours_poly, vector<vector<vector<Point>>> lcluster);

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
vector<Vec3d> matchingScore(vector<vector<Vec2i>> lineCharacter, vector<Vec4i> pairNum, vector<vector<Point>> bCenter, vector<vector<vector<Point>>> lcluster_2p, int threshold_bc, int alpha);

//��תƥ��ֱ�߱�ź���	transMatchingNum
//c1Num ����1�ı��
//c2Num ����2�ı��
//c1_segmentNum ����1���߶α��
//c2_segmentNum ����2���߶α��
//Threshold ��ת������2���ĺ�����1����֮���ŷ�Ͼ���ӦС�ڵ���ֵ
//�������ܣ����ݳ���ɸѡ�����ɸѡ������ǰֱ�߶������ת������1.���ľ���С��һ����ֵ 2.�н�С��һ����ֵ ���߶���ϣ�������ת��ֱ�߶�ƥ�����ϱ��
vector<Vec2i> transMatchingNum(vector<vector<Point>> bCenter, vector<vector<vector<Point>>> lcluster_2p, int c1Num, int c1_segmentNum, int c2Num, int c2_segmentNum, double Threshold);

//����ת����	rotatePoint
//src ����ת������
//angle ����ת�Ƕȣ���ת��Ϊԭ��
Point rotatePoint(const Point src, double angle);

Mat selectAndStiching(const Mat src, Mat PreProcessedImage);