#include "GRI.h"
#include<iostream>
#include<opencv2/imgproc/types_c.h>

void CGRI::calculateHSV(Mat& hsvImage)
{
	vector<Mat> hsv_planes;
	split(hsvImage, hsv_planes);
	Mat hChannel = hsv_planes[0];
	Mat sChannel = hsv_planes[1];
	Mat vChannel = hsv_planes[2];

	int PerPixSum_h[180] = { 0 };
	int PerPixSum_s[256] = { 0 };
	int PerPixSum_v[256] = { 0 };

	for (int i = 0; i < hChannel.rows; i++)
	{
		for (int j = 0; j < hChannel.cols; j++)
		{
			int hValue = (int)hChannel.at<uchar>(i, j);
			int sValue = (int)sChannel.at<uchar>(i, j);
			int vValue = (int)vChannel.at<uchar>(i, j);
			PerPixSum_h[hValue]++;
			PerPixSum_s[sValue]++;
			PerPixSum_v[vValue]++;
		}
	}

	//for (int i = 0; i < 180; i++)
	//{
	//	cout << PerPixSum_h[i] << endl;
	//	//cout << i << endl;
	//}
	for (int i = 0; i < 256; i++)
	{
		//cout << PerPixSum_s[i] << endl;
		//cout << i << endl;
		cout << PerPixSum_v[i] << endl;
	}



	//namedWindow("hChannel", WINDOW_NORMAL);
	//moveWindow("hChannel", 0, 0);
	//imshow("hChannel", hChannel);

	//waitKey(0);
}

void CGRI::SaveImg(String filename, Mat& img)
{
	// Get the full path of the source image file name
	std::string fullpath = cv::samples::findFile(filename, true, true);

	// Get the directory and file name from the full path
	std::string directory = fullpath.substr(0, fullpath.find_last_of("/\\") + 1);
	std::string basename = fullpath.substr(fullpath.find_last_of("/\\") + 1);

	// Remove the file extension from the file name
	std::string filename_without_extension = basename.substr(0, basename.find_last_of("."));

	// Construct the file name and path for saving
	std::string outfilename = "E:\\·¢Ñ¿ÂÊ¼ì²âÍ¼Ïñ\\" + filename_without_extension + "S0-60_v200-250" + ".jpg";
	

	// Save image
	cv::imwrite(outfilename, img);
}