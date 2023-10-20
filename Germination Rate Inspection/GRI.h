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
		Mat segmentation(Mat src);
		Mat MorphologicalOperation(Mat src, int kernel_size, int cycle_num_e, int cycle_num_d);
		Mat EightConnectivity(Mat& img, float cof);

	private:

};
