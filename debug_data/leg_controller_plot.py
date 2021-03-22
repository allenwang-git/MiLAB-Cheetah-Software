import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter
import numpy as np

# This tool file is used to visualize robot Joint PD or Foot Cartesian Trajectory PD tracking performance
# You can switch between above two plotting modes by changing JOINT_PD value. Data format of input file is
# as follow and the sampling frequency is about 50Hz (0.02s), which can be changed in LegController.cpp.
#
#                                     Data Format
#
#legindex  legs'q  legs'qdes Est torque   kp_joint  kd_joint  legs'p  legs'pdes  Kp_cartesian  kd_cartesian  ff_force
#   0        1-3     4-6       7-9                            46-48   49-51                                    76-78
#  10       11-13   14-16     17-19                           52-54   55-57                                    79-81
#  20           ...              29                           58-60   61-63                                    82-83
#  30           ...              39                           64-66   67-69                                    84-86
#                                           40-42     43-45                         70-72         73-75
#
# Author: Yinuo Wang
# Date: 03/16/21
# Email: dbdxwyn@163.com

# JOINT_PD = True  #Joint PD
JOINT_PD = False  # Cartesian PD
TORQUE_PLOT = True
# TORQUE_PLOT = False
FF_F_PLOT = True
# FF_F_PLOT = False
FILE_NAME = 'leg_controller_data.txt'

## read force data from file
def loadFFF(flieName,leg):
    inFile = open(flieName, 'r') #open in read only
    x_f= np.empty(shape=[1,0])
    y_f= np.empty(shape=[1,0])
    z_f= np.empty(shape=[1,0])
    for line in inFile:
        trainingSet = line.split(' ') #split data by ' '
        if FF_F_PLOT == True:
            x_f=np.append(x_f,float(trainingSet[75+3*leg+1]))
            y_f=np.append(y_f,float(trainingSet[75+3*leg+2]))
            z_f=np.append(z_f,float(trainingSet[75+3*leg+3]))
    x_f = np.delete(x_f,[0,1,2,3,4])
    y_f = np.delete(y_f,[0,1,2,3,4])
    z_f = np.delete(z_f,[0,1,2,3,4])
    return x_f,y_f,z_f

## read torque data from file
def loadTorque(flieName,leg):
    inFile = open(flieName, 'r') #open in read only
    abad_tau= np.empty(shape=[1,0])
    hip_tau= np.empty(shape=[1,0])
    knee_tau= np.empty(shape=[1,0])
    for line in inFile:
        trainingSet = line.split(' ') #split data by ' '
        if TORQUE_PLOT == True:
            abad_tau=np.append(abad_tau,float(trainingSet[10*leg+7]))
            hip_tau=np.append(hip_tau,float(trainingSet[10*leg+8]))
            knee_tau=np.append(knee_tau,float(trainingSet[10*leg+9]))

    abad_tau = np.delete(abad_tau,[0,1,2,3,4])
    hip_tau = np.delete(hip_tau,[0,1,2,3,4])
    knee_tau = np.delete(knee_tau,[0,1,2,3,4])
    return abad_tau,hip_tau,knee_tau

## read leg data from file
def loadData(flieName,leg):
    inFile = open(flieName, 'r') #open in read only
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
        if JOINT_PD == True:
            abad_q=np.append(abad_q,float(trainingSet[10*leg+1]))
            abad_qdes=np.append(abad_qdes,float(trainingSet[10*leg+4]))

            hip_q=np.append(hip_q,float(trainingSet[10*leg+2]))
            hip_qdes=np.append(hip_qdes,float(trainingSet[10*leg+5]))

            knee_q=np.append(knee_q,float(trainingSet[10*leg+3]))
            knee_qdes=np.append(knee_qdes,float(trainingSet[10*leg+6]))
        elif JOINT_PD == False: # Cartesian PD
            x_p=np.append(x_p,float(trainingSet[45+6*leg+1]))
            x_pdes=np.append(x_pdes,float(trainingSet[45+6*leg+4]))

            y_p=np.append(y_p,float(trainingSet[45+6*leg+2]))
            y_pdes=np.append(y_pdes,float(trainingSet[45+6*leg+5]))

            z_p=np.append(z_p,float(trainingSet[45+6*leg+3]))
            z_pdes=np.append(z_pdes,float(trainingSet[45+6*leg+6]))

    if JOINT_PD:
        abad_q = np.delete(abad_q,[0,1,2,3,4])
        abad_qdes = np.delete(abad_qdes,[0,1,2,3,4])
        hip_q = np.delete(hip_q,[0,1,2,3,4])
        hip_qdes = np.delete(hip_qdes,[0,1,2,3,4])
        knee_q = np.delete(knee_q,[0,1,2,3,4])
        knee_qdes = np.delete(knee_qdes,[0,1,2,3,4])
    if not JOINT_PD:
        x_p = np.delete(x_p,[0,1,2,3,4])
        x_pdes = np.delete(x_pdes,[0,1,2,3,4])
        y_p = np.delete(y_p,[0,1,2,3,4])
        y_pdes = np.delete(y_pdes,[0,1,2,3,4])
        z_p = np.delete(z_p,[0,1,2,3,4])
        z_pdes = np.delete(z_pdes,[0,1,2,3,4])

    if JOINT_PD == True:
        return abad_q,abad_qdes,hip_q,hip_qdes,knee_q,knee_qdes
    elif  JOINT_PD == False:
        return x_p,x_pdes,y_p,y_pdes,z_p,z_pdes


for i in range(4):

    y1, y1_des, y2, y2_des, y3, y3_des = loadData(FILE_NAME, i)
    if TORQUE_PLOT == True:
        y4, y5, y6 = loadTorque(FILE_NAME, i)
    if FF_F_PLOT ==True:
        y7, y8, y9 = loadFFF(FILE_NAME, i)

    plt.figure(1,figsize=(10,8))
    # plt.title("footTrajectory/jointAngle")
    plt.subplot(4,3,3*i+1)
    plt.plot(y1)
    plt.plot(y1_des)
    ax1 = plt.gca()
    ax1.yaxis.set_major_formatter(FormatStrFormatter('%.3f'))
    plt.grid(axis='both')

    plt.subplot(4,3,3*i+2)
    plt.plot(y2)
    plt.plot(y2_des)
    ax2 = plt.gca()
    ax2.yaxis.set_major_formatter(FormatStrFormatter('%.3f'))
    plt.grid(axis='both')

    plt.subplot(4,3,3*i+3)
    plt.plot(y3)
    plt.plot(y3_des)
    ax3 = plt.gca()
    ax3.yaxis.set_major_formatter(FormatStrFormatter('%.3f'))
    plt.grid(axis='both')

    if TORQUE_PLOT == True:
        plt.figure(2,figsize=(10,8))
        # plt.title("estimatedTorque")
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

    if FF_F_PLOT == True:
        plt.figure(3,figsize=(10,8))
        # plt.title("MPCfeedforwardForce")
        plt.subplot(4,3,3*i+1)
        plt.plot(y7)
        ax1 = plt.gca()
        ax1.yaxis.set_major_formatter(FormatStrFormatter('%.3f'))
        plt.grid(axis='both')

        plt.subplot(4,3,3*i+2)
        plt.plot(y8)
        ax2 = plt.gca()
        ax2.yaxis.set_major_formatter(FormatStrFormatter('%.3f'))
        plt.grid(axis='both')

        plt.subplot(4,3,3*i+3)
        plt.plot(y9)
        ax3 = plt.gca()
        ax3.yaxis.set_major_formatter(FormatStrFormatter('%.3f'))
        plt.grid(axis='both')
plt.show()



