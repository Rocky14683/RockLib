//
// Created by Rocky Chen on 2023/10/2.
//
#pragma once

#include <type_traits>
#include "RockLib/Chassis/ChassisBuilder.hpp"

namespace RockLib {

    template<Chassis ChassisType>
    ChassisBuilder<ChassisType>::ChassisBuilder() {

    }

    template<Chassis ChassisType>
    auto &
    ChassisBuilder<ChassisType>::withSetting(const typename ChassisType::DriveSetting_t &driveSetting) {
        this->driveSetting = &driveSetting;
        return *this;
    }

    template<Chassis ChassisType>
    auto &
    ChassisBuilder<ChassisType>::withLocalizer(const RockLib::Localizer &localizer) {
        this->localizer = &localizer;
        return *this;
    }

    template<Chassis ChassisType>
    auto &
    ChassisBuilder<ChassisType>::withControllers(const typename ChassisType::Controllers_t &controllers) {
        this->controllers = &controllers;
        return *this;
    }

    template<Chassis ChassisType>
    std::shared_ptr<ChassisType>
    ChassisBuilder<ChassisType>::build() {

        if (this->driveSetting != nullptr &&
            this->controllers != nullptr &&
            this->localizer != nullptr &&
            std::is_constructible<ChassisType, decltype(*this->driveSetting), decltype(*this->controllers), decltype(*this->localizer)>::value) {

            return std::move(
                    std::make_shared<ChassisType>(*this->driveSetting, *this->controllers, *this->localizer));

        } else if (this->driveSetting != nullptr &&
                   this->controllers != nullptr &&
                   std::is_constructible<ChassisType, decltype(*this->driveSetting), decltype(*this->controllers)>::value) {

            return std::move(
                    std::make_shared<ChassisType>(*this->driveSetting, *this->controllers));

        } else {
            throw std::runtime_error("ChassisBuilder: Not all parameters supplied, failed to build");
        }
    }

};// RockLib