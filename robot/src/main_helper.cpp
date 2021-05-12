/*!
 * @file main.cpp
 * @brief Main Function for the robot program
 *
 * The main function parses command line arguments and starts the appropriate
 * driver.
 */

#include <cassert>
#include <iostream>

#include "HardwareBridge.h"
#include "SimulationBridge.h"
#include "main_helper.h"
#include "RobotController.h"

MasterConfig gMasterConfig;

/*!
 * Print a message describing the command line flags for the robot program
 */
void printUsage() {
  printf(
      "Usage: robot [robot-id] [sim-or-robot] [parameters-from-file]\n"
      "\twhere robot-id:     i for milab cheetah, 3 for cheetah 3, m for mini-cheetah\n"
      "\t      sim-or-robot: s for sim, r for robot\n"
      "\t      param-file:   f for loading parameters from file, l (default option if no input) for LCM\n"
      "                      this option can only be used in robot mode\n");
}

/*!
 * Setup and run the given robot controller
 */
int main_helper(int argc, char** argv, RobotController* ctrl) {
  if (argc != 3 && argc != 4) {
    printUsage();
    return EXIT_FAILURE;
  }

  if (argv[1][0] == 'i') {
    gMasterConfig._robot = RobotType::MILAB;
//  } else if (argv[1][0] == 'm') {
//    gMasterConfig._robot = RobotType::MINI_CHEETAH;
  } else if (argv[1][0] == '3') {
      gMasterConfig._robot = RobotType::CHEETAH_3;
  } else {
    printUsage();
    return EXIT_FAILURE;
  }

  if (argv[2][0] == 's') {
    gMasterConfig.simulated = true;
  } else if (argv[2][0] == 'r') {
    gMasterConfig.simulated = false;
  } else {
    printUsage();
    return EXIT_FAILURE;
  }

  if(argc == 4 && argv[3][0] == 'f') {
    gMasterConfig.load_from_file = true;
    printf("[main] Load parameters from file\n");
  } else {
    gMasterConfig.load_from_file = false;
    printf("[main] Load parameters from network\n");
  }

  printf("[Quadruped] Cheetah Software\n");
  printf("        Quadruped:  %s\n",
         gMasterConfig._robot == RobotType::MILAB ? "Milab Robot" : "MIT Cheetah");
  printf("        Driver: %s\n", gMasterConfig.simulated
                                     ? "Development Simulation Driver"
                                     : "Quadruped Driver");

  // dispatch the appropriate driver
  if (gMasterConfig.simulated) {
    if(argc != 3) {
      printUsage();
      return EXIT_FAILURE;
    }
    if (gMasterConfig._robot == RobotType::MILAB) {
      SimulationBridge simulationBridge(gMasterConfig._robot, ctrl);
      simulationBridge.run();
      printf("[Quadruped] SimDriver run() has finished!\n");
    } else if (gMasterConfig._robot == RobotType::CHEETAH_3) {
      SimulationBridge simulationBridge(gMasterConfig._robot, ctrl);
      simulationBridge.run();
    } else {
      printf("[ERROR] unknown robot\n");
      assert(false);
    }
  } else {
#ifdef linux
    if (gMasterConfig._robot == RobotType::MILAB) {
        MilabHardwareBridge hw(ctrl, gMasterConfig.load_from_file);
        hw.run();
        printf("[Quadruped] HardwareDriver run() has finished!\n");
//    } else if (gMasterConfig._robot == RobotType::MINI_CHEETAH) {
//      MiniCheetahHardwareBridge hw(ctrl, gMasterConfig.load_from_file);
//      hw.run();
//      printf("[Quadruped] HardwareDriver run() has finished!\n");
    } else if (gMasterConfig._robot == RobotType::CHEETAH_3) {
      Cheetah3HardwareBridge hw(ctrl);
      hw.run();
    } else {
      printf("[ERROR] unknown robot\n");
      assert(false);
    }
#endif
  }

  return 0;
}
