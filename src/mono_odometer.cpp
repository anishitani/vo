/*
 * mono_odometer.cpp
 *
 *  Created on: Feb 11, 2016
 *      Author: anishitani
 */

#include <vo/mono_odometer.h>

using namespace vo;

MonoOdometer::MonoOdometer() {

}

MonoOdometer::~MonoOdometer() {

}

cv::Mat MonoOdometer::getCurrentImage() {
	return this->curr_image;
}

cv::Mat MonoOdometer::getPreviousImage() {
	return this->prev_image;
}

bool MonoOdometer::process(const cv::InputArray image) {

	// Asserts the array is in fact a MAT type
	assert(image.isMat());

	this->prev_image = this->curr_image;
	this->curr_image = image.getMat();

	featureDetection();

	// First loop only reads the image
	// No processing is done
	if (this->prev_image.empty()) {
		return true;
	}

	featureTracking();

	return true;
}

void MonoOdometer::featureDetection() {
	std::vector<cv::KeyPoint> keypoints_1;
	int fast_threshold = 20;
	bool nonmaxSuppression = true;
	cv::FAST(this->curr_image, keypoints_1, fast_threshold, nonmaxSuppression);
}

void MonoOdometer::featureTracking() {

}
