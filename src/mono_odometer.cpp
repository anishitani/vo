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

bool MonoOdometer::process(const cv::InputArray image) {

	// Asserts the array is in fact a MAT type
	assert(image.isMat());

	this->prevState = this->currState;

	this->currState = new VoState();
	this->currState->setImage(image.getMat());

	this->featureDetection();

	// If it's the first loop this step is skipped
	if (this->prevState != NULL) {
		this->featureTracking();
	}

	return true;
}

void MonoOdometer::featureDetection() {
	int fast_threshold = 20;
	bool nonmaxSuppression = true;
	std::vector<cv::KeyPoint> features;
	cv::FAST(this->currState->getImage(), features, fast_threshold,
			nonmaxSuppression);
	this->currState->setFeatureKeyPoints(features);
}

void MonoOdometer::featureTracking() {
	std::vector<uchar> status;
	std::vector<float> err;
	cv::Size winSize = cv::Size(21, 21);
	cv::TermCriteria termcrit = cv::TermCriteria(
			cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 30, 0.01);

	// Estimates optical flow using Lucas Kanade pyramid alignment method.
	cv::calcOpticalFlowPyrLK(this->prevState->getImage(),
			this->currState->getImage(), this->prevState->getFeatureKeyPoints(),
			this->currState->getFeatureKeyPoints(), status, err, winSize, 3,
			termcrit, 0, 0.001);

	//getting rid of points for which the KLT tracking failed or those who have gone outside the frame
	int indexCorrection = 0;
	for (int i = 0; i < status.size(); i++) {
		cv::Point2f pt = this->currState->getFeaturePoints().at(
				i - indexCorrection);
		if ((status.at(i) == 0) || (pt.x < 0) || (pt.y < 0)) {
			if ((pt.x < 0) || (pt.y < 0)) {
				status.at(i) = 0;
			}
			this->prevState->getFeaturePoints().erase(
					this->prevState->getFeaturePoints().begin()
							+ (i - indexCorrection));
			this->currState->getFeaturePoints().erase(
					this->currState->getFeaturePoints().begin()
							+ (i - indexCorrection));
			indexCorrection++;
		}

	}

}
