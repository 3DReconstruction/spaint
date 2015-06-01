/**
 * spaint: ImageProcessor_CPU.cpp
 */

#include "imageprocessing/cpu/ImageProcessor_CPU.h"

#include "imageprocessing/shared/ImageProcessor_Shared.h"

namespace spaint {

//#################### PUBLIC MEMBER FUNCTIONS ####################

void ImageProcessor_CPU::calculate_depth_difference(const ITMFloatImage_CPtr& firstInputImage, const ITMFloatImage_CPtr& secondInputImage, const AFImage_Ptr& outputImage) const
{
  check_image_size_equal(firstInputImage, secondInputImage);
  check_image_size_equal(firstInputImage, outputImage);

  int height = outputImage->dims(0);
  int width = outputImage->dims(1);
  int imgSize = height * width;
  float *output = outputImage->device<float>(); // Selecing host pointer does not work.
  const float *first = firstInputImage->GetData(MEMORYDEVICE_CPU);
  const float *second = secondInputImage->GetData(MEMORYDEVICE_CPU);

#ifdef WITH_OPENMP
  #pragma omp parallel for
#endif
  for(int locId = 0; locId < imgSize; ++locId)
  {
    int locIdcm = ImageProcessor::column_major_index_from_row_major_index(locId, width, height);
    shade_pixel_absolute_difference(&output[locIdcm], first[locId], second[locId]);
  }
}

void ImageProcessor_CPU::set_on_threshold(const ITMFloatImage_CPtr& input, ComparisonOperator op, float threshold, float value, const ITMFloatImage_Ptr& output) const
{
  check_image_size_equal(output, input);
  int imgSize = input->noDims.x * input->noDims.y;
  float *outputData = output->GetData(MEMORYDEVICE_CPU);
  const float *inputData = input->GetData(MEMORYDEVICE_CPU);

#ifdef WITH_OPENMP
#pragma omp parallel for
#endif
  for(int locId = 0; locId < imgSize; ++locId)
  {
    shade_pixel_on_comparison(&outputData[locId], inputData[locId], threshold, op, value);
  }
}

}
