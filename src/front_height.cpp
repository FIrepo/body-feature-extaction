#include "front_height.h"

/*
 * �о�����: ��������ͼ
 * ������ͨ����������
 *		���϶��±������ص㣬��һ�� 255 �ĵ�Ϊ head
 *		���¶��ϱ������ص㣬��һ�� 255 �ĵ�Ϊ foot
 */

void GetHeight(cv::Mat& edge, int * head, int * foot) {
	cv::Mat outImage = edge.clone();
	int rowNumber = outImage.rows;	//source image ����
	int colNumber = outImage.cols;  //source image ����
	int count = 0;					//count: �洢ÿһ������ֵΪ255�����صĸ���

	/*
	* up  : ��������ڰ׶�ֵͼ����, ͷ������
	* down: ��������ڰ׶�ֵͼ����, �ŵ�����
	*/
	int up = 0, down = 0;

	uchar* data;
	// Ѱ����������ڰ׶�ֵͼ���� up ͷ������
	for (int i = 0; i < rowNumber; i++) {       // ��ѭ��
		data = outImage.ptr<uchar>(i);			// ��õ�i�е��׵�ַ
		for (int j = 0; j < colNumber; j++) {   // ��ѭ��
			if (data[j] == 255) {
				up = i;
				break;
			}
		}
		if (up > 0){
			break;
		}
	}

	// Ѱ����������ڰ׶�ֵͼ���� down �ŵ�����
	for (int i = rowNumber - 1; i > 0; i--){
		data = outImage.ptr<uchar>(i);
		for (int j = 0; j < colNumber; j++) {
			if (data[j] == 255) {
				down = i;
				break;
			}
		}
		if (down > 0) {
			break;
		}
	}

	/*
	 * head�� ͷ������
	 * foot:  �ŵ�����
	 */
	*head = up;
	*foot = down;
}