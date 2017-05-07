#pragma once
#include "/usr/local/include/opencv2/opencv.hpp"
#include "/usr/local/include/opencv2/highgui/highgui.hpp"
#include "/usr/local/include/opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>


typedef struct livepoint {
	int x;
	int y;
} livepoint;

/*
 * void findthepoint(): Ѱ��˫�ȷֲ������� (point_x, point_y)
 * ����������
 *	 step1: ��ͼƬ�����Ὺʼ���ϱ���
 *	 step2: ������ left leg or right leg �ı߽�ʱ���ж�middlepoint�� left leg ���� right leg�����left leg and right leg������
 *	 step3: middlepoint = (leftpoint + rightpoint) / 2 ;�ظ� step1, ֱ�� middlepoint = leftpoint or middlepoint = rightpoint
 */
//void findthepoint(cv::Mat& edge, int *point_x, int *point_y);
void findthepoint(cv::Mat& edge, struct livepoint *dstpoint);
