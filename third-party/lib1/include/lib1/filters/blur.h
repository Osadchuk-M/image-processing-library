#include <opencv2/core.hpp>

namespace lib1 {

/**
 * Blurs an image using the normalized box filter.
 * @param src input image.
 * @param dst output image of the same size and type as src.
 * @param ksize blurring kernel size (from 0 to 255).
 */
void blur(cv::InputArray src, cv::OutputArray dst, cv::Size ksize);

}

