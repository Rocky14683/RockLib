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
    public:
        struct DriveSetting_t{};

        explicit AbstractChassis() = default;
        void operator=(const AbstractChassis& rhs) = delete;
        explicit AbstractChassis(const Localizer& localizer);

        Pose getPose()const;
        void setPose(Pose pose)const;

//        struct Kinematics_t{};
//        virtual Kinematics_t inverseKinematics(const double yDir, const double xDir,const double theta) = 0;//yDir : fwd and bwd direction, xDir : right and left direction


        template<class ChassisType>
        friend class ChassisBuilder;

    private:
        std::shared_ptr<Localizer> localizer;
    };

} // RockLib
