/**
 * spaint: VoxelMarker_CPU.h
 * Copyright (c) Torr Vision Group, University of Oxford, 2015. All rights reserved.
 */

#ifndef H_SPAINT_VOXELMARKER_CPU
#define H_SPAINT_VOXELMARKER_CPU

#include "../interface/VoxelMarker.h"

namespace spaint {

/**
 * \brief An instance of this class can be used to mark a set of voxels with a semantic label using the CPU.
 */
class VoxelMarker_CPU : public VoxelMarker
{
  //#################### PUBLIC MEMBER FUNCTIONS ####################
public:
  /** Override */
  virtual void clear_labels(SpaintVoxel *voxels, int voxelCount, ClearingSettings settings) const;

  /** Override */
  virtual void mark_voxels(const ORUtils::MemoryBlock<Vector3s>& voxelLocationsMB, SpaintVoxel::PackedLabel label,
                           ITMLib::Objects::ITMScene<SpaintVoxel,ITMVoxelIndex> *scene,
                           ORUtils::MemoryBlock<SpaintVoxel::PackedLabel> *oldVoxelLabelsMB,
                           MarkingMode mode) const;

  /** Override */
  virtual void mark_voxels(const ORUtils::MemoryBlock<Vector3s>& voxelLocationsMB,
                           const ORUtils::MemoryBlock<SpaintVoxel::PackedLabel>& voxelLabelsMB,
                           ITMLib::Objects::ITMScene<SpaintVoxel,ITMVoxelIndex> *scene,
                           ORUtils::MemoryBlock<SpaintVoxel::PackedLabel> *oldVoxelLabelsMB,
                           MarkingMode mode) const;
};

}

#endif
