#include <iostream>
#include"GRI.h"

using namespace std;
using namespace cv;


int main()
{
	string filename = "C:\\Users\\ÀµÐÅ¶«\\Desktop\\1.jpg";
	Mat inputImage = imread(filename);
	//CGRI::imgCols = inputImage.cols;
	//CGRI::imgRows = inputImage.rows;

	Mat hsvImage;
	cvtColor(inputImage, hsvImage, COLOR_BGR2HSV);

	CGRI myCGRI;
	//myCGRI.calculateHSV(hsvImage);

	Mat mask = myCGRI.segmentation(hsvImage);

	//filtering
	Mat temp = mask.clone();
	//GaussianBlur(temp, temp, Size(5, 5), 0, 0);
	medianBlur(temp, temp, 7);

	Mat morph = myCGRI.MorphologicalOperation(temp, 3, 8, 8);

	Mat connect = myCGRI.EightConnectivity(morph, 0.5);


	//myCGRI.SaveImg(filename, mask);
	myCGRI.ShowImg(mask, "mask", 0, 0);
	myCGRI.ShowImg(temp, "filter", 100, 100);
	myCGRI.ShowImg(morph, "morph", 200, 200);
	myCGRI.ShowImg(connect, "connect", 300, 300);

	waitKey(0);

	return 0;
}