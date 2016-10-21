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

//预处理函数
Mat PreProcess(Mat srcImage);

//“从”函数_将边缘轮廓打断成【弧】线段
vector<vector<vector<Point>>> cClusters(Mat srcImage);

//“从”函数_将边缘轮廓打断成【直】线段
vector<vector<Point>> lClusters(Mat srcImage);

//线段长度函数_欧几里得距离
int lineLength(Point a, Point b);

//直线平均灰度函数
int lineAveGscale(Mat srcImage, Point a, Point b);

//计算直线中点坐标
Point lineBaryCenter(Point a, Point b);

//小线段特征矢量表述
vector<vector<Vec2i>> lineCharacter(vector<vector<Point>> Clusters, Mat srcImage);

//计算matchin的w值
//vec1 轮廓i的小线段特征矢量
//vec2 轮廓j的小线段特征矢量，其中ij为旋转组合标号对
//PairNum 根据ij旋转组合标号得到的【旋转匹配直线标号】组合
double wCalculate(vector<Vec2i> vec1, vector<Vec2i> vec2, vector<Vec2i> PairNum, int a);

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
vector<Vec3d> matchingScore(vector<vector<Vec2i>> lineCharacter, vector<Vec4i> pairNum, vector<vector<Point>> bCenter, vector<vector<vector<Point>>>lcluster_2p, int threshold_bc, int alpha);

//弧线重心
Point cBaryCenter(vector<Point>segment);

//旋转组合标号阵（初步筛选标号阵）
//标号阵―匹配轮廓1中segment_i和轮廓2中segment_j的标号，组合成初步筛选的标号阵
vector<Vec4i> vpairNum(vector<vector<Vec2i>> lineCharacter, int dlThreshold, int daThreshold);

//计算轮廓重心阵
//lcluster_2p 按两点组合存放的轮廓描绘子
//bCenter 生成重心阵存放的向量
vector<vector<Point>> vBarycenter(vector<vector<vector<Point>>> lcluster_2p, vector<vector<Point>> bCenter);

//旋转轮廓重心阵i
//Segment2p_1 线段1，两点向量表示
//Segment2p_2 线段2，两点向量表示
//bc_i 待旋转重心阵
//基本功能：根据线段1和线段2，将轮廓阵旋转至对应位置，得到旋转后轮廓重心阵坐标。注意，bCenter包含多个轮廓的重心阵，
//本函数传入参数仅为单一轮廓的重心阵。
vector<Point> rotateVecBcenter(vector<Point> Segment2p_1, vector<Point> Segment2p_2, vector<Point> bc_i);

//进一步封装多边形近似，返回以两点组成的线段为单元进行储存的向量
vector<vector<vector<Point>>> lcluster2p(vector<vector<Point>>contours_poly, vector<vector<vector<Point>>> lcluster);

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
vector<Vec3d> matchingScore(vector<vector<Vec2i>> lineCharacter, vector<Vec4i> pairNum, vector<vector<Point>> bCenter, vector<vector<vector<Point>>> lcluster_2p, int threshold_bc, int alpha);

//旋转匹配直线标号函数	transMatchingNum
//c1Num 轮廓1的标号
//c2Num 轮廓2的标号
//c1_segmentNum 轮廓1的线段标号
//c2_segmentNum 轮廓2的线段标号
//Threshold 旋转后轮廓2重心和轮廓1重心之间的欧氏距离应小于的阈值
//基本功能：根据初步筛选结果，筛选出按当前直线段组合旋转后，满足1.重心距离小于一定阈值 2.夹角小于一定阈值 的线段组合，返回旋转后直线段匹配的组合标号
vector<Vec2i> transMatchingNum(vector<vector<Point>> bCenter, vector<vector<vector<Point>>> lcluster_2p, int c1Num, int c1_segmentNum, int c2Num, int c2_segmentNum, double Threshold);

//点旋转函数	rotatePoint
//src 待旋转点坐标
//angle 待旋转角度，旋转轴为原点
Point rotatePoint(const Point src, double angle);

Mat selectAndStiching(const Mat src, Mat PreProcessedImage);