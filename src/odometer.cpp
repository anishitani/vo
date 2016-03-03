/*
 * mono_odometer.cpp
 *
 *  Created on: Feb 11, 2016
 *      Author: anishitani
 */

#include <vo/odometer.h>

#include <iostream>

using namespace vo;

Odometer::Odometer() {
}

Odometer::~Odometer() {

}

bool Odometer::process(const cv::InputArray image) {
	std::cout << "MonoOdometer::process" << std::endl;

	// Asserts the array is in fact a MAT type
	assert(image.isMat());

	// First run
	// Tests for a previous state null
	if (!this->prevState) {
		std::cout << "First run!" << std::endl;
		this->prevState = new VoState();
		this->prevState->setImage(image.getMat());
		this->featureDetection();
		return true;
	}

	if (this->currState) {
		std::cout << "MonoOdometer::process - Update the previous state"
				<< std::endl;
		// Moves last iteration current to previous
		this->prevState = this->currState;
	}

	// If there's not a minimum number of available features
	// a new set o features are generated
	if (this->prevState->getFeatureKeyPoints().size() < 2000) {
		std::cout << "MonoOdometer::process - Refreshing features set"
				<< std::endl;
		this->featureDetection();
	}

	std::cout << "MonoOdometer::process - Update the previous state"
			<< std::endl;
	// Creates a new state
	this->currState = new VoState();
	this->currState->setImage(image.getMat());

	std::cout << "MonoOdometer::process - Tracking" << std::endl;
	this->featureTracking();

	return true;
}

void Odometer::featureDetection() {
	std::cout << "MonoOdometer::featureDetection" << std::endl;

	int fast_threshold = 20;
	bool nonmaxSuppression = true;
	std::vector<cv::KeyPoint> features;

	cv::FAST(this->prevState->getImage(), features, fast_threshold,
			nonmaxSuppression);

	this->prevState->setFeatureKeyPoints(features);
}

void Odometer::featureTracking() {
	std::cout << "MonoOdometer::featureTracking" << std::endl;

	std::vector<uchar> status;
	std::vector<float> err;
	cv::Size winSize = cv::Size(21, 21);
	cv::TermCriteria termcrit = cv::TermCriteria(
			cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 30, 0.01);

	// Estimates optical flow using Lucas Kanade pyramid alignment method.
	std::vector<cv::Point2f> prevPts = this->prevState->getFeaturePoints();
	std::vector<cv::Point2f> currPts = this->currState->getFeaturePoints();
	std::cout << "MonoOdometer::featureTracking - calcOpticalFlowPyrLK()"
			<< std::endl;
	cv::calcOpticalFlowPyrLK(this->prevState->getImage(),
			this->currState->getImage(), prevPts, currPts, status, err, winSize,
			3, termcrit, 0, 0.001);

	//getting rid of points for which the KLT tracking failed or those who have gone outside the frame
	int indexCorrection = 0;
	for (int i = 0; i < status.size(); i++) {
		cv::Point2f pt = currPts.at(i - indexCorrection);
		if ((status.at(i) == 0) || (pt.x < 0) || (pt.y < 0)) {
			if ((pt.x < 0) || (pt.y < 0)) {
				status.at(i) = 0;
			}
			prevPts.erase(prevPts.begin() + (i - indexCorrection));
			currPts.erase(currPts.begin() + (i - indexCorrection));
			indexCorrection++;
		}
	}

	this->prevState->setFeaturePoints(prevPts);
	this->currState->setFeaturePoints(currPts);

}
