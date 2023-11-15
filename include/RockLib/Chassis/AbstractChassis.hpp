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
        typedef struct DriveSetting_t{
        } DriveSetting_t;

        typedef struct Controllers_t{
            struct PID_t{};
            struct FeedForward_t{};

            PID_t pidControllers;
            std::optional<FeedForward_t> feedForwardControllers{std::nullopt};
        } Controllers_t;

        Pose getPose() const;
        void setPose(Pose pose) const;

        pros::Mutex *getMutex();

    protected:
        AbstractChassis();

        AbstractChassis(const Localizer &localizer);

        void operator=(const AbstractChassis &rhs) = delete;

    private:
        std::shared_ptr<Localizer> localizer;
        pros::Mutex mutex;
    };

} // RockLib
