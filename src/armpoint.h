#pragma once
#include "/usr/local/include/opencv2/opencv.hpp"
#include "/usr/local/include/opencv2/highgui/highgui.hpp"
#include "/usr/local/include/opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>

using namespace std;
/*
 * ���������������ͼ
 * ��������: ����첲�ֲ�������
 * ���㷽���������ڼ���˫�ȷֲ�������
 */


// allarmpit Ҹ�ѵ�����
typedef struct allarmpit {
	int x;
	int y;
} allarmpit;

// armpit Ҹ�ѵ�����
typedef struct armpit {
	struct allarmpit leftarmpit;
	struct allarmpit rightarmpit;
} armpit;

// armpit ��ʼ������
typedef struct find_armpit_start_line {
	int left_start_line;
	int right_start_line;
} find_armpit_start_line;

void GetArmpit(cv::Mat& edge, const struct find_armpit_start_line * start_line, struct armpit * my_armpit);
void get_left_arm_point (cv::Mat& edge, int start_line, struct allarmpit * left_arm);
void get_right_arm_point(cv::Mat& edge, int start_line, struct allarmpit * right_arm);
