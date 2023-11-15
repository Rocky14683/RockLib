//
// Created by Rocky Chen on 2023/10/2.
//

#include "RockLib/Chassis/DifferentialDrive.hpp"

namespace RockLib {
    DifferentialDrive::DifferentialDrive(const typename DifferentialDrive::DriveSetting_t &setting,
                                         const typename DifferentialDrive::Controllers_t &controllers)
            : AbstractChassis(), setting(
            std::make_unique<DifferentialDrive::DriveSetting_t>(setting)),
              controllers(std::make_unique<DifferentialDrive::Controllers_t>(controllers)) {};

    DifferentialDrive::DifferentialDrive(const typename DifferentialDrive::DriveSetting_t &setting,
                                         const typename DifferentialDrive::Controllers_t &controllers,
                                         const RockLib::Localizer &localizer) : AbstractChassis(localizer), setting(
            std::make_unique<DifferentialDrive::DriveSetting_t>(setting)), controllers(
            std::make_unique<DifferentialDrive::Controllers_t>(controllers)) {}

    void DifferentialDrive::setControllers(const DifferentialDrive::Controllers_t &controllers) {
        this->controllers = std::make_unique<DifferentialDrive::Controllers_t>(controllers);
    }


//    Kinematics_t
    /*DifferentialDrive::inverseKinematics(const double yDir, const double xDir, const double theta) const override{
        double left = (yDir - (this->setting->trackWidth / 2) * theta) / (this->setting->wheelDiameter / 2);
        double right = (yDir + (this->setting->trackWidth / 2) * theta) / (this->setting->wheelDiameter / 2);
        return {left, right};
    }*/
} // RockLib