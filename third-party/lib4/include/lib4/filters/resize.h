#pragma once

#include <opencv2/core/core.hpp>

namespace lib4 {

/**
 * Resizes the given image.
 *
 * @param src Source image.
 * @param dst Destination image.
 * @param dsize Size of the destination image.
 */
void resize(const cv::Mat& src, cv::Mat& dst, const cv::Size& dsize);

} // namespace lib4
