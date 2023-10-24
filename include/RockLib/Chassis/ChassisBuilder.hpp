//
// Created by Rocky Chen on 2023/10/2.
//
#pragma once

#include "AbstractChassis.hpp"
#include <type_traits>

namespace RockLib {
    template<class ChassisType>
    concept Chassis = std::is_base_of<AbstractChassis, ChassisType>::value;


    template<Chassis ChassisType>
    class ChassisBuilder {
    public:
        ChassisBuilder();

        ~ChassisBuilder() = default;

        ChassisBuilder &withSetting(const typename ChassisType::DriveSetting_t &driveSetting);

        ChassisBuilder &withLocalizer(const Localizer &localizer);

        std::shared_ptr<ChassisType> build();

    private:

        const typename ChassisType::DriveSetting_t *driveSetting{nullptr};
        const Localizer *localizer{nullptr};
        bool hasSetting = false;
        bool hasLocalizer = false;
    };
} // RockLib

#include "../src/RockLib/Chassis/ChassisBuilder_impl.hpp"
