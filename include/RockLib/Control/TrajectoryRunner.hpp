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
#include "ActionBuilder.hpp"


namespace RockLib {

    class TrajectoryRunner : public AsyncWrapper {
        friend class ActionBuilder;
    public:

        TrajectoryRunner(std::shared_ptr<AbstractChassis> chassis, double defaultVelocity, double defaultAcceleration,
                         double defaultJerk);

        void run(bool waitUntilSettled = false)override;

        std::unique_ptr<ActionBuilder> buildAction();

    private:

        bool isSettled();

        void build();

        void loop()override;

        std::shared_ptr<AbstractChassis> chassis;

        std::unique_ptr<ActionBuilder> action;

        std::unique_ptr<TrajectoryProcessor> trajectoryProcessor;

        const double defaultVelocity;
        const double defaultAcceleration;
        const double defaultJerk;

        bool actionHaveBeenBuilt = false;
    };

}

