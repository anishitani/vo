/**
 * \file vo_state.cpp
 * \date Feb 25, 2016
 * \author anishitani
 * \brief
 */
#include <vo/vo_state.h>

namespace vo {

VoState::VoState() {
	// TODO Auto-generated constructor stub

}

VoState::~VoState() {
	// TODO Auto-generated destructor stub
}

cv::Mat VoState::getImage(){
	return this->image;
}

void VoState::setImage(cv::Mat image){
	this->image = image;
}

std::vector<cv::KeyPoint> VoState::getFeatureKeyPoints(){
	return this->features;
}

void VoState::setFeatureKeyPoints(std::vector<cv::KeyPoint> features){
	this->features = features;
}

std::vector<cv::Point2f> VoState::getFeaturePoints(){
	std::vector<cv::Point2f> points2f;
	cv::KeyPoint::convert(this->features,points2f);

	return points2f;
}

} /* namespace vo */
