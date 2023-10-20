//
// Created by Rocky Chen on 2023/10/2.
//

#pragma once

#include <optional>
#include "AbstractChassis.hpp"
#include "pros/motor_group.hpp"

namespace RockLib {

    class DifferentialDrive : public AbstractChassis {
    public:
        typedef struct DriveSetting_t {
        public:
            DriveSetting_t(const pros::MotorGroup& left, const pros::MotorGroup& right, double wheelDiameter, double trackWidth) :
            left(left), right(right), wheelDiameter(wheelDiameter), trackWidth(trackWidth) {};
        private:
            const pros::MotorGroup& left;
            const pros::MotorGroup& right;
            const double wheelDiameter;
            const double trackWidth;
        } DriveSetting_t;

        DifferentialDrive() = delete;

        DifferentialDrive(DifferentialDrive::DriveSetting_t setting);

        DifferentialDrive(DifferentialDrive::DriveSetting_t setting, Localizer localizer);

        //virtual Kinematics_t inverseKinematics(double yDir, double xDir, double theta)const final;
    private:
        std::unique_ptr<DifferentialDrive::DriveSetting_t> setting;
    };

} // RockLib
