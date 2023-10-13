//
// Created by Rocky Chen on 2023/10/2.
//
#pragma once

#include "AbstractChassis.hpp"

namespace RockLib {
    template<class ChassisType>
    class ChassisBuilder {
    public:
        ChassisBuilder();

        ~ChassisBuilder() = default;

        ChassisBuilder &withSetting(const typename ChassisType::DriveSetting_t& driveSetting);

        ChassisBuilder &withLocalizer(const Localizer& localizer);

        std::shared_ptr<ChassisType> build();

    private:
        template<typename... Args>
        const ChassisType& buildSFINAE(std::true_type, Args... args);

        template<typename... Args>
        const ChassisType& buildSFINAE(std::false_type, Args... args);

        const typename ChassisType::DriveSetting_t driveSetting;
        const Localizer& localizer;
        bool hasSetting;
        bool hasLocalizer;
    };
} // RockLib

