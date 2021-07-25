/*
 * @brief Utility function to build a Milab Quadruped object
 *
 * Authors: Yinuo Wang, Shuyu Yang
 * Date: 2021/03/04
 * E-mial: dbdxwyn@163.com, yangshuyu@westlake.edu.cn
 * First Version Date: 2021/03/17  Total mass:27.925
 * Second Version Date: 2021/03/26 Total mass:25.693
 *
 * This file builds a model of the Milab robot.
 * The mass, inertia and size parameters of all bodies are determined from SolidWorks.
 */

#ifndef MILAB_milab_SOFTWARE_MILAB_H
#define MILAB_milab_SOFTWARE_MILAB_H
// Todo: fix abadRotorLocation x
#include "FloatingBaseModel.h"
#include "Quadruped.h"

/*!
 * Generate a Quadruped model of Milab robot
 */
template<typename T>
Quadruped<T> buildMilab() {
    Quadruped<T> milab;
    milab._robotType = RobotType::MILAB;
//    mass parameters
//  Nominal Total Mass = 25.693
//  Real Total Mass = 22.94 (without Nvidia and outer covering and 2 heads)
    milab._bodyMass = 11;//13.777;
//  Other Parts Mass  11.916
    milab._abadMass = 0.766;
    milab._hipMass = 1.598;
    milab._kneeMass = 0.363;
    milab._rotorMass = 0.084;

//    link parameters
    milab._bodyLength = 0.5779;
    milab._bodyWidth = 0.152;
    milab._bodyHeight = 0.153;
    milab._abadLinkLength = 0.100;
    milab._hipLinkLength = 0.3000;
    milab._kneeLinkY_offset = 0.00;
    milab._kneeLinkLength = 0.34426; // plus foot link length 0.023
    milab._maxLegLength = 0.644;
    milab._hipRotorLocationYOffset = 0.0375;

//    motor parameters
    milab._motorTauMax = 8.f;
    milab._abadGearRatio = 6;
    milab._hipGearRatio = 6;
    milab._kneeGearRatio = 6;
    milab._batteryV = 36;
    milab._motorKT = 0.08;  // this is flux linkage(0.0025) * pole pairs(21)*1.5
    milab._motorR = 0.13;
    milab._jointDamping = 0.02;
    milab._jointDryFriction = 0.4;

    // rotor inertia if the rotor is oriented so it spins around the z-axis
    Mat3 <T> rotorRotationalInertiaZ;
    rotorRotationalInertiaZ << 53, 0, 0, 0, 53, 0, 0, 0, 105;
    rotorRotationalInertiaZ = 1e-6 * rotorRotationalInertiaZ;

    Mat3 <T> RY = coordinateRotation<T>(CoordinateAxis::Y, M_PI / 2);
    Mat3 <T> RX = coordinateRotation<T>(CoordinateAxis::X, M_PI / 2);
    Mat3 <T> rotorRotationalInertiaX = RY * rotorRotationalInertiaZ * RY.transpose();
    Mat3 <T> rotorRotationalInertiaY = RX * rotorRotationalInertiaZ * RX.transpose();

    // spatial inertias
    Mat3 <T> abadRotationalInertia;
    abadRotationalInertia << 712.408, -3.535, -5.317, -3.535, 1095.432, 13.78, -5.317, 13.78, 772.605;
    abadRotationalInertia = abadRotationalInertia * 1e-6;
    Vec3 <T> abadCOM(-0.004444, -0.000541, -0.000536);  // LEFT
    SpatialInertia<T> abadInertia(milab._abadMass, abadCOM, abadRotationalInertia);

    Mat3 <T> hipRotationalInertia;
    hipRotationalInertia << 17479.820, -9.63, 1236.601, -9.63, 17229.4, -20.313, 1236.601, -20.313, 2982.14;
    hipRotationalInertia = hipRotationalInertia * 1e-6;
    Vec3<T> hipCOM(-0.004928, -0.022568, -0.039632);
    SpatialInertia<T> hipInertia(milab._hipMass, hipCOM, hipRotationalInertia);

    Mat3<T> kneeRotationalInertia, kneeRotationalInertiaRotated;
    kneeRotationalInertiaRotated << 7880.558, -0.083, -15.380, -0.083, 7917.82, -0.27, -15.38, -0.27, 71.290;
    kneeRotationalInertiaRotated = kneeRotationalInertiaRotated * 1e-6;
//    kneeRotationalInertia = RY * kneeRotationalInertiaRotated * RY.transpose();
    Vec3 <T> kneeCOM(-0.000838, -0.000038, -0.157249);
    SpatialInertia<T> kneeInertia(milab._kneeMass, kneeCOM, kneeRotationalInertiaRotated);

    Vec3 <T> rotorCOM(0, 0, 0);
    SpatialInertia<T> rotorInertiaX(milab._rotorMass, rotorCOM, rotorRotationalInertiaX);
    SpatialInertia<T> rotorInertiaY(milab._rotorMass, rotorCOM, rotorRotationalInertiaY);

    Mat3 <T> bodyRotationalInertia;
    bodyRotationalInertia << 84746.639, -505.566, -1520.915, -505.566, 460537.565, 143.817, -1520.915, 143.817, 487181.361;// inertia from solidworks
    bodyRotationalInertia = bodyRotationalInertia * 1e-6;
//    baseInertia << 0.0996, 0, 0, 0, 0.765, 0, 0, 0, 0.765;
    Vec3 <T> bodyCOM(-0.004017, -0.000209, -0.005174);
    Vec3<T> bodyDims(milab._bodyLength, milab._bodyWidth,milab._bodyHeight);
    SpatialInertia<T> bodyInertia(milab._bodyMass, bodyCOM, rotInertiaOfBox(milab._bodyMass, bodyDims)); // simplified inertia

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
