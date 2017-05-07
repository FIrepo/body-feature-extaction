#pragma once
#include "/usr/local/include/opencv2/opencv.hpp"
#include "/usr/local/include/opencv2/highgui/highgui.hpp"
#include "/usr/local/include/opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>

#include "middlepoint.h"
#include "hand.h"
#include "armpoint.h"

/*
 * bodyp: �洢body��ͬ���ε�����
 * 
 * ��������������Ϊ�궨���磬��첲�����֣����
 * (ע: ���Ұ������Ϊ�о�����ͬ������)
 */
typedef struct bodyp{
	int head;						// ͷ��
	int neck;						// ����
	struct armpit    my_armpit;		// ��֫��
	struct hand      my_hand;		// �������� �� ��������
	struct livepoint legpoint;		// ˫�ȷֲ�������
	int foot;						// �ŵ� 
} bodyp;

/*
 * struct find_armpit_start_line;
 * �ṹ�壬���� armpit ����ʼ��
 */

void GetBodyPosition(cv::Mat& edge, struct bodyp * body);
