//
// Created by Rocky Chen on 2023/10/3.
//
#pragma once

namespace RockLib {

    class PID {
    public:
        PID() = default;
        PID(const PID&) = default;

        PID(double kP, double kI, double kD):
        kP(kP), kI(kI), kD(kD){};

        void setP(double kP);
        void setI(double kI);
        void setD(double kD);
        void setTolerance(double tolerance);

        double update();
    private:
        double kP, kI, kD;
        double tolerance;

    };

    using Pid = PID;
} // RockLib
