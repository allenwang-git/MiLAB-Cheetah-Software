#ifndef LOWLEVEL_CONTROLLER
#define LOWLEVEL_CONTROLLER

#include <RobotController.h>
#include "LowLevelUserParameters.h"
#include <lcm/lcm-cpp.hpp>
#include "lowlevel_cmd.hpp"
#include "lowlevel_state.hpp"
#include <Controllers/LegController.h>
#include <thread>
#include <mutex>

class Lowlevel_Controller:public RobotController{
  public:
    Lowlevel_Controller():RobotController(), _lcm(getLcmUrl(255)) {
        _lcmThread = std::thread([&](){for(;;) _lcm.handle();});
    }

    void all_Passive();
    void pub_sub_lcm();
    void handleLowlevelCmdLCM(const lcm::ReceiveBuffer *rbuf, const std::string &chan, const lowlevel_cmd *msg);
    virtual ~Lowlevel_Controller(){}

    virtual void initializeController();
    virtual void runController();
    virtual void updateVisualization(){}
    virtual ControlParameters* getUserControlParameters() {
      return &userParameters;
    }
  protected:
    Vec3<float> zero_vec3;
    LowLevelUserParameters userParameters;
  private:
    long l_iter=0;
    int motion_iter=0;
    lcm::LCM _lcm;
    std::thread _lcmThread;
};

#endif
