/*
 * Arthor: Yiming Sun
 * Date:   May 8th, 2017
 * Email:  guguant@yahoo.com
 * Description: The Project is about Computer graphics. 
 *		It can self-collect the key data through a front and side image.
 *		BodyEdgeDetection is only used in Eduction.
 * Copyright (c) 2017- Yiming Sun <guguant@yahoo.com>
 * All rights reserved
 */

#include "../main.h"

cv::Mat show(cv::Mat edge, int x, int y);
cv::Mat draw_position(cv::Mat edge, int line);

int main()
{

	/* 
	 * whileѭ��: ����ԭͼƬ�����в��ԣ�������Ч��
	 *		while (char(waitKey(1)) != 'q') { } // �� 'q' ���˳�whileѭ��
	 * �� 'q' ���˳�whileѭ��; �رմ���, ����������һ��ͼƬ
	 */
	int outflag = 0;
	while (1) {
		outflag++;
		cv::Mat srcImage;
		string ImageName = "/0";
		cout << "input image path:(ENTER 'q' to exit) " << endl;

		cin >> ImageName;
		// �� 'q' �� 'Q' �˳�����
		if (ImageName == "q" || ImageName == "Q") {
			return 0;
		}

		// ��ȡͼƬ ImageName
		srcImage = cv::imread(ImageName);

		/* 
		 * while(!srcImage.data){ }: ��ȡ��ȷ��ͼƬ�ļ�·��
		 */
 		while (!srcImage.data) { 
			cout << "error to read image." << endl;
			cout << "input again: ";
			cin >> ImageName;
			if (ImageName == "q" || ImageName == "Q") {
				return 0;
			}
			srcImage = cv::imread(ImageName);
			cout << endl;
		}

		/*
		 * Dst : ����ڰ׶�ֵͼ
		 * get_BinaryImage(): ����ԭͼƬΪ�ڰ׶�ֵͼ ; 
		 */
		cv::Mat Dst;
		get_BinaryImage(srcImage, Dst);

		/***********  ͨ������ͼ������������ֵ��ʵ�ʳ��ȵı���  **********/
		double height = 170.00 * 10; // ����ʵ�����Ϊ 170.00 * 10 mm
		double ratio = 0.0;			 // ratio ������߱���
		GetRatio(Dst, height, &ratio);
		cout << "one pixel = " << ratio << " mm" << endl;
		/*****************************************************************/

	
		cv::Mat DSTSHOW = Dst.clone();


		// ����: �������νṹ��
		struct bodyp pp;
		GetBodyPosition(Dst, &pp);
		cout << endl;
		cout << "|--------  FRONT ---------|" << endl;
		cout << "head         : " << pp.head << endl;
		cout << "foot         : " << pp.foot << endl;
		cout << "legpoint     : " << pp.legpoint.x << " , " << pp.legpoint.y << endl;
		cout << "left  armpit : " << pp.my_armpit.leftarmpit.x  << " , " << pp.my_armpit.leftarmpit.y << endl;
		cout << "right armpit : " << pp.my_armpit.rightarmpit.x << " , " << pp.my_armpit.rightarmpit.y << endl;
		cout << "left  hand   : " << pp.my_hand.my_left_hand.x  << " , " << pp.my_hand.my_left_hand.y << endl;
		cout << "right hand   : " << pp.my_hand.my_right_hand.x << " , " << pp.my_hand.my_right_hand.y << endl;



		/***************** ������ ****************************************/
		struct FindArea WaistArea;
		WaistArea.UpperLimit = (pp.my_armpit.leftarmpit.y > pp.my_armpit.rightarmpit.y) ? (pp.my_armpit.rightarmpit.y) : (pp.my_armpit.leftarmpit.y);
		WaistArea.LowerLimit.x = pp.legpoint.x;
		WaistArea.LowerLimit.y = pp.legpoint.y;

		int WaistWidth = 0; 
		WaistWidth = FindWaist(Dst, WaistArea);
		cout << "Waist Width  : " << WaistWidth <<  endl;
		/*****************************************************************/


		/*
		 * �������� 
		 */
		// head
		draw_position(DSTSHOW, pp.head);
		// left armpit
		draw_position(DSTSHOW, pp.my_armpit.leftarmpit.y);
		// left hand
		draw_position(DSTSHOW, pp.my_hand.my_left_hand.y);
		// ˫�ȷֲ��
		draw_position(DSTSHOW, pp.legpoint.y);
		// foot
		draw_position(DSTSHOW, pp.foot);




		/**************  б��������  *************************************/
	
		vector <DstPoint> Left_Gradient_Collection;
		Get_Left_PointGradient(Dst, Left_Gradient_Collection);
		
		int length_Left_Gradient_Collection = Left_Gradient_Collection.size();

		for (int i = 0; i < length_Left_Gradient_Collection; i++) {
			show(DSTSHOW, Left_Gradient_Collection[i].x, Left_Gradient_Collection[i].y);
		}

		cout << endl;
		cout << "Left gradient feature point num = " << length_Left_Gradient_Collection << endl;

		Left_Gradient_Collection.clear();


		vector <DstPoint> Right_Gradient_Collection;
		Get_Right_PointGradient(Dst, Right_Gradient_Collection);

		int length_Right_Gradient_Collection = Right_Gradient_Collection.size();

		for (int i = 0; i < length_Right_Gradient_Collection; i++) {
			show(DSTSHOW, Right_Gradient_Collection[i].x, Right_Gradient_Collection[i].y);
		}
		cout << "Right gradient feature point num = " << length_Right_Gradient_Collection << endl;

		Right_Gradient_Collection.clear();

		/******************************************************************/



		/****************  ������  **************************************/
		/*
		 * vector<int>sum: ����ÿһ������ֵ = 255 �ĵ������
		 * pixSum():       ����ÿһ�����ص� = 255 �ĸ���, saved to 'sum'
		 *
		 */
		vector<int>sum;
		pixSum(Dst, sum);        // ����1����������; vector<int>sum ����ÿһ��Ŀ�����ص������
		//pixSum_side(Dst, sum); // ����2: body���˿�ʼ�ƽ��������Ҷ˵�����Ĳ�ֵ

		/* 
		 * vector <int> pointgradient: ����ÿһ���������ݵ��ݶ�
		 * getGradient():              ���� sum ���ݼ��������ݶ�
		 */
		vector<double> pointgradient;
		getGradient(sum, pointgradient);

		/*
		 * ���������ݶ����ݵ��ļ� sum.txt��ʹ��cv::Matlab��������ݶ�����
		 */
		/*
		ofstream ocout;
		ocout.open("C:\\Users\\Administrator\\Desktop\\sum.txt");
		for (int i = 0; i < (int)pointgradient.size(); i++) {
			ocout << pointgradient[i] << endl;
		}
		ocout.close();
		*/

		/*
		 * ��ȡ����λ��
		 * flag: �洢�ݶ����ֵ������
		 */
		int flag = 0; 
		flag = MaxGradient(pointgradient);

		// ���������
		cout << endl;
		cout << "Shoulder     line[" << flag << "]" << endl;
		cout << "Shoulder Width    : " <<  sum[flag] << " pixels." << endl;
		//cout << "����Ϊ����  : " << sum[flag] * 0.0606577 << " cm" << endl;


		// show the source image and the binary image.
		cv::Mat temp1;

		// ��õ�i�е��׵�ַ
		uchar* data = DSTSHOW.ptr<uchar>(flag);   

		// ��ѭ��, ������λ����������ɫ��ע����
		draw_position(DSTSHOW, flag);

		/*
		 * ���´��������: ֱ����ʾ�ҵ��� ������
		 */
		cv::destroyAllWindows();

		imshow("DST", DSTSHOW);
		/*
		int pwidth  = GetSystemMetrics(SM_CXSCREEN); // ��ʾ�����
		int pheight = GetSystemMetrics(SM_CYSCREEN); // ��ʾ���߶�

		// the height of source image is lower than height of the Srceen
		if (srcImage.rows < pheight) 
		{
			imshow(ImageName, DSTSHOW);
		}
		// height of the source image is higher than height of the Screen, ��С��ʾ source image
		else { 
			int zoom = (srcImage.rows / pheight) + 1;
			resize(DSTSHOW, temp1, cv::Size(int(srcImage.cols / zoom), int(srcImage.rows / zoom)), (0, 0), (0, 0), 3);
			imshow(ImageName, temp1);
		}
		*/

		/*
		 * clear data variable, release all resource
		 */
		sum.clear();
		pointgradient.clear();
		cout << "--------------------------" << endl;
		cout << endl;
		/*********************************************************************/

		
		/* save output result
		//imwrite("../../DST.jpg", DSTSHOW);
		char* outpath = (char*)malloc(100*sizeof(char));
		memset(outpath, 0, 100);

		sprintf(outpath, "out_%d.jpg", outflag);
		cout << outpath << endl;
		imwrite("outpath", DSTSHOW);
		//cout << "output image is saved at " << outpath << endl;	

		// freepath
		free(outpath);
		*/
		cv::waitKey(0);
	}
	return 0;
}

cv::Mat show(cv::Mat edge, int x, int y) {
	int i = 0, j = 0;
	int move = 5;

	// ��ȡ ��y�� ���׵�ַ
	uchar *data1 = edge.ptr<uchar>(y);

	// �ı����� { [x - move, x + move], y } ����ֵ�Ĵ�С
	for (int i = x - move; i < x + move; i++) {
		data1[i] = 180;
	}

	// �ı� { x, [y - move, y + move ] } ����ֵ�Ĵ�С 
	for (int i = y - move; i < y + move; i++) {

		// ��ȡ ��i�е� �׵�ַ
		uchar *data2 = edge.ptr<uchar>(i); // 
		data2[x] = 180; // 
	}
	return (edge);
}

cv::Mat draw_position(cv::Mat edge, int line) {
	uchar* data_area = edge.ptr<uchar>(line);
	for (int i = 0; i < edge.cols; i++) {
		data_area[i] = 133;
	}
	return (edge);
}
