#include <image_processor/filter.hpp>

namespace image_processor {
namespace filter_factory {

/**
 * @brief Create a filter for resizing an image.
 *
 * @param width Desired width of the image after resizing.
 * @param height Desired height of the image after resizing.
 * @return Filter instance configured for resizing.
 */
Filter CreateResizeFilter(std::uint16_t width, std::uint16_t height);

/**
 * @brief Create a filter for cropping an image.
 *
 * This method creates a filter that will crop an image to the specified
 * rectangle, defined by its top-left corner (`x`, `y`) and its dimensions (`width`, `height`).
 *
 * @param x Horizontal coordinate of the top-left corner of the cropping rectangle.
 * @param y Vertical coordinate of the top-left corner of the cropping rectangle.
 * @param width Width of the cropping rectangle.
 * @param height Height of the cropping rectangle.
 * @return Filter instance configured for cropping.
 */
Filter CreateCropFilter(std::uint16_t x, std::uint16_t y, std::uint16_t width,
                        std::uint16_t height);

/**
 * @brief Create a filter for applying a blur effect to an image.
 *
 * The blur effect is controlled by a kernel size, with larger values resulting
 * in a more pronounced blur.
 *
 * @param kernel_size Size of the blur kernel. Typically, larger values produce more blur.
 * @return Filter instance configured for blurring.
 */
Filter CreateBlurFilter(std::uint8_t kernel_size);

/**
 * @brief Create a filter for transforming an image into a watercolor painting style.
 *
 * This method creates a filter that will process an image to give it the appearance
 * of being painted with watercolors. The effect is controlled by parameters for brush
 * size, hardness, and strength.
 *
 * @param brush_size Size of the virtual brush. Determines the coarseness of the painting effect.
 * @param brush_hardness Hardness of the virtual brush. Influences the edge sharpness of painted areas.
 * @param brush_strength Strength of the brush strokes. Determines the intensity of the painting effect.
 * @return Filter instance configured for the watercolor effect.
 */
Filter CreateWatercolorFilter(float brush_size, float brush_hardness,
                              float brush_strength);

/**
 * @brief Create a filter for transforming an image into a cartoon style.
 *
 * This method creates a filter that will process an image to give it the appearance
 * of being a cartoon. The effect is controlled by a detalization level.
 *
 * @param detalization_level Level of detail preserved in the cartoon effect. Higher values retain more fine detail.
 * @return Filter instance configured for the cartoon effect.
 */
Filter CreateCartoonizeFilter(float detalization_level);

} // namespace filter_factory
} // namespace image_processor
