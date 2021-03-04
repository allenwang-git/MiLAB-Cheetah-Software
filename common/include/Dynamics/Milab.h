/*
* Created by WYN on 2021/3/4.
*
* @brief Utility function to build a Milab Quadruped object
*
* This file  builds a model of the Milab robot.
* The inertia parameters of all bodies are determined from CAD.
*
*/

#ifndef MILAB_CHEETAH_SOFTWARE_MILAB_H
#define MILAB_CHEETAH_SOFTWARE_MILAB_H

#include "FloatingBaseModel.h"
#include "Quadruped.h"

/*!
 * Generate a Quadruped model of Milab robot
 */
template<typename T>
Quadruped<T> buildMilab() {
    Quadruped<T> milab;
    milab._robotType = RobotType::MILAB;
//  todo: modify following parameters according to real robot measurements:
    milab._bodyMass = 8.69;
    milab._bodyLength = 0.789;
    milab._bodyWidth = 0.253;
    milab._bodyHeight = 0.1515;
    milab._abadGearRatio = 6;
    milab._hipGearRatio = 6;
    milab._kneeGearRatio = 6;
    milab._abadLinkLength = 0.0536;
    milab._hipLinkLength = 0.370;
    milab._kneeLinkY_offset = 0.004;
    milab._kneeLinkLength = 0.3932;
    milab._maxLegLength = 0.7632;


    milab._motorTauMax = 16.f;
    milab._batteryV = 36;
    milab._motorKT = 0.09;  // this is flux linkage * pole pairs
    milab._motorR = 0.3;
    milab._jointDamping = 0.05;
    milab._jointDryFriction = 0.6;



    // rotor inertia if the rotor is oriented so it spins around the z-axis
    Mat3 <T> rotorRotationalInertiaZ;
    rotorRotationalInertiaZ << 33, 0, 0, 0, 33, 0, 0, 0, 63;
    rotorRotationalInertiaZ = 1e-6 * rotorRotationalInertiaZ;

    Mat3 <T> RY = coordinateRotation<T>(CoordinateAxis::Y, M_PI / 2);
    Mat3 <T> RX = coordinateRotation<T>(CoordinateAxis::X, M_PI / 2);
    Mat3 <T> rotorRotationalInertiaX = RY * rotorRotationalInertiaZ * RY.transpose();
    Mat3 <T> rotorRotationalInertiaY = RX * rotorRotationalInertiaZ * RX.transpose();

    // spatial inertias
    Mat3 <T> abadRotationalInertia;
    abadRotationalInertia << 381, 58, 0.45, 58, 560, 0.95, 0.45, 0.95, 444;
    abadRotationalInertia = abadRotationalInertia * 1e-6;
    Vec3 <T> abadCOM(0, 0.036, 0);  // LEFT
    SpatialInertia<T> abadInertia(0.54, abadCOM, abadRotationalInertia);

    Mat3 <T> hipRotationalInertia;
    hipRotationalInertia << 1983, 245, 13, 245, 2103, 1.5, 13, 1.5, 408;
    hipRotationalInertia = hipRotationalInertia * 1e-6;
    Vec3<T> hipCOM(0, 0.016, -0.02);
    SpatialInertia<T> hipInertia(0.634, hipCOM, hipRotationalInertia);

    Mat3<T> kneeRotationalInertia, kneeRotationalInertiaRotated;
    kneeRotationalInertiaRotated << 6, 0, 0, 0, 248, 0, 0, 0, 245;
    kneeRotationalInertiaRotated = kneeRotationalInertiaRotated * 1e-6;
    kneeRotationalInertia = RY * kneeRotationalInertiaRotated * RY.transpose();
    Vec3 <T> kneeCOM(0, 0, -0.061);
    SpatialInertia<T> kneeInertia(0.064, kneeCOM, kneeRotationalInertia);

    Vec3 <T> rotorCOM(0, 0, 0);
    SpatialInertia<T> rotorInertiaX(0.055, rotorCOM, rotorRotationalInertiaX);
    SpatialInertia<T> rotorInertiaY(0.055, rotorCOM, rotorRotationalInertiaY);

    Mat3 <T> bodyRotationalInertia;
    bodyRotationalInertia << 11253, 0, 0, 0, 36203, 0, 0, 0, 42673;
    bodyRotationalInertia = bodyRotationalInertia * 1e-6;
    Vec3 <T> bodyCOM(0, 0, 0);
    SpatialInertia<T> bodyInertia(milab._bodyMass, bodyCOM,
                                  bodyRotationalInertia);

    milab._abadInertia = abadInertia;
    milab._hipInertia = hipInertia;
    milab._kneeInertia = kneeInertia;
    milab._abadRotorInertia = rotorInertiaX;
    milab._hipRotorInertia = rotorInertiaY;
    milab._kneeRotorInertia = rotorInertiaY;
    milab._bodyInertia = bodyInertia;

    // locations
    milab._abadRotorLocation = Vec3<T>(0.125, 0.049, 0);
    milab._abadLocation =
            Vec3<T>(milab._bodyLength, milab._bodyWidth, 0) * 0.5;
    milab._hipLocation = Vec3<T>(0, milab._abadLinkLength, 0);
    milab._hipRotorLocation = Vec3<T>(0, 0.04, 0);
    milab._kneeLocation = Vec3<T>(0, 0, -milab._hipLinkLength);
    milab._kneeRotorLocation = Vec3<T>(0, 0, 0);

    return milab;
}


#endif //MILAB_H
