//
// Created by Rocky Chen on 2023/10/2.
//
#pragma once

#include "AbstractChassis.hpp"
#include <type_traits>
#include "RockLib/Control/PID.hpp"

namespace RockLib {
    template<class ChassisType>
    concept Chassis = std::is_base_of<AbstractChassis, ChassisType>::value;


    template<Chassis ChassisType>
    class ChassisBuilder {
    public:
        ChassisBuilder() = default;

        ~ChassisBuilder() = default;

        auto &withSetting(const typename ChassisType::DriveSetting_t &driveSetting);

        auto &withLocalizer(const Localizer &localizer);

        auto &withPIDControllers(const typename ChassisType::Controllers_t::PID_t &controllers);

        auto &withFeedForwardControllers(const typename ChassisType::Controllers_t::FeedForward_t &controllers);

        [[nodiscard("\nThe builder returns a chassis.\nYou can use std::shared_ptr<ChassisType> or auto to get the chassis object")]] std::shared_ptr<ChassisType> build();

    private:

        const typename ChassisType::DriveSetting_t *driveSetting{nullptr};

        typename ChassisType::Controllers_t *controllers{};
        bool pidControllerInited = false;

        const Localizer *localizer{nullptr};
    };
} // RockLib

#include "../src/RockLib/Chassis/ChassisBuilder_impl.hpp"
