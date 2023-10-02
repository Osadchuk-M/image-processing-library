#include <image_processor/filter_factory.hpp>

namespace image_processor {
namespace filter_factory {

Filter CreateResizeFilter(std::uint16_t width, std::uint16_t height) {
  Filter filter;
  filter.type = Filter::Type::Resize;
  filter.width = width;
  filter.height = height;
  return filter;
}

Filter CreateCropFilter(std::uint16_t x, std::uint16_t y, std::uint16_t width,
                        std::uint16_t height) {
  Filter filter;
  filter.type = Filter::Type::Crop;
  filter.x = x;
  filter.y = y;
  filter.width = width;
  filter.height = height;
  return filter;
}

Filter CreateBlurFilter(std::uint8_t kernel_size) {
  Filter filter;
  filter.type = Filter::Type::Blur;
  filter.kernel_size = kernel_size;
  return filter;
}

Filter CreateWatercolorFilter(float brush_size, float brush_hardness,
                              float brush_strength) {
  Filter filter;
  filter.type = Filter::Type::Watercolor;
  filter.brush_size = brush_size;
  filter.brush_hardness = brush_hardness;
  filter.brush_strength = brush_strength;
  return filter;
}

Filter CreateCartoonizeFilter(float detalization_level) {
  Filter filter;
  filter.type = Filter::Type::Cartoonize;
  filter.detalization_level = detalization_level;
  return filter;
}

} // namespace filter_factory
} // namespace image_processor
