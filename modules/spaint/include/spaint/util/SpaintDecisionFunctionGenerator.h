/**
 * spaint: SpaintDecisionFunctionGenerator.h
 */

#ifndef H_SPAINT_SPAINTDECISIONFUNCTIONGENERATOR
#define H_SPAINT_SPAINTDECISIONFUNCTIONGENERATOR

#include <rafl/decisionfunctions/CompositeDecisionFunctionGenerator.h>

#include "SpaintVoxel.h"

namespace spaint {

/**
 * \brief An instance of this class can be used to generate a decision function with which to split a set of spaint examples.
 *
 * An spaint example consists of a feature vector for an individual voxel and a semantic label for that voxel. A feature vector for a
 * voxel is split into three segments:
 *
 * 1) A voxel-oriented patch (VOP) segment of size (patchSize * patchSize * 3) that captures LAB colour information from a small patch
 *    of the surface plane at the voxel.
 * 2) A normal segment of size 3 that contains the surface normal at the voxel.
 * 3) A height segment of size 1 that contains the vertical displacement of the voxel from the dominant horizontal plane in the scene.
 *
 * An spaint decision function generator contains a separate subsidiary generator for each segment. When asked to generate a candidate
 * decision function, it randomly picks a segment and then uses the generator for that segment to generate the candidate.
 */
class SpaintDecisionFunctionGenerator : public rafl::CompositeDecisionFunctionGenerator<SpaintVoxel::LabelType>
{
  //#################### CONSTRUCTORS ####################
public:
  /**
   * \brief Constructs an spaint decision function generator.
   *
   * \param patchSize The side length of a VOP patch.
   */
  explicit SpaintDecisionFunctionGenerator(size_t patchSize);

  //#################### PUBLIC MEMBER FUNCTIONS ####################
public:
  /**
   * \brief Gets the type of the decision function generator.
   *
   * \return  The type of the decision function generator.
   */
  static std::string get_static_type();

  /** Override */
  virtual std::string get_type() const;
};

}

#endif
