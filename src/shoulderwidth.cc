#include "shoulderwidth.h"

void pixSum(cv::Mat& edge, vector<int>& sum);							// ����ڰ׶�ֵͼÿһ�����ص�ĸ���
void pixSum_side(cv::Mat& edge, vector<int> &sum);						// ��������������������ķ����� ����ֵ = 255 �����ص�ĸ���
void getGradient(vector<int>& sumpx, vector<double> &pointgradient);// ������������ `sum` ���ݶȣ����������vector `pointgradient`
int  MaxGradient(vector<double>arr);								// Ѱ���ݶ����� `pointgradient`�е����ֵ



/*
 * void pixSum
 * funciton: ����ÿһ������ֵΪ255�����ص���ܸ���
 * ����
 *    edge: ԭͼ��
 *    sum : �洢ÿһ������ֵΪ 255 �����ص�ĸ���
 */
void pixSum(cv::Mat& edge, vector<int> &sum) {
	cv::Mat outImage = edge.clone();
	int rowNumber = outImage.rows;	//source image ����
	int colNumber = outImage.cols;  //source image ����
	int count = 0;					//count: �洢ÿһ������ֵΪ255�����صĸ���

									// ˫��ѭ�����������е�����ֵ
	for (int i = 0;i < rowNumber;i++) {       // ��ѭ��
		uchar* data = outImage.ptr<uchar>(i); // ��õ�i�е��׵�ַ
		count = 0;
		for (int j = 0;j < colNumber;j++) {   // ��ѭ��
			if (data[j] == 255) {
				count++;
			}
		}
		sum.push_back(count);
	}
}

/*
 * void pixSum
 * funciton : ÿһ�����ص�ֵ�����һ��Ϊ 255 �����ص�λ������ - �ұߵ�һ������ֵΪ 255�����ص��λ������
 * ���ڴ����������  1. �����������Ч���Ϻ� 2.���������ڲ����Ч������
 * ���� : edge: ԭͼ��
 * sum : �洢ÿһ������ֵΪ 255 �����ص�ĸ���
 */
void pixSum_side(cv::Mat& edge, vector<int> &sum) {
	cv::Mat outImage = edge.clone();
	int rowNumber = outImage.rows;	//����
	int colNumber = outImage.cols;  //����

	int targetPoint_Left = 0;  // ��ߵ�һ������ֵ���� 255 �����ص������
	int targetPoint_Right = 0; // �ұߵ�һ������ֵ���� 255 �����ص������


	int count = 0; //count: �洢ÿһ������ֵΪ255�����صĸ���

	// ˫��ѭ�����������е�����ֵ
	for (int i = 0;i < rowNumber;i++) {       // ��ѭ��
		uchar* data = outImage.ptr<uchar>(i); // ��õ�i�е��׵�ַ
		count = 0;
		targetPoint_Left = 0;
		targetPoint_Right = 0;

		for (int j = 0;j < colNumber;j++) {   // ��ѭ����Ѱ�� targetPoint_Left
			if (data[j] == 255) {
				targetPoint_Left = j;
				break;
			}
		}
		for (int j = colNumber - 1;j >= targetPoint_Left;j--) {   // ��ѭ��
			if (data[j] == 255) {
				targetPoint_Right = j;
				break;
			}
		}
		count = (targetPoint_Right - targetPoint_Left + 1);
		sum.push_back(count);
	}
}

/*
 * void getGradient();
 * function: �������ؾ�����ݶ�
 * ����:
 * vector<int>& sumpx: ÿһ������ֵΪ 255 �ĸ���
 * vector<double>& pointgradient: �洢ÿһ�����ص��ݶ�
 */
void getGradient(vector<int>& sumpx, vector<double> &pointgradient) {
	size_t length = sumpx.size();
	double count = 0; // ��ʱ�洢ÿһ�е��ݶ�
	if (length == 0) {
		cout << "�������ݴ���" << endl;
	}
	else if (length == 1) {
		count = sumpx[0];
		pointgradient.push_back(count);
	}
	else if (length == 2) {
		count = sumpx[1] - sumpx[0];
		pointgradient.push_back(count);
		pointgradient.push_back(count);
	}
	else {
		// pointgradient[0]
		count = (sumpx[1] - sumpx[0]);
		pointgradient.push_back(count);

		// pointgradient[1] ... pointgradient[length -2]
		for (int i = 1; i < int(length - 1);i++) {
			count = (sumpx[i + 1] - sumpx[i - 1]) * 1.0 / 2;
			pointgradient.push_back(count);
		}

		// pointgradient[length - 1]
		count = (sumpx[length - 1] - sumpx[length - 2]);
		pointgradient.push_back(count);
	}
}

/*
 * int MaxGradient();
 * function:  Ѱ��ͼƬǰ�벿�֣������ݶȵ����ֵ�ı�ţ��Ӷ��ҵ� ������ڵ����� 
 * ����	:
 *       vector<float>arr: �ݶ�����
 *
 * ���Ľ�:
 * ȥ�����������: ͷ�� �������ݶ����ֵ�ĵ�
 */
int MaxGradient(vector<double>arr) {
	size_t arr_length = 0;
	double MaxGrad_value = 0; // �ݶ����ֵ��ֵ 
	int MaxGrad_number   = 0; // �ݶ����ֵ�ı��

	arr_length = arr.size();
	// �������һ����ͼƬ���ϰ벿�֣�����������ֻ��Ѱ�� arr ����ǰ�벿�ֵ����ֵ
	// arr_length /= 2;
	//printf("arr_length : %d\n", arr_length);

	for (int i = 0;i < int(arr_length);i++) {
		if (arr[i] > 0) {
			//for (i = i + 200; i < int(arr_length); i++) {
			for (;i < int(arr_length);i++) {
				if (arr[i] > MaxGrad_value) {
					MaxGrad_value = arr[i];
					MaxGrad_number = i;
				}
			}
		}
	}
	return MaxGrad_number;
}