void VS_Result(){
		Mat src;
	
	Mat kernel(5, 5, CV_8U);

	src = imread("name21.jpg");

	Mat sky = imread("sky6.jpg");
	
	resize(src, src, Size(800,800),1,1);
	Mat img,img_b,img_r;
	img_r =TransferColor(src);

	Laplacian(src, img_b, -1, 3, 1, 0, 4);
	
	img=img_b+ img_r;
	cvtColor(img, img, COLOR_BGR2HSV);
	Mat RGB_channels[3];
	split(img, RGB_channels);
	equalizeHist(RGB_channels[2], RGB_channels[2]);
	merge(RGB_channels,3, img);

	inRange(img, Scalar(100, 43, 46), Scalar(124, 255, 255), img);

	medianBlur(img, img, 9);
	
	morphologyEx(img, img, MORPH_OPEN, kernel, Point(-1, -1), 10);
	medianBlur(img, img, 9 );


	vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
	double maxArea = 0;
	double maxLength = 0;
	int maxIndex = 0;
	findContours(img, contours, hierarchy, RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	Rect boundRect;
	Mat Wang_Rect(img.size(), src.type(), cv::Scalar(0));
	


	for (int i = 0; i < contours.size(); i++) {

		if (maxLength < arcLength(contours[i], true)&& maxArea<contourArea(contours[i])) {
			maxLength = arcLength(contours[i], true);
			maxArea = contourArea(contours[i]);
			maxIndex = i;
		}
	}

	boundRect = boundingRect(Mat(contours[maxIndex]));
	rectangle(Wang_Rect, boundRect, Scalar(255, 255, 255), -1,8,0);


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

	seamlessClone(sky,src_clone,  img, p, result, NORMAL_CLONE);

	
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

	










    result=imread("yourname.jpg");
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
	 test=Gamma(test);


	 imshow("Gamma Result", test);

	 cvtColor(result, canny_img, CV_BGR2HLS);
	 imshow("canny_img", canny_img);
	 for (int i = 1; i < canny_img.rows; i++) {
	 	for (int j = 1; j < canny_img.cols; j++) {
	 		Vec3b c_v=canny_img.at<Vec3b>(i, j) ;
	 		c_v.val[1] *= 2;
	 		canny_img.at<Vec3b>(i, j) = c_v;

	 	}
	 }

	 cvtColor(canny_img, canny_img, CV_HLS2BGR);
	 img;
	 bilateralFilter(canny_img, img, 10, 50, 50, 4);

	 bilateralFilter(result, canny_img, 10, 50, 50, 4);
	
	 imshow("˫���˲� result", canny_img);
	 canny_img=Gamma(canny_img);
	 imshow("Gamma", canny_img);





	 for (int i = 1; i < result.rows; i++) {
	 	for (int j = 1; j < result.cols; j++) {
	 		Vec3b c_v = result.at<Vec3b>(i, j);
	 		int res = 0;
	 		int mixPixel = c_v.val[0];
	 		int basePixel = (c_v.val[0] + c_v.val[1] + c_v.val[2]) / 3;
	 		res = 255 - (255 - mixPixel) * (255 - basePixel) / 255;
	 		c_v.val[0] =min(255, max(0, res));
	 		mixPixel = c_v.val[1];
	 		res = 255 - (255 - mixPixel) * (255 - basePixel) / 255;
	 		c_v.val[1] = min(255, max(0, res));
	 		mixPixel = c_v.val[2];
	 		res = 255 - (255 - mixPixel) * (255 - basePixel) / 255;
	 		c_v.val[2] = min(255, max(0, res));

	 		result.at<Vec3b>(i, j) = c_v;//filter.at<Vec3b>(x, y);

	 	}
	 }
	 imshow("ɫ��ӳ��", result);
	 waitKey(0);



}