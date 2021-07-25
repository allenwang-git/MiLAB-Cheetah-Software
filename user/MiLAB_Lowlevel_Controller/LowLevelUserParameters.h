#ifndef PROJECT_LOWLEVELUSERPARAMETERS_H
#define PROJECT_LOWLEVELUSERPARAMETERS_H

#include "ControlParameters/ControlParameters.h"

class LowLevelUserParameters : public ControlParameters {
public:
  LowLevelUserParameters()
      : ControlParameters("user-parameters"),
        INIT_PARAMETER(max_tau),
        INIT_PARAMETER(max_iter),
        INIT_PARAMETER(zero),
        INIT_PARAMETER(calibrate)
      {}

  DECLARE_PARAMETER(double, max_tau);
  DECLARE_PARAMETER(double, max_iter);
  DECLARE_PARAMETER(double, zero);
  DECLARE_PARAMETER(double, calibrate);
};

#endif //PROJECT_JPOSUSERPARAMETERS_H
