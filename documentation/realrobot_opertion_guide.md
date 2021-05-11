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

* Switch C: UP-- Trotting gait    /  Walking gait
            MID--Trotrunning gait /  Pronking gait
            DWN--Pacing gait      /  Galloping gait

* Switch D: UP-- Work with SwC to select first gait group
            DWN--Work with SwC to select second gait group

* Variable B: Adjust Step Height (0-0.2m)
```
**3.Operation Procedure**
* Initial Configuration

<img src="https://user-images.githubusercontent.com/69251304/114666456-de63b700-9d30-11eb-8eac-3709a0d2f4b8.png" width="350" height="400"/>  <img src="https://user-images.githubusercontent.com/69251304/114668072-e1f83d80-9d32-11eb-9e97-1f8280d150a0.png" width="350" height="400"/><br/>
```
SwA = UP
SwC = UP
SwD = UP
SwE = UP
SwG = UP
```
* Start Up To RecoveryStand Mode

<img src="https://user-images.githubusercontent.com/69251304/114670896-0f92b600-9d36-11eb-954b-871278e042f2.jpg" width="350" height="400"/> <img src="https://user-images.githubusercontent.com/69251304/114669538-98105700-9d34-11eb-8252-f92dfd722140.png" width="350" height="400"/><br/>
```
SwA = DWN
SwC = UP
SwD = UP
SwE = UP
SwG = UP
```

* Trans To BalanceStand Mode

<img src="https://user-images.githubusercontent.com/69251304/114671111-4d8fda00-9d36-11eb-84bc-f4a03572412c.jpg" width="350" height="400"/><br/>

```
SwA = DWN
SwC = UP
SwD = UP
SwE = UP
SwG = MID
```

* Trans To Locomotion Mode

<img src="https://user-images.githubusercontent.com/69251304/114671396-a495af00-9d36-11eb-8594-62bacf697500.jpg" width="350" height="400"/><br/>

```
SwA = DWN
SwC = UP
SwD = UP
SwE = UP
SwG = DWN
```

* Switch Gaits

<img src="https://user-images.githubusercontent.com/69251304/114671531-c727c800-9d36-11eb-8d2f-8a24a7f084c4.jpg" width="250" height="300"/> <img src="https://user-images.githubusercontent.com/69251304/114671542-ca22b880-9d36-11eb-889f-cb7eaca6088a.jpg" width="250" height="300"/> <img src="https://user-images.githubusercontent.com/69251304/114671590-d7d83e00-9d36-11eb-84d5-75a8535a36e3.jpg" width="250" height="300"/> <img src="https://user-images.githubusercontent.com/69251304/114671599-d9a20180-9d36-11eb-8b6a-31e914889c65.jpg" width="250" height="300"/><br/>
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

```

* Emergency Stop\
**IN ANY SITUATIONS (IGNORE OTHER SWITCHES' STATES):**

<img src="https://user-images.githubusercontent.com/69251304/114672505-cba0b080-9d37-11eb-8966-cbc98cc2cb80.jpg" width="350" height="400"/><br/>
```
SwA = UP
```

* Trans To StandUp Mode

<img src="https://user-images.githubusercontent.com/69251304/114672524-d3605500-9d37-11eb-93cb-e3b02ffd8671.jpg" width="350" height="400"/><br/>
```
SwA = DWN
SwC = UP
SwD = UP
SwE = MID
SwG = UP
```

* Trans To SquartDown Mode 

<img src="https://user-images.githubusercontent.com/69251304/114672542-d8bd9f80-9d37-11eb-8f1e-55caf8009318.jpg" width="350" height="400"/><br/>
```
SwA = DWN
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
