#include "image_processor.hpp"
#include "utils.hpp"
#include <cctype>
#include <opencv2/imgcodecs.hpp>

#include <lib1/filters/blur.h>
#include <lib2/filters/watercolor.h>
#include <lib3/filters/cartoonize.h>
#include <lib4/filters/resize.h>
#include <lib5/filters/crop.h>

namespace image_processor {

namespace {

bool IsBetweenZeroAndOne(float value) { return 0 <= value && value <= 1; }

bool IsValidFilter(const Filter& filter) {
  switch (filter.type) {
  case Filter::Type::Resize:
    return filter.width.has_value() && filter.height.has_value();
  case Filter::Type::Crop:
    return filter.x.has_value() && filter.y.has_value() && filter.width.has_value() &&
           filter.height.has_value() && *filter.x < *filter.width &&
           filter.y < *filter.height;
  case Filter::Type::Blur:
    return filter.kernel_size.has_value();
  case Filter::Type::Watercolor:
    return filter.brush_size.has_value() && filter.brush_hardness.has_value() &&
           filter.brush_strength.has_value() && IsBetweenZeroAndOne(*filter.brush_size) &&
           IsBetweenZeroAndOne(*filter.brush_hardness) &&
           IsBetweenZeroAndOne(*filter.brush_strength);
  case Filter::Type::Cartoonize:
    return filter.detalization_level.has_value() &&
           IsBetweenZeroAndOne(*filter.detalization_level);
  default:
    return false;
  }
}

ImageProcessingError CheckImage(const std::string& original_image_path_) {
  size_t pos = original_image_path_.rfind('.');
  if (pos == std::string::npos) {
    return ImageProcessingError::kInvalidImageFormat;
  }

  std::string extension = original_image_path_.substr(pos);
  std::transform(extension.begin(), extension.end(), extension.begin(),
                 ::tolower); // Convert to lowercase for comparison

  if (extension != ".jpg" && extension != ".jpeg" && extension != ".png") {
    return ImageProcessingError::kInvalidImageFormat;
  }

  if (!std::filesystem::exists(original_image_path_)) {
    return ImageProcessingError::kImageNotFound;
  }

  std::ifstream file(original_image_path_);
  if (!file.good()) {
    return ImageProcessingError::kImageInaccessible;
  }

  return ImageProcessingError::kNoError;
}

} // namespace

ImageProcessor::ImageProcessor(const std::string& original_image_path_,
                               const std::vector<Filter>& operations,
                               const std::string& processed_images_path)
    : original_image_path_(original_image_path_), operations_(operations),
      processed_images_path_(processed_images_path),
      image_(cv::imread(original_image_path_)) {}

ImageProcessingError ImageProcessor::ProcessImage() {
  auto error_code = ValidateArguments();
  if (error_code != ImageProcessingError::kNoError) {
    return error_code;
  }

  error_code = ApplyFilters();
  if (error_code != ImageProcessingError::kNoError) {
    return error_code;
  }

  error_code = SaveImage();
  if (error_code != ImageProcessingError::kNoError) {
    return error_code;
  }

  return ImageProcessingError::kNoError;
}

std::string ImageProcessor::GetResultImagePath() const {
  return result_image_path_.string();
}

ImageProcessingError ImageProcessor::ValidateArguments() const {
  for (const auto& filter : operations_) {
    if (!IsValidFilter(filter)) {
      return ImageProcessingError::kInvalidFilter;
    }
  }

  return CheckImage(original_image_path_);
}

ImageProcessingError ImageProcessor::ApplyFilters() {
  for (const auto& filter : operations_) {
    switch (filter.type) {
    case Filter::Type::Resize:
      lib4::resize(image_, image_, cv::Size(*filter.width, *filter.height));
      break;

    case Filter::Type::Blur: {
      cv::Size kernelSize(*filter.kernel_size, *filter.kernel_size);
      lib1::blur(image_, image_, kernelSize);
      break;
    }

    case Filter::Type::Watercolor:
      lib2::watercolor(image_, image_, *filter.brush_size, *filter.brush_hardness,
                       *filter.brush_strength);
      break;

    case Filter::Type::Cartoonize: {
      SIPL::Image<float> siplImage = utils::ConvertToSIPL(image_);
      SIPL::Image<float> cartoonized =
          lib3::cartoonize(siplImage, *filter.detalization_level);
      image_ = utils::ConvertToCV(cartoonized);
      break;
    }

    case Filter::Type::Crop: {
      cv::Rect rect(*filter.x, *filter.y, *filter.width, *filter.height);
      lib5::crop(image_, image_, rect);
      break;
    }

    default:
      return ImageProcessingError::kInvalidFilter;
    }
  }

  return ImageProcessingError::kNoError;
}

ImageProcessingError ImageProcessor::SaveImage() {
  std::string base_filename = std::filesystem::path(original_image_path_).stem().string();
  std::string extension =
      std::filesystem::path(original_image_path_).extension().string();

  result_image_path_ = processed_images_path_ + "/" + (base_filename + extension);

  int counter = 1;
  while (std::filesystem::exists(result_image_path_)) {
    result_image_path_ = processed_images_path_ + "/" +
                         (base_filename + "_" + std::to_string(counter) + extension);
    counter++;
  }

  if (!cv::imwrite(result_image_path_.string(), image_)) {
    return ImageProcessingError::kImageSaveError;
  }

  return ImageProcessingError::kNoError;
}

} // namespace image_processor