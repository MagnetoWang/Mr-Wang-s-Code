#include<iostream>
#include <opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <stdio.h>
#include <opencv2/imgproc.hpp>

#include <opencv2/ml/ml.hpp>
using namespace std;
using namespace cv;

//----------------------------------------
void printMatInfo(Mat img, string name);
void printMat(Mat img);
Mat IncreaseColor(Mat img, double Value);
Mat Gamma(Mat image);



void correcting(Mat src);
void printMatValue(Mat img);
void Wait_Wang();
Vec3b RandomColor(int value);
void Hough(Mat srcImage);
void ExcellentCorrecting(Mat src);
void Rotation(Mat img);

RNG rng(12345);


void yourname();
void callBack(int, void*);
void hsv_function();
void colorMap();
Mat TransferColor(Mat src);

void VS_Style();




//ɫ��  
int hmin = 0;
int hmin_Max = 360;
int hmax = 360;
int hmax_Max = 360;
//���Ͷ�  
int smin = 0;
int smin_Max = 255;
int smax = 255;
int smax_Max = 255;
//����  
int vmin = 106;
int vmin_Max = 255;
int vmax = 250;
int vmax_Max = 255;
//��ʾԭͼ�Ĵ���  
string windowName = "src";
//���ͼ�����ʾ����  
string dstName = "dst";

//����ͼ��  
Mat img = imread("name13.jpg");
//�Ҷ�ֵ��һ��  
Mat bgr;
//HSVͼ��  
Mat hsv;
//���ͼ��  
Mat dst;





//----------------------------------------

int main() {
	Mat img;
	img = imread("name26.jpg");
	resize(img, img, Size(800, 800));
	//yourname();
	//colorMap();
	VS_Style();
	//hsv_function();
	// TransferColor();
	// IncreaseColor(img,100.0);
	// Gamma(img);
	int  i = 0;
	cin >> i;

	img = imread("adjust14.jpg");
	//img = imread("rotation2.jpg");
	//Hough(img);
	printMat(img);
	Mat result(800, 800, CV_32F);
	resize(img, result, result.size(), 1, 1);
	printMat(result);
	ExcellentCorrecting(result);
	//Rotation(result);

}
//��ӡMat����ϸ��Ϣ�����Ϳ�
void printMat(Mat img) {
	cout << img << endl;
}
void Rotation(Mat img) {
	Mat srcImg = img;
	imshow("ԭʼͼ", srcImg);
	Mat gray, binImg;
	//�ҶȻ�
	cvtColor(srcImg, gray, COLOR_RGB2GRAY);
	imshow("�Ҷ�ͼ", gray);
	//��ֵ��
	threshold(gray, binImg, 100, 200, CV_THRESH_BINARY);
	imshow("��ֵ��", binImg);
	vector<vector<Point> > contours;
	vector<Rect> boundRect(contours.size());
	//ע���5������ΪCV_RETR_EXTERNAL��ֻ�������  
	findContours(binImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); //������
	cout << contours.size() << endl;
	for (int i = 0; i < contours.size(); i++)
	{
		//��Ҫ��ȡ������  
		CvPoint2D32f rectpoint[4];
		CvBox2D rect = minAreaRect(Mat(contours[i]));

		cvBoxPoints(rect, rectpoint); //��ȡ4����������  
									  //��ˮƽ�ߵĽǶ�  
		float angle = rect.angle;
		cout << "angle : " << angle << endl;

		int line1 = sqrt((rectpoint[1].y - rectpoint[0].y)*(rectpoint[1].y - rectpoint[0].y) + (rectpoint[1].x - rectpoint[0].x)*(rectpoint[1].x - rectpoint[0].x));
		int line2 = sqrt((rectpoint[3].y - rectpoint[0].y)*(rectpoint[3].y - rectpoint[0].y) + (rectpoint[3].x - rectpoint[0].x)*(rectpoint[3].x - rectpoint[0].x));
		//rectangle(binImg, rectpoint[0], rectpoint[3], Scalar(255), 2);
		//���̫С��ֱ��pass
		if (line1 * line2 < 600)
		{
			continue;
		}

		//Ϊ���������κ��ŷţ�������ת�Ƕ��ǲ�һ���ġ����ŵģ�������90�ȣ�������  
		// if (line1 > line2)
		// {
		// 	angle = 90 + angle;
		// }

		//�½�һ������Ȥ������ͼ����С��ԭͼһ����  
		Mat RoiSrcImg(srcImg.rows, srcImg.cols, CV_8UC3); //ע���������ѡCV_8UC3
		RoiSrcImg.setTo(0); //��ɫ������Ϊ��ɫ  
							//imshow("�½���ROI", RoiSrcImg);
							//�Եõ����������һ��  
		drawContours(binImg, contours, -1, Scalar(255), CV_FILLED);

		//��ͼ��RoiSrcImg
		srcImg.copyTo(RoiSrcImg, binImg);


		//����ʾһ�¿��������˸���Ȥ�������������ֶ��Ǻ�ɫ����  
		namedWindow("RoiSrcImg", 1);
		imshow("RoiSrcImg", RoiSrcImg);

		//����һ����ת���ͼ��  
		Mat RatationedImg(RoiSrcImg.rows, RoiSrcImg.cols, CV_8UC1);
		RatationedImg.setTo(0);
		//��RoiSrcImg������ת  
		Point2f center = rect.center;  //���ĵ�  
		Mat M2 = getRotationMatrix2D(center, angle, 1);//������ת�����ŵı任���� 
		warpAffine(RoiSrcImg, RatationedImg, M2, RoiSrcImg.size(), 1, 0, Scalar(0));//����任 
		imshow("��ת֮��", RatationedImg);
		imwrite("r.jpg", RatationedImg); //���������ͼƬ��������

		vector<vector<Point> > contours2;
		Mat raw = imread("r.jpg");
		Mat SecondFindImg;
		//SecondFindImg.setTo(0);
		cvtColor(raw, SecondFindImg, COLOR_BGR2GRAY);  //�ҶȻ�  
		threshold(SecondFindImg, SecondFindImg, 80, 200, CV_THRESH_BINARY);
		findContours(SecondFindImg, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
		//cout << "sec contour:" << contours2.size() << endl;

		for (int j = 0; j < contours2.size(); j++)
		{
			//��ʱ����ʵ����һ���������ˣ����Ի�ȡrect  
			Rect rect = boundingRect(Mat(contours2[j]));
			//���̫С������ֱ��pass,ͨ�����ù��������С�����Ա�ֻ֤�õ����
			if (rect.area() < 600)
			{
				continue;
			}
			Mat dstImg = raw(rect);
			imshow("dst", dstImg);
			imwrite("lastResult.jpg", dstImg);
		}


	}
	waitKey(0);
	Wait_Wang();



}
void ExcellentCorrecting(Mat src) {
	Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	vector<Vec2f> lines;
	Mat imageGray;
	cvtColor(src, imageGray, CV_RGB2GRAY);


	for (int i = 0; i < imageGray.rows; i++)
	{
		for (int j = 0; j < imageGray.cols; j++)
		{
			imageGray.at<uchar>(i, j) = pow((imageGray.at<uchar>(i, j)), 0.5);

		}
	}
	normalize(imageGray, imageGray, 0, 255, CV_MINMAX);
	imshow("imageGray_gammar", imageGray);
	//medianBlur(imageGray, imageGray, 5);
	//threshold(imageGray, imageGray, 100, 200, CV_THRESH_BINARY);
	GaussianBlur(imageGray, imageGray, Size(5, 5), 2);
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(30, 30));
	//��������������Ч�Ĵ���߽�Ϊ���ӵ�����
	morphologyEx(imageGray, imageGray, MORPH_CLOSE, element);

	// 	MORPH_OPEN�� ������ 
	// MORPH_CLOSE �������� 
	// MORPH_GRADIENT�� ��̬ѧ�ݶ� 
	// MORPH_TOPHAT����ñ���� 
	// MORPH_BLACKHAT�� ��ñ���� 
	// MORPH_ERODE ����ʴ���� 
	// MORPH_DILATE ���������� 
	// MORPH_HITMISS: ���л���������(ֻ֧��CV_8UC1���͵Ķ�ֵͼ��)

	imshow("������", imageGray);
	Canny(imageGray, imageGray, 50, 200, 5);//��������ǳ���Ҫ����������������Ч��

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(imageGray, contours, hierarchy, RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point());


	Mat Wang_mark(src.size(), CV_32S, cv::Scalar(0));
	Mat	Wang_Contours = Mat::zeros(src.size(), CV_8UC1);
	Mat Wang_Rect(src.size(), src.type(), cv::Scalar(0));
	Mat Wang_8UC1 = Mat::zeros(src.size(), imageGray.type());
	Mat Wang_Output(src.size(), CV_8UC3, cv::Scalar(0));
	//Mat Wang_hole;

	double maxArea = 0;
	double maxLength = 0;
	int maxIndex = 0;
	cout << "contours.size() = " << contours.size();
	for (int i = 0; i < contours.size(); i++) {
		//����ȷ���������ܳ������ȷ���Ƿ�պϡ���������ѡ�����Ҫ�ľ���ͼ�γ�����ȱһ����
		//Ŀǰ��û�кܺü�⣬����ֱ����ȡ���Σ�ֻ�ܽ��ơ�
		//������Ȼ���ڲ�����
		if (maxLength < arcLength(contours[i], true) && maxArea<contourArea(contours[i])) {
			maxLength = arcLength(contours[i], true);
			maxArea = contourArea(contours[i]);
			maxIndex = i;
		}
		drawContours(Wang_mark, contours, i, Scalar::all(i + 1), 1, 8, hierarchy);
		drawContours(Wang_Contours, contours, i, Scalar(255), 1, 8, hierarchy);
		//cout << arcLength(contours[i], true) << endl;
		//drawContours(Wang_Mat, contours, i, Scalar::all(i + 1), 1, 8, hierarchy);//ΪʲôҪ��������
	}

	//watershed(src, Wang_mark);
	////convertScaleAbs(Wang_mark, Wang_mark);
	//cout << src.type() << endl;
	//Wang_mark.convertTo(Wang_mark, src.type(), 1, 0);
	//imshow("src.type()( Wang_mark);", Wang_mark);
	//Mat new_mark;
	//cvtColor(src, new_mark, CV_RGB2GRAY);
	//imshow("watershed( Wang_mark);", new_mark);

	//findContours(Wang_mark, contours, hierarchy, -1, CV_CHAIN_APPROX_SIMPLE, Point());
	//maxArea = 0;
	//maxLength = 0;
	//maxIndex = 0;
	//Wang_mark.setTo(0);
	//Wang_Contours.setTo(0);
	//int SecondArea = 0;
	//int SecondLength = 0;
	//int SecondIndex = 0;
	//int area[4];
	//cout <<"contours.size() = " <<contours.size();
	//for (int i = 0; i < contours.size(); i++) {
	//	//����ȷ���������ܳ������ȷ���Ƿ�պϡ���������ѡ�����Ҫ�ľ���ͼ�γ�����ȱһ����
	//	//Ŀǰ��û�кܺü�⣬����ֱ����ȡ���Σ�ֻ�ܽ��ơ�
	//	//������Ȼ���ڲ�����
	//	//cout << i<<endl ;
	//	area[i] = contourArea(contours[i]);
	//	if (maxLength < arcLength(contours[i], true) && maxArea<contourArea(contours[i])) {
	//		maxLength = arcLength(contours[i], true);
	//		maxArea = contourArea(contours[i]);
	//		SecondIndex = maxIndex;
	//		maxIndex = i;
	//	}
	//	drawContours(Wang_mark, contours, i, Scalar::all(i + 1), 1, 8, hierarchy);
	//	drawContours(Wang_Contours, contours, i, Scalar(255), 1, 8, hierarchy);
	//	//imshow("loop Wang_Contours", Wang_Contours);
	//	//cout << arcLength(contours[i], true) << endl;
	//	//drawContours(Wang_Mat, contours, i, Scalar::all(i + 1), 1, 8, hierarchy);//ΪʲôҪ��������
	//}
	//Mat img1= Mat::zeros(src.size(), CV_8UC1);
	//Mat img2= Mat::zeros(src.size(), CV_8UC1);
	//Mat img3= Mat::zeros(src.size(), CV_8UC1);
	//drawContours(img1, contours, 0, Scalar(255), 1, 8, hierarchy);
	//drawContours(img2, contours, 1, Scalar(255), 1, 8, hierarchy);
	//drawContours(img3, contours, 2, Scalar(255), 1, 8, hierarchy);
	//imshow("img1", img1);
	//imshow("img2", img2);
	//imshow("img3", img3);
	//maxIndex = SecondIndex;



	cout << " arcLength(contours[maxIndex], true):" << arcLength(contours[maxIndex], true) << "contourArea(contours[i]) :" << contourArea(contours[maxIndex]) << endl;
	drawContours(Wang_Rect, contours, maxIndex, Scalar(255, 255, 255), 1, 8, hierarchy);
	imshow("Wang_Rect", Wang_Rect);





	imshow("Wang_Contours", Wang_Contours);
	convertScaleAbs(Wang_Rect, Wang_8UC1);
	drawContours(Wang_8UC1, contours, maxIndex, Scalar(255, 255, 255), CV_FILLED);//������ֲ�
	imshow("before Wang_8UC1", Wang_8UC1);
	//printMatValue(Wang_8UC1);

	//Wang_8UC1 = ~Wang_8UC1;
	//imshow("Wang_8UC1", Wang_8UC1);
	//Wang_8UC1.convertTo(Wang_8UC1, src.type());
	imshow("Wang_8UC1", Wang_8UC1);
	//addWeighted(src, 0.5, Wang_Rect, 1, 0, Wang_Output);
	//for (int i = 1; i<Wang_mark.rows; i++)
	//{
	//	for (int j = 1; j<Wang_mark.cols; j++)
	//	{
	//		/*����<>��Ӧ����m0Ԫ�ص��������ͣ�uchar��Ӧ����CV_8U��char��Ӧ����CV_8S��int��Ӧ����CV_32S��float��Ӧ����CV_32F��double��Ӧ����CV_64F��
	//			��m0�Ƕ�ͨ����������������ӦΪVec3b, cΪ��ǰ�����ͨ����š�i��j��c���Ǵ��㿪ʼ�ġ�*/
	//		int index = Wang_8UC1.at<uchar>(i, j);

	//		if (index != 0)
	//		{
	//			Wang_Output.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
	//		}
	//		else
	//		{
	//			Wang_Output.at<Vec3b>(i, j) = Vec3b(0,0,0);
	//		}
	//	}
	//}


	//�����е�������ȡ�������˷���һ�������ʱ�䡣������ѭ������copytoʲô�ģ�����ͼ���ں�֮��ġ����кܴ����⡣
	//�����õ�����clone������ѭ�����ơ�
	Wang_Output = Wang_8UC1.clone();
	cout << Wang_8UC1.size() << endl << Wang_Output.size() << endl;
	// src.copyTo(Wang_Output, Wang_8UC1);
	imshow("Wang_Output", Wang_Output);
	for (int i = 0; i<Wang_Output.rows; i++)
	{
		for (int j = 0; j<Wang_Output.cols; j++)
		{
			/*����<>��Ӧ����m0Ԫ�ص��������ͣ�uchar��Ӧ����CV_8U��char��Ӧ����CV_8S��int��Ӧ����CV_32S��float��Ӧ����CV_32F��double��Ӧ����CV_64F��
			��m0�Ƕ�ͨ����������������ӦΪVec3b, cΪ��ǰ�����ͨ����š�i��j��c���Ǵ��㿪ʼ�ġ�*/
			Vec3b index = Wang_Output.at<Vec3b>(i, j);

			if (index == Vec3b(255, 255, 255))
			{
				src.at<Vec3b>(i, j) = src.at<Vec3b>(i, j);
			}
			else
			{
				src.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			}
		}
	}
	imshow("src", src);
	//Rect rect = boundingRect(Mat(contours[maxIndex]));
	//Mat dstImg = raw(rect)
	//imshow("dstImg", src);
	imwrite("rotation1.jpg", src);

	waitKey(0);


}
void correcting(Mat src) {
	Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	int g_CannyThred = 150, g_CannyP = 0, g_CannySize = 0, g_HoughThred = 100, g_HoughThick = 0;
	int g_Blue = 255, g_Green = 255, g_Red = 0;
	int g_nWay = 0, g_nValue = 1000;

	Mat imageGray;
	vector<Vec2f> lines;
	cvtColor(src, imageGray, CV_RGB2GRAY);
	GaussianBlur(imageGray, imageGray, Size(5, 5), 2);
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(20, 20));
	//��������������Ч�Ĵ���߽�Ϊ���ӵ�����
	morphologyEx(imageGray, imageGray, MORPH_CLOSE, element);
	imshow("��ǿͼ��", imageGray);
	Canny(imageGray, imageGray, 100, 200, 5);//��������ǳ���Ҫ����������������Ч��
											 //Mat grad_x, abs_grad_x;
											 //Mat grad_y, abs_grad_y;
											 //Sobel(imageGray, grad_x, CV_8S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
											 //Sobel(imageGray, grad_y, CV_8S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
											 //convertScaleAbs(grad_x, abs_grad_x);
											 //convertScaleAbs(grad_y, abs_grad_y);
											 //addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, imageGray);
											 //imshow("��Ч��ͼ�����巽��Sobel", imageGray);
											 //printMatValue(imageGray);
											 //for (int i = 0; i<imageGray.rows; i++)
											 //{
											 //	for (int j = 0; j<imageGray.cols; j++)
											 //	{
											 //		int index = imageGray.at<int>(i, j);

											 //		if (index != 0)
											 //		{
											 //			imageGray.at<int>(i, j) =10;
											 //		}
											 //		else
											 //		{
											 //			imageGray.at<int>(i, j) = 0;
											 //		}
											 //	}
											 //}
											 //imshow("��ǿͼ��", imageGray);


	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(imageGray, contours, hierarchy, RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point());
	cout << "imageGray type : " << imageGray.type() << endl;
	Mat imageContours = Mat::zeros(src.size(), CV_8UC1);  //����


	Mat imageMask(src.size(), CV_8U, cv::Scalar(0));


	Mat Wang_Mat(src.size(), CV_32S, cv::Scalar(0));
	Mat Wang_8UC1;



	Mat mark1(src.size(), CV_32S, cv::Scalar(0));
	int index = 0;
	int compCount = 0;
	//for (; index >= 0; index = hierarchy[index][0], compCount++)
	//	for (index = 0; index  <=20; index++, compCount++)
	//{
	//	cout << "index " << index << endl;
	//	cout << "compCount" << compCount << endl;
	//	//��marks���б�ǣ��Բ�ͬ������������б�ţ��൱������עˮ�㣬�ж������������ж���עˮ��  
	//	//drawContours(mark1, contours, index, Scalar::all(compCount + 1), 1, 8, hierarchy);
	//	drawContours(mark1, contours, index, Scalar::all(compCount + 1), 1, 8, hierarchy);
	//	drawContours(imageContours, contours, index, Scalar(255), 1, 8, hierarchy);
	//}
	double max = 0;
	int maxIndex = 0;
	for (int i = 0; i < contours.size(); i++) {
		if (max < arcLength(contours[i], true)) {
			max = arcLength(contours[i], true);
			maxIndex = i;
		}
		drawContours(mark1, contours, i, Scalar::all(i + 1), 1, 8, hierarchy);
		drawContours(imageContours, contours, i, Scalar(255), 1, 8, hierarchy);
		//cout << contourArea(contours[i]) << endl;
		//drawContours(Wang_Mat, contours, i, Scalar::all(i + 1), 1, 8, hierarchy);//ΪʲôҪ��������


	}
	cout << arcLength(contours[maxIndex], true) << endl;
	/*drawContours(mark1, contours, maxIndex, Scalar::all(compCount + 1), 1, 8, hierarchy);*/
	drawContours(imageContours, contours, maxIndex, Scalar(255), 1, 8, hierarchy);
	drawContours(mark1, contours, maxIndex, Scalar::all(maxIndex + 1), 1, 8, hierarchy);
	drawContours(Wang_Mat, contours, maxIndex, Scalar::all(maxIndex + 1), 1, 8, hierarchy);


	Mat marksShows;
	convertScaleAbs(mark1, marksShows);//��ʹ�����Ա任ת����������Ԫ�س�8λ�޷������͡�
	imshow("mark1", mark1);
	imshow("marksShow", marksShows);

	imshow("����", imageContours);

	//cvHoughLines2(imageContours,)
	HoughLines(imageContours, lines, (double)g_CannyThred, (double)((g_CannyThred + 1) * (2 + g_CannyP / 100.0)), 3);

	//imshow("����任", imageContours);

	watershed(src, mark1);
	imshow("Aftermark1", mark1);
	Mat Wang_32S;
	convertScaleAbs(Wang_Mat, Wang_8UC1);
	imshow("before Watershed Wang_8UC1", Wang_8UC1);

	findContours(Wang_8UC1, contours, hierarchy, -1, CV_CHAIN_APPROX_NONE, Point());//������8λ��ͨ����ͼ��
	max = 0;
	maxIndex = 0;
	Mat Wang_Contours = Mat::zeros(Wang_8UC1.size(), CV_8UC1);
	for (int i = 0; i < contours.size(); i++) {
		if (max < arcLength(contours[i], true)) {
			max = arcLength(contours[i], true);
			maxIndex = i;
		}
		/*	Rect rect = cvBoundingRect(contours, 0);
		cvRectangle(imgSrc, cvPoint(rect.x, rect.y), cvPoint(rect.x + rect.width, rect.y + rect.height), cvScalar(0, 0, 0), 0);*/
		/*drawContours(Wang_Contours, contours, i, Scalar(255), 1, 8, hierarchy);*/
		cout << "����  " << i << " : " << arcLength(contours[i], true) << endl;

	}
	//printMatValue(twice_Contours);
	//imshow("twice", twice_Contours);
	cout << "maxIndex  " << maxIndex << " : " << arcLength(contours[index], true);
	drawContours(Wang_Contours, contours, maxIndex, color, 1, 8, hierarchy);
	imshow("Wang_Contours", Wang_Contours);
	Mat Wang_Output = Mat::zeros(src.size(), CV_8UC3);
	Mat Wang_8UC3 = Mat::zeros(src.size(), CV_8UC3);

	Wang_Contours.convertTo(Wang_8UC3, CV_8UC3);
	imshow("Wang_8UC3", Wang_8UC3);
	//addWeighted(src, 0.4, Wang_8UC3, 0.6, 0, Wang_Output);
	imshow("Wang_Output", Wang_Output);
	//cvBoundingRect()
	//	CvRect cvBoundingRect(CvArr* points, int update = 0);
	//points
	//	��ά�㼯��������л�����(CvMat)
	//	update
	//	���±�ʶ���������������ͺͱ�ʶ��һЩ������� :
	//update = 0, contour ~CvContour* : ��������α߽磬��ֱ��������ͷ�� rect ��õ���
	//	update = 1, contour ~CvContour* : ������α߽磬���ҽ����д�뵽����ͷ�� rect ���� header.
	//	update = 0, contour ~CvSeq* or CvMat* : ���㲢���ر߽����
	//	update = 1, contour ~CvSeq* or CvMat* : �������д��� ��runtime error is raised��
	//	���� cvBoundingRect ���ض�ά�㼯�������� ��up - right�����α߽硣


	watershed(src, Wang_Mat);//32λ����ͨ�������ͼ��
	imshow("AfteimageWang_Mat", Wang_Mat);


	//convertScaleAbs(Wang_Mat, Wang_8UC1);
	//imshow("After Watershed Wang_8UC1", Wang_8UC1);

	//����������һ�·�ˮ���㷨֮��ľ���marks����ʲô����  

	//findContours(mark1, contours, hierarchy, RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point());
	//imshow("again Mark1", mark1);


	Mat afterWatershed;
	convertScaleAbs(mark1, afterWatershed);
	imshow("After Watershed", afterWatershed);

	//printMatValue(mark1);





	//��ÿһ�����������ɫ���  
	Mat PerspectiveImage = Mat::zeros(src.size(), CV_8UC3);
	for (int i = 0; i<mark1.rows; i++)
	{
		for (int j = 0; j<mark1.cols; j++)
		{
			int index = mark1.at<int>(i, j);

			if (mark1.at<int>(i, j) == -1)
			{
				PerspectiveImage.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
			}
			else
			{
				PerspectiveImage.at<Vec3b>(i, j) = RandomColor(index);
			}
		}
	}
	imshow("After ColorFill", PerspectiveImage);

	//�ָ�����ɫ�Ľ����ԭʼͼ���ں�  
	Mat wshed;
	addWeighted(src, 0.4, PerspectiveImage, 0.6, 0, wshed);

	imshow("AddWeighted Image", wshed);

	cvtColor(PerspectiveImage, PerspectiveImage, CV_RGB2GRAY);
	imshow("PerspectiveImage Gray", PerspectiveImage);
	//GaussianBlur(wshed, wshed, Size(5, 5), 2);
	//imshow("PerspectiveImage GaussianBlur", wshed);
	//Canny(wshed, wshed, 80, 150);
	//imshow("PerspectiveImage Canny", wshed);
	Mat Mat_8UC1_wang = Mat::zeros(imageContours.size(), CV_8UC1);
	convertScaleAbs(imageContours, Mat_8UC1_wang);


	//�ڶ���������ѡ��Ӧ�û�����һ�η�ˮ��֮�����֮ǰ�����߶���һ�������ơ�
	//���Ի�Ҫ�����е��㷨����
	findContours(imageContours, contours, hierarchy, -1, CV_CHAIN_APPROX_NONE, Point());
	//_levels:
	//3���������������������������������������
	//	2��������������������������
	//	1:����������
	//	0����һ��������
	//	- 1����һ����������������������
	//	- 2����һ�����������������������������������
	//findContours(imageGray, contours, hierarchy, RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point());
	cout << "�ҵڶ�������";
	max = 0;
	maxIndex = 0;
	Mat twice_Contours = Mat::zeros(PerspectiveImage.size(), CV_8UC1);
	for (int i = 0; i < contours.size(); i++) {
		if (max < contourArea(contours[i])) {
			max = contourArea(contours[i]);
			maxIndex = i;
		}
		drawContours(twice_Contours, contours, i, Scalar(255), 1, 8, hierarchy);
		cout << "����  " << i << " : " << contourArea(contours[i]) << endl;

	}
	//printMatValue(twice_Contours);
	//imshow("twice", twice_Contours);
	//drawContours(twice_Contours, contours, maxIndex, Scalar(255), 1, 8, hierarchy);
	imshow("twice", twice_Contours);


	waitKey(0);

	//����������
	//rectangle(imageMask, cv::Point(1, 1), cv::Point(src.cols - 2, src.rows - 2), cv::Scalar(255), 1);
	//cv::rectangle(imageMask, cv::Point(src.cols / 2 - 10, src.rows / 2 - 10),
	//	cv::Point(src.cols / 2 + 10, src.rows / 2 + 10), cv::Scalar(64), 10);


	//cv::rectangle(imageMask, cv::Point(64, 284),
	//	cv::Point(68, 300), cv::Scalar(128), 5);

	imageMask.convertTo(imageMask, CV_32S);
	watershed(src, imageMask);
	imshow("imageMask", imageMask);
	//waitKey(0);

	imshow("src", src);
	//waitKey(0);

	imageMask.convertTo(mark1, CV_8U);

	imshow("marker", mark1);
	waitKey(0);
	//printMatValue(imageMask);
	Wait_Wang();





	Mat imglabels = src;
	cvtColor(src, src, CV_BGR2GRAY);


	//imshow("�ҶȻ�",src);
	//waitKey(0);
	//adaptiveThreshold(src, src, 256, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 41, 0);

	threshold(src, src, 0, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);
	element = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
	morphologyEx(src, src, MORPH_OPEN, element, Point(-1, -1), 2);
	dilate(src, src, element, Point(-1, -1), 3);
	//watershed(src, imglabels);
	/*WatershedGray()*/
	//printMatValue(src);
	imshow("��ֵ��", src);
	imshow("���ͼ", imglabels);
	waitKey(0);
}
//��ӡMat�������������
void printMatValue(Mat img) {
	cout << img;
	//for (int i = 0; i < img.rows; i++) {
	//	for (int j = 0; j < img.cols; j++)
	//	{
	//		cout << img[i][j] << " ";
	//	}
	//	cout << endl;
	//}
}

void Wait_Wang() {
	cout << "wait" << endl;
	int wait;
	cin >> wait;
}

Vec3b RandomColor(int value) {
	value = value % 255;  //����0~255�������  
	RNG rng;
	int aa = rng.uniform(0, value);
	int bb = rng.uniform(0, value);
	int cc = rng.uniform(0, value);
	return Vec3b(aa, bb, cc);
}

//����任
void Hough(Mat srcImage) {
	int g_CannyThred = 150, g_CannyP = 0, g_CannySize = 0, g_HoughThred = 100, g_HoughThick = 0;
	int g_Blue = 255, g_Green = 255, g_Red = 0;
	int g_nWay = 0, g_nValue = 1000;

	imshow("��ԭͼ��", srcImage);

	Mat grayImage;
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);

	Mat cannyImage;
	vector<Vec2f> lines;
	Point point1, point2;

	namedWindow("�����������ڡ�", 0);
	createTrackbar("CannyThred", "�����������ڡ�", &g_CannyThred, 255, 0);
	createTrackbar("P:", "�����������ڡ�", &g_CannyP, 100, 0);
	createTrackbar("Size", "�����������ڡ�", &g_CannySize, 20, 0);
	createTrackbar("HThred", "�����������ڡ�", &g_HoughThred, 255, 0);
	createTrackbar("Blue", "�����������ڡ�", &g_Blue, 255, 0);
	createTrackbar("Green", "�����������ڡ�", &g_Green, 255, 0);
	createTrackbar("Red", "�����������ڡ�", &g_Red, 255, 0);
	createTrackbar("Bgr/Gray", "�����������ڡ�", &g_nWay, 1, 0);
	createTrackbar("Thick", "�����������ڡ�", &g_HoughThick, 100, 0);
	createTrackbar("Value", "�����������ڡ�", &g_nValue, 2000, 0);

	char key;
	Mat CannyBgrImage;
	Mat dstImage;
	while (1)
	{
		Canny(srcImage, cannyImage, (double)g_CannyThred, (double)((g_CannyThred + 1) * (2 + g_CannyP / 100.0)), 3);
		HoughLines(cannyImage, lines, 1, CV_PI / 180, g_HoughThred + 1, 0, 0);

		cvtColor(cannyImage, CannyBgrImage, CV_GRAY2BGR);

		//��ʾ�߶�  
		for (size_t i = 0; i < lines.size(); i++)
		{
			//�������еõ� ����ֵ�ͽǶ�ֵ  
			//������仹����д�ɣ�  
			/*Vec2f vec = Vec2f(lines[i][0], lines[i][1]);
			float rho = vec[0], theta = vec[1];*/
			float rho = lines[i][0], theta = lines[i][1];
			//���ȵõ�ԭ��(0, 0)����ֱ�ߵĴ��� �� ��ֱ�ߵĽ��������  
			double x0 = rho * cos(theta), y0 = rho * sin(theta);
			//ȡ�ý������صĵ�  ������  
			point1.x = cvRound(x0 + g_nValue * (-sin(theta)));
			point1.y = cvRound(y0 + g_nValue * (cos(theta)));
			point2.x = cvRound(x0 - g_nValue * (-sin(theta)));
			point2.y = cvRound(y0 - g_nValue * (cos(theta)));

			if (g_nWay)
				dstImage = cannyImage;
			else
				dstImage = CannyBgrImage;

			line(dstImage, point1, point2, Scalar(g_Blue, g_Green, g_Red), g_HoughThick + 1, CV_AA);
		}

		imshow("�������", dstImage);

		key = waitKey(1);
		if (key == 27)
			break;
	}
}
//void cv::adaptiveThreshold(
//	cv::InputArray src, // ����ͼ��  
//	cv::OutputArray dst, // ���ͼ��  
//	double maxValue, // �������ֵ  
//	int adaptiveMethod, // ����Ӧ������ƽ�����˹  
//	int thresholdType // ��ֵ������  
//	int blockSize, // ���С  
//	double C // ����  
//);


//resize(img, result, result.size(), 1, 1);
//src�����룬ԭͼ�񣬼����ı��С��ͼ��
//
//dst��������ı��С֮���ͼ�����ͼ���ԭͼ�������ͬ�����ݣ�ֻ�Ǵ�С��ԭͼ��һ�����ѣ�
//
//dsize�����ͼ��Ĵ�С��������������Ϊ0����ô�ʹ���ԭͼ�����ŵ����Size(width��height)ָ���Ĵ�С������������Ϊ0����ôԭͼ������֮��Ĵ�С��Ҫͨ������Ĺ�ʽ�����㣺
//
//dsize = Size(round(fx*src.cols), round(fy*src.rows))
//
//���У�fx��fy��������Ҫ˵��������������ͼ��width�����height��������ű�����
//
//fx��width��������ű������������0����ô���ͻᰴ��(double)dsize.width / src.cols�����㣻
//
//fy��height��������ű������������0����ô���ͻᰴ��(double)dsize.height / src.rows�����㣻
//
//interpolation�������ָ����ֵ�ķ�ʽ��ͼ������֮�󣬿϶�����Ҫ�������¼���ģ��Ϳ����������ָ�����¼������صķ�ʽ�������¼��֣�
//
//
//INTER_NEAREST - ���ڽ���ֵ
//INTER_LINEAR - ˫���Բ�ֵ��������һ�������㲻ָ����Ĭ��ʹ�����ַ���
//INTER_AREA - resampling using pixel area relation.It may be a preferred method for image decimation, as it gives moire�� - free results.But when the image is zoomed, it is similar to the INTER_NEAREST method.
//INTER_CUBIC - 4x4���������ڵ�˫������ֵ
//INTER_LANCZOS4 - 8x8���������ڵ�Lanczos��ֵ
//
//
//ʹ��ע�����
//
//1. dsize��fx / fy����ͬʱΪ0��Ҫô���ָ����dsize��ֵ����fx��fy����ֱ��ʹ��Ĭ��ֵ������
//
//resize(img, imgDst, Size(30, 30));
//
//Ҫô�����dsizeΪ0��ָ����fx��fy��ֵ������fx = fy = 0.5����ô���൱�ڰ�ԭͼ����������Сһ����
//
//
//
//2. �������Ĳ�ֵ���������������ʹ��Ĭ�ϵ�˫���Բ�ֵ�͹����ˡ�
//
//���ֳ��÷�����Ч���ǣ����ڽ���ֵ>˫���Բ�ֵ>˫������ֵ>Lanczos��ֵ��
//
//����Ч�ʺ�Ч���ɷ��ȣ����Ը����Լ����������ʹ�á�
//
//
//
//3. ��������£���ʹ��֮ǰdstͼ��Ĵ�С�����Ͷ��ǲ�֪���ģ����ʹ�srcͼ��̳ж�������СҲ�Ǵ�ԭͼ����ݲ��������������������������Ѿ�ָ����dstͼ��Ĵ�С����ô�����ͨ���������ַ�ʽ�����ú���





//findContours��������
//�ڶ���������contours������Ϊ��vector<vector<Point>> contours������һ��������������һ��˫������������
//
//��ÿ��Ԫ�ر�����һ����������Point�㹹�ɵĵ�ļ��ϵ�������ÿһ��Point�㼯����һ��������
//
//�ж�������������contours���ж���Ԫ�ء�
//
//
//
//������������hierarchy������Ϊ��vector<Vec4i> hierarchy����������һ��Vec4i�Ķ��壺
//
//typedef    Vec<int, 4>   Vec4i;
//
//Vec4i��Vec<int, 4>�ı�����������һ����������ÿһ��Ԫ�ذ�����4��int�ͱ�������������
//
//���ԴӶ����Ͽ���hierarchyҲ��һ��������������ÿ��Ԫ�ر�����һ������4��int���͵����顣
//
//����hiararchy�ڵ�Ԫ�غ���������contours�ڵ�Ԫ����һһ��Ӧ�ģ�������������ͬ��
//
//hierarchy������ÿһ��Ԫ�ص�4��int�ͱ�������hierarchy[i][0] ~hierarchy[i][3]���ֱ��ʾ��
//
//i�������ĺ�һ��������ǰһ������������������Ƕ������������š������ǰ����û�ж�Ӧ�ĺ�һ��
//
//������ǰһ������������������Ƕ�����Ļ�����hierarchy[i][0] ~hierarchy[i][3]����Ӧλ������Ϊ
//
//Ĭ��ֵ - 1��
//
//
//
//���ĸ�������int�͵�mode�����������ļ���ģʽ��
//
//
//
//ȡֵһ��CV_RETR_EXTERNALֻ�������Χ��������������Χ�����ڵ���Χ����������
//
//
//
//ȡֵ����CV_RETR_LIST   ������е�������������Χ����Χ���������Ǽ�⵽�������������ȼ���
//
//ϵ���˴�֮�������û�еȼ���ϵ�������ζ���������ģʽ�²����ڸ���������Ƕ������
//
//����hierarchy����������Ԫ�صĵ�3����4���������ᱻ��Ϊ - 1���������Ļὲ��
//
//
//
//ȡֵ����CV_RETR_CCOMP  ������е�����������������ֻ���������ȼ���ϵ����ΧΪ���㣬����Χ
//
//�ڵ���Χ������������������������Ϣ������Χ�ڵ����������������ڶ���
//
//
//
//ȡֵ�ģ�CV_RETR_TREE�� �������������������������һ���ȼ����ṹ��������������ڲ���������
//
//�����������Լ���������Ƕ������
//
//
//
//�����������int�͵�method�����������Ľ��Ʒ�����
//
//
//
//ȡֵһ��CV_CHAIN_APPROX_NONE ��������߽������������������㵽contours������
//
//
//
//ȡֵ����CV_CHAIN_APPROX_SIMPLE �����������Ĺյ���Ϣ�������������յ㴦�ĵ㱣����contours
//
//�����ڣ��յ���յ�֮��ֱ�߶��ϵ���Ϣ�㲻�豣��
//
//
//
//ȡֵ�����ģ�CV_CHAIN_APPROX_TC89_L1��CV_CHAIN_APPROX_TC89_KCOSʹ��teh - Chinl chain ��
//
//���㷨
//
//
//
//������������Pointƫ���������е�������Ϣ�����ԭʼͼ���Ӧ���ƫ�������൱����ÿһ���������������ϼ�
//
//�ϸ�ƫ����������Point�������Ǹ�ֵ��
//void findContours//��ȡ������������ȡͼ�������
//(
//	InputOutputArray image,//����ͼ�񣬱�����8λ��ͨ��ͼ�񣬲���Ӧ��ת���ɶ�ֵ��
//	OutputArrayOfArrays contours,//��⵽��������ÿ����������ʾ��һ��point����
//	OutputArray hierarchy,//��ѡ���������������ͼ���������Ϣ������Ԫ�صĸ����ͼ�⵽���������������
//	int mode,//˵����Ҫ���������ͺ�ϣ���ķ���ֵ��ʽ
//	int method,//�������Ʒ���
//	Point offset = Point()
//)




//void drawContours//�������������ڻ����ҵ���ͼ������
//(
//	InputOutputArray image,//Ҫ����������ͼ��
//	InputArrayOfArrays contours,//���������������ÿ�������������һ��point����
//	int contourIdx,//ָ��Ҫ���������ı�ţ�����Ǹ�������������е�����
//	const Scalar& color,//�����������õ���ɫ
//	int thickness = 1, //�����������ߵĴ�ϸ������Ǹ������������ڲ������
//	int lineType = 8, / �����������ߵ���ͨ��
//	InputArray hierarchy = noArray(),//���ڲ㼶�Ŀ�ѡ������ֻ�л��Ʋ�������ʱ�Ż��õ�
//	int maxLevel = INT_MAX,//������������߼����������ֻ��hierarchy��Ч��ʱ�����Ч
//						   //maxLevel=0��������������������ͬһ�ȼ������������������������������ڵ�����
//						   //maxLevel=1, ��������������ͬһ�ȼ����������������ӽڵ㡣
//						   //maxLevel=2����������������ͬһ�ȼ����������������ӽڵ��Լ��ӽڵ���ӽڵ�
//	Point offset = Point()
//)







void yourname() {
	Mat src;
	src = imread("name3.jpg");
	imshow("ԭʼͼ", src);
	Mat img;
	resize(src, img, Size(800, 800), 1, 1);

	imshow("800X800ͼ", img);
	cvtColor(img, img, COLOR_BGR2HSV);

	imshow("COLOR_BGR2HSVͼ", img);

	Mat RGB_channels[3];
	split(img, RGB_channels);
	imshow("H", RGB_channels[0]);
	imshow("S", RGB_channels[1]);
	imshow("V", RGB_channels[2]);



	equalizeHist(RGB_channels[2], RGB_channels[2]);
	merge(RGB_channels, 3, img);
	imshow("����ͼ", img);
	inRange(img, Scalar(60, 43, 46), Scalar(260, 255, 255), img);
	imshow("�������", img);
	medianBlur(img, img, 9);
	imshow("������գ���ֵ�˲�", img);

	Mat kernel(5, 5, CV_8U);
	morphologyEx(img, img, MORPH_OPEN, kernel, Point(-1, -1), 10);
	medianBlur(img, img, 9);
	imshow("�����", img);

	//������
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//findContours(img, contours, hierarchy,CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	cout << endl << " img.channels " << img.channels() << endl;
	//cout << endl << " img.size " << img. << endl;


	findContours(img, contours, hierarchy, RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	imshow("img", img);

	Rect boundRect;
	Mat Wang_Rect(img.size(), src.type(), cv::Scalar(0));


	//drawContours(Wang_Rect, contours, 0, Scalar(255,255,255), CV_FILLED, 8, hierarchy);
	//imshow("Wang_Rect",Wang_Rect);
	//waitKey(0);
	boundRect = boundingRect(Mat(contours[0]));

	//void cv::rectangle(Mat & 	img,
	//	Rect 	rec,
	//	const Scalar & 	color,
	//	int 	thickness = 1,
	//	int 	lineType = LINE_8,
	//	int 	shift = 0
	//)

	rectangle(Wang_Rect, boundRect, Scalar(255, 255, 255), 1, 8, 0);

	imshow("Wang_Rect", Wang_Rect);

	int x = boundRect.x;
	int y = boundRect.y;
	int height = boundRect.height;
	int width = boundRect.width;


	Point 	p((x + width) / 2, (y + height) / 2);



	Mat sky = imread("sky5.jpg");

	Mat src_clone = src;
	resize(sky, sky, Size(800, 800));
	resize(src_clone, src_clone, Size(800, 800));
	cout << "sky.type" << sky.type() << endl;
	cout << "src_clone.type" << src_clone.type() << endl;
	imshow("src", src_clone);
	imshow("sky", sky);
	//waitKey(0);




	//void cv::seamlessClone(InputArray 	src,
	//	InputArray 	dst,
	//	InputArray 	mask,
	//	Point 	p,
	//	OutputArray 	blend,
	//	int 	flags
	//)
	//Parameters
	//	src	Input 8 - bit 3 - channel image.
	//	dst	Input 8 - bit 3 - channel image.
	//	mask	Input 8 - bit 1 or 3 - channel image.
	//	p	Point in dst image where object is placed.
	//	blend	Output image with the same size and type as dst.
	//	flags	Cloning method that could be one of the following :
	//NORMAL_CLONE The power of the method is fully expressed when inserting objects with complex outlines into a new background
	//	MIXED_CLONE The classic method, color - based selection and alpha masking might be time consuming and often leaves an undesirable halo.Seamless cloning, even averaged with the original image, is not effective.Mixed seamless cloning based on a loose selection proves effective.
	//	MONOCHROME_TRANSFER Monochrome transfer allows the user to easily replace certain features of one object by alternative features.
	Mat result(sky.size(), sky.type(), cv::Scalar(0));
	seamlessClone(sky, src_clone, img, p, result, NORMAL_CLONE);
	imshow("result", result);

	imwrite("yourname.jpg", result);
	Mat org = imread("ԭʼɫͼ.jpg");
	Mat filter = imread("�º���.jpg");
	resize(filter, filter, Size(800, 800));
	cout << "result.type" << result.type() << endl;
	cout << "result.channels()" << result.channels() << endl;
	cout << "result.color()" << result.at<Vec3b>(1, 1) << endl;
	cout << "filter.type" << filter.type() << endl;
	cout << "filter.channels()" << filter.channels() << endl;
	cout << "filter.color()" << filter.at<Vec3b>(1, 1) << endl;
	//A = y / 4 + (x / 32) * 64

	//	B = z / 4 + ((x % 32) / 4) * 64

	//waitKey(0);
	for (int i = 1; i < result.rows; i++) {
		for (int j = 1; j < result.cols; j++) {
			Vec3b c_v = result.at<Vec3b>(i, j);
			int x = c_v.val[1] / 4 + (c_v.val[0] / 32) * 64;
			int y = c_v.val[2] / 4 + (c_v.val[0] % 4) * 64;
			/*		x = x % 500;
			y = y % 500;*/
			result.at<Vec3b>(i, j) = filter.at<Vec3b>(x, y);

		}
	}
	imshow("�˾�Ч��", result);



	//��ͨ��ͼ���ȡ��ʽ

	//	Mat img1 = imread(filename, IMREAD_GRAYSCALE);
	//for (size_t nrow = 0; nrow < img1.rows; nrow++)
	//{
	//	for (size_t ncol = 0; ncol < img1.cols; ncol++)
	//	{
	//		uchar val = mat_CV_8UC1.at<uchar>(nrow, ncol);
	//	}
	//}
	//��ͨ��ͼ���ȡ��ʽ
	//Mat img2 = imread(filename, IMREAD_COLOR);
	//for (size_t nrow = 0; nrow < img2.rows; nrow++)
	//{
	//	for (size_t ncol = 0; ncol < img2.cols; ncol++)
	//	{
	//		Vec3i bgr = mat_CV_8UC3.at<Vec3b>(nrow, ncol);//��Vec3bҲ��  
	//		cout << "(" << bgr.val[0] << ","
	//			<< bgr.val[1] << ","
	//			<< bgr.val[2] << ")";
	//	}
	//	cout << endl;
	//}








	// hsv_function();





	waitKey(0);
}

void colorMap() {
	Mat result = imread("yourname.jpg");
	Mat test = imread("yourname.jpg");



	Mat canny_img;
	bilateralFilter(test, canny_img, 5, 150, 150);
	bilateralFilter(canny_img, test, 5, 150, 150);

	Mat src;
	cvtColor(test, src, CV_BGR2GRAY);
	//���ߣ�Խ��Խ�֣����ǻ��д������  
	Mat imgL;
	//����������ddepth��ʾĿ��ͼ�����ȣ�ddepth=-1ʱ����ԭͼ��һ��  
	Laplacian(src, imgL, -1, 3, 1);
	imshow("Laplacian", imgL);
	//waitKey(0);

	Mat imgC;
	Canny(src, imgC, 30, 90);
	imshow("Canny", imgC);
	//waitKey(0);

	Mat imgS, imgSx, imgSy, imgS0;
	Sobel(src, imgSx, -1, 0, 1);
	Sobel(src, imgSx, -1, 1, 0);
	imgS = imgSx + imgSy;
	Sobel(src, imgS0, -1, 1, 1);
	imshow("SobeL0", imgS0);
	imshow("SobeL1", imgS);
	//waitKey(0);

	Mat imgTotal;
	imgTotal = imgC + imgS + imgL;
	//imgTotal.convertTo(imgTotal,CV_32FC1);  
	normalize(imgTotal, imgTotal, 255, 0, CV_MINMAX);
	GaussianBlur(imgTotal, imgTotal, Size(3, 3), 3);
	threshold(imgTotal, imgTotal, 100, 255, THRESH_BINARY_INV);
	imshow("Total", imgTotal);
	//waitKey(0);

	Mat imgTotalC3;
	cvtColor(imgTotal, imgTotalC3, CV_GRAY2BGR);
	bitwise_and(test, imgTotalC3, test);
	imshow("Result", test);
	waitKey(0);
	result = test;

	//Canny(result, canny_img, 70, 70 * 3, 3);
	//imshow("canny_img",canny_img);
	//cvtColor(canny_img, canny_img, CV_GRAY2BGR);
	//imshow("add", canny_img + result);
	cvtColor(result, canny_img, CV_BGR2HLS);
	imshow("canny_img", canny_img);
	for (int i = 1; i < canny_img.rows; i++) {
		for (int j = 1; j < canny_img.cols; j++) {
			Vec3b c_v = canny_img.at<Vec3b>(i, j);
			c_v.val[1] *= 2;
			canny_img.at<Vec3b>(i, j) = c_v;

		}
	}
	imshow("CV_BGR2HLS", canny_img);
	cvtColor(canny_img, canny_img, CV_HLS2BGR);
	Mat img;
	bilateralFilter(canny_img, img, 10, 50, 50, 4);
	imshow("˫���˲� CV_BGR2HLS", img);
	//@param src Source 8 - bit or floating - point, 1 - channel or 3 - channel image.
	//	@param dst Destination image of the same size and type as src .
	//	@param d Diameter of each pixel neighborhood that is used during filtering.If it is non - positive,
	//	it is computed from sigmaSpace.
	//	@param sigmaColor Filter sigma in the color space.A larger value of the parameter means that
	//	farther colors within the pixel neighborhood(see sigmaSpace) will be mixed together, resulting
	//	in larger areas of semi - equal color.
	//	@param sigmaSpace Filter sigma in the coordinate space.A larger value of the parameter means that
	//	farther pixels will influence each other as long as their colors are close enough(see sigmaColor
	//	).When d\>0, it specifies the neighborhood size regardless of sigmaSpace.Otherwise, d is
	//	proportional to sigmaSpace.
	//	@param borderType border mode used to extrapolate pixels outside of the image, see cv::BorderTypes
	bilateralFilter(result, canny_img, 10, 50, 50, 4);

	imshow("˫���˲� result", canny_img);




	//cvtColor(canny_img, canny_img, CV_BGR2HLS);
	//imshow("canny_img_2", canny_img);
	//for (int i = 1; i < canny_img.rows; i++) {
	//	for (int j = 1; j < canny_img.cols; j++) {
	//		Vec3b c_v = canny_img.at<Vec3b>(i, j);
	//		c_v.val[2] *= 2;
	//		canny_img.at<Vec3b>(i, j) = c_v;

	//	}
	//}
	//imshow("CV_BGR2HLS_2", canny_img);
	//cvtColor(canny_img, canny_img, CV_HLS2BGR);
	//
	//bilateralFilter(canny_img, img, 10, 50, 50, 4);
	//imshow("˫���˲� CV_BGR2HLS_2", img);





	Mat org = imread("ԭʼɫͼ.jpg");
	Mat filter = imread("�º���.jpg");
	resize(filter, filter, Size(800, 800));
	cout << "result.type" << result.type() << endl;
	cout << "result.channels()" << result.channels() << endl;
	cout << "result.color()" << result.at<Vec3b>(1, 1) << endl;
	cout << "filter.type" << filter.type() << endl;
	cout << "filter.channels()" << filter.channels() << endl;
	cout << "filter.color()" << filter.at<Vec3b>(1, 1) << endl;
	//A = y / 4 + (x / 32) * 64

	//	B = z / 4 + ((x % 32) / 4) * 64

	//waitKey(0);
	for (int i = 1; i < result.rows; i++) {
		for (int j = 1; j < result.cols; j++) {
			Vec3b c_v = result.at<Vec3b>(i, j);
			int res = 0;
			int mixPixel = c_v.val[0];
			int basePixel = (c_v.val[0] + c_v.val[1] + c_v.val[2]) / 3;
			res = 255 - (255 - mixPixel) * (255 - basePixel) / 255;
			c_v.val[0] = min(255, max(0, res));
			mixPixel = c_v.val[1];
			res = 255 - (255 - mixPixel) * (255 - basePixel) / 255;
			c_v.val[1] = min(255, max(0, res));
			mixPixel = c_v.val[2];
			res = 255 - (255 - mixPixel) * (255 - basePixel) / 255;
			c_v.val[2] = min(255, max(0, res));
			//int x = c_v.val[1] / 4 + (c_v.val[0] / 32) * 64;
			//int y = c_v.val[2] / 4 + (c_v.val[0] % 4) * 64;
			/*		x = x % 500;
			y = y % 500;*/
			result.at<Vec3b>(i, j) = c_v;//filter.at<Vec3b>(x, y);

		}
	}
	imshow("�˾�Ч��", result);
	waitKey(0);
}



void hsv_function() {

	imshow(windowName, img);
	//��ɫͼ��ĻҶ�ֵ��һ��  
	img.convertTo(bgr, CV_32FC3, 1.0 / 255, 0);
	//��ɫ�ռ�ת��  
	cvtColor(bgr, hsv, COLOR_BGR2HSV);
	namedWindow(dstName, WINDOW_GUI_EXPANDED);
	//����ɫ�� H  
	createTrackbar("hmin", dstName, &hmin, hmin_Max, callBack);
	createTrackbar("hmax", dstName, &hmax, hmax_Max, callBack);
	//���ڱ��Ͷ� S  
	createTrackbar("smin", dstName, &smin, smin_Max, callBack);
	createTrackbar("smax", dstName, &smax, smax_Max, callBack);
	//�������� V  
	createTrackbar("vmin", dstName, &vmin, vmin_Max, callBack);
	createTrackbar("vmax", dstName, &vmax, vmax_Max, callBack);
}
//�ص�����  
void callBack(int, void*)
{

	//���ͼ������ڴ�  
	dst = Mat::zeros(img.size(), CV_32FC3);
	//����  
	Mat mask;
	inRange(hsv, Scalar(hmin, smin / float(smin_Max), vmin / float(vmin_Max)), Scalar(hmax, smax / float(smax_Max), vmax / float(vmax_Max)), mask);
	//ֻ����  
	for (int r = 0; r < bgr.rows; r++)
	{
		for (int c = 0; c < bgr.cols; c++)
		{
			if (mask.at<uchar>(r, c) == 255)
			{
				dst.at<Vec3f>(r, c) = bgr.at<Vec3f>(r, c);
			}
		}
	}
	//���ͼ��  
	imshow(dstName, dst);
	//����ͼ��  
	dst.convertTo(dst, CV_8UC3, 255.0, 0);
	imwrite("HSV_inRange.jpg", dst);
}

Mat TransferColor(Mat src) {
	cout << "TransferColor enter" << endl;
	Mat colorBlue = imread("sky12.jpg");
	// Mat src=imread("name29.jpg");
	resize(src, src, Size(800, 800));
	resize(colorBlue, colorBlue, Size(800, 800));
	imshow("src", src);
	imshow("colorBlue", colorBlue);
	//waitKey(0);
	cvtColor(colorBlue, colorBlue, COLOR_BGR2Lab);
	cvtColor(src, src, COLOR_BGR2Lab);
	imshow("src_Lab", src);
	imshow("colorBlue_Lab", colorBlue);
	//waitKey(0);
	//Scalar src_tempVal = cv::mean(src);
	//Scalar colorBlue_tempVal = cv::mean(colorBlue);
	Mat src_mean, src_Std;
	Mat colorBlue_mean, colorBlue_Std;
	meanStdDev(src, src_mean, src_Std, noArray());
	meanStdDev(colorBlue, colorBlue_mean, colorBlue_Std, noArray());
	printMatInfo(colorBlue, "colorBlue");
	printMatInfo(src, "src");
	printMatInfo(src_mean, "src_mean");
	printMatInfo(src_Std, "src_Std");
	printMatInfo(colorBlue_mean, "colorBlue_mean");
	printMatInfo(colorBlue_Std, "colorBlue_Std");
	printMat(src_mean);
	printMat(colorBlue_mean);
	//waitKey(0);

	//��ɫӳ��
	//Size(cols, rows) opencv��api�����������ˡ��Һ�֮ǰ�Ķ�800*800�Ĵ�С
	//�У��� ���� �У���
	for (int i = 0; i < src.cols; i++) {
		for (int j = 0; j < src.rows; j++) {

			for (int channels = 0; channels < 3; channels++) {
				double pix = src.at<Vec3b>(i, j)[channels];
				//Vec3b c_v = result.at<Vec3b>(i, j);
				double cm = colorBlue_mean.at<double>(channels, 0);
				double cs = colorBlue_Std.at<double>(channels, 0);
				double sm = src_mean.at<double>(channels, 0);
				double ss = src_Std.at<double>(channels, 0);
				/*			���ȣ���Դͼ��ԭ�е����ݼ���Դͼ��ľ�ֵ

				L = l �C ml

				A = a �C ma

				B = b �C mb

				�ٽ��õ��������ݰ����������������ϵ��������ͼ���׼����ı�ֵ

				L�� = (nl�� / nl)* L

				A�� = (na�� / na)* A

				B�� = (nb�� / nb)* B

				���õ���l����a����b���ֱ����Ŀ��ͼ������ͨ���ľ�ֵ���õ���������

				L = L�� + ml��

				A = A�� + ma��

				B = B�� + mb��

				�����õ�Ŀ��ͼ����Դͼ��֮������ع�ϵ���

				L = (nl�� / nl)* (l �C ml) + ml��

				A = (na�� / na)* (a �C ma) + ma��

				B = (nb�� / nb)* (b �C mb) + mb��*/

				pix = (pix - sm)*(cs / ss) + cm;

				//pix = (pix - colorBlue_mean.at<double>(0, channels))*
				//	(src_Std.at<double>(0, channels) / colorBlue_Std.at<double>(0, channels))
				//	+ src_mean.at<double>(0, channels);
				if (pix < 0) {
					pix = 0;
				}
				if (pix > 255) {
					pix = 255;
				}
				src.at<Vec3b>(i, j)[channels] = pix;



			}
		}
	}
	imshow("��ɫǨ��", src);
	cvtColor(src, src, COLOR_Lab2BGR);
	imshow("COLOR_Lab2BGR", src);
	waitKey(0);
	return src;



	//src_mean:
	//	img.type() : 6
	//		img.size() : [1 x 3]
	//		img.channels() : 1
	//		img.depth() : 6
	//
	//
	//		src_Std :
	//		img.type() : 6
	//		img.size() : [1 x 3]
	//		img.channels() : 1
	//		img.depth() : 6
	//
	//
	//		colorBlue_mean :
	//		img.type() : 6
	//		img.size() : [1 x 3]
	//		img.channels() : 1
	//		img.depth() : 6
	//
	//
	//		colorBlue_Std :
	//		img.type() : 6
	//		img.size() : [1 x 3]
	//		img.channels() : 1
	//		img.depth() : 6








}


void printMatInfo(Mat img, string name) {
	cout << endl;
	cout << name << " : " << endl;
	cout << "img.type() : ";
	cout << img.type() << endl;
	cout << "img.size() : ";
	cout << img.size() << endl;
	cout << "img.channels() : ";
	cout << img.channels() << endl;
	cout << "img.depth() : ";
	cout << img.depth() << endl;
	// depth ��������ÿһ��������ÿһ��ͨ���ľ��ȣ�����������ͼ���ͨ�����޹أ�depth��ֵԽ�󣬾���Խ�ߡ���                 Opencv�У�Mat.depth()�õ�����һ��0~6�����֣��ֱ����ͬ��λ������Ӧ��ϵ���£�                            
	// enum{CV_8U=0,CV_8S=1,CV_16U=2,CV_16S=3,CV_32S=4,CV_32F=5,CV_64F=6}          

	// ����U��unsigned����˼��S��ʾsigned��Ҳ�����з��ź��޷�������

	// �������Ϊ������ÿ�Ŵ�����˯�����ˣ�������������ж��ٴ����޹�ϵ��

	cout << endl;
}


void VS_Style() {
	Mat src;

	Mat kernel(5, 5, CV_8U);
	//excellent name6 and sky1 
	//wrong: name24,12
	//bad: 9,7
	//excellent : name 21,20,18,8,5
	src = imread("yourname1.jpg");
	//none:4
	//excellent �� sky6,5
	Mat sky = imread("sky1.jpg");

	imshow("ԭʼͼ", src);
	resize(src, src, Size(800, 800), 1, 1);
	Mat img, img_b, img_r;
	img_r = TransferColor(src);
	// img_r = Gamma(src);


	//img_r = src;

	Laplacian(src, img_b, -1, 3, 1, 0, 4);

	img = img_b + img_r;
	imshow("img_b+ img_r", img);
	imshow("img_b", img_b);
	//morphologyEx(img, img, MORPH_OPEN, kernel, Point(-1, -1), 1);
	//gamma�����Ժ�ϸ�ھͻ���ʧӰ�죬����ı�Ե���� 	
	//  img=Gamma(src);

	imshow("800X800ͼ", img);
	waitKey(0);
	cvtColor(img, img, COLOR_BGR2HSV);

	imshow("COLOR_BGR2HSVͼ", img);

	Mat RGB_channels[3];
	split(img, RGB_channels);
	imshow("H", RGB_channels[0]);
	imshow("S", RGB_channels[1]);
	imshow("V", RGB_channels[2]);



	equalizeHist(RGB_channels[2], RGB_channels[2]);
	merge(RGB_channels, 3, img);
	imshow("hsv�ϳ�ͼ", img);
	//blue
	inRange(img, Scalar(100, 43, 46), Scalar(124, 255, 255), img);
	//white
	//inRange(img, Scalar(0, 0, 221), Scalar(360,30,255), img);
	imshow("�������", img);
	medianBlur(img, img, 9);
	imshow("������գ���ֵ�˲�", img);


	morphologyEx(img, img, MORPH_OPEN, kernel, Point(-1, -1), 10);
	medianBlur(img, img, 9);
	imshow("�����", img);
	// waitKey(0);

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	double maxArea = 0;
	double maxLength = 0;
	int maxIndex = 0;
	findContours(img, contours, hierarchy, RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	imshow("img", img);

	Rect boundRect;
	Mat Wang_Rect(img.size(), src.type(), cv::Scalar(0));


	waitKey(0);


	for (int i = 0; i < contours.size(); i++) {
		//����ȷ���������ܳ������ȷ���Ƿ�պϡ���������ѡ�����Ҫ�ľ���ͼ�γ�����ȱһ����
		//Ŀǰ��û�кܺü�⣬����ֱ����ȡ���Σ�ֻ�ܽ��ơ�
		//������Ȼ���ڲ�����
		if (maxLength < arcLength(contours[i], true) && maxArea<contourArea(contours[i])) {
			maxLength = arcLength(contours[i], true);
			maxArea = contourArea(contours[i]);
			maxIndex = i;
		}
		// drawContours(Wang_mark, contours, i, Scalar::all(i + 1), 1, 8, hierarchy);
		//drawContours(Wang_Rect, contours, i, Scalar(255), 1, 8, hierarchy);
		//cout << arcLength(contours[i], true) << endl;
		//drawContours(Wang_Mat, contours, i, Scalar::all(i + 1), 1, 8, hierarchy);//ΪʲôҪ��������
	}

	boundRect = boundingRect(Mat(contours[maxIndex]));
	rectangle(Wang_Rect, boundRect, Scalar(255, 255, 255), -1, 8, 0);

	imshow("Wang_Rect", Wang_Rect);

	int x = boundRect.x;
	int y = boundRect.y;
	int height = boundRect.height;
	int width = boundRect.width;


	Point 	p((x + width) / 2, (y + height) / 2);



	Mat src_clone = src;
	resize(sky, sky, Size(800, 800));
	resize(src_clone, src_clone, Size(800, 800));
	cout << "sky.type" << sky.type() << endl;
	cout << "src_clone.type" << src_clone.type() << endl;
	imshow("src_clone", src_clone);
	imshow("sky", sky);
	imshow("src_clone_sky_img", img);
	waitKey(0);
	//cvtColor
	img = Wang_Rect;


	Mat result(sky.size(), sky.type(), cv::Scalar(0));
	printMatInfo(sky, "sky");
	printMatInfo(src_clone, "src_clone");
	printMatInfo(img, "img");
	seamlessClone(sky, src_clone, img, p, result, NORMAL_CLONE);
	imshow("result", result);

	imwrite("yourname.jpg", result);

	Mat org = imread("ԭʼɫͼ.jpg");
	Mat filter = imread("�º���.jpg");
	resize(filter, filter, Size(800, 800));


	for (int i = 1; i < result.rows; i++) {
		for (int j = 1; j < result.cols; j++) {
			Vec3b c_v = result.at<Vec3b>(i, j);
			int x = c_v.val[1] / 4 + (c_v.val[0] / 32) * 64;
			int y = c_v.val[2] / 4 + (c_v.val[0] % 4) * 64;
			result.at<Vec3b>(i, j) = filter.at<Vec3b>(x, y);
		}
	}
	imshow("�˾�Ч��", result);






	waitKey(0);





	result = imread("yourname.jpg");
	Mat test = imread("yourname.jpg");



	Mat canny_img;
	bilateralFilter(test, canny_img, 5, 150, 150);
	bilateralFilter(canny_img, test, 5, 150, 150);

	src;
	cvtColor(test, src, CV_BGR2GRAY);

	Mat imgL;

	Laplacian(src, imgL, -1, 3, 1);
	imshow("Laplacian", imgL);


	Mat imgC;
	Canny(src, imgC, 30, 90);
	imshow("Canny", imgC);


	Mat imgS, imgSx, imgSy, imgS0;
	Sobel(src, imgSx, -1, 0, 1);
	Sobel(src, imgSx, -1, 1, 0);
	imgS = imgSx + imgSy;
	Sobel(src, imgS0, -1, 1, 1);
	imshow("SobeL0", imgS0);
	imshow("SobeL1", imgS);

	Mat imgTotal;
	imgTotal = imgC + imgS + imgL;
	normalize(imgTotal, imgTotal, 255, 0, CV_MINMAX);
	GaussianBlur(imgTotal, imgTotal, Size(3, 3), 3);
	threshold(imgTotal, imgTotal, 100, 255, THRESH_BINARY_INV);
	imshow("Total", imgTotal);

	Mat imgTotalC3;
	cvtColor(imgTotal, imgTotalC3, CV_GRAY2BGR);
	bitwise_and(test, imgTotalC3, test);
	imshow("Result", test);



	waitKey(0);



	result = test;
	test = Gamma(test);
	imshow("Gamma Result", test);

	cvtColor(result, canny_img, CV_BGR2HLS);
	imshow("canny_img", canny_img);
	for (int i = 1; i < canny_img.rows; i++) {
		for (int j = 1; j < canny_img.cols; j++) {
			Vec3b c_v = canny_img.at<Vec3b>(i, j);
			c_v.val[1] *= 2;
			canny_img.at<Vec3b>(i, j) = c_v;

		}
	}
	imshow("CV_BGR2HLS", canny_img);
	cvtColor(canny_img, canny_img, CV_HLS2BGR);
	img;
	bilateralFilter(canny_img, img, 10, 50, 50, 4);
	imshow("˫���˲� CV_BGR2HLS", img);
	bilateralFilter(result, canny_img, 10, 50, 50, 4);

	imshow("˫���˲� result", canny_img);
	canny_img = Gamma(canny_img);
	imshow("Gamma", canny_img);



	//  canny_img=IncreaseColor(canny_img,100);
	//  imshow("IncreaseColor result", canny_img);

	for (int i = 1; i < result.rows; i++) {
		for (int j = 1; j < result.cols; j++) {
			Vec3b c_v = result.at<Vec3b>(i, j);
			int res = 0;
			int mixPixel = c_v.val[0];
			int basePixel = (c_v.val[0] + c_v.val[1] + c_v.val[2]) / 3;
			res = 255 - (255 - mixPixel) * (255 - basePixel) / 255;
			c_v.val[0] = min(255, max(0, res));
			mixPixel = c_v.val[1];
			res = 255 - (255 - mixPixel) * (255 - basePixel) / 255;
			c_v.val[1] = min(255, max(0, res));
			mixPixel = c_v.val[2];
			res = 255 - (255 - mixPixel) * (255 - basePixel) / 255;
			c_v.val[2] = min(255, max(0, res));
			//int x = c_v.val[1] / 4 + (c_v.val[0] / 32) * 64;
			//int y = c_v.val[2] / 4 + (c_v.val[0] % 4) * 64;
			/*		x = x % 500;
			y = y % 500;*/
			result.at<Vec3b>(i, j) = c_v;//filter.at<Vec3b>(x, y);

		}
	}
	imshow("�˾�Ч��", result);
	waitKey(0);




}





Mat IncreaseColor(Mat img, double Value) {
	imshow("img", img);
	cvtColor(img, img, COLOR_BGR2HSV);
	//cvtColor(img, img, COLOR_HSV2BGR);
	imshow("img COLOR_BGR2HSV", img);
	double H = 360;
	double S = 2;
	double L = 2;
	//��һ������
	//img.convertTo(img,CV_32FC3,1.0/255,0);

	printMatInfo(img, "img");
	//0<H<360,0<L<1,0<S<1
	imshow("before color enhance", img);
	for (int i = 0; i < img.cols; i++) {
		for (int j = 0; j < img.rows; j++) {
			//Vec3f ����Ӧ���� Vec3b
			//��һ����Ҫ���Vec3f
			Vec3b hls = img.at<Vec3b>(j, i);

			/*hls = Vec3f(hls[0],
			(1 + L / Value)*hls[1] > 1 ? 1 : (1 + L / Value)*hls[1],
			(1 + S / Value)*hls[2] > 1 ? 1 : (1 + S / Value)*hls[2]);*/
			//hls[0] += 0.3;
			hls[1] += 50;
			hls[2] += 20;
			if (hls[1] > 255) {
				hls[1] -= 50;
			}
			if (hls[2] > 255) {
				hls[2] -= 50;
			}

			img.at<Vec3b>(j, i) = hls;

		}
	}
	cvtColor(img, img, COLOR_HSV2BGR);
	imshow("color enhance", img);
	waitKey(0);
	return img;
}

Mat Gamma(Mat image) {

	Mat imageGamma(image.size(), CV_32FC3);
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			//     imageGamma.at<Vec3f>(i, j)[0] = (image.at<Vec3b>(i, j)[0])*(image.at<Vec3b>(i, j)[0])*(image.at<Vec3b>(i, j)[0]);  
			//     imageGamma.at<Vec3f>(i, j)[1] = (image.at<Vec3b>(i, j)[1])*(image.at<Vec3b>(i, j)[1])*(image.at<Vec3b>(i, j)[1]);  
			//     imageGamma.at<Vec3f>(i, j)[2] = (image.at<Vec3b>(i, j)[2])*(image.at<Vec3b>(i, j)[2])*(image.at<Vec3b>(i, j)[2]);  
			// 
			imageGamma.at<Vec3f>(i, j)[0] = pow(image.at<Vec3b>(i, j)[0], 0.5);
			imageGamma.at<Vec3f>(i, j)[1] = pow(image.at<Vec3b>(i, j)[1], 0.5);
			imageGamma.at<Vec3f>(i, j)[2] = pow(image.at<Vec3b>(i, j)[2], 0.5);
		}
	}
	//��һ����0~255    
	normalize(imageGamma, imageGamma, 0, 255, CV_MINMAX);
	//ת����8bitͼ����ʾ    
	convertScaleAbs(imageGamma, imageGamma);
	imshow("ԭͼ", image);
	imshow("٤��任ͼ����ǿЧ��", imageGamma);
	waitKey();
	return imageGamma;
}