#pragma once
#include "/usr/local/include/opencv2/opencv.hpp"
#include "/usr/local/include/opencv2/highgui/highgui.hpp"
#include "/usr/local/include/opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>

/*
 * Ѱ����������
 *		�������� A [Ҹ��, ˫�ȷֲ��] 
 *		����: ���� A ����, ��¼ÿ�����ص������(�������ֱ�)���������ٵļ�Ϊ ����
 *
 */

// position of single point
typedef struct point {
	int x;
	int y;
} point;

// Area which find the waist
typedef struct FindArea {
	int UpperLimit;
	point LowerLimit;
} FindArea;

// function to get waist width: return "waist width"
int FindWaist(cv::Mat& edge, const FindArea WaistArea);
