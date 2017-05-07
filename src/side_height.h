#pragma once
#include "/usr/local/include/opencv2/opencv.hpp"
#include "/usr/local/include/opencv2/highgui/highgui.hpp"
#include "/usr/local/include/opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>

using namespace std;

/*
 * �������: �������ͼ
 * �������ã�����һ�����ض�Ӧ�ĳߴ�
 * ������
 *		1. �������ͼ��������ص�ĸ���
 *		2. ���������ʵ����ߣ���һ�������һ�����ض�Ӧʵ�ʳ��ȵĴ�С
 */
void GetRatio(cv::Mat& edge, double height, double* Pix_Ratio);
