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
    ChassisBuilder<ChassisType>::withLinearController(const RockLib::PID linearController) {
        this->linearController = linearController;
        return *this;
    }

    template<Chassis ChassisType>
    auto &
    ChassisBuilder<ChassisType>::withAngularController(const RockLib::PID angularController) {
        this->angularController = angularController;
        return *this;
    }


    template<Chassis ChassisType>
    std::shared_ptr<ChassisType>
    ChassisBuilder<ChassisType>::build() {
        std::shared_ptr<ChassisType> chassisPtr;
        if (this->driveSetting != nullptr && this->localizer != nullptr &&
            std::is_constructible<ChassisType, decltype(*this->driveSetting), decltype(*this->localizer)>::value) {
            chassisPtr = std::move(std::make_shared<ChassisType>(*this->driveSetting, *this->localizer));
        } else if (this->driveSetting != nullptr &&
                   std::is_constructible<ChassisType, decltype(*this->driveSetting)>::value) {
            chassisPtr = std::move(std::make_shared<ChassisType>(*this->driveSetting));
        } else {
            throw std::runtime_error("ChassisBuilder: Not all parameters supplied, failed to build");
        }

        if (this->linearController.has_value()) {
            chassisPtr->setLinearPID(this->linearController.value());
        }

        if (this->angularController.has_value()) {
            chassisPtr->setAngularPID(this->angularController.value());
        }

        return chassisPtr;
    }

};// RockLib