#pragma once

#include <image_processor/error.hpp>
#include <image_processor/filter.hpp>
#include <string>

#include <SIPL/Core.hpp>
#include <opencv2/opencv.hpp>

namespace image_processor::utils {

/**
 * @brief Generates a universally unique identifier (UUID).
 *
 * This function creates a new UUID and returns it as a string.
 * The generated UUID is based on RFC 4122 and uses version 4 (random).
 *
 * @return A string representation of the generated UUID.
 */
std::string GenerateUUID();

/**
 * @brief Converts a cv::Mat image to SIPL::Image<float>.
 *
 * This function is designed to convert an OpenCV grayscale image to a SIPL image.
 * The input cv::Mat should have a single channel and uchar type. The output SIPL image
 * will contain float values normalized in the range [0.0, 1.0].
 *
 * @param cv_image The OpenCV grayscale image (CV_8UC1) to be converted.
 * @return SIPL::Image<float> The converted SIPL image with float values in the range
 * [0.0, 1.0].
 */
SIPL::Image<float> ConvertToSIPL(const cv::Mat& cv_image);

/**
 * @brief Converts a SIPL::Image<float> to cv::Mat.
 *
 * This function is designed to convert a SIPL grayscale image to an OpenCV image.
 * The input SIPL::Image<float> should have float values in the range [0.0, 1.0].
 * The output cv::Mat image will contain uchar values in the range [0, 255].
 *
 * @param sipl_image The SIPL grayscale image with float values in the range [0.0, 1.0] to
 * be converted.
 * @return cv::Mat The converted OpenCV grayscale image (CV_8UC1).
 */
cv::Mat ConvertToCV(const SIPL::Image<float>& sipl_image);

} // namespace image_processor::utils