# Milab-Cheetah-Software 
## Workload List
*Created on 2020.03.01 by Wang,Yinuo*\
*Email: dbdxwyn@163.com*

This list records nearly all files we modified or created for our own MiLAB quadrupedal. \
Remember to check corresponding include files of following source files. \
Whenever you change or add other project files, please update this list. \
**done**: have submitted final modification \
**doing**: working on it now \
**todo**: plan to modify recently or still have *TODO* tips in the file \
**new**: new file specifically for Milab robot
```
********/resources*********************************************
                                  done   doing    todo    new
milab_body.obj                      *                      *
milab_hip.obj                       *                      *
milab_upper_link.obj                *                      *
milab_upper_link_mirror.obj         *                      *
milab_lower_link.obj                *                      *


********/config************************************************
                                  done   doing    todo    new
milab-robot-defaults.yaml          *                       *
milab-user-defaults.yaml           *                       *


********/common************************************************
******/src**                     done   doing    todo     new
****/Dynamics**
Quadruped.cpp                      * todo
FloatingBaseModel.cpp                      * 
******/include**
cppTypes.h                         *
****/Dynamics**
need to create file according to MiniCheetah.h:
Milab.h                                    * todo           *
****/ControlParameters
SimulatorParameters.h              *


********/robot*************************************************
******/src**                     done   doing    todo     new
RobotRunner.cpp                    * todo
main_helper.cpp                    *
HardwareBridge.cpp                 *
******/include**
HardwareBridge.h                   *


********/sim***************************************************
******/src**                     done   doing    todo     new
Simulation.cpp                     * todo
SimControlPanel.cpp                * todo
SimControlPanel.ui                 *
RobotInterface.cpp                 *
Graphics3D.cpp                     *
DrawList.cpp                       * todo


********/user**************************************************
******/MIT_Controller**          done   doing    todo     new
****/Controllers**
**/convexMPC**
RobotState.cpp                     * todo
ConvexMPCLocomotion.cpp            * todo
**/WBC_Ctrl** 
WBC_Ctrl.cpp                       * todo
*/LocomotionCtrl
LocomotionCtrl.cpp                 * todo
****/FSM_States**
FSM_State.cpp                      * todo
FSM_State_Locomotion.cpp           * todo
FSM_State_RecoveryStand.cpp                        *
FSM_State_StandUp.cpp              * todo
FSM_BalanceStand.cpp               * todo
SafetyChecker.cpp                  *
```
## Differences
* The coordinates of Milab Robot between abad and upper link is different from MIT cheetah, which are not rotated 180 degree around z-axis. Our difinition makes all 8 hip and knee motors obey the right-hand rule and the direction of the rotation axis parallel to the positive y-axis. Like MIT Cheetah, the rotation direction of 2 front abad motors is parallel to the positive direction of the x-axis, while the rotation direction of rear ones is parallel to the x-axiz negative direction.
* The Milab Robot model in simulator needs to use at least 5 mesh parts, because our robot's upper link is mirror symmetrical.

## Introduction
This repository contains the Robot and Simulation software project. For a getting started guide, see [Getting Started](https://github.com/AWang-Cabin/MiLAB-Cheetah-Software/blob/master/documentation/getting_started.md).

* The **common** folder contains the common library with dynamics and utilities
* The **resources** folder will contain data files, like CAD of the robot used for the visualization
* The **robot** folder will contain the robot program
* The **sim** folder will contain the simulation program. It is the only program which depends on QT.
* The **third-party** will contain *small* third party libraries that we have modified. This should just be libsoem for Cheetah 3, which Pat modified at one point.
* The **config** folder contains simulator and robot's configuration or parameter files.
* The **scripts** folder will be used when run in a real robot.
* The **lcm-types** folder contains all lcm message definition files and corresponding compiled include files in ./cpp folder.

## Build
To avoid error about Qt5, following settings should be add to sim/CMakeLists.txt
```
set(CMAKE_PREFIX_PATH ~/Your_Qt_PATH/Your_Qt_VERSION/gcc_64)

set(Qt5Core_DIR ~/Your_Qt_PATH/Your_Qt_VERSION/gcc_64/lib/cmake/Qt5Core)
set(Qt5Widgets_DIR ~/Your_Qt_PATH/Your_Qt_VERSION/gcc_64/lib/cmake/Qt5Widgets)
set(Qt5Gamepad_DIR ~/Your_Qt_PATH/Your_Qt_VERSION/gcc_64/lib/cmake/Qt5Gamepad)
```
To build all code:
```
mkdir build
cd build
cmake ..
./../scripts/make_types.sh
make -j4
```

If you are building code on your computer that you would like to copy over to the real robot, you must replace the cmake command with
```
cmake -DMINI_CHEETAH_BUILD=TRUE
```
otherwise it will not work.  If you are building mini cheetah code on the mini cheetah computer, you do not need to do this.

This build process builds the common library, robot code, and simulator. If you just change robot code, you can simply run `make -j4` again. If you change LCM types, you'll need to run `cmake ..; make -j4`. This automatically runs `make_types.sh`.

To test the common library, run `common/test-common`. To run the robot code, run `robot/robot`. To run the simulator, run `sim/sim`.

Part of this build process will automatically download the gtest software testing framework and sets it up. After it is done building, it will produce a `libbiomimetics.a` static library and an executable `test-common`.  Run the tests with `common/test-common`. This output should hopefully end with

```
[----------] Global test environment tear-down
[==========] 18 tests from 3 test cases ran. (0 ms total)
[  PASSED  ] 18 tests.
```
## Run simulator
1.To avoid Stack overflow, append following commands to the end of ~/.bashrc
```
ulimit -s 102400
echo "Stack size has been changed to $(ulimit -s) KB"
```
2.To run the simulator, open a command window
```
cd MiLAB-Cheetah-Software/build
./sim/sim
```
3.In the another command window in the same path, run the robot controller
```
./user/${controller_folder}/${controller_name} ${robot_name} ${target_system}
```
Example:
```
./user/MIT_Controller/mit_ctrl i s 
```
i: Milab robot,  3: Cheetah 3,  m: Mini Cheetah \
s: simulation,  r: robot

## Manipulate guidance


## Run Real Robot
0. Find detailed guidance in [Running Mini Cheetah](http://ghttps://github.com/AWang-Cabin/MiLAB-Cheetah-Software/blob/master/documentation/running_mini_cheetah.mdoogle.com)
1. Create build folder `mkdir mc-build`
2. Build as mini cheetah executable `cd mc-build; cmake -DMINI_CHEETAH_BUILD=TRUE ..; make -j`
3. Connect to mini cheetah over ethernet, verify you can ssh in
4. Copy program to mini cheetah with `../scripts/send_to_mini_cheetah.sh`
5. ssh into the mini cheetah `ssh user@10.0.0.34`
6. Enter the robot program folder `cd robot-software-....`
7. Run robot code `./run_mc.sh` 

## Dependencies
- Qt 5.10 - https://www.qt.io/download-qt-installer
- LCM - https://lcm-proj.github.io/ (Please make it sure that you have a java to let lcm compile java-extension together)
- Eigen - http://eigen.tuxfamily.org
- `mesa-common-dev`
- `freeglut3-dev`
- `libblas-dev liblapack-dev`

To use Ipopt, use CMake Ipopt option. Example: cmake -DIPOPT_OPTION=ON ..

