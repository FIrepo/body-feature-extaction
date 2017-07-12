#include "point_gradient.h"

/*
 *  ���������֮���б��
 *
 */


/*
 * �ж�����֮���б������һ���߶ε�б���Ƿ����
 */

double get_gradient(DstPoint p1, DstPoint p2) {
	// k б��
	double k = 0;
	if ( p1.x == p2.x) {
		k = INF;
	}
	else {
		k = (p1.y - p2.y) * 1.0 / (p1.x - p2.x);
	}

	// ����б��
	return (k);
}


/*
 * �����������Ե ����֮���б�ʣ��Ӷ����������ļ���
 *
 */
void Get_Left_PointGradient(cv::Mat& edge, vector<DstPoint> &Left_Gradient_Collection) {
	cv::Mat outImage = edge.clone();
	int rowNumber = outImage.rows;	//����
	int colNumber = outImage.cols;  //����

	/* 
	 * p1 : ǰһ���ڵ�
	 * p2 : ��һ���ڵ�
	 */
	DstPoint p1 = { 0, 0 };
	DstPoint p2 = { 0, 0 };

	/*
	 * k1 ǰһ�߶ε�б��
  	 * k2 ������֮���б��
	 */
	double k1 = 0.0;
	double k2 = 0.0;


	// ˫��ѭ�����������е�����ֵ
	for (int i = 0; i < rowNumber; i = i + 1) {     // ��ѭ��
		uchar* data = outImage.ptr<uchar>(i); // ��õ�i�е��׵�ַ

		for (int j = 0; j < colNumber; j++) { // ��ѭ����Ѱ�� ���Ե��
			if (data[j] == 255) {
				p2.x = j;
				p2.y = i;

				k2 = get_gradient(p1, p2);
				if (k1 == k2) {
					Left_Gradient_Collection.pop_back();    // ɾ�����һ��Ԫ��
					Left_Gradient_Collection.push_back(p2); // ����Ԫ�ش��� Left_Gradient_Collection
					p1 = p2;
				}
				else {
					Left_Gradient_Collection.push_back(p2);
					k1 = k2;
					p1 = p2;
				}
				break;
			}
		}
	}
}

/*
 * ���Ұ������ ����֮���б�ʣ��Ӷ����������ļ���
 *
 */
void Get_Right_PointGradient(cv::Mat& edge, vector<DstPoint> &Right_Gradient_Collection) {
	cv::Mat outImage = edge.clone();
	int rowNumber = outImage.rows;	//����
	int colNumber = outImage.cols;  //����

	/*
	* p1 : ǰһ���ڵ�
	* p2 : ��һ���ڵ�
	*/
	DstPoint p1 = { 0, 0 };
	DstPoint p2 = { 0, 0 };

	/*
	* k1 ǰһ�߶ε�б��
	* k2 ������֮���б��
	*/
	double k1 = 0.0;
	double k2 = 0.0;


	// ˫��ѭ�����������е�����ֵ
	for (int i = 0; i < rowNumber; i = i + 1) {       // ��ѭ��
		uchar* data = outImage.ptr<uchar>(i); // ��õ�i�е��׵�ַ


		for (int j = colNumber - 1; j >= 0; j--) {   // ��ѭ��
			if (data[j] == 255) {
				p2.x = j;
				p2.y = i;
				k2 = get_gradient(p1, p2);
				if (k1 == k2) {
					Right_Gradient_Collection.pop_back();    // ɾ�����һ��Ԫ��
					Right_Gradient_Collection.push_back(p2); // ����Ԫ�ش��� Left_Gradient_Collection
					p1 = p2;
				}
				else {
					Right_Gradient_Collection.push_back(p2);
					k1 = k2;
					p1 = p2;
				}

				break;
			}
		}
	}
}