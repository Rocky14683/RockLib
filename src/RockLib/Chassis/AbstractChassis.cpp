//
// Created by Rocky Chen on 2023/10/2.
//

#include "RockLib/Chassis/AbstractChassis.hpp"

namespace RockLib {
    AbstractChassis::AbstractChassis(const RockLib::Localizer &localizer) : localizer(
            std::make_unique<Localizer>(localizer)) {};

    Pose AbstractChassis::getPose() const {
        return this->localizer->getPose();
    }

    void AbstractChassis::setPose(Pose pose) const {
        this->localizer->setPose(pose);//do not modify  the address of the localizer
    }
} // RockLib