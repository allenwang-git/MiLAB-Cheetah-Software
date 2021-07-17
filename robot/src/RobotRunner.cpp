/*!
 * @file RobotRunner.cpp
 * @brief Common framework for running robot controllers.
 * This code is a common interface between control code and hardware/simulation
 * for mini cheetah and cheetah 3 and milab robot
 *
 */

#include <unistd.h>

#include "RobotRunner.h"
#include "Controllers/OrientationEstimator.h"
#include "Dynamics/Cheetah3.h"
#include "Dynamics/MiniCheetah.h"
#include "Dynamics/Milab.h"
#include "ParamHandler.hpp"
#include "Controllers/PositionVelocityEstimator.h"
#include <fstream>
bool flagSimReal;

RobotRunner::RobotRunner(RobotController* robot_ctrl, 
    PeriodicTaskManager* manager, 
    float period, std::string name):
  PeriodicTask(manager, period, name),
  _lcm(getLcmUrl(255)) {

    _robot_ctrl = robot_ctrl;
  }

/**
 * Initializes the robot model, state estimator, leg controller,
 * robot data, and any control logic specific data.
 */
void RobotRunner::init() {
  printf("[RobotRunner] initialize\n");
#ifdef OUTPUT_LEG_DATA
  //clear debug Data file
  if (flagSimReal) {
      std::ofstream fs(SIM_PATH, std::fstream::out | std::ios_base::trunc);
      fs.close();
      printf("[RobotRunner] Init sim file\n");
  }else {
      std::ofstream fr(REAL_PATH, std::fstream::out | std::ios_base::trunc);
      fr.close();
      printf("[RobotRunner] Init real file\n");
  }
#endif
  // Build the appropriate Quadruped object
  if (robotType == RobotType::MINI_CHEETAH) {
    _quadruped = buildMiniCheetah<float>();
  } else if (robotType == RobotType::MILAB){
    _quadruped = buildMilab<float>();
  }
  else{
      _quadruped = buildCheetah3<float>();
  }

  // Initialize the model and robot data
  _model = _quadruped.buildModel();
  _jpos_initializer = new JPosInitializer<float>(3., controlParameters->controller_dt);

  // Always initialize the leg controller and state entimator
  _legController = new LegController<float>(_quadruped);
  _stateEstimator = new StateEstimatorContainer<float>(
      cheaterState, vectorNavData, _legController->datas,
      &_stateEstimate, controlParameters);
  initializeStateEstimator(false);

  memset(&rc_control, 0, sizeof(rc_control_settings));
  // Initialize the DesiredStateCommand object
  _desiredStateCommand =
    new DesiredStateCommand<float>(driverCommand,
        &rc_control,
        controlParameters,
        &_stateEstimate,
        controlParameters->controller_dt);

  // Controller initializations
  _robot_ctrl->_model = &_model;
  _robot_ctrl->_quadruped = &_quadruped;
  _robot_ctrl->_legController = _legController;
  _robot_ctrl->_stateEstimator = _stateEstimator;
  _robot_ctrl->_stateEstimate = &_stateEstimate;
  _robot_ctrl->_visualizationData= visualizationData;
  _robot_ctrl->_robotType = robotType;
  _robot_ctrl->_driverCommand = driverCommand;
  _robot_ctrl->_controlParameters = controlParameters;
  _robot_ctrl->_desiredStateCommand = _desiredStateCommand;

  _robot_ctrl->initializeController();

}

/**
 * Runs the overall robot control system by calling each of the major components
 * to run each of their respective steps.
 */
void RobotRunner::run() {
  // Run the state estimator step
  //_stateEstimator->run(cheetahMainVisualization);
  _stateEstimator->run();
  //cheetahMainVisualization->p = _stateEstimate.position;
  visualizationData->clear();

  // Update the data from the robot
  setupStep();

  static int count_ini(0);
  ++count_ini;
  if (count_ini < 10) {
    _legController->setEnabled(false);
  } else if (20 < count_ini && count_ini < 30) {
    _legController->setEnabled(false);
  } else if (40 < count_ini && count_ini < 50) {
    _legController->setEnabled(false);
  } else {
    _legController->setEnabled(true);

    if( rc_control.mode == 0 && controlParameters->use_rc ) {
//    if(0){
      if(count_ini%1000 ==0) {
              printf("[RobotRunner] ESTOP mode && use_rc = 1, wait to start...\n");
      }
      for (int leg = 0; leg < 4; leg++) {
        _legController->commands[leg].zero();
      }
      _robot_ctrl->Estop();
//      rc motor test command
        _legController->setEnabled(false);
    }else {
      // Controller
      /*
       * This configuration allows robot to stand from lying pose directly,
       * so that robot won't move its legs when set use_rc = 0
       */
//      if (!_jpos_initializer->IsInitialized(_legController))
        if (0)
      {
        Mat3<float> kpMat;
        Mat3<float> kdMat;
        // Update the jpos feedback gains
        if (robotType == RobotType::MINI_CHEETAH) {
          kpMat << 5, 0, 0, 0, 5, 0, 0, 0, 5;
          kdMat << 0.1, 0, 0, 0, 0.1, 0, 0, 0, 0.1;
        } else if (robotType == RobotType::CHEETAH_3) {
          kpMat << 50, 0, 0, 0, 50, 0, 0, 0, 50;
          kdMat << 1, 0, 0, 0, 1, 0, 0, 0, 1;
        } else if (robotType == RobotType::MILAB){
            kpMat << 5, 0, 0, 0, 5, 0, 0, 0, 5;
            kdMat << 0.1, 0, 0, 0, 0.1, 0, 0, 0, 0.1;
        } else{
          assert(false);
        } 

        for (int leg = 0; leg < 4; leg++) {
          _legController->commands[leg].kpJoint = kpMat;
          _legController->commands[leg].kdJoint = kdMat;
        }
      } else {
        // Run Control 
        _robot_ctrl->runController();
        cheetahMainVisualization->p = _stateEstimate.position;

        // Update Visualization
        _robot_ctrl->updateVisualization();
        cheetahMainVisualization->p = _stateEstimate.position;
      }
    }

  }



  // Visualization (will make this into a separate function later)
  for (int leg = 0; leg < 4; leg++) {
    for (int joint = 0; joint < 3; joint++) {
      cheetahMainVisualization->q[leg * 3 + joint] =
        _legController->datas[leg].q[joint];
    }
  }
  cheetahMainVisualization->p.setZero();
  cheetahMainVisualization->p = _stateEstimate.position;
  cheetahMainVisualization->quat = _stateEstimate.orientation;

  // Sets the leg controller commands for the robot appropriate commands
  finalizeStep();
}

/*!
 * Before running user code, setup the leg control and estimators
 */
void RobotRunner::setupStep() {
  // Update the leg data
  if (robotType == RobotType::MILAB) {
    _legController->updateData(spiData);
  } else if (robotType == RobotType::CHEETAH_3) {
    _legController->updateData(tiBoardData);
  } else if (robotType == RobotType::MINI_CHEETAH) {
      _legController->updateData(spiData);
  } else {
    assert(false);
  }

  // Setup the leg controller for a new iteration
  _legController->zeroCommand();
  _legController->setEnabled(true);
  _legController->setMaxTorqueCheetah3(208.5);

  // state estimator
  // check transition to cheater mode:
  if (!_cheaterModeEnabled && controlParameters->cheater_mode) {
    printf("[RobotRunner] Transitioning to Cheater Mode...\n");
    initializeStateEstimator(true);
    _cheaterModeEnabled = true;
  }

  // check transition from cheater mode:
  if (_cheaterModeEnabled && !controlParameters->cheater_mode) {
    printf("[RobotRunner] Transitioning from Cheater Mode...\n");
    initializeStateEstimator(false);
    _cheaterModeEnabled = false;
  }

  get_rc_control_settings(&rc_control);

}

/*!
 * After the user code, send leg commands, update state estimate, and publish debug data
 */
void RobotRunner::finalizeStep() {
  if (robotType == RobotType::MILAB) {
    _legController->updateCommand(spiCommand);
  } else if (robotType == RobotType::CHEETAH_3) {
    _legController->updateCommand(tiBoardCommand);
  } else if (robotType == RobotType::MINI_CHEETAH) {
      _legController->updateCommand(spiCommand);
  } else {
    assert(false);
  }
  _legController->setLcm(&leg_control_data_lcm, &leg_control_command_lcm, _iterations);
  _stateEstimate.setLcm(state_estimator_lcm);
  _lcm.publish("leg_control_command", &leg_control_command_lcm);
  _lcm.publish("leg_control_data", &leg_control_data_lcm);
  _lcm.publish("state_estimator", &state_estimator_lcm);
  //  print leg cmd and data, state estimation output.
  #ifdef DEBUG_SHOW
  debugPrint(_legController,_stateEstimate);
  #endif
  _iterations++;
}

/*!
 * Reset the state estimator in the given mode.
 * @param cheaterMode
 */
void RobotRunner::initializeStateEstimator(bool cheaterMode) {
  _stateEstimator->removeAllEstimators();
  _stateEstimator->addEstimator<ContactEstimator<float>>();
  Vec4<float> contactDefault;
  contactDefault << 0.5, 0.5, 0.5, 0.5;
  _stateEstimator->setContactPhase(contactDefault);
  if (cheaterMode) {
    _stateEstimator->addEstimator<CheaterOrientationEstimator<float>>();
    _stateEstimator->addEstimator<CheaterPositionVelocityEstimator<float>>();
  } else {
    _stateEstimator->addEstimator<VectorNavOrientationEstimator<float>>();
    _stateEstimator->addEstimator<LinearKFPositionVelocityEstimator<float>>();
  }
}

RobotRunner::~RobotRunner() {
  delete _legController;
  delete _stateEstimator;
  delete _jpos_initializer;
}

void RobotRunner::cleanup() {}

void RobotRunner::debugPrint(LegController<float>* legs, StateEstimate<float> states){
    if (_iterations==100){
        for (int i = 0; i < 4; ++i) {
            if (std::abs(legs->datas[i].q[0]) > 0.19 || std::abs(legs->datas[i].q[0]) < 0.04)
                motorError = true;
            if (legs->datas[i].q[1] > -1.25 || legs->datas[i].q[1] < -1.35)
                motorError = true;
            if (legs->datas[i].q[2] > 2.92 || legs->datas[i].q[2] < 2.80)
                motorError = true;
        }
    }

    if (_iterations%10000==0)
    {
        if (motorError && !flagSimReal){
            printf("\033[1;33m**************************************************\n");
            printf("**************************************************\n");
            printf("******\033[0m            \033[1;31mFATAL ERROR\033[0m               \033[1;33m******\n");
            printf("******\033[0m \033[1;31mMotor Zero Initialization Is Wrong!\033[0m  \033[1;33m******\n");
            printf("******\033[0m     \033[1;31mRestart Motors And Controller!\033[0m   \033[1;33m******\n");
            printf("**************************************************\n");
            printf("**************************************************\033[0m\n");
        }
        printf("Iteration Stamp:\t%d\n",(int)_iterations);
        printf("--------------------STATE-------------------------\n");
        printf("POS = [%f, %f, %f]\n", states.position[0],states.position[1],states.position[2]);
        printf("RPY = [%f, %f, %f]\n", states.rpy[0],states.rpy[1],states.rpy[2]);
        printf("VEL = [%f, %f, %f]\n", states.vWorld[0],states.vWorld[1],states.vWorld[2]);
        printf("OMG = [%f, %f, %f]\n", states.omegaWorld[0],states.omegaWorld[1],states.omegaWorld[2]);
        printf("CONTACT = [%f, %f, %f, %f]\n", states.contactEstimate[0],states.contactEstimate[1],states.contactEstimate[2], states.contactEstimate[3]);
        printf("--------------------DATA--------------------------\n");
        printf("ABAD Q = [%f, %f, %f, %f]\n", legs->datas[0].q[0],legs->datas[1].q[0],legs->datas[2].q[0],legs->datas[3].q[0]);
        printf("HIP  Q = [%f, %f, %f, %f]\n", legs->datas[0].q[1],legs->datas[1].q[1],legs->datas[2].q[1],legs->datas[3].q[1]);
        printf("KNEE Q = [%f, %f, %f, %f]\n", legs->datas[0].q[2],legs->datas[1].q[2],legs->datas[2].q[2],legs->datas[3].q[2]);
        printf("ABAD QD = [%f, %f, %f, %f]\n", legs->datas[0].qd[0],legs->datas[1].qd[0],legs->datas[2].qd[0],legs->datas[3].qd[0]);
        printf("HIP  QD = [%f, %f, %f, %f]\n", legs->datas[0].qd[1],legs->datas[1].qd[1],legs->datas[2].qd[1],legs->datas[3].qd[1]);
        printf("KNEE QD = [%f, %f, %f, %f]\n", legs->datas[0].qd[2],legs->datas[1].qd[2],legs->datas[2].qd[2],legs->datas[3].qd[2]);
//        printf("-------------------COMMAND------------------------\n");
//        printf("ABAD DES Q = [%f, %f, %f, %f]\n", legs->commands[0].qDes[0],legs->commands[1].qDes[0],legs->commands[2].qDes[0],legs->commands[3].qDes[0]);
//        printf("HIP  DES Q = [%f, %f, %f, %f]\n", legs->commands[0].qDes[1],legs->commands[1].qDes[1],legs->commands[2].qDes[1],legs->commands[3].qDes[1]);
//        printf("KNEE DES Q = [%f, %f, %f, %f]\n", legs->commands[0].qDes[2],legs->commands[1].qDes[2],legs->commands[2].qDes[2],legs->commands[3].qDes[2]);
//        printf("KP A= [%f, %f, %f, %f]\n", legs->commands[0].kpJoint(0,0),legs->commands[1].kpJoint(0,0),legs->commands[2].kpJoint(0,0),legs->commands[3].kpJoint(0,0));
//        printf("KP H= [%f, %f, %f, %f]\n", legs->commands[0].kpJoint(1,1),legs->commands[1].kpJoint(1,1),legs->commands[2].kpJoint(1,1),legs->commands[3].kpJoint(1,1));
//        printf("KP K= [%f, %f, %f, %f]\n", legs->commands[0].kpJoint(2,2),legs->commands[1].kpJoint(2,2),legs->commands[2].kpJoint(2,2),legs->commands[3].kpJoint(2,2));
//        printf("KD A= [%f, %f, %f, %f]\n", legs->commands[0].kdJoint(0,0),legs->commands[1].kdJoint(0,0),legs->commands[2].kdJoint(0,0),legs->commands[3].kdJoint(0,0));
//        printf("KD H= [%f, %f, %f, %f]\n", legs->commands[0].kdJoint(1,1),legs->commands[1].kdJoint(1,1),legs->commands[2].kdJoint(1,1),legs->commands[3].kdJoint(1,1));
//        printf("KD K= [%f, %f, %f, %f]\n", legs->commands[0].kdJoint(2,2),legs->commands[1].kdJoint(2,2),legs->commands[2].kdJoint(2,2),legs->commands[3].kdJoint(2,2));
//        printf("ABAD DES T = [%f, %f, %f, %f]\n", legs->commands[0].tauFeedForward[0],legs->commands[1].tauFeedForward[0],legs->commands[2].tauFeedForward[0],legs->commands[3].tauFeedForward[0]);
//        printf("HIP  DES T = [%f, %f, %f, %f]\n", legs->commands[0].tauFeedForward[1],legs->commands[1].tauFeedForward[1],legs->commands[2].tauFeedForward[1],legs->commands[3].tauFeedForward[1]);
//        printf("KNEE DES T = [%f, %f, %f, %f]\n", legs->commands[0].tauFeedForward[2],legs->commands[1].tauFeedForward[2],legs->commands[2].tauFeedForward[2],legs->commands[3].tauFeedForward[2]);
        printf("--------------------------------------------------\n");
    }
}