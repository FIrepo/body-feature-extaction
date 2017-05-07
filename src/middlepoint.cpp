#include "middlepoint.h"

using namespace std;
//livepoint: �ṹ��, �����������
struct livepoint leftpoint, rightpoint, middlepoint;

/*
 * void findthepoint(){} Ѱ�����ȷֲ�������
 * point_x: ��  point_y:��
 *
 */
void findthepoint(cv::Mat& edge, struct livepoint * dstpoint);

void findthepoint(cv::Mat& edge, struct livepoint * dstpoint) {
	cv::Mat outImage = edge.clone();
	int rowNumber = outImage.rows;	//ԭͼƬ����
	int colNumber = outImage.cols;  //ԭͼƬ����
	//cout << "hang:" << rowNumber << " " << colNumber << endl;
	// ��ʼ�� leftpoint, rightpoint, middlepoint �������
	leftpoint.x = 0;
	leftpoint.y = 0;

	rightpoint.x = 0;
	rightpoint.y = 0;

	middlepoint.x = (int) (colNumber / 2); // x ΪͼƬ������
	middlepoint.y = rowNumber - 1;		   // y ΪͼƬ������

	//cout << middlepoint.x << " " << middlepoint.y << endl;


	// �� (middlepoint.x, middlepoint.y) ��ʼ��ֱ����������ֱ��������˫�ȵķֲ��
	for (int i = rowNumber - 1;i > 0;i--) {
		// ��ȡ ��i�� ���׵�ַ
		uchar* data = outImage.ptr<uchar>(i);
		
		// data[middlepoint.x] = 255 ʱ�������ҷ�������
		if (data[middlepoint.x] == 255) {
			middlepoint.y = i;

			// �����10��������
			int count = 0;
			for (int j = 1;j <= 10;j++) {
				if (data[middlepoint.x - j] == 255) {
					count++;
				}
			}
			if (count > 5) {
				// middlepoint = left leg �ı߽�
				leftpoint.x = middlepoint.x;
				leftpoint.y = middlepoint.y;

				for (int j = 1;j < colNumber;j++) {
					if (data[middlepoint.x + j] == 255) {
						// �ұߵĵ�
						rightpoint.x = middlepoint.x + j;
						rightpoint.y = middlepoint.y;
						break;
					}
				}
			}
			else {
				// middlepoint Ϊright leg �ı߽�
				rightpoint.x = middlepoint.x;
				rightpoint.y = middlepoint.y;

				for (int j = 1;j > 0;j++) {
					if (data[middlepoint.x - j] == 255) {
						leftpoint.x = middlepoint.x - j;
						leftpoint.y = middlepoint.y;
						break;
					}
				}
			}
			// middlepoint
			middlepoint.x = (int)((leftpoint.x + rightpoint.x) / 2);
		}

		else {
			;
		}
		
		// �ҵ�˫�ȷֲ�������
		if (middlepoint.x == leftpoint.x || middlepoint.x == rightpoint.x) {
			break;
		}
		else {
			;
		}
	}
	
	// �õ� (point_x,point_y)
	dstpoint -> x = middlepoint.x;    // ˫�ȷֲ���������
	dstpoint -> y = middlepoint.y;    // ˫�ȷֲ��������� 

	//����������
	//cout << "middlepoint.x: " << middlepoint.x << endl;
	//cout << "middlepoint.y: " << middlepoint.y << endl;
}