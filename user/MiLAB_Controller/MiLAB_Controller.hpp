#ifndef MILAB_CONTROLLER
#define MILAB_CONTROLLER

#include <RobotController.h>
#include "Controllers/GaitScheduler.h"
#include "Controllers/ContactEstimator.h"
#include "FSM_States/ControlFSM.h"
#include "MiLAB_UserParameters.h"
//#include <gui_main_control_settings_t.hpp>

class MiLAB_Controller: public RobotController{
public:
  MiLAB_Controller();
  virtual ~MiLAB_Controller(){}

  virtual void initializeController();
  virtual void runController();
  virtual void updateVisualization(){}
  virtual ControlParameters* getUserControlParameters() {
    return &userParameters;
  }
  virtual void Estop(){ _controlFSM->initialize(); }


protected:
  ControlFSM<float>* _controlFSM;
  // Gait Scheduler controls the nominal contact schedule for the feet
  GaitScheduler<float>* _gaitScheduler;
  MiLAB_UserParameters userParameters;

};


#endif
