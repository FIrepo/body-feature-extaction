#pragma once
#include "/usr/local/include/opencv2/opencv.hpp"
#include "/usr/local/include/opencv2/highgui/highgui.hpp"
#include "/usr/local/include/opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>

using namespace std;

/*
 * ����: ����ԭͼ���õ� �ڰ׶�ֵͼ
 * get_BinaryImage:		��ԭͼ����д����õ��ڰ׶�ֵͼ
 * fillHole:			��������ڲ�������
 * RemoveSmallRegion:	�Ƴ��ڰ׶�ֵͼ�ж����С����
 */


void get_BinaryImage(const cv::Mat srcImage, cv::Mat &dstBw); // ��ԭͼ����д����õ��ڰ׶�ֵͼ
void fillHole(const cv::Mat srcBw, cv::Mat &dstBw);			  // ��������ڲ�������
void RemoveSmallRegion(cv::Mat& Src, cv::Mat& Dst, int AreaLimit, int CheckMode, int NeihborMode); // �Ƴ������С����

