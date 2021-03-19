/*
 * @brief Utility function to build a Milab Quadruped object
 *
 * Authors: Shuyu Yang, Yinuo Wang
 * Date: 2021/03/04
 * E-mial: yangshuyu@westlake.edu.cn , dbdxwyn@163.com
 * First Version Date: 2021/03/17
 *
 * This file builds a model of the Milab robot.
 * The mass, inertia and size parameters of all bodies are determined from SolidWorks.
 */

#ifndef MILAB_milab_SOFTWARE_MILAB_H
#define MILAB_milab_SOFTWARE_MILAB_H

#include "FloatingBaseModel.h"
#include "Quadruped.h"
//  todo: modify following parameters according to real robot measurements:
/*!
 * Generate a Quadruped model of Milab robot
 */
template<typename T>
Quadruped<T> buildMilab() {
    Quadruped<T> milab;
    milab._robotType = RobotType::MILAB;
//    mass parameters
//  Nominal Total Mass = 27.925
    milab._bodyMass = 15.905;
    milab._abadMass = 0.851;
    milab._hipMass = 1.598;
    milab._kneeMass = 0.304;
    milab._rotorMass = 0.084;

//    link parameters
    milab._bodyLength = 0.5779;
    milab._bodyWidth = 0.152;
    milab._bodyHeight = 0.153;
    milab._abadLinkLength = 0.100;
    milab._hipLinkLength = 0.3000;
    milab._kneeLinkY_offset = 0.00;
    milab._kneeLinkLength = 0.34426; // plus foot link length 0.023
    milab._maxLegLength = 0.621;
    milab._hipRotorLocationYOffset = 0.0375;

//    motor parameters
    milab._motorTauMax = 8.f;
    milab._abadGearRatio = 6;
    milab._hipGearRatio = 6;
    milab._kneeGearRatio = 6;
    milab._batteryV = 36;
    milab._motorKT = 0.1;  // this is flux linkage * pole pairs
    milab._motorR = 0.3;
    milab._jointDamping = 0.02;
    milab._jointDryFriction = 0.4;

    // rotor inertia if the rotor is oriented so it spins around the z-axis
    Mat3 <T> rotorRotationalInertiaZ;
    rotorRotationalInertiaZ << 53, 0, 0, 0, 53, 0, 0, 0, 105;
    rotorRotationalInertiaZ = 1e-6 * 2* rotorRotationalInertiaZ;

    Mat3 <T> RY = coordinateRotation<T>(CoordinateAxis::Y, M_PI / 2);
    Mat3 <T> RX = coordinateRotation<T>(CoordinateAxis::X, M_PI / 2);
    Mat3 <T> rotorRotationalInertiaX = RY * rotorRotationalInertiaZ * RY.transpose();
    Mat3 <T> rotorRotationalInertiaY = RX * rotorRotationalInertiaZ * RX.transpose();

    // spatial inertias
    Mat3 <T> abadRotationalInertia;
    abadRotationalInertia << 785.098, -1.682, -3.604, -1.682, 1223.521, 11.631, -3.604, 11.631, 866.078;;
    abadRotationalInertia = abadRotationalInertia * 1e-6;
    Vec3 <T> abadCOM(-0.004122, -0.000422, -0.000388);  // LEFT
    SpatialInertia<T> abadInertia(milab._abadMass, abadCOM, abadRotationalInertia);

    Mat3 <T> hipRotationalInertia;
    hipRotationalInertia << 17479.820, 0.659, 1217.843, 0.659, 16957.82, 22.085, 1217.843, 22.085, 2928.195;
    hipRotationalInertia = hipRotationalInertia * 1e-6;
    Vec3<T> hipCOM(-0.004928, 0.022568, -0.040268);
    SpatialInertia<T> hipInertia(milab._hipMass, hipCOM, hipRotationalInertia);

    Mat3<T> kneeRotationalInertia, kneeRotationalInertiaRotated;
    kneeRotationalInertiaRotated << 14348.139, -0.069, -10.901, -0.069, 14381.501, 1.424, -10.901, 1.424, 60.547;
    kneeRotationalInertiaRotated = kneeRotationalInertiaRotated * 1e-6;
    kneeRotationalInertia = RY * kneeRotationalInertiaRotated * RY.transpose();
    Vec3 <T> kneeCOM(-0.000127, -0.00004, -0.162845);
    SpatialInertia<T> kneeInertia(milab._kneeMass, kneeCOM, kneeRotationalInertia);

    Vec3 <T> rotorCOM(0, 0, 0);
    SpatialInertia<T> rotorInertiaX(milab._rotorMass, rotorCOM, rotorRotationalInertiaX);
    SpatialInertia<T> rotorInertiaY(milab._rotorMass, rotorCOM, rotorRotationalInertiaY);

    Mat3 <T> bodyRotationalInertia;
    bodyRotationalInertia << 87315.704, -1616.648, 3635.591, -1616.648, 478969.026, 8.292, 3635.591, 8.292, 504293.328;
    bodyRotationalInertia = 2* bodyRotationalInertia * 1e-6;
//    bodyRotationalInertia << 0.109, 0, 0, 0, 0.834, 0, 0, 0, 0.833;
    Vec3 <T> bodyCOM(0, 0, 0);
    Vec3<T> bodyDims(milab._bodyLength, milab._bodyWidth,milab._bodyHeight);
    SpatialInertia<T> bodyInertia(milab._bodyMass, bodyCOM, rotInertiaOfBox(milab._bodyMass, bodyDims));

    milab._abadInertia = abadInertia;
    milab._hipInertia = hipInertia;
    milab._kneeInertia = kneeInertia;
    milab._abadRotorInertia = rotorInertiaX;
    milab._hipRotorInertia = rotorInertiaY;
    milab._kneeRotorInertia = rotorInertiaY;
    milab._bodyInertia = bodyInertia;

    // locations
    milab._abadLocation = Vec3<T>(milab._bodyLength, milab._bodyWidth, 0) * 0.5;
    milab._abadRotorLocation = Vec3<T>(milab._bodyLength, milab._bodyWidth, 0) * 0.5;
    milab._hipLocation = Vec3<T>(0, milab._abadLinkLength, 0);
    milab._hipRotorLocation = Vec3<T>(0,  milab._abadLinkLength - milab._hipRotorLocationYOffset, 0);
    milab._kneeLocation = Vec3<T>(0, 0, -milab._hipLinkLength);
    milab._kneeRotorLocation = Vec3<T>(0, 0, 0);

    return milab;
}


#endif //MILAB_H
