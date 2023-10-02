#include "utils.hpp"

#include <image_processor/error.hpp>

#include <fstream>
#include <stdexcept>
#include <uuid/uuid.h>

namespace image_processor::utils {

std::string GenerateUUID() {
  uuid_t bin_uuid;
  char char_uuid[37];
  uuid_generate(bin_uuid);
  uuid_unparse(bin_uuid, char_uuid);
  return std::string(char_uuid);
}

SIPL::Image<float> ConvertToSIPL(const cv::Mat& cv_image) {
  SIPL::Image<float> sipl_image(cv_image.cols, cv_image.rows);

  for (int i = 0; i < cv_image.rows; i++) {
    for (int j = 0; j < cv_image.cols; j++) {
      sipl_image.set(j, i, cv_image.at<uchar>(i, j) / 255.0f); // Normalize to [0.0, 1.0]
    }
  }

  return sipl_image;
}

cv::Mat ConvertToCV(const SIPL::Image<float>& sipl_image) {
  cv::Mat cv_image(sipl_image.getHeight(), sipl_image.getWidth(), CV_8UC1);

  for (int i = 0; i < cv_image.rows; i++) {
    for (int j = 0; j < cv_image.cols; j++) {
      cv_image.at<uchar>(i, j) = static_cast<uchar>(
          sipl_image.get(j, i) * 255.0f); // Convert from [0.0, 1.0] to [0, 255]
    }
  }

  return cv_image;
}

} // namespace image_processor::utils