// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>


//cv
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/core/core_c.h>

using namespace cv;
using namespace std;



void topview_getMatrix() {
	int CHECKERBOARD[2]{ 4, 4 };
	bool success;
	Mat gray;
	Mat gray_tmp;
	vector<cv::Point2f> corner_pts;
	Mat imges[4];
	//앞
	imges[0] = imread("front_top_undi.png");
	//왼쪽
	imges[2] = imread("left_top_undi.png");
	//오른쪽
	imges[1] = imread("right_top_undi.png");
	//뒤
	imges[3] = imread("back_top_undi.png");

	//전체
	Mat img5 = imread("car.png");
	imshow("test112", img5);
	cv::cvtColor(img5, gray_tmp, cv::COLOR_BGR2GRAY);
	Point2f coners_from[4];

	Mat dsts[4];
	Mat Ms[4];
	for (int j = 0; j < 4; j++) {

		cv::cvtColor(imges[j], gray, cv::COLOR_BGR2GRAY);
		bool res = cv::findChessboardCorners(gray, cv::Size(CHECKERBOARD[0], CHECKERBOARD[1]), corner_pts, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);
		cout << res;
		cout << corner_pts[0];
		Point2f coners_from[4];
		coners_from[0] = corner_pts[0];
		coners_from[1] = corner_pts[CHECKERBOARD[0] - 1];
		coners_from[2] = corner_pts[CHECKERBOARD[0] * (CHECKERBOARD[1] - 1)];
		coners_from[3] = corner_pts[CHECKERBOARD[0] * CHECKERBOARD[1] - 1];
		for (int i = 0; i < 4; i++) {
			circle(imges[j], coners_from[i], 1, Scalar(0, 0, 255), 3, 8, 0);
			putText(imges[j], to_string(i + 1), coners_from[i], 1, 2, Scalar(0, 0, 255), 2, 8);
		}
		cv::cvtColor(img5, gray, cv::COLOR_BGR2GRAY);
		cv::findChessboardCorners(gray, cv::Size(CHECKERBOARD[0], CHECKERBOARD[1]), corner_pts, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);
		cout << corner_pts[0];
		Point2f coners_to[4];
		switch (j) {
		case 0:
			coners_to[0] = corner_pts[0];
			coners_to[1] = corner_pts[CHECKERBOARD[0] - 1];
			coners_to[2] = corner_pts[CHECKERBOARD[0] * (CHECKERBOARD[1] - 1)];
			coners_to[3] = corner_pts[CHECKERBOARD[0] * CHECKERBOARD[1] - 1];
			break;
		case 1:
			coners_to[2] = corner_pts[0];
			coners_to[0] = corner_pts[CHECKERBOARD[0] - 1];
			coners_to[3] = corner_pts[CHECKERBOARD[0] * (CHECKERBOARD[1] - 1)];
			coners_to[1] = corner_pts[CHECKERBOARD[0] * CHECKERBOARD[1] - 1];
			break;
		case 2://3142
			coners_to[2] = corner_pts[0];
			coners_to[0] = corner_pts[CHECKERBOARD[0] - 1];
			coners_to[3] = corner_pts[CHECKERBOARD[0] * (CHECKERBOARD[1] - 1)];
			coners_to[1] = corner_pts[CHECKERBOARD[0] * CHECKERBOARD[1] - 1];
			break;
		case 3:
			coners_to[2] = corner_pts[0];
			coners_to[3] = corner_pts[CHECKERBOARD[0] - 1];
			coners_to[0] = corner_pts[CHECKERBOARD[0] * (CHECKERBOARD[1] - 1)];
			coners_to[1] = corner_pts[CHECKERBOARD[0] * CHECKERBOARD[1] - 1];
			break;
		}

		
		rectangle(img5, Rect(coners_to[0], coners_to[3]), Scalar(0, 0, 255), -1, 8, 0);
		putText(img5, to_string(j + 1), corner_pts[5] , 1, 2, Scalar(255, 0, 0), 2, 8);
		for (int i = 0; i < 4; i++) {
			circle(img5, coners_to[i], 1, Scalar(0, 0, 255), 3, 8, 0);
			putText(img5, to_string(i + 1), coners_to[i], 1, 2, Scalar(0, 0, 0), 2, 8);
		}
		Ms[j] = getPerspectiveTransform(coners_from, coners_to);
		Mat dst(img5.size(), CV_8UC3);
		dsts[j] = dst;
		warpPerspective(imges[j], dsts[j], Ms[j], img5.size(), INTER_LINEAR, BORDER_CONSTANT);
		imshow(to_string(j), dsts[j]);
		
		rectangle(dsts[j], Rect(coners_to[0], coners_to[3]), Scalar(0, 0, 255), -1, 8, 0);
		imwrite(to_string(j) + ".jpg", dsts[j]);
	}

	imshow("test231", imges[0]);
	imshow("test232", imges[1]);
	imshow("test233", imges[2]);
	imshow("test234", imges[3]);
	imshow("test24", img5);
	Mat result1(img5.size(), CV_8UC3);
	Mat result2(img5.size(), CV_8UC3);
	Mat result3(img5.size(), CV_8UC3);

	addWeighted(dsts[0], 0.5, dsts[2], 0.5, 0.0, result1);
	addWeighted(dsts[1], 0.5, dsts[3], 0.5, 0.0, result2);
	addWeighted(result1, 0.5, result2, 0.5, 0.0, result3);
	imshow("test25", result3);
	imwrite("test26.png", dsts[0] + dsts[1] + dsts[2] + dsts[3]);
	waitKey(0);
}

int main() {
	topview_getMatrix();
}