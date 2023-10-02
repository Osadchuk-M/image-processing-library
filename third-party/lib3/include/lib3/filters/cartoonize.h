#include <SIPL/Core.hpp>

namespace lib3 {

/**
 * Create a cartoon picture from the image.
 * @param img input image.
 * @param detalizationLevel painting conversion detalization (from 0 to 1).
 * @return output image of the same size and type as img.
 */
SIPL::Image<float> cartoonize(const SIPL::Image<float>& img, float detalizationLevel);

} // namespace lib3
