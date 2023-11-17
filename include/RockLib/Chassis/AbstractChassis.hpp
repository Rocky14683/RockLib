//
// Created by Rocky Chen on 2023/10/2.
//

#pragma once

#include "pros/imu.hpp"
#include "pros/motors.hpp"
#include "RockLib/Util/Pose.hpp"
#include "RockLib/Localizer/Localizer.hpp"
#include "RockLib/Control/PID.hpp"
#include "RockLib/Control/FeedForward.hpp"

namespace RockLib {

    class AbstractChassis {
    public:

        Pose getPose() const;

        void setPose(Pose pose) const;

        std::unique_ptr<pros::Mutex> getMutex();

    protected:
        AbstractChassis();

        AbstractChassis(const Localizer &localizer);

        void operator=(const AbstractChassis &rhs) = delete;

    private:
        std::shared_ptr<Localizer> localizer;
        std::unique_ptr<pros::Mutex> mutex;
    };


    template<class ChassisType>
    concept IsChassis = std::is_base_of<AbstractChassis, ChassisType>::value && !std::is_same<AbstractChassis, ChassisType>::value;


    template<class ChassisType>
    struct DriveSetting_t {
        static_assert(IsChassis<ChassisType>, "The template parameter is a not a Chassis type");
    };


    template<class ChassisType>
    struct Controllers_t {

        static_assert(IsChassis<ChassisType>, "The template parameter is a not a Chassis type");

        struct PID_t {
        };
        struct FeedForward_t {
        };

        PID_t pidControllers;
        std::optional<FeedForward_t> feedForwardControllers{std::nullopt};
    };
} // RockLib
