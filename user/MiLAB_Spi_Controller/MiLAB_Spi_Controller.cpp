#include "MiLAB_Spi_Controller.h"

void MiLAB_Spi_Controller::runController() {
  _mutex.lock();

  u32 idx = 0;
  for(u32 leg = 0; leg < 4; leg++) {
    for(u32 joint = 0; joint < 3; joint++) {
//      _legController->commands[leg].qDes[joint] = command.q_des[idx];
//      _legController->commands[leg].kpJoint(joint,joint) = command.kp_joint[idx];
//      _legController->commands[leg].kdJoint(joint,joint) = command.kd_joint[idx];
      _legController->commands[leg].qDes[joint] = 0.1;
      _legController->commands[leg].kpJoint(joint,joint) = 10;
      _legController->commands[leg].kdJoint(joint,joint) = 1;
      idx++;
    }
  }


  _mutex.unlock();
}