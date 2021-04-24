#include "JPos_Controller.hpp"
# include <iostream>
/*
 * This controller is able to control any number of legs and any number of joints by setting the joint_enable
 * and leg_enable param in jpos-user-parameters.yaml. KP, KD, feedforward-torque can also be tuned in that file.
 * By modifying this file, the robot motion logic can be changed as you need.
 *
 * Wang Yinuo, 04/24/2021, dbdxwyn@163.com
 */
void JPos_Controller::runController(){

  Mat3<float> kpMat;
  Mat3<float> kdMat;
  //kpMat << 20, 0, 0, 0, 20, 0, 0, 0, 20;
  //kdMat << 2.1, 0, 0, 0, 2.1, 0, 0, 0, 2.1;
  kpMat << userParameters.kp[0], 0, 0, 0,  userParameters.kp[1], 0, 0, 0,  userParameters.kp[2];
  kdMat <<  userParameters.kd[0], 0, 0, 0, userParameters.kd[1], 0, 0, 0, userParameters.kd[2];

  static int iter(0);
  ++iter;

  if(iter < 100){
    for(int leg(0); leg<4; ++leg){
      for(int jidx(0); jidx<3; ++jidx){
        _jpos_ini[3*leg+jidx] = _legController->datas[leg].q[jidx];
      }
    }
  }

  if (iter%5000 == 0 && iter < userParameters.max_iter)
      printf("[Jpos_Ctrl] INFO: Control iteration is %d now ...\n\n", iter);

  _legController->_maxTorque = userParameters.max_tau;
  _legController->_legsEnabled = true;

    if(userParameters.calibrate > 0.4) {
        _legController->_calibrateEncoders = userParameters.calibrate;
    } else {
        if(userParameters.zero > 0.5) {
            _legController->_zeroEncoders = true;
        } else {
            _legController->_zeroEncoders = false;
            if (iter>= 100 && iter <= userParameters.max_iter){
                for(int leg(0); leg<4; ++leg){
                    if (userParameters.leg_enable[leg]){ // check leg enable state
                        for(int jidx(0); jidx<3; ++jidx){
                            float pos = std::sin(.001f * (iter-100));

                            if (userParameters.joint_enable[jidx]){ //check joint enable state
                                if (jidx == 2)
                                    _legController->commands[leg].qDes[jidx] = userParameters.move_range * pos + _jpos_ini[3*leg+jidx] - userParameters.move_offset;
                                else
                                    _legController->commands[leg].qDes[jidx] = userParameters.move_range * pos + _jpos_ini[3*leg+jidx];
                                _legController->commands[leg].qdDes[jidx] = 0.;
                                _legController->commands[leg].tauFeedForward[jidx] = userParameters.tau_ff;
                            }else{
                                _legController->commands[leg].tauFeedForward[jidx] = 0.;
                                kpMat(jidx,jidx) = 0.;
                                kdMat(jidx,jidx) = 0.;
                            }
                        }
                        _legController->commands[leg].kpJoint = kpMat;
                        _legController->commands[leg].kdJoint = kdMat;
//                        std::cout<<_legController->commands[leg].kpJoint<<std::endl;
                    }else{
                        _legController->commands[leg].kpJoint = kpMat.setZero();
                        _legController->commands[leg].kdJoint = kdMat.setZero();
                        for (int jidx = 0; jidx < 3; ++jidx) {
                            _legController->commands[leg].tauFeedForward[jidx] = 0.;
                        }
                    }
                }
            }
            else{
                for(int leg(0); leg<4; ++leg){
                    _legController->commands[leg].kpJoint = kpMat.setZero();
                    _legController->commands[leg].kdJoint = kdMat.setZero();
                    for (int jidx = 0; jidx < 3; ++jidx) {
                        _legController->commands[leg].tauFeedForward[jidx] = 0.;
                    }
                }
            }
        }
    }
}
