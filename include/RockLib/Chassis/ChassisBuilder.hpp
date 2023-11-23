//
// Created by Rocky Chen on 2023/10/2.
//
#pragma once

#include "AbstractChassis.hpp"
#include <type_traits>
#include "RockLib/Control/PID.hpp"
#include "DifferentialDrive.hpp"

namespace RockLib {


    template<IsChassis ChassisType>
    class ChassisBuilder {
    public:
        ChassisBuilder() = default;

        ~ChassisBuilder() = default;

        auto withSetting(const DriveSetting_t<ChassisType> &driveSetting) -> ChassisBuilder<ChassisType> &;

        auto withLocalizer(const Localizer &localizer) -> ChassisBuilder<ChassisType> &;

        auto withPIDControllers(const Controllers_t<ChassisType>::PID_t &controllers) -> ChassisBuilder<ChassisType> &;

        auto withFeedForwardControllers(
                const Controllers_t<ChassisType>::FeedForward_t &controllers) -> ChassisBuilder<ChassisType> &;

        [[nodiscard("\nThe builder returns a chassis.\nYou can use std::shared_ptr<ChassisType> or auto to get the chassis object")]]
        std::shared_ptr<ChassisType> build();

    private:

        const DriveSetting_t<ChassisType> *driveSetting{nullptr};

        Controllers_t<ChassisType> *controllers{};
        bool pidControllerInited = false;

        const Localizer *localizer{nullptr};
    };
} // RockLib

#include "../src/RockLib/Chassis/ChassisBuilder_impl.hpp"
