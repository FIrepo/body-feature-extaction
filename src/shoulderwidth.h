#pragma once
#include "/usr/local/include/opencv2/opencv.hpp"
#include "/usr/local/include/opencv2/highgui/highgui.hpp"
#include "/usr/local/include/opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>

using namespace std;

void pixSum(cv::Mat& edge, vector<int>& sum);							// ����ڰ׶�ֵͼÿһ�����ص�ĸ���
void pixSum_side(cv::Mat& edge, vector<int> &sum);						// ��������������������ķ����� ����ֵ = 255 �����ص�ĸ���
void getGradient(vector<int>& sumpx, vector<double> &pointgradient);// ������������ `sum` ���ݶȣ����������vector `pointgradient`
int  MaxGradient(vector<double>arr);								// Ѱ���ݶ����� `pointgradient`�е����ֵ
