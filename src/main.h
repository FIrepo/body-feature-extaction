#pragma once
#include "/usr/local/include/opencv2/opencv.hpp"
#include "/usr/local/include/opencv2/highgui/highgui.hpp"
#include "/usr/local/include/opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>
#include <fstream>

/*
 * converttobinary.h	תԭͼΪ�ڰ׶�ֵͼ
 * shoulderwidth.h		����
 * side_height.h		�Ӳ���ͼ�����������
 * armpoint.h			��첲�ֲ������� [ ��첲 + �Ҹ첲 ]
 * bodypostion.h		������ṹ���� [ head��neck��armpit��hand��legpoint��foot ]
 * waist.h				����������Χ
 */

#include "converttobinary.h"
#include "shoulderwidth.h"
#include "side_height.h"
#include "bodyposition.h"
#include "point_gradient.h"
#include "waist.h"

using namespace std;

cv::Mat show(cv::Mat edge, int x, int y);
