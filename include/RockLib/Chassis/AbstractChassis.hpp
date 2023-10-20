//
// Created by Rocky Chen on 2023/10/2.
//

#pragma once
#include "pros/imu.hpp"
#include "pros/motors.hpp"
#include "RockLib/Util/Pose.hpp"
#include "RockLib/Localizer/Localizer.hpp"

namespace RockLib {

    class AbstractChassis {
    protected:


        AbstractChassis();
        AbstractChassis(const Localizer& localizer);
        void operator = (const AbstractChassis& rhs) = delete;

    public:
        typedef struct {}DriveSetting_t;

        Pose getPose()const;
        void setPose(Pose pose)const;

        pros::Mutex* getMutex();

//        struct Kinematics_t{};
//        virtual Kinematics_t inverseKinematics(const double yDir, const double xDir,const double theta) = 0;//yDir : fwd and bwd direction, xDir : right and left direction


    private:
        std::shared_ptr<Localizer> localizer;
        pros::Mutex mutex;
    };

} // RockLib
