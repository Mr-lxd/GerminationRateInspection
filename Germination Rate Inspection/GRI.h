#pragma once

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/ximgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

class CGRI
{
	public:
		static int imgCols, imgRows;

		void calculateHSV(Mat& hsvImage);
		void SaveImg(String filename, Mat& img);
		void ShowImg(Mat& img, String name, int x, int y);
		Mat segmentation(Mat src, int label);
		Mat MorphologicalOperation(Mat src, int kernel_size, int cycle_num_e, int cycle_num_d, int label);
		pair<Mat, int> EightConnectivity(Mat& img, float cof);
		Mat OTSU(Mat& src);

	private:

};
