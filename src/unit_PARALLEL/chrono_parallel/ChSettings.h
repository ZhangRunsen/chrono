// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2014 projectchrono.org
// All right reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================
// Authors: Hammad Mazhar
// =============================================================================
//
// Description: This file contains all of the setting structures that are used
// within chrono parallel. THe constructor for each struct should specify
// default values for every setting parameter
// =============================================================================

#ifndef CH_SETTINGS_H
#define CH_SETTINGS_H

#include "chrono_parallel/ChParallelDefines.h"
#include "parallel/ChOpenMP.h"

namespace chrono {
// collision_settings, like the name implies is the structure that contains all
// settings associated with the collision detection step of chrono parallel
struct collision_settings {
	// The default values are specified in the constructor, use these as
	// guidelines when experimenting with your own simulation setup.
  collision_settings() {
    use_aabb_active = false;
    // I chose to set the default envelope because there is no good default
    // value (in my opinion, feel free to disagree!) I suggest that the envelope
    // be set to 5-10 percent of the smallest object radius. Using too large of
    // a value will slow the collision detection down.
    collision_envelope = 0;
    // The number of slices in each direction will greatly effect the speed at
    // which the collision detection operates. I would suggest that on average
    // the number of objects in a bin/grid cell should not exceed 100.
    // NOTE!!! this really depends on the architecture that you run on and how
    // many cores you are using.
    bins_per_axis = I3(20, 20, 20);
    narrowphase_algorithm = NARROWPHASE_HYBRID_MPR;
    // edge_radius = 0.1;
  }

  real3 min_bounding_point, max_bounding_point;
  // This parameter, similar to the one in chrono inflates each collision shape
  // by a certain amount. This is necessary when using DVI as it creates the
  // contact constraints before objects acutally come into contact. In general
  // this helps with stability.
  real collision_envelope;
  // Chrono parallel has an optional feature that allows the user to set a
  // bounding box that automatically freezes (makes inactive) any object that
  // exits the bounding box
  bool use_aabb_active;
  // The size of the bounding box (if set to active) is specified by its min and
  // max extents
  real3 aabb_min, aabb_max;
  // This variable is the primary method to control the granularity of the
  // collision detection grid used for the broadphase.
  // As the name suggests, it is the number of slices along each axis. During
  // the broadphase stage the extents of the simulation are computed and then
  // sliced according to the variable.
  int3 bins_per_axis;
  // There are multiple narrowphase algorithms implemented in the collision
  // detection code. The narrowphase_algorithm parameter can be used to change
  // the type of narrowphase used at runtime.
  NARROWPHASETYPE narrowphase_algorithm;
  // real edge_radius;
};

struct solver_settings {

  solver_settings() {
    tolerance = 1e-4;
    tolerance_objective = 1e-6;
    collision_in_solver = false;
    update_rhs = false;
    verbose = false;
    test_objective = false;

    alpha = .2;
    contact_recovery_speed = .6;
    bilateral_clamp_speed = .6;
    clamp_bilaterals = true;
    perform_stabilization = false;
    collision_in_solver = false;

    max_iteration = 100;
    max_iteration_normal = 0;
    max_iteration_sliding = 100;
    max_iteration_spinning = 0;
    max_iteration_bilateral = 100;

    solver_type = APGD;
    solver_mode = SLIDING;
    step_size = .01;
  }

  SOLVERTYPE solver_type;
  SOLVERMODE solver_mode;
  real alpha;

  real contact_recovery_speed;
  real bilateral_clamp_speed;
  bool clamp_bilaterals;
  bool perform_stabilization;
  bool collision_in_solver;
  bool update_rhs;
  bool verbose;
  bool test_objective;

  uint max_iteration;
  uint max_iteration_normal;
  uint max_iteration_sliding;
  uint max_iteration_spinning;
  uint max_iteration_bilateral;

  // Solver variables
  real step_size;
  real tolerance;
  real tolerance_objective;
};

struct settings_container {

  settings_container() {
    min_threads = 1;
    max_threads = CHOMPfunctions::GetNumProcs();
    // Only perform thread tuning if max threads is greater than min_threads;
    // I don't really check to see if max_threads is > than min_threads
    // not sure if that is a huge issue
    perform_thread_tuning = ((min_threads == max_threads) ? false : true);
    perform_bin_tuning = true;
    system_type = SYSTEM_DVI;
    bin_perturb_size = 2;    // increase or decrease the number of bins by 2
    bin_tuning_frequency = 20;    // bins will be tuned every 20 frames
  }

  // CD Settings
  collision_settings collision;
  // Solver Settings
  solver_settings solver;
  // System Settings
  bool perform_thread_tuning;
  bool perform_bin_tuning;
  int bin_perturb_size;
  int bin_tuning_frequency;
  int min_threads;
  int max_threads;
  SYSTEMTYPE system_type;
};
}

#endif
