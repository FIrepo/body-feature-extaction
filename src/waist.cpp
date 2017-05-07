#include "waist.h"

using namespace std;

int FindWaist(cv::Mat& edge, const FindArea WaistArea) {
	cv::Mat outImage = edge.clone();
	int up = 0;                 // ������������
	int down_x = 0, down_y = 0; // ������������

	up = WaistArea.UpperLimit;
	down_x = WaistArea.LowerLimit.x;
	down_y = WaistArea.LowerLimit.y;

	int count = 0;				//count: �洢ÿһ������ֵΪ255�����صĸ���

	vector<int>sum;
	// ˫��ѭ�����������е�����ֵ
	for (int i = up + 10; i < down_y - 3; i++) {   // up -> down_y
		uchar* data = outImage.ptr<uchar>(i); // ��õ�i�е��׵�ַ
		count = 0;

		// ��������
		for (int j = down_x; j < edge.cols; j++) {   // ��ѭ��
			if (data[j] == 255) {
				count++;
			}
			if (data[j] == 0) {
				break;
			}
		}

		// ��������
		for (int j = down_x; j > 0; j--) {   // ��ѭ��
			if (data[j] == 255) {
				count++;
			}
			if (data[j] == 0) {
				break;
			}
		}

		// ��������ѹ��sum
		sum.push_back(count);
	}

	// ��� Ĭ�� MIN (sum) = ��
	int result = 0, flag = 0;
	result = edge.cols;

	for (int i = 0; i < sum.size(); i++){
		if (sum[i] < result) {
			result = sum[i];
			flag = i;
		};
	}

	cout << endl;
	cout << "Waist        line[" << flag + up + 10 << "]" << endl;
	return ( result );
}