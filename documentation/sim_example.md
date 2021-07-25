# Simulation Example
The simulator default settings can be configured with `config/default-simulator-parameters.yaml` and `config/default-terrain.yaml`.  
The default settings should be good for most uses, and the `default-terrain` file has commented out examples of how to add a mesh, box, and stairs. 
The friction of the floor can be set from within the terrain file.

To launch the simulator, first plug in your joystick, then run `sim/sim` from within the `build` folder.  
Select "Mini Cheetah" and "Simulator", then click "Start".  
Somewhere in the output, you should see：
```
[GameController] Found 1 joystick
```

The left panel allows you to change simulator settings. The most useful setting is `simulation_speed`. 
Defaults are loaded `simulator-defaults.yaml` when the simulator opens.  
The settings file you load must have exactly the same set of parameters as is defined in the code.  
You must recompile `sim` if you add or remove a parameter. 
You can save and load the parameters at any time, but note that the `use_spring_damper` setting will not take effect unless you restart the simulator.

The center panel allows you to change robot settings which are not specific to the controller.  
Defaults are loaded `milab-robot-parameters.yaml` when Mini Cheetah is selected and you click "Start".  
If you stop and start the simulator, the file will be reloaded.  
The settings file you load must have exactly the same set of parameters as is defined in the code.  
You must recompile `sim` if you add or remove a parameter.  
Currently most of these parameters do nothing and many will be removed. 
The most useful setting is `cheater_mode`, which sends the robot code the current position/orientation/velocity of the robot, 
and `controller_dt`, which changes how frequently the control code runs. (The `controller_dt` setting still needs to be tested).

The right panel allows you to change parameters which are specific to your controller, called "User Parameters".  
If your control code does not use user parameters, it will be ignored.  
If your code does use user parameters, then you must load user configuration parameters that match the parameters your code is expecting, or your controller will not start.

To start the robot control code, run `user/MiLAB_Controller/milab_ctrl i s`.  
The `i` argument is for milab-cheetah, and the `s` indicates it should connect to the simulator. 
This uses shared memory to communicate with the simulator. 
The simulator should start running, then, set control mode to 4, and the robot will start trotting.

You can use the joysticks to drive the robot around.  
You will see two robots - the gray one is the actual robot position from the simulation, 
and the red one is the estimate of the robot's position from our state estimator.  
Turning on "cheater_mode" will make the estimated position equal to the actual position.  
To adjust the simulation view, you can click and drag on the screen and scroll. 
Press and hold `t` to make the simulation run as fast as possible. 
Press the **spacebar** to turn on free camera mode, and click and drag to adjust the orientation.

