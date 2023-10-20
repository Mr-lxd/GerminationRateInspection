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

	private:

};
