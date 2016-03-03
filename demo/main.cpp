/**
 * \file main.cpp
 * \date Feb 19, 2016
 * \author anishitani
 * \brief
 */

#include <cstdio>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vo/odometer.h>

cv::Mat openImage(char *format, int i) {
	char filename[256];
	sprintf(filename, format, i);
	return cv::imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
}

int main(int argc, char **argv) {
	cv::Mat list;

	std::string basedir;
	cv::Mat ICurr;
	char format0[256] = "/home/anishitani/workspace/visionws/deps/dataset/cvlibs/dataset/sequences/00/image_0/%06d.png";

	cv::Mat_<float> K(3, 3);
	K << 721.5377, 0.0, 609.5593, 0.0, 721.5377, 172.854, 0.0, 0.0, 1.0;

	vo::MonoOdometer odom;

	ICurr = openImage(format0, 0);
	for (int i = 1; !ICurr.empty() ; i++) {

		cv::imshow("MONO", ICurr);
		if ('q' == (char) cv::waitKey(1))
			exit(0);

		if (odom.process(ICurr)) {
//			cv::Mat T;
//			double _motion[16];
//			odom.getMotion().getData(_motion, 0, 0, 3, 3);
//			cv::Mat(4, 4, CV_64F, _motion).convertTo(T,CV_32F);
//			pose *= T.inv();
//			poses.push_back(pose.reshape(1, 1));
		}

		ICurr = openImage(format0, i);
	}

	return 0;
}

