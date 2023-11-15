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
            DriveSetting_t(const pros::MotorGroup &left, const pros::MotorGroup &right, double wheelDiameter,
                           double trackWidth) :
                    left(left), right(right), wheelDiameter(wheelDiameter), trackWidth(trackWidth) {};
        private:
            const pros::MotorGroup &left;
            const pros::MotorGroup &right;
            const double wheelDiameter;
            const double trackWidth;
        } DriveSetting_t;

        typedef struct Controllers_t {
        public:
            struct PID_t{
                PID leftPID;
                PID rightPID;
            };
            struct FeedForward_t{
                FeedForward leftFeedFwd;
                FeedForward rightFeedFwd;
            };

            PID_t pidControllers;
            std::optional<FeedForward_t> feedForwardControllers{std::nullopt};
        } Controllers_t;

        DifferentialDrive() = delete;

        DifferentialDrive(const DifferentialDrive::DriveSetting_t &setting,
                          const DifferentialDrive::Controllers_t &controllers);

        DifferentialDrive(const DifferentialDrive::DriveSetting_t &setting,
                          const DifferentialDrive::Controllers_t &controllers, const Localizer &localizer);

        void setControllers(const Controllers_t &controllers);

    private:
        std::unique_ptr<DifferentialDrive::DriveSetting_t> setting;
        std::unique_ptr<DifferentialDrive::Controllers_t> controllers;
    };

} // RockLib
