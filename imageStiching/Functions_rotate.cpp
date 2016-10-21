#include "header.h"

extern Mat g_srcImage;
extern vector<vector<Point>> bCenter;

//����ֱ���е�����
Point lineBaryCenter(Point a, Point b);

//����ת����	rotatePoint
//src ����ת������
//angle ����ת�Ƕȣ���ת��Ϊԭ��
Point rotatePoint(const Point src, double angle)
{
	Point dst;
	int x = (src.x)*cos(angle) - (src.y)*sin(angle);
	int y = (src.x)*sin(angle) + (src.y)*cos(angle);
	dst.x = x;
	dst.y = y;
	return dst;
}

//ʸ����ת�Ǽ���
//a_2p ��������ɵ�����a
//b_2p ��������ɵ�����b
double vecRotateTheta(vector<Point> a_2p, vector<Point> b_2p)
{
	Point lineBaryCenter(Point a, Point b);
	//����r1
	int r1_x = a_2p[1].x - a_2p[0].x;
	int r1_y = a_2p[1].y - a_2p[0].y;
	//����r2
	int r2_x = b_2p[0].x - b_2p[1].x;
	int r2_y = b_2p[0].y - b_2p[1].y;
	int dot_r1r2 = r1_x*r2_x + r1_y*r2_y; //���
	double modr1 = sqrt(r1_x*r1_x + r1_y*r1_y);//ȡ��
	double modr2 = sqrt(r2_x*r2_x + r2_y*r2_y);
	double theta = acos(dot_r1r2 / (modr1*modr2));
	//���
	double cross_r1r2 = r1_x*r2_y - r1_y*r2_x;
	if (cross_r1r2 >= 0) theta = -theta;
	return theta;
}
//��ת����������i
//Segment2p_1 �߶�1������������ʾ
//Segment2p_2 �߶�2������������ʾ
//bc_i ����ת������
//�������ܣ������߶�1���߶�2������������ת����Ӧλ�ã��õ���ת���������������ꡣע�⣬bCenter�������������������
//���������������Ϊ��һ������������
vector<Point> rotateVecBcenter(vector<Point> Segment2p_1, vector<Point> Segment2p_2, vector<Point> bc_i)
{
	Mat drawing1 = Mat::zeros(g_srcImage.size(), CV_8UC3);
	vector<Point> bc_d;
	int endNum_a = Segment2p_1.size() - 1;
	int endNum_b = Segment2p_2.size() - 1;
	Point mid_a = lineBaryCenter(Segment2p_1[0], Segment2p_1[endNum_a]);
	Point mid_b = lineBaryCenter(Segment2p_2[0], Segment2p_2[endNum_b]);
	double dtheta = vecRotateTheta(Segment2p_1, Segment2p_2);
	for (unsigned int j = 0; j < bc_i.size(); j++)
	{
		Point temp = bc_i[j] - mid_b;
		Point bc = rotatePoint(temp, dtheta);
		bc = bc + mid_a;
		bc_d.push_back(bc);
	}
	//ʵ��۲��ã���ʽ���ע�͵���Ӧ����
	for (int i = 0; i < bc_d.size(); i++)
		circle(drawing1, bc_d[i], 2, CV_RGB(255, 0, 0), 2);
	for (unsigned int j = 0; j < bCenter.size(); j++)
		for (unsigned int i = 0; i < bCenter[j].size(); i++)
			circle(drawing1, bCenter[j][i], 2, CV_RGB(0, 255, 0), 2);
	namedWindow("zhongxin", 0);
	imshow("zhongxin", drawing1);
	return bc_d;
}