#include<iostream>
#include <opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <stdio.h>
#include <opencv2/imgproc.hpp>

#include <opencv2/ml/ml.hpp>
using namespace std;
using namespace cv;

Mat VS_IncreaseColor(Mat img, double Value);
Mat VS_Gamma(Mat image);
Mat VS_TransferColors(Mat src);

void VS_Results();
int VS_main() {
	VS_Results();
	int  i = 0;
	cin >> i;
	return 0;
}
void VS_Results() {
	Mat src;

	Mat kernel(5, 5, CV_8U);

	src = imread("name21.jpg");
	
	Mat sky = imread("sky6.jpg");

	resize(src, src, Size(800, 800), 1, 1);
	imshow("读入图", src);
	Mat img, img_b, img_r;
	img_r = VS_TransferColors(src);

	Laplacian(src, img_b, -1, 3, 1, 0, 4);

	img = img_b + img_r;
	cvtColor(img, img, COLOR_BGR2HSV);
	Mat RGB_channels[3];
	split(img, RGB_channels);
	equalizeHist(RGB_channels[2], RGB_channels[2]);
	merge(RGB_channels, 3, img);

	inRange(img, Scalar(100, 43, 46), Scalar(124, 255, 255), img);

	medianBlur(img, img, 9);

	morphologyEx(img, img, MORPH_OPEN, kernel, Point(-1, -1), 10);
	medianBlur(img, img, 9);


	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	double maxArea = 0;
	double maxLength = 0;
	int maxIndex = 0;
	findContours(img, contours, hierarchy, RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	Rect boundRect;
	Mat Wang_Rect(img.size(), src.type(), cv::Scalar(0));



	for (int i = 0; i < contours.size(); i++) {

		if (maxLength < arcLength(contours[i], true) && maxArea<contourArea(contours[i])) {
			maxLength = arcLength(contours[i], true);
			maxArea = contourArea(contours[i]);
			maxIndex = i;
		}
	}

	boundRect = boundingRect(Mat(contours[maxIndex]));
	rectangle(Wang_Rect, boundRect, Scalar(255, 255, 255), -1, 8, 0);


	int x = boundRect.x;
	int y = boundRect.y;
	int height = boundRect.height;
	int width = boundRect.width;


	Point 	p((x + width) / 2, (y + height) / 2);



	Mat src_clone = src;
	resize(sky, sky, Size(800, 800));
	resize(src_clone, src_clone, Size(800, 800));


	img = Wang_Rect;


	Mat result(sky.size(), sky.type(), cv::Scalar(0));

	seamlessClone(sky, src_clone, img, p, result, NORMAL_CLONE);


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













	result = imread("yourname.jpg");
	Mat test = imread("yourname.jpg");



	Mat canny_img;
	bilateralFilter(test, canny_img, 5, 150, 150);
	bilateralFilter(canny_img, test, 5, 150, 150);

	src;
	cvtColor(test, src, CV_BGR2GRAY);

	Mat imgL;

	Laplacian(src, imgL, -1, 3, 1);
	Mat imgC;
	Canny(src, imgC, 30, 90);



	Mat imgS, imgSx, imgSy, imgS0;
	Sobel(src, imgSx, -1, 0, 1);
	Sobel(src, imgSx, -1, 1, 0);
	imgS = imgSx + imgSy;
	Sobel(src, imgS0, -1, 1, 1);


	Mat imgTotal;
	imgTotal = imgC + imgS + imgL;
	normalize(imgTotal, imgTotal, 255, 0, CV_MINMAX);
	GaussianBlur(imgTotal, imgTotal, Size(3, 3), 3);
	threshold(imgTotal, imgTotal, 100, 255, THRESH_BINARY_INV);


	Mat imgTotalC3;
	cvtColor(imgTotal, imgTotalC3, CV_GRAY2BGR);
	bitwise_and(test, imgTotalC3, test);

	result = test;
	test = VS_Gamma(test);


	//imshow("Gamma Result", test);

	cvtColor(result, canny_img, CV_BGR2HLS);
	
	for (int i = 1; i < canny_img.rows; i++) {
		for (int j = 1; j < canny_img.cols; j++) {
			Vec3b c_v = canny_img.at<Vec3b>(i, j);
			c_v.val[1] *= 2;
			canny_img.at<Vec3b>(i, j) = c_v;

		}
	}

	cvtColor(canny_img, canny_img, CV_HLS2BGR);
	img;
	bilateralFilter(canny_img, img, 10, 50, 50, 4);

	bilateralFilter(result, canny_img, 10, 50, 50, 4);

	imshow("双边滤波 result", canny_img);
	imwrite("双边滤波.jpg", canny_img);

	canny_img = VS_Gamma(canny_img);
	imshow("Gamma", canny_img);

	
	imwrite("Gamma.jpg", canny_img);



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

			result.at<Vec3b>(i, j) = c_v;//filter.at<Vec3b>(x, y);

		}
	}
	imshow("色彩映射", result);
	imwrite("色彩映射.jpg", canny_img);
	waitKey(0);



}






Mat VS_IncreaseColor(Mat img, double Value) {
	
	cvtColor(img, img, COLOR_BGR2HSV);
	//cvtColor(img, img, COLOR_HSV2BGR);
	
	double H = 360;
	double S = 2;
	double L = 2;

	
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
	
	//waitKey(0);
	return img;
}

Mat VS_Gamma(Mat image) {

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
	//imshow("原图", image);
	//imshow("伽马变换图像增强效果", imageGamma);
	//waitKey();
	return imageGamma;
}





Mat VS_TransferColors(Mat src) {

	Mat colorBlue = imread("sky12.jpg");

	resize(src, src, Size(800, 800));
	resize(colorBlue, colorBlue, Size(800, 800));


	cvtColor(colorBlue, colorBlue, COLOR_BGR2Lab);
	cvtColor(src, src, COLOR_BGR2Lab);

	//waitKey(0);
	//Scalar src_tempVal = cv::mean(src);
	//Scalar colorBlue_tempVal = cv::mean(colorBlue);
	Mat src_mean, src_Std;
	Mat colorBlue_mean, colorBlue_Std;
	meanStdDev(src, src_mean, src_Std, noArray());
	meanStdDev(colorBlue, colorBlue_mean, colorBlue_Std, noArray());


	for (int i = 0; i < src.cols; i++) {
		for (int j = 0; j < src.rows; j++) {

			for (int channels = 0; channels < 3; channels++) {
				double pix = src.at<Vec3b>(i, j)[channels];
				//Vec3b c_v = result.at<Vec3b>(i, j);
				double cm = colorBlue_mean.at<double>(channels, 0);
				double cs = colorBlue_Std.at<double>(channels, 0);
				double sm = src_mean.at<double>(channels, 0);
				double ss = src_Std.at<double>(channels, 0);


				pix = (pix - sm)*(cs / ss) + cm;


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
	/*imshow("颜色迁移", src);*/
	cvtColor(src, src, COLOR_Lab2BGR);
	//imshow("COLOR_Lab2BGR", src);
	//waitKey(0);
	return src;


}