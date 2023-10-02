#include <opencv2/core.hpp>

namespace lib2 {

/**
 * Turns an image into a watercolor painting.
 * @param src input image.
 * @param dst output image of the same size and type as src.
 * @param brush_size painting brush size (from 0 to 1).
 * @param brush_hardness painting brush hardness (from 0 to 1).
 * @param brush_strength painting brush strength (from 0 to 1).
 */
void watercolor(cv::InputArray src, cv::OutputArray dst, float brush_size,
                float brush_hardness, float brush_strength);

} // namespace lib2

