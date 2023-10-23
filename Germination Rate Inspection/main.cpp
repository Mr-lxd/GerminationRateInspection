#include <iostream>
#include"GRI.h"

using namespace std;
using namespace cv;


int main()
{
	string filename = "C:\\Users\\ÀµÐÅ¶«\\Desktop\\2.jpg";
	Mat inputImage = imread(filename);
	//CGRI::imgCols = inputImage.cols;
	//CGRI::imgRows = inputImage.rows;

	Mat hsvImage;
	cvtColor(inputImage, hsvImage, COLOR_BGR2HSV);

	CGRI myCGRI;
	//myCGRI.calculateHSV(hsvImage);

	Mat mask_white = myCGRI.segmentation(hsvImage, 0);
	Mat mask_yellow = myCGRI.segmentation(hsvImage, 1);

	//filtering
	Mat temp_white = mask_white.clone();
	Mat temp_yellow = mask_yellow.clone();
	medianBlur(temp_white, temp_white, 7);

	Mat morph_sprout = myCGRI.MorphologicalOperation(temp_white, 3, 8, 8, 1);
	Mat morph_seed = myCGRI.MorphologicalOperation(temp_yellow, 3, 5, 5, 0);

	auto result_first = myCGRI.EightConnectivity(morph_sprout, 0.5);
	Mat connect_sprout = result_first.first;
	int sproutNum = result_first.second;
	auto result_second = myCGRI.EightConnectivity(morph_seed, 0.5);
	Mat connect_seed = result_second.first;
	int seedNum = result_second.second;

	float GR = (float)sproutNum / seedNum;

	//myCGRI.SaveImg(filename, mask);
	myCGRI.ShowImg(mask_white, "mask_white", 0, 0);
	myCGRI.ShowImg(mask_yellow, "mask_yellow", 50, 50);
	myCGRI.ShowImg(temp_white, "filter_white", 100, 100);
	myCGRI.ShowImg(morph_sprout, "morph_sprout", 200, 200);
	myCGRI.ShowImg(morph_seed, "morph_seed", 250, 250);
	myCGRI.ShowImg(connect_sprout, "connect_sprout", 300, 300);
	myCGRI.ShowImg(connect_seed, "connect_seed", 350, 350);

	cout << GR << endl;

	waitKey(0);

	return 0;
}