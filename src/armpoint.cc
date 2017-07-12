#include "armpoint.h"
/*
 * leftpoint1   :  ���� 
 * right        :  �һ��
 * middlepoint1 :  ��е�
 */
struct allarmpit leftpoint1, rightpoint1, middlepoint1;


/*
 * void GetArmpit(); ��ȡ Ҹ�ѵ������
 * ����:
 *		struct hand * my_hand_y_line:  ��ʼ�����е������
 *		struct armpit * my_armpit   :  Ŀ�� Ҹ�ѵ� ������
 */
void GetArmpit(cv::Mat& edge, const struct find_armpit_start_line * start_line, struct armpit * my_armpit){
	cv::Mat outImage = edge.clone();
	
	// ����첲�������
	struct allarmpit leftarm;
	get_left_arm_point (outImage, start_line->left_start_line, &leftarm);

	// ���Ҹ첲�������
	struct allarmpit rightarm;
	get_right_arm_point(outImage, start_line->right_start_line, &rightarm);

	my_armpit->leftarmpit  = leftarm;
	my_armpit->rightarmpit = rightarm;
}

// Ѱ�� left armpit �ֲ�������
void get_left_arm_point(cv::Mat& edge, int start_line, struct allarmpit *left_arm) {
	cv::Mat outImage = edge.clone();
	int rowNumber = outImage.rows;	//ԭͼƬ����
	int colNumber = outImage.cols;  //ԭͼƬ����
	// ��ʼ�� leftpoint1, rightpoint1, middlepoint1 �������
	leftpoint1.x = 0;
	leftpoint1.y = 0;

	rightpoint1.x = 0;
	rightpoint1.y = 0;

	middlepoint1.x = (int)(colNumber / 2); // x ΪͼƬ������
	middlepoint1.y = start_line - 50;		      // y ΪͼƬ������


	// ���� left arm ����������
	for (int i = middlepoint1.y; i > 0; i--) {
		uchar *data = outImage.ptr<uchar>(i);
		// ��������,Ѱ�����ӵ�
 		for (int j = middlepoint1.x; j > 0; j--) {
			if (data[j] == 0) {
				rightpoint1.x = j;
				rightpoint1.y = i;
				for (; j > 0; j--){
					if (data[j] == 255){
						leftpoint1.x = j;
						leftpoint1.y = i;
						break;
					}
				}

				middlepoint1.x = (rightpoint1.x + leftpoint1.x ) / 2;
				middlepoint1.y = i;
				break;
			}
		}
		if (rightpoint1.x != 0 && leftpoint1.x != 0) {
			break;
		}
	}


	// �� middlepoint1 ��ʼ��ֱ����������ֱ��������˫�ȵķֲ��
	for (int i = middlepoint1.y; i > 0; i--) {
		uchar* data = outImage.ptr<uchar>(i);

		// data[middlepoint1.x] = 255 ʱ�������ҷ�������
		if (data[middlepoint1.x] == 255) {
			middlepoint1.y = i;

			// �����10��������
			int count = 0;
			for (int j = 1; j <= 10; j++) {
				if (data[middlepoint1.x - j] == 255) {
					count++;
				}
			}
			if (count > 5) {
				// middlepoint1 = left leg �ı߽�
				leftpoint1.x = middlepoint1.x;
				leftpoint1.y = middlepoint1.y;

				for (int j = 1; j < colNumber; j++) {
					if (data[middlepoint1.x + j] == 255) {
						// �ұߵĵ�
						rightpoint1.x = middlepoint1.x + j;
						rightpoint1.y = middlepoint1.y;
						break;
					}
				}
			}
			else {
				// middlepoint1 Ϊright leg �ı߽�
				rightpoint1.x = middlepoint1.x;
				rightpoint1.y = middlepoint1.y;

				for (int j = 1; j > 0; j++) {
					if (data[middlepoint1.x - j] == 255) {
						leftpoint1.x = middlepoint1.x - j;
						leftpoint1.y = middlepoint1.y;
						break;
					}
				}
			}
			// middlepoint1
			middlepoint1.x = (int)((leftpoint1.x + rightpoint1.x) / 2);
		}

		else {
			;
		}

		// �ҵ�˫�ȷֲ�������
		if (middlepoint1.x == leftpoint1.x || middlepoint1.x == rightpoint1.x) {
			break;
		}
		else {
			;
		}
	}

	// �õ� ��첲������
	left_arm -> x = middlepoint1.x;    // ˫�ȷֲ���������
	left_arm -> y = middlepoint1.y;    // ˫�ȷֲ��������� 

	//����������
	//cout << "left_arm x: " << left_arm -> x << endl;
	//cout << "left_arm y: " << left_arm -> y << endl;
}

// Ѱ�� right armpit �ķֲ��
void get_right_arm_point(cv::Mat& edge, int start_line, struct allarmpit *right_arm) {
	cv::Mat outImage = edge.clone();
	int rowNumber = outImage.rows;	//ԭͼƬ����
	int colNumber = outImage.cols;  //ԭͼƬ����
	// ��ʼ�� leftpoint1, rightpoint1, middlepoint1 �������
	leftpoint1.x = 0;
	leftpoint1.y = 0;

	rightpoint1.x = 0;
	rightpoint1.y = 0;

	middlepoint1.x = (int)(colNumber / 2); // x ΪͼƬ������
	middlepoint1.y = start_line - 50;		      // y ΪͼƬ������

	/*
	 * �����������λ�����ѡȡ
	 * ? ���ҵ��ֵ�����
	 *
	 *
	 */
	// ���� right arm ����������
	for (int i = middlepoint1.y; i > 0; i--) {
		uchar *data = outImage.ptr<uchar>(i);
		// ���ұ�����,Ѱ�����ӵ�
		for (int j = middlepoint1.x; j < colNumber - 1; j++) {
			if (data[j] == 0) {
				leftpoint1.x = j;
				leftpoint1.y = i;
				for (; j < colNumber - 1; j++){
					if (data[j] == 255){
						rightpoint1.x = j;
						rightpoint1.y = i;
						break;
					}
				}

				middlepoint1.x = (rightpoint1.x + leftpoint1.x) / 2;
				middlepoint1.y = i;
				break;
			}
		}
		if (rightpoint1.x != 0 && leftpoint1.x != 0) {
			break;
		}
	}


	// �� middlepoint1 ��ʼ��ֱ����������ֱ��������˫�ȵķֲ��
	for (int i = middlepoint1.y; i > 0; i--) {
		uchar* data = outImage.ptr<uchar>(i);

		// data[middlepoint1.x] = 255 ʱ�������ҷ�������
		if (data[middlepoint1.x] == 255) {
			middlepoint1.y = i;

			// �����10��������
			int count = 0;
			for (int j = 1; j <= 10; j++) {
				if (data[middlepoint1.x - j] == 255) {
					count++;
				}
			}
			if (count > 5) {
				// middlepoint1 = left leg �ı߽�
				leftpoint1.x = middlepoint1.x;
				leftpoint1.y = middlepoint1.y;

				for (int j = 1; j < colNumber; j++) {
					if (data[middlepoint1.x + j] == 255) {
						// �ұߵĵ�
						rightpoint1.x = middlepoint1.x + j;
						rightpoint1.y = middlepoint1.y;
						break;
					}
				}
			}
			else {
				// middlepoint1 Ϊright leg �ı߽�
				rightpoint1.x = middlepoint1.x;
				rightpoint1.y = middlepoint1.y;

				for (int j = 1; j > 0; j++) {
					if (data[middlepoint1.x - j] == 255) {
						leftpoint1.x = middlepoint1.x - j;
						leftpoint1.y = middlepoint1.y;
						break;
					}
				}
			}
			// middlepoint1
			middlepoint1.x = (int)((leftpoint1.x + rightpoint1.x) / 2);
		}

		else {
			;
		}

		// �ҵ�˫�ȷֲ�������
		if (middlepoint1.x == leftpoint1.x || middlepoint1.x == rightpoint1.x) {
			break;
		}
		else {
			;
		}
	}

	// �õ� ��첲������
	right_arm -> x = middlepoint1.x;    // ˫�ȷֲ���������
	right_arm -> y = middlepoint1.y;    // ˫�ȷֲ��������� 

	//����������
	//cout << "right_arm x: " << left_arm -> x << endl;
	//cout << "right_arm y: " << left_arm -> y << endl;
}
