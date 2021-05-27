# MiLAB-Cheetah-Software 
*Creation Date: 2021.03.01* \
*Contributor: Wang Yinuo, Yang Shuyu* \
*Current Maintainer: Wang Yinuo* \
*Email: dbdxwyn@163.com*

## Contents
1. [Introduction](#Introduction)
2. [Robot Basic Definition](#Robot-Basic-Definition)
3. [Coordinate Definition](#Coordinate-Definition)
4. [Download](#Download)
5. [Build](#Build)
6. [Run Simulator](#Run-Simulator)
7. [Run Real Robot](#Run-Real-Robot)
8. [Dependencies](#Dependencies)
9. [Install Linux RT Kernel for UP-board](#Install-Linux-RT-Kernel-for-UP-board)
10. [Change Controller or Robot](#Change-Controller-or-Robot)
11. [Joystick of Simulation](#Joystick-of-Simulation)
12. [LCM](#LCM)
13. [Operation Guide](#Operation-Guide)
14. [Writing New Controller](#Writing-New-Controller)
15. [Change Log](#Change-Log)


## Introduction
Based on [MIT-Cheetah-Software](https://github.com/mit-biomimetics/Cheetah-Software) open-source project, we developed this repository which contains the Robot and Simulation software for our MiLAB quadruped robot.

* The **common** folder contains the common library with dynamics and utilities.
* The **resources** folder will contain data files, like CAD of the robot used for the visualization.
* The **robot** folder will contain the robot hardware program including serial port, remote commander and spi board.
* The **sim** folder will contain the simulation program. It is the only program which depends on QT.
* The **third-party** folder contains *small* third party libraries that we used, including qp solvers, imu api and other libraries. 
* The **config** folder contains simulator and robot's configuration or parameter files.
* The **scripts** folder contains many shell scripts used when running in a real robot.
* The **lcm-types** folder contains all lcm message definition files and corresponding compiled include files in ./cpp folder.
* The **debug-tools** folder contains several debug tool written in Python when develop this project.
* The **googletest** folder contains googletest files downloaded from github so you can run cmake command without network connection.

## Robot Basic Definition
Although part of the following definitions and settings are also applicable to MIT or UNITREE robots, they are specifically written for MiLAB Robot.
* Default Units in project
```
Length:           m
Angle:            rad
Angular velocity: rad/s
Torque:           N.m
Mass:             kg
Inertia tensor:   kg·m^2
```
* Serial numbers of the legs, joints and links:
```
     FRONT
LEFT 1  0 RIGHT
     3  2
     BACK
```
```
leg 0: FR -- Front-Right           joint 0: Abduction/Adduction(Ab/Ad)       link 0: Hip link
leg 1: FL -- Front-Left            joint 1: Hip                              link 1: Upper link   
leg 2: RR -- Rear-Right            joint 2: Knee                             link 2: Lower link
leg 3: RL -- Rear-Right
```
* Joint limitation

Joint  | LowerBound | UpperBound
-------|------------|-----------
Ab/Ad  |-90°/45°    | 45°/90°
Hip    |-240°       |  60°
Knee   |36°         | 166°

* Size and mass parameters

Part       | Length | Mass
---------  | ------ | ------
Hip link   | 0.1    | 0.766
Upper link | 0.3    | 1.598
Lower link | 0.34   | 0.363
Motor rotor|    \   | 0.084
Body       |0.5779 x 0.152 x 0.153| 13.777
Total robot|    \   | **26.35**

* The Milab Robot model in simulator needs to use at least 5 kinds and totally 13 pieces of mesh parts, because our robot's upper link is mirror symmetrical. Noted that the MIT cheetah robots only use 4 kinds of mesh parts.

## Coordinate Definition
* The coordinate definition and the zero degrees position of each joint are shown as below.\
The rotation axis of the ab/ad joints is the x axis, and the rotation axis of the hip joint and the knee joint is the y axis. 
Due to joint limitation, although we indicate the nominal zero position of knee joints, it's not actually possible to reach there.\
<img src="https://user-images.githubusercontent.com/69251304/112633818-cbb63a80-8e74-11eb-9679-37c465ab8043.png" width="500" height="500" alt="The Coordinate Definition"/><br/>

* The joint rotation axis definition in simulation is shown as below.\
Note that our joint rotation axis definition is different from UNITREE, but it is consistent with MIT, and the positive direction of rotation conforms to the right-hand rule.\
<img src="https://user-images.githubusercontent.com/69251304/112635651-0c16b800-8e77-11eb-9bb2-08ddf950ed4c.png" width="500" height="500" alt="The motorframe"/><br/>

* The actual motor rotation axis definition is shown as below.\
For each motor in our robot, the rotation axis points along the motor shaft from the motor output to the motor driver.\
<img src="https://user-images.githubusercontent.com/69251304/115496834-12912780-a29d-11eb-8142-d62174f64656.png" width="300" height="300" alt="real motorframe"/><br/>

## Download
```
cd 
git clone https://github.com/AWang-Cabin/MiLAB-Cheetah-Software.git
```

## Build 
* [Install all Dependencies](#dependencies) on computer.
* To avoid error about Qt5, following settings should be add to sim/CMakeLists.txt:
    ```
    set(CMAKE_PREFIX_PATH {Your_Qt_PATH}/{Your_Qt_VERSION}/gcc_64)

    set(Qt5Core_DIR {Your_Qt_PATH}/{Your_Qt_VERSION}/gcc_64/lib/cmake/Qt5Core)
    set(Qt5Widgets_DIR {Your_Qt_PATH"/{Your_Qt_VERSION}/gcc_64/lib/cmake/Qt5Widgets)
    set(Qt5Gamepad_DIR {Your_Qt_PATH"/{Your_Qt_VERSION}/gcc_64/lib/cmake/Qt5Gamepad)
    ```
    The default Qt path and version is`~/Qt5.10.0/5.10.0/gcc/...`, so we highly recommand you to install Qt5.10.0 under `/home/user` directory and rename Qt directory to `Qt5.10.0`, which means you do not need to modify CMakeLists.txt any more. 
* To avoid Stack Overflow, append following commands to the end of ~/.bashrc (Not a mandatory step):
    ```
    ulimit -s 102400
    echo "[Bash Info] Stack size has been changed to $(ulimit -s) KB for Milab Quadrupedal"
    ```
* To build all code:
    ```
    mkdir build
    cd build
    cmake ..
    ./../scripts/make_types.sh
    make -j8
    ```
If you are building code on your computer that you would like to copy over to the real robot, go to [Run Real Robot] for details.

If you are building code on the robot's UP-board, you do not need to change above commands.

This build process builds the common library, robot code, and simulator. If you just change robot code, you can simply run `make -j4` again. 

If you change LCM types, you'll need to run `cmake ..; make -j8`. This automatically runs `make_types.sh`.

To test the common library, run `common/test-common`. To run the robot code, run `robot/robot`. To run the simulator, run `sim/sim`.

Part of this build process will automatically download the googletest software testing framework and sets it up. 

After it is done building, it will produce a `libbiomimetics.a` static library and an executable `test-common`.  Run the tests with `common/test-common`. 

This output should hopefully end with
```
[----------] Global test environment tear-down
[==========] 97 tests from 20 test suites ran. (1212 ms total)
[  PASSED  ] 97 tests.
```
## Run Simulator
* To run the simulator, open a command window:
    ```
    cd MiLAB-Cheetah-Software/build
    ./sim/sim
    ```
* In the another command window in the same path, run the robot controller:
    ```
    ./user/${controller_folder}/${controller_name} ${robot_name} ${target_system}
    ``` 
    Example:
    ```
    ./user/MiLAB_Controller/milab_ctrl i s 
    ```
    i: Milab robot,  3: Cheetah 3,  m: Mini Cheetah \
    s: simulation,  r: robot
* For more info, go to see [simulation example](https://github.com/AWang-Cabin/MiLAB-Cheetah-Software/blob/dev2/documentation/sim_example.md)

## Run Real Robot
* [Install Linux System (Recommend Ubuntu 16.04) and RT kernel for UP-board](#install-linux-rt-kernel-for-up-board). 
* [Install all Dependencies except Qt](#dependencies) on robot's UP-board.
* [Finish LCM UDP Multicast Setup](#udp-multicast-setup) fot both PC and UP-board.
* Open terminal and create mc-build folder:
    ```
    cd MiLAB-Cheetah-Software
    mkdir mc-build && cd mc-build
    ```
* Build for milab robot: 
    ```
    cmake -DUP_BOARD=TRUE ..
    ../scripts/make_types.sh
    make -j8
    ``` 
* In a new terminal, connect to robot's UP-board over ethernet or WIFI:
    *  By ethernet: 
        * Set server PC's ethernet ip as`10.0.0.2` 
        * robot's ethernet ip as`10.0.0.21` and then
        ```
        ssh robot@10.0.0.21
        ``` 
    * By WIFI without other pre-settings: 
        ```
        ssh robot@10.61.6.124
        ``` 
    The password of robot's UP-board is `1`

* Go back to the terminal that under server PC account and mc-build path.
* Copy robot-software to robot's UP-board with: 
    For example:
    ```
    sh ../scripts/milab_scripts/send_to_milab_cheetah.sh mpc wire
    ``` 
   *More details in **send_to_milab_cheetah.sh**, default option is sending MiLAB_Controller by WIFI if not specified*

* Go to ssh terminal and enter the robot program folder: 
    ```
    cd robot-software-XXX/build
    ```
* To check the project, you can run test first:
    ```
    ./run_test_common.sh
    ```
* If all 97 tests passed, you can run robot controller: 
    ```
    ./run_milab.sh mpc f l
    ``` 
    or
    ```
    ./run_mc.sh jpos f
    ```
    mpc: MPC controller, spi: Spi connection test, jpos: Joint PD controller
    f: Load parameters from files, l: Load from LCM
    l: Print output to log file (This is an optional param)
 * For more guides, go to [Running Real Robot](https://github.com/AWang-Cabin/MiLAB-Cheetah-Software/blob/dev2/documentation/running_real_robot.md).

## Dependencies
*Following Dependencies Have Been Tested On Ubuntu 16.04 Successfully, But May Meet Some Problem On Other Ubuntu Versions.*
* Update linux software repositories:
    ```
    sudo add-apt-repository ppa:ubuntu-toolchain-r/test
    sudo apt update
    sudo apt upgrade
    ```
* Intall dependent packages:
    ```
    sudo apt install mesa-common-dev freeglut3-dev coinor-libipopt-dev libblas-dev liblapack-dev gfortran cmake gcc build-essential libglib2.0-dev git
    ```
* Check cmake version (Must higher than 3.5)
    ```
    cmake --version
    ```
* Install gcc (If lower than 5.0): 
    ```
    g++ --version
    gcc -v
    ```
    ```
    sudo apt-get install gcc-5 g++-5
    sudo updatedb && sudo ldconfig
    ```
* Install openjdk (Must installed before LCM):
    ```
    sudo apt-get install openjdk-8-jdk default-jdk
    ```
* Install LCM (Recommend lcm-1.4)
    * Download package [lcm-1.4.0](https://github.com/AWang-Cabin/MiLAB-Cheetah-Software/releases/download/v1.0.0/lcm-1.4.0.zip) 
    * Unzip to /home and install (Must unzip to /home)
        ```
        cd lcm-1.4.0
        mkdir build && cd build
        cmake ..
        make -j4
        sudo make install
        sudo ldconfig
        ```
    * [LCM main page](https://lcm-proj.github.io/)

* Install [Eigen](http://eigen.tuxfamily.org/)
    ```
    sudo apt-get install libeigen3-dev
    ```
* Install Qt5 on Ubuntu 16.04 (Recommend Qt5.10)
    * Download package [qt5.10.0](https://github.com/AWang-Cabin/MiLAB-Cheetah-Software/releases/download/v1.0.0/qt-opensource-linux-x64-5.10.0.run) 
    * Run installer 
      ```
      sudo chmod a+x qt-opensource-linux-x64-5.10.0.run
      ./qt-opensource-linux-x64-5.10.0.run
      ```
    * Follow [config instructions](https://github.com/AWang-Cabin/MiLAB-Cheetah-Software/blob/dev2/documentation/qt_install.md)
    * On Ubuntu 18.10 or 19.04, you may instead install Qt directly with command:
        ```
        sudo apt install libqt5 libqt5gamepad5
        ```
* Install IPOPT (Recommend ipopt-3.12.7 or newer)
    * Install dependency
        ```  
        sudo apt-get install cppad subversion patch wget checkinstall
        ```
    * Download package [Ipopt-3.12.7](https://github.com/AWang-Cabin/MiLAB-Cheetah-Software/releases/download/v1.0.0/Ipopt-3.12.7.zip) 
    * Unzip to /home and install third-party lib
        ```
        unzip Ipopt-3.12.7.zip
        cd Ipopt-3.12.7
        ```
        ```
        cd ThirdParty/Blas
        ./get.Blas
    
        cd ../ASL
        ./get.ASL
    
        cd ../Lapack
        ./get.Lapack
    
        cd ../Mumps
        ./get.Mumps
    
        cd ../Metis
        ./get.Metis
        ```
    * Make and install on /usr/local
        ```
        cd ../..
        mkdir build && cd build
        ../configure --prefix=/usr/local/
        sudo make
        sudo make test
        sudo make install
        sudo ldconfig
        ```
    * To use Ipopt, use CMake Ipopt option. Example: cmake -DIPOPT_OPTION=ON ..

## Install Linux RT Kernel for UP-board
To keep real time performance of controller running on UP-board, the ubuntu rt kernel need to be installed.
* Install Ubuntu System
     * Download Ubuntu 16.04.6 ISO from the Ubuntu download page (works with desktop and server edition)
       http://releases.ubuntu.com/16.04/ubuntu-16.04.6-desktop-amd64.iso  \
       http://releases.ubuntu.com/16.04/ubuntu-16.04.6-server-amd64.iso
     * Burn the downloaded image on a USB stick. We suggest to use etcher for doing that. You can download it from:\
       https://etcher.io
     * Insert the USB thumb drive in a empty USB port and proceed with a normal Ubuntu installation.

* Install RT Kernel
     * System required: Ubuntu 16.04 
     * There are several different methods to install rt kernel. Here we choose an easiest way. If you want to build from source code, go to https://github.com/AWang-Cabin/Ubuntu-RT-UP-Board for more instruction about it.
     * Download the compiled rt kernel image package [4.4.86-rt99](https://github.com/AWang-Cabin/MiLAB-Cheetah-Software/releases/download/v1.0.0/UP-board-4.4.86-rt99.zip) for UP-board.
     * Unzip it in /usr/src
          ```
          cd /usr/src
          unzip UP-board-4.4.86-rt99.zip
          ```
     * Install kernel
          ```
          cd UP-board-4.4.86-rt99
          sudo dpkg -i linux-*.deb
          sudo update-grub
          reboot
          ```
          If you want to modify GRUB configuration, 
          ```
          sudo gedit /etc/default/grub
          sudo update-grub
          reboot
          ```
     * Check and Config
          Check kernel:
          ```
          uname -r
          ```
          If rt kernel installed, you will get:
          ```
          4.4.86-rt99
          ```
          Check spi driver:
          ```
          ls /dev/spidev*
          ```
          If driver installed, you will get: 
          ```
          /dev/spidev2.0  /dev/spidev2.1
          ```
          Enable the HAT functionality from userspace:
          ```
          sudo add-apt-repository ppa:ubilinux/up
          sudo apt install upboard-extras
          sudo usermod -a -G gpio ${USER}
          sudo usermod -a -G leds ${USER}
          sudo usermod -a -G spi ${USER}
          sudo usermod -a -G i2c ${USER}
          sudo usermod -a -G dialout ${USER}
          sudo reboot
          ```
     * Test 
          Install requirement
          ```
          sudo apt install rt-tests stress gnuplot
          ```
          Download [rt-kernel-test](https://github.com/AWang-Cabin/MiLAB-Cheetah-Software/releases/download/v1.0.0/rt-kernal-test.tar.gz) and unzip
          ```
          tar xvf rt-kernel-test.tar.gz
          cd rt-kernel-test
          chmod +777 *.sh
          ```
          blink test and then the green led of UP board will blink
          ```
          sudo ./blink.sh
          ```
          real time latency test
          ```
          sudo ./rt-test.sh
          ```
          rt test result will be saved in the directory
   
          
## Change Controller or Robot
Go to the [Instruction of changing Controller Parameters or Robots](https://github.com/AWang-Cabin/MiLAB-Cheetah-Software/blob/dev2/documentation/ChangeController.md) for details.

## Joystick of Simulation
We use the Logitech F310 controller. There's a switch in the back, which should be in the "X" position. 
The controller needs to reconnected if you change the switch position. Also, the LED on the front near the mode button should be off.
(https://www.amazon.com/Logitech-940-000110-Gamepad-F310/dp/B003VAHYQY)

## LCM
We use LCM (https://lcm-proj.github.io/) to connect the control interface to the actual robot hardware, 
and also as a debugging tool when running the simulator. Also, LCM can connect between your PC and robot UP-board by UDP Multicast setup. 
The `make_types.sh` script runs an LCM tool to generate C++ header files for the LCM data types. You can create and make your own lcm data types by `lcm-gen`. 
When the simulator is running, you can run command`lcm-spy` to open the LCM spy utility, which shows detailed information from the simulator and controller.  
You can click on data streams to plot them, which is nice for debugging.  There is also a tool called `lcm-logger` which can save LCM data to a file.
### UDP Multicast Setup
* Using LCM on a single host
     If your computer(**UP-board**) is not connected to any network, you need to explicitly enable multicast traffic by adding multicast entries to your system's routing table. On Linux, you can setup the loopback interface for multicast with the following commands:
     ```
     sudo ifconfig lo multicast
     sudo route add -net 224.0.0.0 netmask 240.0.0.0 dev lo
     ```
     Remember, you must always do this to use LCM if your machine is not connected to any external network.\
     **Note**: Above commands have been added into `run_milab.sh`, so actually you don't need to worry about it now. 
* Using LCM across multiple hosts
     LCM defaultly uses a time-to-live (TTL) value of **0**. This will prevent any LCM packets from being transmitted on the wire. Only local applications will see them. Choose a value of **1** for the entire subnet to see the traffic. Even larger values will enable the packets to pass through routers. However, these routers must be set up with multicast routing tables in order to successfully relay multicast traffic.
     If you want to enable communication between PC and UP-board by LCM, firstly make sure they are connected by ethernet wire and can ssh successfully into each other. Then, you only need to run following commands on both mechines at the first time:
     ```
     echo "export LCM_DEFAULT_URL=udpm://239.255.76.67:7667?ttl=1" >> ~/.bashrc
     source ~/.bashrc
     ```
     **Note**: If you only want to run simulator on you PC, you don't need to do above steps. And multi-host LCM can only run on computers connected by ethernet.
* Learn More  (https://lcm-proj.github.io/multicast_setup.html)

## Operation Guide
* [Real robot operation guide](https://github.com/AWang-Cabin/MiLAB-Cheetah-Software/blob/dev2/documentation/realrobot_opertion_guide.md) 
* [Simulation operation guide](https://github.com/AWang-Cabin/MiLAB-Cheetah-Software/blob/dev2/documentation/simulation_opertion_guide.md)

## Writing New Controller
To add your own robot controller, you should add a folder under `Cheetah-Software/user`, and add the folder to the `CMakeLists.txt` in `user`.  
The `JPos_Controller` is an example of a very simple controller.  
The `JPosUserParameters.h` file has an example of declaring two user parameters which can be adjusted from the simulator interface, but using user parameters is optional.  
The `JPos_Controller.hpp` and `JPos_Controller.cpp` files are the actual controller, which should extend `RobotController`.  
Notice that in the `JPos_Controller.hpp` file, the `getUserControlParameters` method retuns a pointer to the user parameters.  
If you do not use user parameters, your `getUserControlParameters` should return `nullptr`.  
Finally, your `main` function must be like the example main function in `main.cpp`.

The `runController` method of your controller will be called automatically at 1 kHz. 
Here, you have access to the following:
- `_quadruped` : contains constant parameters about the robot (link lengths, gear ratios, inertias...).  The `getHipLocation` function returns the location of the "hip" in the body coordinate system.  The x-axis points forward, y-axis to the left, and z-axis up.  T
- `_model` : a dynamics model of the robot.  This can be used to compute forward kinematics, Jacobians, etc...
- `_legController`: Interface to the robot's legs. This data is syncronized with the hardware at around 700 Hz. There are multiple ways to control the legs, and the result from all the controllers are added together.
    - `commands[leg_id].tauFeedForward` : Leg torque (Nm, at the joint).  Order is ab/ad, hip, knee.
    - `commands[leg_id].forceFeedForward` : Force to apply at foot (N), in hip frame. (Same orientation as body frame, origin is the hip)
    - `commands[leg_id].qDes` : Desired joint position for joint PD controller (radians). Order is ab/ad, hip, knee.  `(0,0,0)` is leg pointing straight down.
    - `commands[leg_id].qdDes` : Desired joint velocity for joint PD controller (rad/sec).
    - `commands[leg_id].pDes, vDes` : Desired foot position/velocity for cartesian PD controller (meters, hip frame)
    - `commands[leg_id].kpCartesian, kdCartesian, kpJoint, kdJoint` : Gains for PD controllers (3x3 matrix).  Use the diagonal entries only.
    - `datas[leg_id].q` : Leg joint encoder (radians).  Order is ab/ad, hip, knee.  `(0,0,0)` is leg pointing straight down.
    - `datas[leg_id].qd` : Leg joint velocity (radians/sec).  Same order as `q`.
    - `datas[leg_id].p`  : Foot cartesian position, in hip frame. (Same orientation as body frame, origin is the hip)
    - `datas[leg_id].v`  : Foot cartesian velocity, in hip frame. 
    - `datas[leg_id].tau` : Estimate of motor torque from combination of all controllers
The joint PD control actually runs at 40 kHz on the motor controllers.
- `_stateEstimate, _stateEstimatorContainer` The result and interface for the provided state estimator.  If you provide the contact state of the robot (which feet are touching the ground), it will determine the robot's position/velocity in the world.
- `_driverCommand` : inputs from the game pad.
- `_controlParameters` : values from the center robot control parameters panel
- `_visualizationData` : interface to add debugging visualizations to the simulator window
- `_robotType` : If you are the mini Cheetah or Cheetah 3 robot.

If you would like to see more of how this works, look at the `robot` folder.  
The `RobotRunner` class actually runs the control code, and connects it with either the `HardwareBridge` or `SimulationBridge`.  
The code in the `rt` folder actually interacts with the hardware.

## Change Log
This list records nearly all files we modified or created for our own MiLAB quadrupedal. \
Remember to check corresponding include files of following source files. \
Whenever you change or add other project files, please update this list. \
**done**: have finished and submitted \
**doing**: working on it now \
**todo**: plan to modify recently or still have *TODO* tips in the file \
**new**: new file specifically for Milab robot
```
**********/MiLAB-Cheetah-Software********************************************
CMakeLists.txt                     *

********/resources*********************************************
                                  done   doing    todo    new
milab_body.obj                     *                       *
milab_hip.obj                      *                       *
milab_upper_link.obj               *                       *
milab_upper_link_mirror.obj        *                       *
milab_lower_link.obj               *                       *


********/config************************************************
                                  done   doing    todo    new
milab-robot-defaults.yaml          *                       *
milab-user-defaults.yaml           *                       *
default-terrain.yaml               *
jpos-user-parameters.yaml          *                       *

********/common************************************************
******/src**                     done   doing    todo     new
****/Dynamics**
Quadruped.cpp                      * 
FloatingBaseModel.cpp              * 
****/SimUtilities**
SpineBoard.cpp                     *
****/ControllerParameters**
ControlParameters.cpp              * 

******/include**
cppTypes.h                         *
****/Dynamics**
Milab.h                            * todo                  *
****/ControlParameters**
SimulatorParameters.h              *
ControlParameters.h                *
RobotParameters.h                  *
****/SimUtilities**
SpineBoard.h                       *
IMUTypes.h
****/Utilities**
utilities.h                        *

********/robot*************************************************
******/src**                     done   doing    todo     new
RobotRunner.cpp                    * todo
main_helper.cpp                    *
HardwareBridge.cpp                 *
SimulationBridge.cpp                 *
****/rt**
rt_rc_interface.cpp                *
rt_subs.cpp                        *
rt_spi.cpp                         *todo
rt_serial.cpp                      *

******/include**
HardwareBridge.h                   *
RobotRunner.h                      *
rt_subs.h                          *
rt_spi.h                           *
rt_rc_interface.h                  *



********/scripts***********************************************
******/milab_scripts**           done   doing    todo     new
send_to_milab_cheetah.sh           *                       *
run_milab.sh                       *                       *
run_test_common.sh                 *                       *

********/sim***************************************************
******/src**                     done   doing    todo     new
Simulation.cpp                     * todo
SimControlPanel.cpp                * todo
SimControlPanel.ui                 *
RobotInterface.cpp                 *
Graphics3D.cpp                     *
DrawList.cpp                       * todo


********/user**************************************************
******/MiLAB_Controller**        done   doing    todo     new
****/Controllers**
**/convexMPC**
RobotState.cpp                     * todo
SolverMPC.cpp                      *
convexMPC_interface.cpp            *
ConvexMPCLocomotion.cpp            * todo
RobotState.h                       *
SolverMPC.h                        *
convexMPC_interface.h              *
ConvexMPCLocomotion.h              *

**/WBC_Ctrl** 
WBC_Ctrl.cpp                       * todo
*/LocomotionCtrl
LocomotionCtrl.cpp                 * todo

****/FSM_States**
ControlFSM.cpp                     *
FSM_State.cpp                      * todo
FSM_State_Locomotion.cpp           * todo
FSM_State_RecoveryStand.cpp        * todo
FSM_State_StandUp.cpp              * todo
FSM_BalanceStand.cpp               * todo
FSM_SquatDown.cpp                  *                        *
FSM_SquatDown.h                    *                        *
SafetyChecker.cpp                  *

******/MiLAB_JPos_Controller**
JPosUserParameters.h               *
JPos_Controller.cpp                *
JPos_Controller.hpp                *

********/third-party*********************************************
******/lord_imu**                 done   doing    todo     new
LordImu.cpp                        *
LordImu.h                          *
****/Source**
mip_sdk_user_functions.c           *
****/Include**
mip_sdk_user_functions.h           *


********/debug-data**********************************************
leg_controller_plot.py             *                        *
positive_matrix_check.py           *                        *

```
