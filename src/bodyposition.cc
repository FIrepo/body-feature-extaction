#include "bodyposition.h"
#include "front_height.h"
#include "middlepoint.h"
#include "armpoint.h"


/*
 * bodypostion.h		������ṹ���� [ head��neck��armpit��hand��legpoint��foot ]
 * front_height.h		����������ͼ ͷ������ �� �ŵ�����
 * middlepoint.h		��˫�ȷֲ�������
 * armpoint.h			��첲�ֲ�������
 * 
 * 
 *
 */

void GetBodyPosition(cv::Mat& edge, struct bodyp * body) {
	cv::Mat Dst = edge.clone();
	int rowNumber = Dst.rows;//source image ����
	int colNumber = Dst.cols;  //source image ����


	/*
	 *	void GetHeight(): ��ȡͷ���ͽŵ׵����� -> front_height.h
	 *  head_tmp: ͷ������
	 *	foot_tmp: �ŵ�����
	 *
	 */
	int head_tmp = 0, foot_tmp = 0;
	GetHeight(Dst, &head_tmp, &foot_tmp);
	body->head = head_tmp;
	body->foot = foot_tmp;


	/*
	 * void GetHand(); ��ȡ�ֵ�����
	 * hand_tmp: �ṹ�� �洢�ֵ����� ( �������� + ��������)
	 */
	struct hand hand_tmp;
	GetHand(Dst, &hand_tmp);
	body->my_hand = hand_tmp;


	/*
	 * void findthepoint(); ��ȡ˫�ȷֲ������� -> middlepoint.h
	 * legpoint_position: �ṹ�� �洢˫�ȷֲ�������
	 *
	 */
	struct livepoint legpoint_position;
	findthepoint(Dst, &legpoint_position);
	body->legpoint = legpoint_position;



	/*
	 * void GetArmpit(cv::Mat& edge, struct hand * my_hand_y_line, struct armpit * my_armpit); ->  armpoint.h
	 * ��ȡ armpit ������
	 * struct armpit armpit_position:            �ṹ�� �洢 armpit ������
	 * struct find_armpit_start_line start_line: �ṹ�� �洢 armpit ��ʼ������
	 */
	struct armpit armpit_position;
	struct find_armpit_start_line start_line = {0, 0};
	// ����
	if ( body->my_hand.my_left_hand.y > body->legpoint.y ) {
		start_line.left_start_line = body->my_hand.my_left_hand.y;
	}
	else {
		start_line.left_start_line = body->my_hand.my_left_hand.y;
	}
	// ����
	if ( body->my_hand.my_right_hand.y > body->legpoint.y ) {
		start_line.right_start_line = body->my_hand.my_right_hand.y;
	}
	else {
		start_line.right_start_line = body->my_hand.my_right_hand.y;
	}

	GetArmpit(Dst, &start_line, &armpit_position);
	body->my_armpit = armpit_position;
	/******************************************************************/
}