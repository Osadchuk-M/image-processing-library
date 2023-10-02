
#pragma once

#include <opencv2/core/core.hpp>

namespace lib5 {

/**
 * Crops the given image.
 *
 * @param src Source image.
 * @param dst Destination image.
 * @param rect Rectangle defining the ROI (region of interest) to crop.
 */
void crop(const cv::Mat& src, cv::Mat& dst, const cv::Rect& rect);

} // namespace lib5
