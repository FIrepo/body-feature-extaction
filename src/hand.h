#pragma once
#include "/usr/local/include/opencv2/opencv.hpp"
#include "/usr/local/include/opencv2/highgui/highgui.hpp"
#include "/usr/local/include/opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>

using namespace std;

/*
 * �������: ��������ͼ
 * �������ã�������������ͼ �������� �� ��������
 * ������
 *	��������ͼ
 *	(������� 0 ��ʼ)   ���϶��±������ص㣬= 255 ��һ�����ص�����꼴Ϊ ���� ����
 *  (������� ���ʼ) ���϶��±������ص㣬= 255 ��һ�����ص�����꼴Ϊ ���� ����
 */


// left_hand: �ṹ�� ��������
typedef struct left_hand{
	int x;
	int y;
} left_hand;

// right_hand: �ṹ�� ��������
typedef struct right_hand{
	int x;
	int y;
} right_hand;

// hand: �ṹ�� �ֵ�����
typedef struct hand{
	left_hand	my_left_hand;
	right_hand  my_right_hand;
} hand;
void GetHand(cv::Mat& edge, struct hand * my_hand);
