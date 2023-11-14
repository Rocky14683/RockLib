//
// Created by Rocky Chen on 2023/10/2.
//

#pragma once

#include "pros/imu.hpp"
#include "pros/motors.hpp"
#include "RockLib/Util/Pose.hpp"
#include "RockLib/Localizer/Localizer.hpp"
#include "RockLib/Control/PID.hpp"

namespace RockLib {

    class AbstractChassis {
    public:
        typedef struct {
        } DriveSetting_t;

        void setLinearPID(PID linearPID);
        void setAngularPID(PID angularPID);

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
        PID linearPID{};
        PID angularPID{};
    };

} // RockLib
