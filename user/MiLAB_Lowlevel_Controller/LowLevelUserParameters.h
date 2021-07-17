#ifndef PROJECT_LOWLEVELUSERPARAMETERS_H
#define PROJECT_LOWLEVELUSERPARAMETERS_H

#include "ControlParameters/ControlParameters.h"

class LowLevelUserParameters : public ControlParameters {
public:
  LowLevelUserParameters()
      : ControlParameters("user-parameters"),
        INIT_PARAMETER(max_tau),
        INIT_PARAMETER(max_iter),
//        INIT_PARAMETER(move_range),
//        INIT_PARAMETER(move_offset),
        INIT_PARAMETER(leg_enable),
        INIT_PARAMETER(joint_enable),
//        INIT_PARAMETER(tau_ff),
        INIT_PARAMETER(kp),
        INIT_PARAMETER(kd),
        INIT_PARAMETER(zero),
        INIT_PARAMETER(calibrate)
      {}

  DECLARE_PARAMETER(double, max_tau);
  DECLARE_PARAMETER(double, max_iter);
//  DECLARE_PARAMETER(double, move_range);
//  DECLARE_PARAMETER(double, move_offset);
  DECLARE_PARAMETER(Vec4<float>, leg_enable);
  DECLARE_PARAMETER(Vec3<double>, joint_enable);
//  DECLARE_PARAMETER(double, tau_ff);
  DECLARE_PARAMETER(Vec3<double>, kp);
  DECLARE_PARAMETER(Vec3<double>, kd);
  DECLARE_PARAMETER(double, zero);
  DECLARE_PARAMETER(double, calibrate);
};

#endif //PROJECT_JPOSUSERPARAMETERS_H
