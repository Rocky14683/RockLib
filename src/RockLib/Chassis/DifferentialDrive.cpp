//
// Created by Rocky Chen on 2023/10/2.
//

#include "RockLib/Chassis/DifferentialDrive.hpp"

namespace RockLib {
    DifferentialDrive::DifferentialDrive(const DifferentialDrive::DriveSetting_t &setting) : setting(
            std::make_unique<DifferentialDrive::DriveSetting_t>(setting)) {};

    DifferentialDrive::DifferentialDrive(const DifferentialDrive::DriveSetting_t &setting,
                                         const RockLib::Localizer &localizer) : AbstractChassis(localizer), setting(
            std::make_unique<DifferentialDrive::DriveSetting_t>(setting)) {};

//    Kinematics_t
    /*DifferentialDrive::inverseKinematics(const double yDir, const double xDir, const double theta) const override{
        double left = (yDir - (this->setting->trackWidth / 2) * theta) / (this->setting->wheelDiameter / 2);
        double right = (yDir + (this->setting->trackWidth / 2) * theta) / (this->setting->wheelDiameter / 2);
        return {left, right};
    }*/
} // RockLib