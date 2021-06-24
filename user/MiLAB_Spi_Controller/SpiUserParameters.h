#ifndef PROJECT_SPIUSERPARAMETERS_H
#define PROJECT_SPIUSERPARAMETERS_H

#include "ControlParameters/ControlParameters.h"

class SpiUserParameters : public ControlParameters {
public:
  SpiUserParameters()
      : ControlParameters("user-parameters"){}
};

#endif //PROJECT_SPIUSERPARAMETERS_H
