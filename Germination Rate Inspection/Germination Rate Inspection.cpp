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
	std::string outfilename = "E:\\发芽率检测图像\\" + filename_without_extension + "S0-60_v200-250" + ".jpg";
	

	// Save image
	cv::imwrite(outfilename, img);
}

void CGRI::ShowImg(Mat& img, String name, int x, int y)
{
	namedWindow(name, WINDOW_NORMAL);
	moveWindow(name, x, y);
	imshow(name, img);
}

Mat CGRI::segmentation(Mat src)
{
	// 定义白色的阈值范围
	Scalar lower_white(0, 0, 200);
	Scalar upper_white(180, 60, 255);
	// 根据阈值构建掩模
	Mat mask;
	inRange(src, lower_white, upper_white, mask);

	return mask;
}

Mat CGRI::MorphologicalOperation(Mat src, int kernel_size, int cycle_num_e, int cycle_num_d)
{
	Mat kernel;

	kernel = getStructuringElement(MORPH_RECT, Size(kernel_size, kernel_size));

	src = src.clone();
	//erode(src, src, kernel, Point(-1, -1), cycle_num_e);
	dilate(src, src, kernel, Point(-1, -1), cycle_num_d);
	erode(src, src, kernel, Point(-1, -1), cycle_num_e);

	return src;
}

Mat CGRI::EightConnectivity(Mat& img, float cof)
{
	img = img.clone();
	Mat labels; // Output labeled image
	int num_labels; // Number of connected components
	Mat stats; // Output statistics for each connected component (bounding box, area, etc.)
	Mat centroids; // Output centroids for each connected component
	num_labels = connectedComponentsWithStats(img, labels, stats, centroids, 8, CV_32S);


	double sum_area = 0.0;
	double mean_area = 0.0;
	for (int i = 1; i < num_labels; i++) { // Start from 1 to skip the background
		sum_area += stats.at<int>(i, CC_STAT_AREA); //  Accumulate area of each connected component
	}
	mean_area = sum_area / (num_labels - 1); // Calculate mean area, excluding background

	Mat output = Mat::zeros(labels.size(), CV_8UC1);
	for (int i = 0; i < labels.rows; i++) {
		for (int j = 0; j < labels.cols; j++) {
			int label = labels.at<int>(i, j); // Get label of the current pixel
			// Check if area of the connected component containing the current pixel is greater than or equal to the mean area
			if (label > 0 && stats.at<int>(label, CC_STAT_AREA) >= mean_area * cof) {
				output.at<uchar>(i, j) = 255;
			}
		}
	}

	return output;
}
