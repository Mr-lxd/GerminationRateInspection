#include <iostream>
#include"GRI.h"

using namespace std;
using namespace cv;


int main()
{
	string filename = "C:\\Users\\���Ŷ�\\Desktop\\1.jpg";
	Mat inputImage = imread(filename);
	//CGRI::imgCols = inputImage.cols;
	//CGRI::imgRows = inputImage.rows;

	Mat hsvImage;
	cvtColor(inputImage, hsvImage, COLOR_BGR2HSV);

	CGRI myCGRI;
	//myCGRI.calculateHSV(hsvImage);

	// �����ɫ����ֵ��Χ
	Scalar lower_white(0, 0, 200);
	Scalar upper_white(180, 30, 255);
	// ������ֵ������ģ
	Mat mask;
	inRange(hsvImage, lower_white, upper_white, mask);

	myCGRI.SaveImg(filename, mask);

	namedWindow("mask", WINDOW_NORMAL);
	moveWindow("mask", 0, 0);
	imshow("mask", mask);

	waitKey(0);

	// ��ԭͼ����ģ����λ����
	/*Mat res;
	bitwise_and(inputImage, inputImage, res, mask);*/


	return 0;
}