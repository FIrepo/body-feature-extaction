#include "hand.h"

/*
 * �о�����: ��������ͼ
 * ����: void GetHand(cv::Mat& edge, struct hand * my_hand);
 * ������ͨ����������ͼ
 *		(������) ���϶��£���һ�����ص�Ϊ 255 �����ص� ��Ϊ ���� ����
 *		(���ҵ���) ���϶��£���һ�����ص�Ϊ 255 �����ص� ��Ϊ ���� ����
 */

void GetHand(cv::Mat& edge, struct hand * my_hand) {
	cv::Mat outImage = edge.clone();
	int rowNumber = outImage.rows;	//source image ����
	int colNumber = outImage.cols;  //source image ����

	struct left_hand left_hand = {0, 0};
	uchar* data_left;

	/*
	 * ��ѭ������: [ 100, rowNumber - 150]
	 * Ԥ�� �ֵ����� ��[100, rowNumber - 150] ֮��
	 *
	 */
	int row_start = 0; 
	int row_end = 0;
	row_start = 100;
	row_end = rowNumber - 200;

	// Ѱ����������ڰ׶�ֵͼ ��������
	for (int i = 0; i < colNumber ; i++) {      // ��ѭ��
		for (int j = row_start; j < row_end; j++) {   // ��ѭ��
			data_left = outImage.ptr<uchar>(j);		// ��õ�j�е��׵�ַ
			if (data_left[i] == 255) {
				left_hand.x = i;
				left_hand.y = j;
				break;
			}
		}
		if (left_hand.x > 0) {
			break;
		}
	}

	/******

	BUG 2017��3��21��22:41:26
	
	****/
	struct right_hand right_hand = { 0, 0 };
	// Ѱ����������ڰ׶�ֵͼ ��������
	uchar* data_right;
	for (int i = colNumber - 1; i > 0; i--) {   // ��ѭ��
		for (int j = row_start; j < row_end; j++) {   // ��ѭ��
			data_right = outImage.ptr<uchar>(j);		// ��õ� j �е��׵�ַ
			if (data_right[i] == 255) {
				right_hand.x = i;
				right_hand.y = j;
				break;
			}
		}
		if (right_hand.x > 0) {
			break;
		}
	}

	/*
	 * ��ȡ �������� �� ��������
	 */
	my_hand->my_left_hand  = left_hand;
	my_hand->my_right_hand = right_hand;


}