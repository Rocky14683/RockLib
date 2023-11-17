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

        DifferentialDrive() = delete;

        DifferentialDrive(const DriveSetting_t<DifferentialDrive> &setting,
                          const Controllers_t<DifferentialDrive> &controllers);

        DifferentialDrive(const DriveSetting_t<DifferentialDrive> &setting,
                          const Controllers_t<DifferentialDrive> &controllers, const Localizer &localizer);

        void setControllers(const Controllers_t<DifferentialDrive> &controllers);

    private:
        std::unique_ptr<DriveSetting_t<DifferentialDrive>> setting;
        std::unique_ptr<Controllers_t<DifferentialDrive>> controllers;
    };



    template<>
    struct DriveSetting_t<DifferentialDrive> {
    public:

        DriveSetting_t(std::initializer_list<int8_t> left,
                       std::initializer_list<int8_t> right, const double wheelDiameter,
                       const double trackWidth, const double gearRatio) :
                leftMotors(std::make_shared<pros::MotorGroup>(left)),
                rightMotors(std::make_shared<pros::MotorGroup>(right)),
                wheelDiameter(wheelDiameter),
                trackWidth(trackWidth),
                gearRatio(gearRatio) {};

        DriveSetting_t(const pros::MotorGroup &left,
                       const pros::MotorGroup &right, const double wheelDiameter,
                       const double trackWidth, const double gearRatio) : leftMotors(
                std::make_shared<pros::MotorGroup>(left.get_port_all())), rightMotors(
                std::make_shared<pros::MotorGroup>(right.get_port_all())),
                wheelDiameter(wheelDiameter),
                trackWidth(trackWidth),
                gearRatio(gearRatio) {};

    private:
        std::shared_ptr<pros::MotorGroup> leftMotors;
        std::shared_ptr<pros::MotorGroup> rightMotors;
        const double wheelDiameter;
        const double trackWidth;
        const double gearRatio;
    };


    template<>
    struct Controllers_t<DifferentialDrive> {
    public:
        struct PID_t {
            PID leftPID;
            PID rightPID;
        };
        struct FeedForward_t {
            FeedForward leftFeedFwd;
            FeedForward rightFeedFwd;
        };

        PID_t pidControllers{};
        std::optional<FeedForward_t> feedForwardControllers{std::nullopt};
    };


} // RockLib
