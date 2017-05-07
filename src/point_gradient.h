#pragma once
#include "/usr/local/include/opencv2/opencv.hpp"
#include "/usr/local/include/opencv2/highgui/highgui.hpp"
#include "/usr/local/include/opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>

#define INF 100000 // ��������������ȣ�б�����޴���Ϊ INF

using namespace std;
/*
 * ���������֮���б�ʣ�Ѱ�Ҳ����
 *
 */

typedef struct DstPoint {
	int x; // ������
	int y; // ������
} DstPoint;


void Get_Left_PointGradient (cv::Mat& edge, vector<DstPoint> &Left_Gradient_Collection);
void Get_Right_PointGradient(cv::Mat& edge, vector<DstPoint> &Right_Gradient_Collection);

double get_gradient(DstPoint p1, DstPoint p2);
