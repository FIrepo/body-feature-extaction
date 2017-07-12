#include "converttobinary.h"

using namespace cv;
/*
 * void get_BinaryImage()    ��úڰ׶�ֵͼ
 * void fillHole()           ����϶
 * void RemoveSmallRegion()  �Ƴ�С����
 */
void get_BinaryImage(const cv::Mat srcImage, cv::Mat &dstBw); 
void fillHole(const cv::Mat srcBw, cv::Mat &dstBw);	
void RemoveSmallRegion(cv::Mat& Src, cv::Mat& Dst, int AreaLimit, int CheckMode, int NeihborMode);

/*
 * get_BinaryImage() ��ԭͼ����д����õ��ڰ׶�ֵͼ
 * ����
 *		srcImage: ԭͼ��
 *		dstBw   : �ڰ׶�ֵͼ
 */
void get_BinaryImage(const cv::Mat srcImage, cv::Mat &dstBw) {
	//��1����ͼƬתΪ�Ҷ�ͼ
	cv::Mat srcImage_Gray;
	cvtColor(srcImage, srcImage_Gray, COLOR_BGR2GRAY);
	//cvtColor(srcImage, srcImage_Gray, 6);

	//��2����˹�˲� ������˹����
	cv::Mat srcImage_Gray_Gauss;
	srcImage_Gray_Gauss = srcImage_Gray;
	GaussianBlur(srcImage_Gray, srcImage_Gray_Gauss, cv::Size(3, 3), 0, 0);

	//��3��canny���ӱ�Ե��⣬edge����ͼ��ı�Ե
	cv::Mat edge = srcImage_Gray_Gauss;
	blur(edge, srcImage_Gray_Gauss, cv::Size(3, 3));//3x3�ں˽���
	//Canny(srcImage_Gray_Gauss, edge, 30, 15, 3); // ���ͼ���Ե, ����canny�ĺ���λ����
	Canny(srcImage_Gray_Gauss, edge, 30, 15, 3);   // ���ͼ���Ե	

	//��4�����Ͳ���,����Ե��϶
	Mat element = getStructuringElement(MORPH_RECT, cv::Size(3, 3));
	//cv::Mat element = getStructuringElement(0, cv::Size(3, 3));

	cv::Mat edge_temp;
	edge_temp = edge;
	for (int i = 0;i < 1;i++) { // ����һ��
		dilate(edge_temp, edge, element);
		edge_temp = edge;
	}

	//��5�����
	for (int i = 0;i < 1;i++) // ���1��
	{
		fillHole(edge_temp, edge);
		edge_temp = edge;
	}
	threshold(edge_temp, edge, 150, 255, CV_THRESH_BINARY); // ͼ���ֵ��
															//blur(edge, edge, Size(3, 3));	//3x3�ں˽���

	cv::Mat Dst = cv::Mat::zeros(edge.size(), CV_8UC1);
	RemoveSmallRegion(edge, Dst, 2000, 1, 1);  // 8����, ���� ��� < 2000 �����ص��С����
										       // blur(Dst, Dst, Size(3, 3));	//3x3�ں˽���
	dstBw = Dst;
}



/*
 * fillHole
 * function: ������������ڵĲ���
 * ����      srcBw : source image
 *           dstBW :  dst image
 */
void fillHole(const cv::Mat srcBw, cv::Mat &dstBw)
{
	cv::Size m_Size = srcBw.size();

	//��չͼ��

	cv::Mat Temp = cv::Mat::zeros(m_Size.height + 2, m_Size.width + 2, srcBw.type());
	srcBw.copyTo(Temp(cv::Range(1, m_Size.height + 1), cv::Range(1, m_Size.width + 1)));

	// floofFill ��ˮ�㷨

	floodFill(Temp, cv::Point(0, 0), cv::Scalar(255));

	//�ü���չ��ͼ��

	cv::Mat cutImg;
	Temp(cv::Range(1, m_Size.height + 1), cv::Range(1, m_Size.width + 1)).copyTo(cutImg);

	dstBw = srcBw | (~cutImg);
}

/*
 * RemoveSmallRegion
 * function: ����ͼ����С��������������
 * ����    
 *		Src		   : ԭͼ��	 
 *		Dst		   : Ŀ�����ͼ��
 *		AreaLimit  : Ԥȥ��С�������
 *		CheckMode  : 0����ȥ��������, 1����ȥ��������(pix = 255);
 *		NeihborMode: 0���� 4 ����   , 1���� 8 ����;
 */
void RemoveSmallRegion(cv::Mat& Src, cv::Mat& Dst, int AreaLimit, int CheckMode, int NeihborMode)
{
	//��¼��ȥ��С����ĸ��� 
	int RemoveCount = 0; 
	
	/*
	 * Pointlabel: ��¼ÿ�����ص����״̬�ı�ǩ����ʼ��Ϊ 0
	 *		0 ���� δ���
	 *		1 ���� ���ڼ��
	 *		2 ���� ��鲻�ϸ���Ҫ��ת��ɫ
	 *		3 ���� ���ϸ������
	 */
	cv::Mat Pointlabel = cv::Mat::zeros(Src.size(), CV_8UC1); 

	//CheckMode = 1, ȥ�� white ���� ������ֵ = 255��
	if (CheckMode == 1)
	{
		//cout << "Mode: ȥ��С����. " << endl;
		for (int i = 0; i < Src.rows; ++i)
		{
			uchar* iData = Src.ptr<uchar>(i); // ��� cv::Mat::Src �� i ���׵�ַ
			uchar* iLabel = Pointlabel.ptr<uchar>(i);

			for (int j = 0; j < Src.cols; ++j)
			{
				if (iData[j] < 10)
				{
					iLabel[j] = 3; // ����ֵ < 10, ���ص���ɫΪ��ɫ������Ҫ��ת
				}
			}
		}
	}
	// ȥ��black���� ������ֵ = 0��
	else
	{
		//cout << "Mode: ȥ���׶�. " << endl;
		for (int i = 0; i < Src.rows; ++i)
		{
			uchar* iData = Src.ptr<uchar>(i); // ȡ�� Src �� i ���׵�ַ
			uchar* iLabel = Pointlabel.ptr<uchar>(i);
			for (int j = 0; j < Src.cols; ++j)
			{
				if (iData[j] > 10)
				{
					iLabel[j] = 3; // ����ֵ > 10, ���ص���ɫΪ��ɫ������Ҫ����
				}
			}
		}
	}

	// NeihborPos ��¼�����λ�� 
	vector <cv::Point2i> NeihborPos;   
	NeihborPos.push_back(cv::Point2i(-1,  0));
	NeihborPos.push_back(cv::Point2i( 1,  0));
	NeihborPos.push_back(cv::Point2i( 0, -1));
	NeihborPos.push_back(cv::Point2i( 0,  1));

	if ( NeihborMode == 1 )
	{
		//cout << "Neighbor mode: 8����." << endl;
		NeihborPos.push_back(cv::Point2i(-1, -1));
		NeihborPos.push_back(cv::Point2i(-1,  1));
		NeihborPos.push_back(cv::Point2i( 1, -1));
		NeihborPos.push_back(cv::Point2i( 1,  1));
	}
	else {
		//cout << "Neighbor mode: 4����." << endl;
	}

	// NeihborCount = 4��4���� NeihborCount = 8��8����
	int NeihborCount = 4 + 4 * NeihborMode; 
	int CurrX = 0, CurrY = 0;

	// ��ʼ���  
	for (int i = 0; i < Src.rows; ++i)
	{
		uchar* iLabel = Pointlabel.ptr<uchar>(i); // ȡ�� Pointlabel �� i �е��׵�ַ
		for (int j = 0; j < Src.cols; ++j)
		{
			if (iLabel[j] == 0)
			{
				//********��ʼ point(i, j)�㴦�ļ��***********//
				vector<cv::Point2i> GrowBuffer;          //��ջ�����ڴ洢������  
				GrowBuffer.push_back(cv::Point2i(j, i));
				Pointlabel.at<uchar>(i, j) = 1;
				int CheckResult = 0;                 //�����жϽ�����Ƿ񳬳���С����0Ϊδ������1Ϊ����  

				for (int z = 0; z < int(GrowBuffer.size()); z++)
				{

					for (int q = 0; q < NeihborCount; q++) //����ĸ������  
					{
						CurrX = GrowBuffer.at(z).x + NeihborPos.at(q).x;
						CurrY = GrowBuffer.at(z).y + NeihborPos.at(q).y;
						if (CurrX >= 0 && CurrX < Src.cols && CurrY >= 0 && CurrY < Src.rows) //��ֹԽ��  
						{
							if (Pointlabel.at<uchar>(CurrY, CurrX) == 0)
							{
								GrowBuffer.push_back(cv::Point2i(CurrX, CurrY)); //��������buffer  
								Pointlabel.at<uchar>(CurrY, CurrX) = 1;      /*���������ļ���ǩ�������ظ����
																			 1 �������ڼ�� */
							}
						}
					}

				}
				if (int(GrowBuffer.size()) > AreaLimit) {
					CheckResult = 2; //�жϽ�����Ƿ񳬳��޶������area����1Ϊδ������2Ϊ����  
				}
				else {
					CheckResult = 1; // GrowBuffer.size() < AreaLimit, ����������
					RemoveCount++;   // �Ƴ�С����ļ��� + 1
				}
				for (int z = 0; z < int(GrowBuffer.size()); z++)  //����Label��¼  
				{
					CurrX = GrowBuffer.at(z).x;
					CurrY = GrowBuffer.at(z).y;
					Pointlabel.at<uchar>(CurrY, CurrX) += CheckResult;
				}
				//********�����õ㴦�ļ��**********//
			}
		}
	}

	CheckMode = 255 * (1 - CheckMode);
	//��ʼ��ת�����С������
	for (int i = 0; i < Src.rows; ++i)
	{
		uchar* iData = Src.ptr<uchar>(i);    // ��� Src �� i �е��׵�ַ
		uchar* iDstData = Dst.ptr<uchar>(i); // ��� Dst �� i �е��׵�ַ 
		uchar* iLabel = Pointlabel.ptr<uchar>(i);
		for (int j = 0; j < Src.cols; ++j)
		{
			if (iLabel[j] == 2) // iLabel = 2, ��Ҫ��ת��ɫ
			{
				iDstData[j] = CheckMode;
			}
			else if (iLabel[j] == 3) // iLabel = 3, ����Ҫ��ת��ɫ
			{
				iDstData[j] = iData[j];
			}
		}
	}
	//cout << "AreaLimit : " << AreaLimit << endl;
	//cout << RemoveCount << " objects was removed." << endl;
}