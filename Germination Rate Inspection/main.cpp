#include <iostream>
#include"GRI.h"

using namespace std;
using namespace cv;


int main()
{
	string filename = "C:\\Users\\赖信东\\Desktop\\1.jpg";
	Mat inputImage = imread(filename);
	//CGRI::imgCols = inputImage.cols;
	//CGRI::imgRows = inputImage.rows;

	Mat hsvImage;
	cvtColor(inputImage, hsvImage, COLOR_BGR2HSV);

	CGRI myCGRI;
	//myCGRI.calculateHSV(hsvImage);

	// 定义白色的阈值范围
	Scalar lower_white(0, 0, 200);
	Scalar upper_white(180, 30, 255);
	// 根据阈值构建掩模
	Mat mask;
	inRange(hsvImage, lower_white, upper_white, mask);

	myCGRI.SaveImg(filename, mask);

	namedWindow("mask", WINDOW_NORMAL);
	moveWindow("mask", 0, 0);
	imshow("mask", mask);

	waitKey(0);

	// 对原图和掩模进行位运算
	/*Mat res;
	bitwise_and(inputImage, inputImage, res, mask);*/


	return 0;
}