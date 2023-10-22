//
// Created by Rocky Chen on 2023/10/21.
//

#pragma once
#include <cmath>
#include <complex>
#include <array>
#include <optional>
namespace RockLib {

    namespace math{
        auto findCubicRealRoots(double a, double b, double c, double d);
        auto findQuadRealRoots(double a, double b, double c);
        double findMinPositiveTwoRoots(double r1, double r2);
        double findMinPositiveThreeRoots(double r1, double r2, double r3);
    }

    class Profile {
    public:

    private:
        static auto getMinPosAndReachedAccelToReachMaxVelocity(double v0, double vMax, double aMax, double jMax);
        static double getReachedAccelWhenNoConstAccelStage(double p, double v, double vMax, double aMax, double jMax);
        static auto getMinPosAndConstAccelTimeToMaxAV(double v0, double vMax, double aMax, double jMax);
        static double getMinPosToMaxAccel(double v0, double vMax, double aMax, double jMax);
        static double getConstAccelTime(double p, double v0, double vMax, double aMax, double jMax);
        static auto getMinPosReachedAccelAndJerkToReachVF(double v0, double vf, double vMax, double aMax, double jMax);
        static auto equalV0VFCasePlanning(double posDiff, double v, double vMax, double aMax, double jMax);
        static auto trajectorySegmentPlanning(double p0, double pf, double v0, double vf, double vMax, double aMax, double jMax);
    };

} // RockLib
