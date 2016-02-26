/*
 * \file mono_odometer.h
 * \date Feb 11, 2016
 * \author anishitani <atoshio25@gmail.com>
 */

#ifndef _MONO_ODOMETER_H_
#define _MONO_ODOMETER_H_

#include <cstdlib>
#include <vector>
#include <queue>

#include <opencv2/opencv.hpp>

#include <vo/odometer.h>
#include <vo/vo_state.h>

namespace vo {

/**
 * \brief The class MonoOdometer processes input images generating
 * a displacement information.
 */
class MonoOdometer : Odometer {

public:
	MonoOdometer();
	~MonoOdometer();

	/**
	 * \brief This is the main method of Odometer class.
	 * \param image Input image to be processed.
	 * \return Returns true in case of a successful process.
	 */
	bool process(const cv::InputArray image);

private:

	VoState* prevState;
	VoState* currState;

	/**
	 * \brief Method for detecting image features.
	 */
	void featureDetection();

	/**
	 * \brief Method for tracking the current feature from previous
	 * image to current image.
	 */
	void featureTracking();

};

}

#endif /* _MONO_ODOMETER_H_ */
