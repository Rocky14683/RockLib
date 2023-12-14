//
// Created by Rocky Chen on 2023/10/2.
//

#include "RockLib/Chassis/AbstractChassis.hpp"
#include "RockLib/Localizer/Localizer.hpp"

namespace RockLib {

    AbstractChassis::AbstractChassis() : mutex(std::make_unique<pros::Mutex>()) {};

    AbstractChassis::AbstractChassis(const RockLib::Localizer &localizer) :
            localizer(std::make_unique<Localizer>(localizer)),
            mutex(std::make_unique<pros::Mutex>()) {};


    Pose AbstractChassis::getPose() const {
        return this->localizer->getPose();
    }

    void AbstractChassis::setPose(Pose pose) const {
        this->localizer->setPose(pose);//do not modify  the address of the localizer
    }

    pros::Mutex* AbstractChassis::getMutex() {
        return this->mutex.get();
    }


} // RockLib