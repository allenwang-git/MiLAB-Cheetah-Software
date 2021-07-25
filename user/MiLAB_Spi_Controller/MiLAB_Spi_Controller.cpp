#include "MiLAB_Spi_Controller.h"

void MiLAB_Spi_Controller::runController() {

  u32 idx = 0;
  for(u32 leg = 0; leg < 4; leg++) {
    for(u32 joint = 0; joint < 3; joint++) {
      _legController->commands[leg].qDes[joint] = _legController->datas[leg].q[joint];
      _legController->commands[leg].kpJoint(joint,joint) = 0;
      _legController->commands[leg].kdJoint(joint,joint) = 0;
      _legController->commands[leg].tauFeedForward[joint] = 0.;
      idx++;
    }
  }


  _mutex.unlock();
}