//
// Created by Rocky Chen on 2023/10/2.
//

#pragma once

#include "AbstractChassis.hpp"
#include "pros/motor_group.hpp"

namespace RockLib {

    class DifferentialDrive : public AbstractChassis {
    public:
        struct DriveSetting_t {
            pros::MotorGroup& left;
            pros::MotorGroup& right;
            const double wheelDiameter;
            const double trackWidth;
        };


        DifferentialDrive() = delete;

        DifferentialDrive(const DifferentialDrive::DriveSetting_t &setting);

        DifferentialDrive(const DifferentialDrive::DriveSetting_t &setting, const Localizer &localizer);

        //virtual Kinematics_t inverseKinematics(double yDir, double xDir, double theta)const final;
    private:
        std::unique_ptr<DriveSetting_t> setting;
    };

} // RockLib
