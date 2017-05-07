#include "side_height.h"

/*
 * �о�����: �������ͼ
 * ������ͨ���������ͼ��������ߵ����ص㣬����һ�����ض�Ӧʵ�����صĳߴ�
 */

void GetRatio(cv::Mat& edge, double height,double* Pix_Ratio) {
	cv::Mat outImage = edge.clone();
	int rowNumber = outImage.rows;	//source image ����
	int colNumber = outImage.cols;  //source image ����
	int count = 0;					//count: �洢ÿһ������ֵΪ255�����صĸ���

	/*
	 * up  : �������ڰ׶�ֵͼ����, ͷ������
	 * down: �������ڰ׶�ֵͼ����, �ŵ�����
	 */
	int up = 0, down = 0;

	uchar* data;
	// Ѱ���������ڰ׶�ֵͼ���� up ͷ������
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

	// Ѱ���������ڰ׶�ֵͼ���� down �ŵ�����
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

	// ����һ������ Ratio��һ�����ص�ʵ�ʳ��ȣ�
	*Pix_Ratio = height * 1.0 / (down - up + 1);
	cout << "|------- Side  ---------|" << endl;
	cout << "head position: " << up   << endl;
	cout << "foot position: " << down << endl;
}
