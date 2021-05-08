# Instruction of changing Controller Parameters or Robots

There are several different controllers for Cheetah robot in this dir. For example, **MiLAB_Controller** is a MPC-WBC controller, 
and **MiLAB_JPos_Controller** is a joint PD controller. Please noticed that, for different kinds of robots, above controllers 
can be used similarly, except the difference in control parameters. Now the default parameters used in these controllers 
are set for MiLAB Cheetah. 

# Change Parameters
**Some params are shared in different robots, while others are unique**
* default-simulator-parameters.yaml & default-terrain.yaml are universal
* milab-user-parameters.yaml & milab-robot-parameters.yaml are only used in MiLAB Cheetah
* mc-mit-ctrl-user-parameters.yaml & cheetah-3-defaults.yaml are used for MIT Cheetah

What's more, parameters are totally different in different controllers. Before changing controller listed in **/user**, 
please make sure the user parameter file has been changed.

### Simulation
For now, we have two version of user parameters in **/config/default-user-parameters-file.yaml**
* **jpos-user-parameters.yaml** for MiLAB_JPos_Controller
* **milab-user-parameters.yaml** for MiLAB_Controller
* **no-parameters.yaml** for MiLAB_Spi_Controller

### Real Robot
To change params for different controllers, select Macro in **/robot/HardwareBridge.cpp**
* **\#define JPOS_CTRL** for MiLAB_JPos_Controller
* **\#define CMPC_CTRL** for MiLAB_Controller
* **\#define SPI_CTRL** for MiLAB_Spi_Controller