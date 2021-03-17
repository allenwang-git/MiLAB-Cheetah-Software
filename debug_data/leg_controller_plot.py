import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter
import numpy as np

# This tool file is used to visualize robot Joint PD or Foot Cartesian Trajectory PD tracking performance
# You can switch between above two plotting modes by changing JOINT_PD value. Data format of input file is
# as follow and the sampling frequency is about 50Hz (0.02s), which can be changed in LegController.cpp.
# # Data Format: legindex  legs'q  legs'qdes legs'torque  kp_joint  kd_joint  legs'p  legs'pdes  Kp_cartesian kd_cartesian
# #                  0        1-3     4-6       7-9                            46-48   49-51
# #                 10       11-13   14-16     17-19                           52-54   55-57
# #                 20           ...              29                           58-60   61-63
# #                 30           ...              39                           64-66   67-69
# #                                                         40-42     43-45                         70-72         73-75
# Author: Yinuo Wang
# Date: 03/16/21
# Email: dbdxwyn@163.com


# JOINT_PD = False  # Cartesian PD
JOINT_PD = True  #Joint PD
# TORQUE_PLOT = False
TORQUE_PLOT = True
file_name = 'leg_controller_data.txt'

## read data from file
def loadData(flieName,leg,switchPD,switchTAU):
    inFile = open(flieName, 'r') #open in read only
    abad_tau= np.empty(shape=[1,0])
    hip_tau= np.empty(shape=[1,0])
    knee_tau= np.empty(shape=[1,0])

    abad_q= np.empty(shape=[1,0])
    abad_qdes= np.empty(shape=[1,0])
    hip_q= np.empty(shape=[1,0])
    hip_qdes= np.empty(shape=[1,0])
    knee_q= np.empty(shape=[1,0])
    knee_qdes= np.empty(shape=[1,0])

    x_p= np.empty(shape=[1,0])
    x_pdes= np.empty(shape=[1,0])
    y_p= np.empty(shape=[1,0])
    y_pdes= np.empty(shape=[1,0])
    z_p= np.empty(shape=[1,0])
    z_pdes= np.empty(shape=[1,0])

    for line in inFile:
        trainingSet = line.split(' ') #split data by ' '
        if switchTAU == True:
            abad_tau=np.append(abad_tau,float(trainingSet[10*leg+7]))
            hip_tau=np.append(hip_tau,float(trainingSet[10*leg+8]))
            knee_tau=np.append(knee_tau,float(trainingSet[10*leg+9]))
        if switchPD == True:
            abad_q=np.append(abad_q,float(trainingSet[10*leg+1]))
            abad_qdes=np.append(abad_qdes,float(trainingSet[10*leg+4]))

            hip_q=np.append(hip_q,float(trainingSet[10*leg+2]))
            hip_qdes=np.append(hip_qdes,float(trainingSet[10*leg+5]))

            knee_q=np.append(knee_q,float(trainingSet[10*leg+3]))
            knee_qdes=np.append(knee_qdes,float(trainingSet[10*leg+6]))
        elif switchPD == False: # Cartesian PD
            x_p=np.append(x_p,float(trainingSet[45+6*leg+1]))
            x_pdes=np.append(x_pdes,float(trainingSet[45+6*leg+4]))

            y_p=np.append(y_p,float(trainingSet[45+6*leg+2]))
            y_pdes=np.append(y_pdes,float(trainingSet[45+6*leg+5]))

            z_p=np.append(z_p,float(trainingSet[45+6*leg+3]))
            z_pdes=np.append(z_pdes,float(trainingSet[45+6*leg+6]))
    if switchTAU:
        abad_tau = np.delete(abad_tau,[0,1,2,3,4])
        hip_tau = np.delete(hip_tau,[0,1,2,3,4])
        knee_tau = np.delete(knee_tau,[0,1,2,3,4])
    if switchPD:
        abad_q = np.delete(abad_q,[0,1,2,3,4])
        abad_qdes = np.delete(abad_qdes,[0,1,2,3,4])
        hip_q = np.delete(hip_q,[0,1,2,3,4])
        hip_qdes = np.delete(hip_qdes,[0,1,2,3,4])
        knee_q = np.delete(knee_q,[0,1,2,3,4])
        knee_qdes = np.delete(knee_qdes,[0,1,2,3,4])
    if not switchPD:
        x_p = np.delete(x_p,[0,1,2,3,4])
        x_pdes = np.delete(x_pdes,[0,1,2,3,4])
        y_p = np.delete(y_p,[0,1,2,3,4])
        y_pdes = np.delete(y_pdes,[0,1,2,3,4])
        z_p = np.delete(z_p,[0,1,2,3,4])
        z_pdes = np.delete(z_pdes,[0,1,2,3,4])


    if switchPD == True and TORQUE_PLOT == True:
        return abad_q,abad_qdes,hip_q,hip_qdes,knee_q,knee_qdes, abad_tau,hip_tau,knee_tau
    elif  switchPD == True and TORQUE_PLOT == False:
        return abad_q,abad_qdes,hip_q,hip_qdes,knee_q,knee_qdes
    elif switchPD == False and TORQUE_PLOT == True:
        return x_p,x_pdes,y_p,y_pdes,z_p,z_pdes, abad_tau,hip_tau,knee_tau
    elif  switchPD == False and TORQUE_PLOT == False:
        return x_p,x_pdes,y_p,y_pdes,z_p,z_pdes


for i in range(4):
    if TORQUE_PLOT ==False:
        y1, y1_des, y2, y2_des, y3, y3_des = loadData(file_name, i, JOINT_PD, TORQUE_PLOT)
    else :
        y1, y1_des, y2, y2_des, y3, y3_des, y4, y5, y6 = loadData(file_name, i, JOINT_PD, TORQUE_PLOT)
    size = len(y1)
    t = np.linspace(0, size, size, endpoint=False)

    plt.figure(1,figsize=(10,8))
    plt.subplot(4,3,3*i+1)
    plt.plot(t,y1)
    plt.plot(t,y1_des)
    ax1 = plt.gca()
    ax1.yaxis.set_major_formatter(FormatStrFormatter('%.3f'))
    plt.grid(axis='both')

    plt.subplot(4,3,3*i+2)
    plt.plot(t,y2)
    plt.plot(t,y2_des)
    ax2 = plt.gca()
    ax2.yaxis.set_major_formatter(FormatStrFormatter('%.3f'))
    plt.grid(axis='both')

    plt.subplot(4,3,3*i+3)
    plt.plot(t,y3,)
    plt.plot(t,y3_des)
    ax3 = plt.gca()
    ax3.yaxis.set_major_formatter(FormatStrFormatter('%.3f'))
    plt.grid(axis='both')

    if TORQUE_PLOT == True:
        plt.figure(2,figsize=(10,8))
        plt.subplot(4,3,3*i+1)
        plt.plot(y4)
        ax1 = plt.gca()
        ax1.yaxis.set_major_formatter(FormatStrFormatter('%.3f'))
        plt.grid(axis='both')

        plt.subplot(4,3,3*i+2)
        plt.plot(y5)
        ax2 = plt.gca()
        ax2.yaxis.set_major_formatter(FormatStrFormatter('%.3f'))
        plt.grid(axis='both')

        plt.subplot(4,3,3*i+3)
        plt.plot(y6)
        ax3 = plt.gca()
        ax3.yaxis.set_major_formatter(FormatStrFormatter('%.3f'))
        plt.grid(axis='both')

plt.show()



