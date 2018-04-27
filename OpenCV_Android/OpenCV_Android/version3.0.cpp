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




//色相  
int hmin = 0;
int hmin_Max = 360;
int hmax = 360;
int hmax_Max = 360;
//饱和度  
int smin = 0;
int smin_Max = 255;
int smax = 255;
int smax_Max = 255;
//亮度  
int vmin = 106;
int vmin_Max = 255;
int vmax = 250;
int vmax_Max = 255;
//显示原图的窗口  
string windowName = "src";
//输出图像的显示窗口  
string dstName = "dst";

//输入图像  
Mat img = imread("name13.jpg");
//灰度值归一化  
Mat bgr;
//HSV图像  
Mat hsv;
//输出图像  
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
//打印Mat的详细信息，长和宽
void printMat(Mat img) {
	cout << img << endl;
}
void Rotation(Mat img) {
	Mat srcImg = img;
	imshow("原始图", srcImg);
	Mat gray, binImg;
	//灰度化
	cvtColor(srcImg, gray, COLOR_RGB2GRAY);
	imshow("灰度图", gray);
	//二值化
	threshold(gray, binImg, 100, 200, CV_THRESH_BINARY);
	imshow("二值化", binImg);
	vector<vector<Point> > contours;
	vector<Rect> boundRect(contours.size());
	//注意第5个参数为CV_RETR_EXTERNAL，只检索外框  
	findContours(binImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); //找轮廓
	cout << contours.size() << endl;
	for (int i = 0; i < contours.size(); i++)
	{
		//需要获取的坐标  
		CvPoint2D32f rectpoint[4];
		CvBox2D rect = minAreaRect(Mat(contours[i]));

		cvBoxPoints(rect, rectpoint); //获取4个顶点坐标  
									  //与水平线的角度  
		float angle = rect.angle;
		cout << "angle : " << angle << endl;

		int line1 = sqrt((rectpoint[1].y - rectpoint[0].y)*(rectpoint[1].y - rectpoint[0].y) + (rectpoint[1].x - rectpoint[0].x)*(rectpoint[1].x - rectpoint[0].x));
		int line2 = sqrt((rectpoint[3].y - rectpoint[0].y)*(rectpoint[3].y - rectpoint[0].y) + (rectpoint[3].x - rectpoint[0].x)*(rectpoint[3].x - rectpoint[0].x));
		//rectangle(binImg, rectpoint[0], rectpoint[3], Scalar(255), 2);
		//面积太小的直接pass
		if (line1 * line2 < 600)
		{
			continue;
		}

		//为了让正方形横着放，所以旋转角度是不一样的。竖放的，给他加90度，翻过来  
		// if (line1 > line2)
		// {
		// 	angle = 90 + angle;
		// }

		//新建一个感兴趣的区域图，大小跟原图一样大  
		Mat RoiSrcImg(srcImg.rows, srcImg.cols, CV_8UC3); //注意这里必须选CV_8UC3
		RoiSrcImg.setTo(0); //颜色都设置为黑色  
							//imshow("新建的ROI", RoiSrcImg);
							//对得到的轮廓填充一下  
		drawContours(binImg, contours, -1, Scalar(255), CV_FILLED);

		//抠图到RoiSrcImg
		srcImg.copyTo(RoiSrcImg, binImg);


		//再显示一下看看，除了感兴趣的区域，其他部分都是黑色的了  
		namedWindow("RoiSrcImg", 1);
		imshow("RoiSrcImg", RoiSrcImg);

		//创建一个旋转后的图像  
		Mat RatationedImg(RoiSrcImg.rows, RoiSrcImg.cols, CV_8UC1);
		RatationedImg.setTo(0);
		//对RoiSrcImg进行旋转  
		Point2f center = rect.center;  //中心点  
		Mat M2 = getRotationMatrix2D(center, angle, 1);//计算旋转加缩放的变换矩阵 
		warpAffine(RoiSrcImg, RatationedImg, M2, RoiSrcImg.size(), 1, 0, Scalar(0));//仿射变换 
		imshow("旋转之后", RatationedImg);
		imwrite("r.jpg", RatationedImg); //将矫正后的图片保存下来

		vector<vector<Point> > contours2;
		Mat raw = imread("r.jpg");
		Mat SecondFindImg;
		//SecondFindImg.setTo(0);
		cvtColor(raw, SecondFindImg, COLOR_BGR2GRAY);  //灰度化  
		threshold(SecondFindImg, SecondFindImg, 80, 200, CV_THRESH_BINARY);
		findContours(SecondFindImg, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
		//cout << "sec contour:" << contours2.size() << endl;

		for (int j = 0; j < contours2.size(); j++)
		{
			//这时候其实就是一个长方形了，所以获取rect  
			Rect rect = boundingRect(Mat(contours2[j]));
			//面积太小的轮廓直接pass,通过设置过滤面积大小，可以保证只拿到外框
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
	//加入闭运算可以有效的处理边界为连接的问题
	morphologyEx(imageGray, imageGray, MORPH_CLOSE, element);

	// 	MORPH_OPEN： 开运算 
	// MORPH_CLOSE ：闭运算 
	// MORPH_GRADIENT： 形态学梯度 
	// MORPH_TOPHAT：顶帽运算 
	// MORPH_BLACKHAT： 黑帽运算 
	// MORPH_ERODE ：腐蚀运算 
	// MORPH_DILATE ：膨胀运算 
	// MORPH_HITMISS: 击中击不中运算(只支持CV_8UC1类型的二值图像)

	imshow("开运算", imageGray);
	Canny(imageGray, imageGray, 50, 200, 5);//这里参数非常重要。决定后面轮廓的效果

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
		//长度确定最大矩形周长，面积确定是否闭合。这样才能选择出想要的矩阵图形出来。缺一不可
		//目前并没有很好检测，可以直接提取矩形，只能近似。
		//所以仍然存在不完美
		if (maxLength < arcLength(contours[i], true) && maxArea<contourArea(contours[i])) {
			maxLength = arcLength(contours[i], true);
			maxArea = contourArea(contours[i]);
			maxIndex = i;
		}
		drawContours(Wang_mark, contours, i, Scalar::all(i + 1), 1, 8, hierarchy);
		drawContours(Wang_Contours, contours, i, Scalar(255), 1, 8, hierarchy);
		//cout << arcLength(contours[i], true) << endl;
		//drawContours(Wang_Mat, contours, i, Scalar::all(i + 1), 1, 8, hierarchy);//为什么要这样画？
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
	//	//长度确定最大矩形周长，面积确定是否闭合。这样才能选择出想要的矩阵图形出来。缺一不可
	//	//目前并没有很好检测，可以直接提取矩形，只能近似。
	//	//所以仍然存在不完美
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
	//	//drawContours(Wang_Mat, contours, i, Scalar::all(i + 1), 1, 8, hierarchy);//为什么要这样画？
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
	drawContours(Wang_8UC1, contours, maxIndex, Scalar(255, 255, 255), CV_FILLED);//填充遮罩层
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
	//		/*其中<>内应填入m0元素的数据类型，uchar对应的是CV_8U，char对应的是CV_8S，int对应的是CV_32S，float对应的是CV_32F，double对应的是CV_64F。
	//			若m0是多通道矩阵，则数据类型应为Vec3b, c为当前处理的通道序号。i，j，c都是从零开始的。*/
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


	//轮廓中的内容提取，足足浪费我一个下午的时间。不管用循环还是copyto什么的，还有图像融合之类的。都有很大问题。
	//还是用第三方clone，再来循环复制。
	Wang_Output = Wang_8UC1.clone();
	cout << Wang_8UC1.size() << endl << Wang_Output.size() << endl;
	// src.copyTo(Wang_Output, Wang_8UC1);
	imshow("Wang_Output", Wang_Output);
	for (int i = 0; i<Wang_Output.rows; i++)
	{
		for (int j = 0; j<Wang_Output.cols; j++)
		{
			/*其中<>内应填入m0元素的数据类型，uchar对应的是CV_8U，char对应的是CV_8S，int对应的是CV_32S，float对应的是CV_32F，double对应的是CV_64F。
			若m0是多通道矩阵，则数据类型应为Vec3b, c为当前处理的通道序号。i，j，c都是从零开始的。*/
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
	//加入闭运算可以有效的处理边界为连接的问题
	morphologyEx(imageGray, imageGray, MORPH_CLOSE, element);
	imshow("增强图像", imageGray);
	Canny(imageGray, imageGray, 100, 200, 5);//这里参数非常重要。决定后面轮廓的效果
											 //Mat grad_x, abs_grad_x;
											 //Mat grad_y, abs_grad_y;
											 //Sobel(imageGray, grad_x, CV_8S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
											 //Sobel(imageGray, grad_y, CV_8S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
											 //convertScaleAbs(grad_x, abs_grad_x);
											 //convertScaleAbs(grad_y, abs_grad_y);
											 //addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, imageGray);
											 //imshow("【效果图】整体方向Sobel", imageGray);
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
											 //imshow("增强图像", imageGray);


	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(imageGray, contours, hierarchy, RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point());
	cout << "imageGray type : " << imageGray.type() << endl;
	Mat imageContours = Mat::zeros(src.size(), CV_8UC1);  //轮廓


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
	//	//对marks进行标记，对不同区域的轮廓进行编号，相当于设置注水点，有多少轮廓，就有多少注水点  
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
		//drawContours(Wang_Mat, contours, i, Scalar::all(i + 1), 1, 8, hierarchy);//为什么要这样画？


	}
	cout << arcLength(contours[maxIndex], true) << endl;
	/*drawContours(mark1, contours, maxIndex, Scalar::all(compCount + 1), 1, 8, hierarchy);*/
	drawContours(imageContours, contours, maxIndex, Scalar(255), 1, 8, hierarchy);
	drawContours(mark1, contours, maxIndex, Scalar::all(maxIndex + 1), 1, 8, hierarchy);
	drawContours(Wang_Mat, contours, maxIndex, Scalar::all(maxIndex + 1), 1, 8, hierarchy);


	Mat marksShows;
	convertScaleAbs(mark1, marksShows);//，使用线性变换转换输入数组元素成8位无符号整型。
	imshow("mark1", mark1);
	imshow("marksShow", marksShows);

	imshow("轮廓", imageContours);

	//cvHoughLines2(imageContours,)
	HoughLines(imageContours, lines, (double)g_CannyThred, (double)((g_CannyThred + 1) * (2 + g_CannyP / 100.0)), 3);

	//imshow("霍夫变换", imageContours);

	watershed(src, mark1);
	imshow("Aftermark1", mark1);
	Mat Wang_32S;
	convertScaleAbs(Wang_Mat, Wang_8UC1);
	imshow("before Watershed Wang_8UC1", Wang_8UC1);

	findContours(Wang_8UC1, contours, hierarchy, -1, CV_CHAIN_APPROX_NONE, Point());//输入是8位单通道的图像
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
		cout << "轮廓  " << i << " : " << arcLength(contours[i], true) << endl;

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
	//	二维点集，点的序列或向量(CvMat)
	//	update
	//	更新标识。下面是轮廓类型和标识的一些可能组合 :
	//update = 0, contour ~CvContour* : 不计算矩形边界，但直接由轮廓头的 rect 域得到。
	//	update = 1, contour ~CvContour* : 计算矩形边界，而且将结果写入到轮廓头的 rect 域中 header.
	//	update = 0, contour ~CvSeq* or CvMat* : 计算并返回边界矩形
	//	update = 1, contour ~CvSeq* or CvMat* : 产生运行错误 （runtime error is raised）
	//	函数 cvBoundingRect 返回二维点集的最外面 （up - right）矩形边界。


	watershed(src, Wang_Mat);//32位，单通道输出的图像
	imshow("AfteimageWang_Mat", Wang_Mat);


	//convertScaleAbs(Wang_Mat, Wang_8UC1);
	//imshow("After Watershed Wang_8UC1", Wang_8UC1);

	//我们再来看一下分水岭算法之后的矩阵marks里是什么东西  

	//findContours(mark1, contours, hierarchy, RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point());
	//imshow("again Mark1", mark1);


	Mat afterWatershed;
	convertScaleAbs(mark1, afterWatershed);
	imshow("After Watershed", afterWatershed);

	//printMatValue(mark1);





	//对每一个区域进行颜色填充  
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

	//分割并填充颜色的结果跟原始图像融合  
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


	//第二次轮廓的选择，应该基于上一次分水岭之后或者之前。两者都有一定的优势。
	//所以还要找折中的算法才行
	findContours(imageContours, contours, hierarchy, -1, CV_CHAIN_APPROX_NONE, Point());
	//_levels:
	//3，所有外轮廓及包含的内轮廓及里面的内轮廓
	//	2：所有外轮廓及包含的内轮廓
	//	1:所有外轮廓
	//	0，第一个外轮廓
	//	- 1：第一个外轮廓及包含的内轮廓
	//	- 2：第一个外轮廓及包含的内轮廓及里面的内轮廓
	//findContours(imageGray, contours, hierarchy, RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point());
	cout << "找第二次轮廓";
	max = 0;
	maxIndex = 0;
	Mat twice_Contours = Mat::zeros(PerspectiveImage.size(), CV_8UC1);
	for (int i = 0; i < contours.size(); i++) {
		if (max < contourArea(contours[i])) {
			max = contourArea(contours[i]);
			maxIndex = i;
		}
		drawContours(twice_Contours, contours, i, Scalar(255), 1, 8, hierarchy);
		cout << "轮廓  " << i << " : " << contourArea(contours[i]) << endl;

	}
	//printMatValue(twice_Contours);
	//imshow("twice", twice_Contours);
	//drawContours(twice_Contours, contours, maxIndex, Scalar(255), 1, 8, hierarchy);
	imshow("twice", twice_Contours);


	waitKey(0);

	//用来画矩阵
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


	//imshow("灰度化",src);
	//waitKey(0);
	//adaptiveThreshold(src, src, 256, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 41, 0);

	threshold(src, src, 0, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);
	element = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
	morphologyEx(src, src, MORPH_OPEN, element, Point(-1, -1), 2);
	dilate(src, src, element, Point(-1, -1), 3);
	//watershed(src, imglabels);
	/*WatershedGray()*/
	//printMatValue(src);
	imshow("阈值化", src);
	imshow("结果图", imglabels);
	waitKey(0);
}
//打印Mat矩阵里面的内容
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
	value = value % 255;  //生成0~255的随机数  
	RNG rng;
	int aa = rng.uniform(0, value);
	int bb = rng.uniform(0, value);
	int cc = rng.uniform(0, value);
	return Vec3b(aa, bb, cc);
}

//霍夫变换
void Hough(Mat srcImage) {
	int g_CannyThred = 150, g_CannyP = 0, g_CannySize = 0, g_HoughThred = 100, g_HoughThick = 0;
	int g_Blue = 255, g_Green = 255, g_Red = 0;
	int g_nWay = 0, g_nValue = 1000;

	imshow("【原图】", srcImage);

	Mat grayImage;
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);

	Mat cannyImage;
	vector<Vec2f> lines;
	Point point1, point2;

	namedWindow("【滚动条窗口】", 0);
	createTrackbar("CannyThred", "【滚动条窗口】", &g_CannyThred, 255, 0);
	createTrackbar("P:", "【滚动条窗口】", &g_CannyP, 100, 0);
	createTrackbar("Size", "【滚动条窗口】", &g_CannySize, 20, 0);
	createTrackbar("HThred", "【滚动条窗口】", &g_HoughThred, 255, 0);
	createTrackbar("Blue", "【滚动条窗口】", &g_Blue, 255, 0);
	createTrackbar("Green", "【滚动条窗口】", &g_Green, 255, 0);
	createTrackbar("Red", "【滚动条窗口】", &g_Red, 255, 0);
	createTrackbar("Bgr/Gray", "【滚动条窗口】", &g_nWay, 1, 0);
	createTrackbar("Thick", "【滚动条窗口】", &g_HoughThick, 100, 0);
	createTrackbar("Value", "【滚动条窗口】", &g_nValue, 2000, 0);

	char key;
	Mat CannyBgrImage;
	Mat dstImage;
	while (1)
	{
		Canny(srcImage, cannyImage, (double)g_CannyThred, (double)((g_CannyThred + 1) * (2 + g_CannyP / 100.0)), 3);
		HoughLines(cannyImage, lines, 1, CV_PI / 180, g_HoughThred + 1, 0, 0);

		cvtColor(cannyImage, CannyBgrImage, CV_GRAY2BGR);

		//显示线段  
		for (size_t i = 0; i < lines.size(); i++)
		{
			//从容器中得到 长度值和角度值  
			//以下语句还可以写成：  
			/*Vec2f vec = Vec2f(lines[i][0], lines[i][1]);
			float rho = vec[0], theta = vec[1];*/
			float rho = lines[i][0], theta = lines[i][1];
			//首先得到原点(0, 0)到该直线的垂线 与 该直线的交点的坐标  
			double x0 = rho * cos(theta), y0 = rho * sin(theta);
			//取该交点延拓的点  再连线  
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

		imshow("【处理后】", dstImage);

		key = waitKey(1);
		if (key == 27)
			break;
	}
}
//void cv::adaptiveThreshold(
//	cv::InputArray src, // 输入图像  
//	cv::OutputArray dst, // 输出图像  
//	double maxValue, // 向上最大值  
//	int adaptiveMethod, // 自适应方法，平均或高斯  
//	int thresholdType // 阈值化类型  
//	int blockSize, // 块大小  
//	double C // 常量  
//);


//resize(img, result, result.size(), 1, 1);
//src：输入，原图像，即待改变大小的图像；
//
//dst：输出，改变大小之后的图像，这个图像和原图像具有相同的内容，只是大小和原图像不一样而已；
//
//dsize：输出图像的大小。如果这个参数不为0，那么就代表将原图像缩放到这个Size(width，height)指定的大小；如果这个参数为0，那么原图像缩放之后的大小就要通过下面的公式来计算：
//
//dsize = Size(round(fx*src.cols), round(fy*src.rows))
//
//其中，fx和fy就是下面要说的两个参数，是图像width方向和height方向的缩放比例。
//
//fx：width方向的缩放比例，如果它是0，那么它就会按照(double)dsize.width / src.cols来计算；
//
//fy：height方向的缩放比例，如果它是0，那么它就会按照(double)dsize.height / src.rows来计算；
//
//interpolation：这个是指定插值的方式，图像缩放之后，肯定像素要进行重新计算的，就靠这个参数来指定重新计算像素的方式，有以下几种：
//
//
//INTER_NEAREST - 最邻近插值
//INTER_LINEAR - 双线性插值，如果最后一个参数你不指定，默认使用这种方法
//INTER_AREA - resampling using pixel area relation.It may be a preferred method for image decimation, as it gives moire’ - free results.But when the image is zoomed, it is similar to the INTER_NEAREST method.
//INTER_CUBIC - 4x4像素邻域内的双立方插值
//INTER_LANCZOS4 - 8x8像素邻域内的Lanczos插值
//
//
//使用注意事项：
//
//1. dsize和fx / fy不能同时为0，要么你就指定好dsize的值，让fx和fy空置直接使用默认值，就像
//
//resize(img, imgDst, Size(30, 30));
//
//要么你就让dsize为0，指定好fx和fy的值，比如fx = fy = 0.5，那么就相当于把原图两个方向缩小一倍！
//
//
//
//2. 至于最后的插值方法，正常情况下使用默认的双线性插值就够用了。
//
//几种常用方法的效率是：最邻近插值>双线性插值>双立方插值>Lanczos插值；
//
//但是效率和效果成反比，所以根据自己的情况酌情使用。
//
//
//
//3. 正常情况下，在使用之前dst图像的大小和类型都是不知道的，类型从src图像继承而来，大小也是从原图像根据参数计算出来。但是如果你事先已经指定好dst图像的大小，那么你可以通过下面这种方式来调用函数





//findContours函数介绍
//第二个参数：contours，定义为“vector<vector<Point>> contours”，是一个向量，并且是一个双重向量，向量
//
//内每个元素保存了一组由连续的Point点构成的点的集合的向量，每一组Point点集就是一个轮廓。
//
//有多少轮廓，向量contours就有多少元素。
//
//
//
//第三个参数：hierarchy，定义为“vector<Vec4i> hierarchy”，先来看一下Vec4i的定义：
//
//typedef    Vec<int, 4>   Vec4i;
//
//Vec4i是Vec<int, 4>的别名，定义了一个“向量内每一个元素包含了4个int型变量”的向量。
//
//所以从定义上看，hierarchy也是一个向量，向量内每个元素保存了一个包含4个int整型的数组。
//
//向量hiararchy内的元素和轮廓向量contours内的元素是一一对应的，向量的容量相同。
//
//hierarchy向量内每一个元素的4个int型变量——hierarchy[i][0] ~hierarchy[i][3]，分别表示第
//
//i个轮廓的后一个轮廓、前一个轮廓、父轮廓、内嵌轮廓的索引编号。如果当前轮廓没有对应的后一个
//
//轮廓、前一个轮廓、父轮廓或内嵌轮廓的话，则hierarchy[i][0] ~hierarchy[i][3]的相应位被设置为
//
//默认值 - 1。
//
//
//
//第四个参数：int型的mode，定义轮廓的检索模式：
//
//
//
//取值一：CV_RETR_EXTERNAL只检测最外围轮廓，包含在外围轮廓内的内围轮廓被忽略
//
//
//
//取值二：CV_RETR_LIST   检测所有的轮廓，包括内围、外围轮廓，但是检测到的轮廓不建立等级关
//
//系，彼此之间独立，没有等级关系，这就意味着这个检索模式下不存在父轮廓或内嵌轮廓，
//
//所以hierarchy向量内所有元素的第3、第4个分量都会被置为 - 1，具体下文会讲到
//
//
//
//取值三：CV_RETR_CCOMP  检测所有的轮廓，但所有轮廓只建立两个等级关系，外围为顶层，若外围
//
//内的内围轮廓还包含了其他的轮廓信息，则内围内的所有轮廓均归属于顶层
//
//
//
//取值四：CV_RETR_TREE， 检测所有轮廓，所有轮廓建立一个等级树结构。外层轮廓包含内层轮廓，内
//
//层轮廓还可以继续包含内嵌轮廓。
//
//
//
//第五个参数：int型的method，定义轮廓的近似方法：
//
//
//
//取值一：CV_CHAIN_APPROX_NONE 保存物体边界上所有连续的轮廓点到contours向量内
//
//
//
//取值二：CV_CHAIN_APPROX_SIMPLE 仅保存轮廓的拐点信息，把所有轮廓拐点处的点保存入contours
//
//向量内，拐点与拐点之间直线段上的信息点不予保留
//
//
//
//取值三和四：CV_CHAIN_APPROX_TC89_L1，CV_CHAIN_APPROX_TC89_KCOS使用teh - Chinl chain 近
//
//似算法
//
//
//
//第六个参数：Point偏移量，所有的轮廓信息相对于原始图像对应点的偏移量，相当于在每一个检测出的轮廓点上加
//
//上该偏移量，并且Point还可以是负值！
//void findContours//提取轮廓，用于提取图像的轮廓
//(
//	InputOutputArray image,//输入图像，必须是8位单通道图像，并且应该转化成二值的
//	OutputArrayOfArrays contours,//检测到的轮廓，每个轮廓被表示成一个point向量
//	OutputArray hierarchy,//可选的输出向量，包含图像的拓扑信息。其中元素的个数和检测到的轮廓的数量相等
//	int mode,//说明需要的轮廓类型和希望的返回值方式
//	int method,//轮廓近似方法
//	Point offset = Point()
//)




//void drawContours//绘制轮廓，用于绘制找到的图像轮廓
//(
//	InputOutputArray image,//要绘制轮廓的图像
//	InputArrayOfArrays contours,//所有输入的轮廓，每个轮廓被保存成一个point向量
//	int contourIdx,//指定要绘制轮廓的编号，如果是负数，则绘制所有的轮廓
//	const Scalar& color,//绘制轮廓所用的颜色
//	int thickness = 1, //绘制轮廓的线的粗细，如果是负数，则轮廓内部被填充
//	int lineType = 8, / 绘制轮廓的线的连通性
//	InputArray hierarchy = noArray(),//关于层级的可选参数，只有绘制部分轮廓时才会用到
//	int maxLevel = INT_MAX,//绘制轮廓的最高级别，这个参数只有hierarchy有效的时候才有效
//						   //maxLevel=0，绘制与输入轮廓属于同一等级的所有轮廓即输入轮廓和与其相邻的轮廓
//						   //maxLevel=1, 绘制与输入轮廓同一等级的所有轮廓与其子节点。
//						   //maxLevel=2，绘制与输入轮廓同一等级的所有轮廓与其子节点以及子节点的子节点
//	Point offset = Point()
//)







void yourname() {
	Mat src;
	src = imread("name3.jpg");
	imshow("原始图", src);
	Mat img;
	resize(src, img, Size(800, 800), 1, 1);

	imshow("800X800图", img);
	cvtColor(img, img, COLOR_BGR2HSV);

	imshow("COLOR_BGR2HSV图", img);

	Mat RGB_channels[3];
	split(img, RGB_channels);
	imshow("H", RGB_channels[0]);
	imshow("S", RGB_channels[1]);
	imshow("V", RGB_channels[2]);



	equalizeHist(RGB_channels[2], RGB_channels[2]);
	merge(RGB_channels, 3, img);
	imshow("分离图", img);
	inRange(img, Scalar(60, 43, 46), Scalar(260, 255, 255), img);
	imshow("掩码天空", img);
	medianBlur(img, img, 9);
	imshow("掩码天空，中值滤波", img);

	Mat kernel(5, 5, CV_8U);
	morphologyEx(img, img, MORPH_OPEN, kernel, Point(-1, -1), 10);
	medianBlur(img, img, 9);
	imshow("多边形", img);

	//找轮廓
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
	Mat org = imread("原始色图.jpg");
	Mat filter = imread("新海诚.jpg");
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
	imshow("滤镜效果", result);



	//单通道图像读取方式

	//	Mat img1 = imread(filename, IMREAD_GRAYSCALE);
	//for (size_t nrow = 0; nrow < img1.rows; nrow++)
	//{
	//	for (size_t ncol = 0; ncol < img1.cols; ncol++)
	//	{
	//		uchar val = mat_CV_8UC1.at<uchar>(nrow, ncol);
	//	}
	//}
	//三通道图像读取方式
	//Mat img2 = imread(filename, IMREAD_COLOR);
	//for (size_t nrow = 0; nrow < img2.rows; nrow++)
	//{
	//	for (size_t ncol = 0; ncol < img2.cols; ncol++)
	//	{
	//		Vec3i bgr = mat_CV_8UC3.at<Vec3b>(nrow, ncol);//用Vec3b也行  
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
	//粗线，越大越粗，但是会有大量噪点  
	Mat imgL;
	//第三个参数ddepth表示目标图像的深度，ddepth=-1时，与原图像一致  
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
	imshow("双边滤波 CV_BGR2HLS", img);
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

	imshow("双边滤波 result", canny_img);




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
	//imshow("双边滤波 CV_BGR2HLS_2", img);





	Mat org = imread("原始色图.jpg");
	Mat filter = imread("新海诚.jpg");
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
	imshow("滤镜效果", result);
	waitKey(0);
}



void hsv_function() {

	imshow(windowName, img);
	//彩色图像的灰度值归一化  
	img.convertTo(bgr, CV_32FC3, 1.0 / 255, 0);
	//颜色空间转换  
	cvtColor(bgr, hsv, COLOR_BGR2HSV);
	namedWindow(dstName, WINDOW_GUI_EXPANDED);
	//调节色相 H  
	createTrackbar("hmin", dstName, &hmin, hmin_Max, callBack);
	createTrackbar("hmax", dstName, &hmax, hmax_Max, callBack);
	//调节饱和度 S  
	createTrackbar("smin", dstName, &smin, smin_Max, callBack);
	createTrackbar("smax", dstName, &smax, smax_Max, callBack);
	//调节亮度 V  
	createTrackbar("vmin", dstName, &vmin, vmin_Max, callBack);
	createTrackbar("vmax", dstName, &vmax, vmax_Max, callBack);
}
//回调函数  
void callBack(int, void*)
{

	//输出图像分配内存  
	dst = Mat::zeros(img.size(), CV_32FC3);
	//掩码  
	Mat mask;
	inRange(hsv, Scalar(hmin, smin / float(smin_Max), vmin / float(vmin_Max)), Scalar(hmax, smax / float(smax_Max), vmax / float(vmax_Max)), mask);
	//只保留  
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
	//输出图像  
	imshow(dstName, dst);
	//保存图像  
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

	//颜色映射
	//Size(cols, rows) opencv的api我真是无语了。幸好之前的都800*800的大小
	//列，行 不是 行，列
	for (int i = 0; i < src.cols; i++) {
		for (int j = 0; j < src.rows; j++) {

			for (int channels = 0; channels < 3; channels++) {
				double pix = src.at<Vec3b>(i, j)[channels];
				//Vec3b c_v = result.at<Vec3b>(i, j);
				double cm = colorBlue_mean.at<double>(channels, 0);
				double cs = colorBlue_Std.at<double>(channels, 0);
				double sm = src_mean.at<double>(channels, 0);
				double ss = src_Std.at<double>(channels, 0);
				/*			首先，将源图像原有的数据减掉源图像的均值

				L = l – ml

				A = a – ma

				B = b – mb

				再将得到的新数据按比例放缩，其放缩系数是两幅图像标准方差的比值

				L’ = (nl’ / nl)* L

				A’ = (na’ / na)* A

				B’ = (nb’ / nb)* B

				将得到的l’、a’、b’分别加上目标图像三个通道的均值，得到最终数据

				L = L’ + ml’

				A = A’ + ma’

				B = B’ + mb’

				整理后得到目标图像与源图像之间的像素关系表达

				L = (nl’ / nl)* (l – ml) + ml’

				A = (na’ / na)* (a – ma) + ma’

				B = (nb’ / nb)* (b – mb) + mb’*/

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
	imshow("颜色迁移", src);
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
	// depth 用来度量每一个像素中每一个通道的精度，但它本身与图像的通道数无关！depth数值越大，精度越高。在                 Opencv中，Mat.depth()得到的是一个0~6的数字，分别代表不同的位数，对应关系如下：                            
	// enum{CV_8U=0,CV_8S=1,CV_16U=2,CV_16S=3,CV_32S=4,CV_32F=5,CV_64F=6}          

	// 其中U是unsigned的意思，S表示signed，也就是有符号和无符号数。

	// 可以理解为房间内每张床可以睡多少人，这个跟房间内有多少床并无关系；

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
	//excellent ： sky6,5
	Mat sky = imread("sky1.jpg");

	imshow("原始图", src);
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
	//gamma变亮以后细节就会消失影响，后面的边缘操作 	
	//  img=Gamma(src);

	imshow("800X800图", img);
	waitKey(0);
	cvtColor(img, img, COLOR_BGR2HSV);

	imshow("COLOR_BGR2HSV图", img);

	Mat RGB_channels[3];
	split(img, RGB_channels);
	imshow("H", RGB_channels[0]);
	imshow("S", RGB_channels[1]);
	imshow("V", RGB_channels[2]);



	equalizeHist(RGB_channels[2], RGB_channels[2]);
	merge(RGB_channels, 3, img);
	imshow("hsv合成图", img);
	//blue
	inRange(img, Scalar(100, 43, 46), Scalar(124, 255, 255), img);
	//white
	//inRange(img, Scalar(0, 0, 221), Scalar(360,30,255), img);
	imshow("掩码天空", img);
	medianBlur(img, img, 9);
	imshow("掩码天空，中值滤波", img);


	morphologyEx(img, img, MORPH_OPEN, kernel, Point(-1, -1), 10);
	medianBlur(img, img, 9);
	imshow("多边形", img);
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
		//长度确定最大矩形周长，面积确定是否闭合。这样才能选择出想要的矩阵图形出来。缺一不可
		//目前并没有很好检测，可以直接提取矩形，只能近似。
		//所以仍然存在不完美
		if (maxLength < arcLength(contours[i], true) && maxArea<contourArea(contours[i])) {
			maxLength = arcLength(contours[i], true);
			maxArea = contourArea(contours[i]);
			maxIndex = i;
		}
		// drawContours(Wang_mark, contours, i, Scalar::all(i + 1), 1, 8, hierarchy);
		//drawContours(Wang_Rect, contours, i, Scalar(255), 1, 8, hierarchy);
		//cout << arcLength(contours[i], true) << endl;
		//drawContours(Wang_Mat, contours, i, Scalar::all(i + 1), 1, 8, hierarchy);//为什么要这样画？
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

	Mat org = imread("原始色图.jpg");
	Mat filter = imread("新海诚.jpg");
	resize(filter, filter, Size(800, 800));


	for (int i = 1; i < result.rows; i++) {
		for (int j = 1; j < result.cols; j++) {
			Vec3b c_v = result.at<Vec3b>(i, j);
			int x = c_v.val[1] / 4 + (c_v.val[0] / 32) * 64;
			int y = c_v.val[2] / 4 + (c_v.val[0] % 4) * 64;
			result.at<Vec3b>(i, j) = filter.at<Vec3b>(x, y);
		}
	}
	imshow("滤镜效果", result);






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
	imshow("双边滤波 CV_BGR2HLS", img);
	bilateralFilter(result, canny_img, 10, 50, 50, 4);

	imshow("双边滤波 result", canny_img);
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
	imshow("滤镜效果", result);
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
	//归一化操作
	//img.convertTo(img,CV_32FC3,1.0/255,0);

	printMatInfo(img, "img");
	//0<H<360,0<L<1,0<S<1
	imshow("before color enhance", img);
	for (int i = 0; i < img.cols; i++) {
		for (int j = 0; j < img.rows; j++) {
			//Vec3f 这里应该是 Vec3b
			//归一化后要变成Vec3f
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
	//归一化到0~255    
	normalize(imageGamma, imageGamma, 0, 255, CV_MINMAX);
	//转换成8bit图像显示    
	convertScaleAbs(imageGamma, imageGamma);
	imshow("原图", image);
	imshow("伽马变换图像增强效果", imageGamma);
	waitKey();
	return imageGamma;
}