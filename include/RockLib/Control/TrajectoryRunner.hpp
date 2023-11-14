//
// Created by Rocky Chen on 2023/10/3.
//
#pragma once

#include <memory>
#include "pros/rtos.hpp"
#include "RockLib/Chassis/AbstractChassis.hpp"
#include "RockLib/Util/AsyncWrapper.hpp"
#include "RockLib/Path/TrajectoryProcessor.hpp"
#include "RockLib/Control/Action.hpp"
#include "RockLib/Control/ActionBuilder.hpp"
#include "RockLib/Control/FeedForward.hpp"
#include "RockLib/Control/PID.hpp"


namespace RockLib {
    class ActionBuilder;
    class TrajectoryProcessor;

    class TrajectoryRunner : public AsyncWrapper {
        friend class ActionBuilder;
    public:

        TrajectoryRunner(std::shared_ptr<AbstractChassis> chassis, double defaultVelocity, double defaultAcceleration,
                         double defaultJerk);

        std::unique_ptr<ActionBuilder> runAction();

    private:

        void run(bool waitUntilSettled = false)override;

        bool isSettled();

        void build();

        void loop()override;

        std::shared_ptr<AbstractChassis> chassis;

        std::unique_ptr<ActionBuilder> action;

        std::unique_ptr<TrajectoryProcessor> trajectoryProcessor;

        std::unique_ptr<FeedForward> rightFeedForward;
        std::unique_ptr<FeedForward> leftFeedForward;

        std::unique_ptr<PID> rightPID;
        std::unique_ptr<PID> leftPID;

        const double defaultVelocity;
        const double defaultAcceleration;
        const double defaultJerk;

        bool actionHaveBeenBuilt = false;
    };

}

