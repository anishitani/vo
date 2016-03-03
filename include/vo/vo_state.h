/**
 * \file vo_state.h
 * \date Feb 25, 2016
 * \author anishitani
 * \brief
 */
#ifndef _VO_STATE_H_
#define _VO_STATE_H_

#include <opencv2/opencv.hpp>

namespace vo {

/*
 *
 */
class VoState {
public:
	VoState();
	virtual ~VoState();

	cv::Mat getImage();
	void setImage(cv::Mat image);

	std::vector<cv::KeyPoint> getFeatureKeyPoints();
	void setFeatureKeyPoints(std::vector<cv::KeyPoint> features);

	std::vector<cv::Point2f> getFeaturePoints();
	void setFeaturePoints(std::vector<cv::Point2f> featurePoints);

private:

	cv::Mat image;
	std::vector<cv::KeyPoint> features;
};

} /* namespace vo */

#endif /* _VO_STATE_H_ */
