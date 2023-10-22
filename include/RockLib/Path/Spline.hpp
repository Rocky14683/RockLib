//
// Created by Rocky Chen on 2023/10/3.
//

#pragma once
#include "RockLib/Util/Point.hpp"
#include "RockLib/Path/Trajectory.hpp"

namespace RockLib {

    class Spline {
    public:
        Spline() = delete;

        Spline(Point c1, Point p1, Point p2, Point c2);

        Point getPoint(double t);

        Point getVelocity(double t);

        Point getAcceleration(double t);

        double getCurvature(double t);
    private:
        Point c1, c2, p1, p2;
    };

} // RockLib

