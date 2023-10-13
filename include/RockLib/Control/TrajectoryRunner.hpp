//
// Created by Rocky Chen on 2023/10/3.
//
#pragma once

#include <memory>
#include "pros/rtos.hpp"
#include "RockLib/Chassis/AbstractChassis.hpp"
#include "RockLib/Util/AsyncWrapper.hpp"
#include "RockLib/Path/TrajectoryProcessor.hpp"
#include "RockLib/Path/Trajectory.hpp"
#include "RockLib/Util/Flags.hpp"
#include "RockLib/Control/Action.hpp"


namespace RockLib {

    class TrajectoryRunner : public AsyncWrapper {
    public:

         struct State_t{
            double velocity;
            double acceleration;
            double jerk;
        };

        TrajectoryRunner(std::shared_ptr<AbstractChassis> chassis, double defaultVelocity, double defaultAcceleration, double defaultJerk);

        void run(const ActionHolder& traget, RockLib::Flags flags = controller::flag::NONE);

        void run(const ActionHolder& target, const State_t& state, RockLib::Flags flags = controller::flag::NONE);

    private:

        std::shared_ptr<AbstractChassis> chassis;

        static TrajectoryProcessor trajProcessor;//only one processor can be used to define the path and motion states

        pros::Mutex mutex;

        const double defaultVelocity;
        const double defaultAcceleration;
        const double defaultJerk;

        State_t tempState;

        ActionHolder actions;
    };

}

