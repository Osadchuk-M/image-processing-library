#pragma once

#include <cstdint>
#include <optional>

namespace image_processor {

/**
 * @struct Filter
 * @brief Represents a filter that can be applied to an image.
 *
 * A Filter consists of a type, which determines the kind of image manipulation to
 * perform, and a set of parameters specific to that type.
 */
struct Filter {

  /**
   * @enum Type
   * @brief Specifies the types of filters that can be applied.
   */
  enum class Type {
    Resize,     ///< Resizes the image to the specified dimensions.
    Crop,       ///< Crops the image to the specified rectangle.
    Blur,       ///< Blurs the image using a kernel of a specified size.
    Watercolor, ///< Applies a watercolor effect to the image.
    Cartoonize  ///< Applies a cartoon effect to the image.
  };

  Type type; ///< The type of the filter to be applied.

  // clang-format off
  std::optional<std::uint16_t> width;           ///< Width (in pixels) for Resize or Crop.
  std::optional<std::uint16_t> height;          ///< Height (in pixels) for Resize or Crop.
  std::optional<std::uint16_t> x;               ///< X-coordinate (in pixels) for Crop's top-left corner.
  std::optional<std::uint16_t> y;               ///< Y-coordinate (in pixels) for Crop's top-left corner.
  std::optional<std::uint8_t> kernel_size;      ///< Size of the kernel for the Blur filter.
  std::optional<float> brush_size;              ///< Size of the brush for the Watercolor filter.
  std::optional<float> brush_hardness;          ///< Hardness of the brush for the Watercolor filter.
  std::optional<float> brush_strength;          ///< Strength of the brush effect for the Watercolor filter.
  std::optional<float> detalization_level;      ///< Level of detail for the Cartoonize filter.
  // clang-format on
};

} // namespace image_processor
