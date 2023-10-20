//
// Created by Rocky Chen on 2023/10/2.
//

#include "RockLib/Chassis/DifferentialDrive.hpp"

namespace RockLib {
    DifferentialDrive::DifferentialDrive(typename DifferentialDrive::DriveSetting_t setting) : AbstractChassis(), setting(
            std::make_unique<DifferentialDrive::DriveSetting_t>(setting)) {};

    DifferentialDrive::DifferentialDrive(typename DifferentialDrive::DriveSetting_t setting,
                                         RockLib::Localizer localizer) : AbstractChassis(localizer), setting(
            std::make_unique<DifferentialDrive::DriveSetting_t>(setting)) {}




//    Kinematics_t
    /*DifferentialDrive::inverseKinematics(const double yDir, const double xDir, const double theta) const override{
        double left = (yDir - (this->setting->trackWidth / 2) * theta) / (this->setting->wheelDiameter / 2);
        double right = (yDir + (this->setting->trackWidth / 2) * theta) / (this->setting->wheelDiameter / 2);
        return {left, right};
    }*/
} // RockLib