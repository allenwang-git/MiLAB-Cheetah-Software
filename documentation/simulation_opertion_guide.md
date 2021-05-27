# Simulation Operation Guide
Author: Yinuo Wang\
Date: 2021.05.27\
Email: dbdxwyn@163.com

## Select Robot and Mode
* The default robot is **Milab** Robot and **Simulator** Mode. 
* You can also select **Cheetah3** or **MiniCheetah** robot if you want. 
* If the real robot is not connected with PC by ethernet, do not select **Robot** Mode.

## Start Up
* Click **Start** button to start the simulation environment, but only when you start controller in another terminal, the robot will run in it.
* Click **Stop** button to stop the simulation environment but not quit the simulation. You can click Start again to restart the environment.

## Parameters
* There are 3 parameter tables in the sim GUI, and we usually do not need to change params in **Simulator Parameters**.
* There are some useful and important params in **Robot Parameters**
    * `cheater_mode`: Choose the *real states(1)* or the *estimated states(0)* as the robot states input.
    * `control_mode`: Select the robot mode:
    
        |Mode           | Value | Trans Logic |
        |---------------|-------|-------------|
        |PASSIVE        |   0   |  0,6        |
        |STAND UP       |   1   |  0,1,2,3,6  |
        |SQUAD DOWN     |   2   |  0,1,2,3,6  |
        |BALANCE STAND  |   3   |  0,1,2,3,4,6|   
        |LOCOMOTION     |   4   |  0,3,4,6    |   
        |RECOVERY STAND |   6   |  0,1,2,3,4,6|     
        |VISION	        |   8   |Not Available|         
        
    * `use_rc`: Using Remote Commander or using Joystick.
* There are also some params you need to know in **User Parameters**.
   
    **`JPos_Controller:`**
    * `max_iter`: The max iterations controller loop will run. 
    * `max_tau`: The max feedforward joint torque.
    * `leg_enable`: Select which leg you need to control.
    * `joint_enable`: Select which joint in each leg you want to control.
    * `kp, kd`: The Kp and Kd factor of joint PD controller.
    * `tau_ff`: The feedforward joint torque of joint PD controller.
    * `move_range`: The joint sine movement range -- move_range * sin(x).
    * `move_offset`: The joint sine movement offset -- sin(x) + move_offset.
     
    **`MPC_Controller:`**
    * `use_wbc`： Using WBC or not.  
    * `cmpc_gait`： Select locomotion gait type
            
         |Gait           | Value |
         |---------------|-------|
         |Bounding       |   1   |
         |Pronking       |   2   |
         |Walking        |   3   |
         |Standing       |   4   |
         |Trot-running   |   5   |
         |Galloping      |   6   |
         |Random         |   7   |
         |Pacing         |   8   |
         |Trotting       |   9   |
    
    * `Q_ang, Q_ori, Q_pos, Q_vel, R`：The weight matrix of MPC problem. 
    * `Kp_body, Kp_ori, Kp_foot, Kd_body, Kd_ori, Kd_foot`：The Kp, Kd factor of WBC Null Space control. 
    * `Swing_traj_height`：foot step height. 

## Kick & Go Home
* After appointing the additional kick velocity, click the **Kick** button to disturb the robot.
* Click the **Go Home** button to put the robot to origin point with certain joint angles, which is useless when robot is emergently stopped.

## Operation Step
* Run the simulator and controller.
* Set `use_rc` to `0` to enable simulator.
* Set `cheater_mode` to `1` if you want.
* Set `control_mode` from `0` to `1` and the robot will stand up.
* Set `control_mode` from `1` to `3` and the robot will enter BALANCE STAND. Then you can change the robot posture by the Left and Right stick on the joystick.
* Set `control_mode` from `3` to `4` and the robot will enter LOCOMOTION. Then you can command the robot to go forward or backward, move left or right by the Left stick and turn left or right by the Right stick.
* You can change `cmpc_gait` to select different gait type when the robot in LOCOMOTION mode.
* If the robot fall down, Set `control_mode` to `6` and the robot will recover and stand up again.
* If the robot fall down and enter ESTOP mode, the only thing you can do is to click **Stop** button to restart the simulator.

