# Instruction of changing Controllers or Robots

There are several different controllers for Cheetah robot in this dir. For example, **MiLAB_Controller** is a MPC-WBC controller, 
and **MiLAB_JPos_Controller** is a joint PD controller. Please noticed that, for different kinds of robots, above controllers 
can be used similarly, except the difference in control parameters. Now the default parameters used in these controllers 
are set for MiLAB Cheetah. 

**Some params are shared in different robots, while others are unique**
* default-simulator-parameters.yaml & default-terrain.yaml are universal
* milab-user-parameters.yaml & milab-robot-parameters.yaml are only used in MiLAB Cheetah
* mc-mit-ctrl-user-parameters.yaml & cheetah-3-defaults.yaml are used for MIT Cheetah

What's more, parameters are totally different in different controllers. Before changing controller listed in **/user**, 
please make sure the user parameters file has been changed.

**For now, we have two version of user parameters in /config**
* jpos-user-parameters.yaml for MiLAB_JPos_Controller
* milab-user-parameters.yaml for MiLAB_Controller
* To select parameter yaml file, go to default-user-parameters-file.yaml
