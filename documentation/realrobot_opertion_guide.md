# Real Robot Operation Guide
Author: Yinuo Wang\
Date: 2021.04.13\
Email: dbdxwyn@163.com
## Remote Commander
**1.Introduction**
<img src="https://user-images.githubusercontent.com/69251304/114665702-ef5ff880-9d2f-11eb-84d0-a2a2d67d967f.png" width="500" height="500"/><br/>

**2.Key Function**
```
TWO-STATE SWITCH: Switch A, Switch B, Switch D
THREE-STATE SWITCH: Switch C, Switch E, Switch G
JOYSTICK: Left Stick, Right Stick

* Left Stick: X--Adjust Pitch Angle
              Y--Turn Left / Right

* Right Stick: X--Go Ahead / Back
               Y--Go Left / Right

* Switch A: UP-- Emergency Stop (Torque=0)
            DWN--Work with SwE

* Switch E: UP-- Work with SwG
            MID--StandUp Mode (0.35m)
            DWN--SquartDown Mode (0.18m)

* Switch G: UP-- RecoveryStand Mode
            MID--BalanceStand Mode
            DWN--Locomotion Mode (0.50m)

* Switch B: UP-- Work with SwC to select 6 Locomotion gaits
            DWN--Standing gait

* Switch C: UP-- Trotting gait    /  Walking gait
            MID--Trotrunning gait /  Pronking gait
            DWN--Pacing gait      /  Galloping gait

* Switch D: UP-- Work with SwC to select first gait group
            DWN--Work with SwC to select second gait group

* Variable B: Adjust Step Height (0-0.2m)
```
**3.Operation Procedure**
* Initial Configuration

<img src="https://user-images.githubusercontent.com/69251304/114666456-de63b700-9d30-11eb-8eac-3709a0d2f4b8.png" width="300" height="400"/>  <img src="https://user-images.githubusercontent.com/69251304/114668072-e1f83d80-9d32-11eb-9e97-1f8280d150a0.png" width="400" height="400"/><br/>
```
SwA = UP
SwB = UP
SwC = UP
SwD = UP
SwE = UP
SwG = UP
```
* Start Up To RecoveryStand Mode

<img src="https://user-images.githubusercontent.com/69251304/114668984-f7ba3280-9d33-11eb-8961-8445c641c17f.png" width="400" height="400"/> <img src="https://user-images.githubusercontent.com/69251304/114668458-57fca480-9d33-11eb-9af9-1b9aae3e1cf3.png" width="400" height="400"/> <br/>
```
SwA = DWN
SwB = UP
SwC = UP
SwD = UP
SwE = UP
SwG = UP
```

* Trans To BalanceStand Mode

```
SwA = DWN
SwB = UP
SwC = UP
SwD = UP
SwE = UP
SwG = MID
```

* Trans To Locomotion Mode
```
SwA = DWN
SwB = UP
SwC = UP
SwD = UP
SwE = UP
SwG = DWN
```

* Switch Gaits
```
SwA = DWN
SwE = UP
SwG = DWN

--------------------------------------------
SwB = UP    |   SwD = UP   |    SwD = DWN   |
---------------------------------------------
SwD = UP    |   Trotting   |     Walking    |
SwD = MID   | Trotrunning  |    Pronking    |
SwD = DWN   |    Pacing    |    Galloping   |
---------------------------------------------
---------------------------------------------
SwB = DWN   |            Standing           |
---------------------------------------------
```

* Emergency Stop\
**IN ANY SITUATIONS (IGNORE OTHER SWITCHES' STATES):**
```
SwA = UP
```

* Trans To StandUp Mode
```
SwA = DWN
SwB = UP
SwC = UP
SwD = UP
SwE = MID
SwG = UP
```

* Trans To SquartDown Mode 
```
SwA = DWN
SwB = UP
SwC = UP
SwD = UP
SwE = DWN
SwG = UP
```

* Shutdown Procedures
```
1. Trans to BalanceStand Mode / Trans To RecoveryStand Mode
2. Trans To StandUp Mode
3. Trans To SquartDown Mode 
4. Shut Down (Trans To Initial Configuration)
5. Robot Power Off 
```
