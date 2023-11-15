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
        ChassisBuilder();

        ~ChassisBuilder() = default;

        auto &withSetting(const typename ChassisType::DriveSetting_t &driveSetting);

        auto &withLocalizer(const Localizer &localizer);

        auto &withControllers(const typename ChassisType::Controllers_t &controllers);


        std::shared_ptr<ChassisType> build();

    private:

        const typename ChassisType::DriveSetting_t *driveSetting{nullptr};
        const typename ChassisType::Controllers_t *controllers{nullptr};
        const Localizer *localizer{nullptr};
        std::optional<PID> linearController = std::nullopt;
        std::optional<PID> angularController = std::nullopt;
    };
} // RockLib

#include "../src/RockLib/Chassis/ChassisBuilder_impl.hpp"
