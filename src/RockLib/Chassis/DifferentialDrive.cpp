//
// Created by Rocky Chen on 2023/10/2.
//

#include "RockLib/Chassis/DifferentialDrive.hpp"

namespace RockLib {
    DifferentialDrive::DifferentialDrive(const DriveSetting_t<DifferentialDrive> &setting,
                                         const Controllers_t<DifferentialDrive> &controllers)
            : AbstractChassis(),
              setting(std::make_unique<DriveSetting_t<DifferentialDrive>>(setting)),
              controllers(std::make_unique<Controllers_t<DifferentialDrive>>(controllers)),
              defaultLocalizer(std::make_unique<IMELocalizer<DifferentialDrive>>(setting)) {};

    DifferentialDrive::DifferentialDrive(const DriveSetting_t<DifferentialDrive> &setting,
                                         const Controllers_t<DifferentialDrive> &controllers,
                                         const RockLib::Localizer &localizer)
            : AbstractChassis(localizer),
              setting(std::make_unique<DriveSetting_t<DifferentialDrive>>(setting)),
              controllers(std::make_unique<Controllers_t<DifferentialDrive>>(controllers)),
              defaultLocalizer(std::make_unique<IMELocalizer<DifferentialDrive>>(setting)) {}

    void DifferentialDrive::setControllers(const Controllers_t<DifferentialDrive> &controllers) {
        this->controllers = std::make_unique<Controllers_t<DifferentialDrive>>(controllers);
    }

}