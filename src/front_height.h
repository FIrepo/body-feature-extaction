#pragma once
#include "/usr/local/include/opencv2/opencv.hpp"
#include "/usr/local/include/opencv2/highgui/highgui.hpp"
#include "/usr/local/include/opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>

using namespace std;

/*
 * �������: ��������ͼ
 * �������ã�������������ͼ ͷ�������� �� �ŵ׵�����
 * ������
 *	��������ͼ
 *	���϶��±������ص㣬��һ�� 255 �����ص㶨��Ϊ head
 *	���¶��ϱ������ص㣬��һ�� 255 �����ص㶨��Ϊ foot
 */
void GetHeight(cv::Mat& edge, int * head, int * foot);
