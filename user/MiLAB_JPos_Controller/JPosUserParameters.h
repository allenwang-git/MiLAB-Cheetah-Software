#ifndef PROJECT_JPOSUSERPARAMETERS_H
#define PROJECT_JPOSUSERPARAMETERS_H

#include "ControlParameters/ControlParameters.h"

class JPosUserParameters : public ControlParameters {
public:
  JPosUserParameters()
      : ControlParameters("user-parameters"),
        INIT_PARAMETER(max_tau),
        INIT_PARAMETER(max_iter),
        INIT_PARAMETER(move_range),
        INIT_PARAMETER(move_offset),
        INIT_PARAMETER(leg_enable),
        INIT_PARAMETER(joint_enable),
        INIT_PARAMETER(tau_ff),
        INIT_PARAMETER(kpj),
        INIT_PARAMETER(kdj),
        INIT_PARAMETER(zero),
        INIT_PARAMETER(calibrate),
        INIT_PARAMETER(cycle),
        INIT_PARAMETER(step_height),
        INIT_PARAMETER(kpc),
        INIT_PARAMETER(kdc)
      {}

  DECLARE_PARAMETER(double, max_tau);
  DECLARE_PARAMETER(double, max_iter);
  DECLARE_PARAMETER(double, move_range);
  DECLARE_PARAMETER(double, move_offset);
  DECLARE_PARAMETER(Vec4<float>, leg_enable);
  DECLARE_PARAMETER(Vec3<double>, joint_enable);
  DECLARE_PARAMETER(double, tau_ff);
  DECLARE_PARAMETER(Vec3<double>, kpj);
  DECLARE_PARAMETER(Vec3<double>, kdj);
  DECLARE_PARAMETER(double, zero);
  DECLARE_PARAMETER(double, calibrate);
  DECLARE_PARAMETER(double, cycle);
  DECLARE_PARAMETER(double, step_height);
  DECLARE_PARAMETER(Vec3<double>, kpc);
  DECLARE_PARAMETER(Vec3<double>, kdc);
};

#endif //PROJECT_JPOSUSERPARAMETERS_H
