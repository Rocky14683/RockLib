//
// Created by Rocky Chen on 2023/10/2.
//
#pragma once

#include <type_traits>
#include "pros/motor_group.hpp"
#include "pros/adi.hpp"
#include "pros/rotation.hpp"
#include "pros/gps.hpp"
#include "RockLib/Util/Pose.hpp"
#include "RockLib/Chassis/AbstractChassis.hpp"

namespace RockLib {
    class Localizer{
    public:
        Pose getPose() const{
            return this->robotPosition;
        }
        void setPose(Pose pose) {
            this->robotPosition = pose;
        }
        virtual void calibrate();
        virtual void update();
    protected:
        Localizer() = delete;
        Localizer(double trackWidth, double wheelDiameter, double gearRatio);
        Pose robotPosition = {0, 0, 0};

    };

    class RotationLocalizer : public Localizer{
    public:
        RotationLocalizer() = delete;
        explicit RotationLocalizer(const pros::Rotation& left, const pros::Rotation&  center, const pros::Rotation&  right, const double trackWidth, const double wheelDiameter = 2.75, const double gearRatio = 1);
        void calibrate();
        void update();
    private:
        std::unique_ptr<pros::Rotation> left;
        std::unique_ptr<pros::Rotation> center;
        std::unique_ptr<pros::Rotation> right;
        const double trackWidth;
        const double wheelDiameter;
        const double gearRatio;
    };

    class EncoderLocalizer : public Localizer{
    public:
        EncoderLocalizer() = delete;
        explicit EncoderLocalizer(const pros::adi::Encoder& left, const pros::adi::Encoder&  center, const pros::adi::Encoder&  right, const double trackWidth, const double wheelDiameter = 2.75, const double gearRatio = 1);
        void calibrate();
        void update();
    private:
        std::unique_ptr<pros::adi::Encoder> left;
        std::unique_ptr<pros::adi::Encoder> center;
        std::unique_ptr<pros::adi::Encoder> right;
        const double trackWidth;
        const double wheelDiameter;
        const double gearRatio;
    };

    template<class ChassisType>
    class IMELocalizer : public Localizer{
    public:
        static_assert(IsChassis<ChassisType>, "The template parameter is a not a Chassis type");
        IMELocalizer() = default;
        IMELocalizer(const DriveSetting_t<ChassisType>& driveSetting);
        void calibrate();
        void update();
    private:
        DriveSetting_t<ChassisType>* driveSetting;
    };

    class GPSLocalizer : public Localizer{
    public:
        GPSLocalizer() = delete;
        explicit GPSLocalizer(const pros::GPS gps);
        void calibrate();
        void update();
    private:
        std::unique_ptr<pros::GPS> gps;
        const Pose gpsOffset;
    };
} // RockLib


