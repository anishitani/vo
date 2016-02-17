/*
 * \file mono_odometer.h
 * \date Feb 11, 2016
 * \author anishitani <atoshio25@gmail.com>
 */

#ifndef _MONO_ODOMETER_H_
#define _MONO_ODOMETER_H_

#include <cstdlib>
#include <vector>

#include <opencv2/opencv.hpp>

namespace vo {

/**
 * \brief The class MonoOdometer processes input images generating
 * a displacement information.
 */
class MonoOdometer {

public:
	MonoOdometer();
	~MonoOdometer();

	/**
	 * \brief This is the main method of Odometer class.
	 * \param image Input image to be processed.
	 * \return Returns true in case of a successful process.
	 */
	bool process(const cv::InputArray image);

	/**
	 * \brief Method for retrieving the latest input image.
	 * \return Latest image matrix.
	 */
	cv::Mat getCurrentImage();

	/**
	 * \brief Method for retrieving the second latest input image.
	 * \return Second latest image.
	 */
	cv::Mat getPreviousImage();

protected:

private:

	cv::Mat curr_image; //!< \brief Latest received image
	cv::Mat prev_image; //!< \brief Second latest received image

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
