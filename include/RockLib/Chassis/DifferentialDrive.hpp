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
            Controllers_t(const PID &leftPID, const PID &rightPID) :
                    leftPID(leftPID), rightPID(rightPID) {};

            Controllers_t(const PID &leftPID, const PID &rightPID, const FeedForward &leftFeedFwd,
                          const FeedForward &rightFeedFwd) :
                    leftPID(leftPID), rightPID(rightPID), leftFeedFwd(leftFeedFwd), rightFeedFwd(rightFeedFwd) {};
        private:
            PID leftPID;
            PID rightPID;
            std::optional<FeedForward> leftFeedFwd = std::nullopt;
            std::optional<FeedForward> rightFeedFwd = std::nullopt;
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
