//
// Created by Rocky Chen on 2023/10/2.
//
#pragma once

#include <type_traits>
#include "RockLib/Chassis/ChassisBuilder.hpp"

namespace RockLib {

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
    ChassisBuilder<ChassisType>::withPIDControllers(const typename ChassisType::Controllers_t::PID_t &pidControllers) {
        this->controllers->pidControllers = pidControllers;
        this->pidControllerInited = true;
        return *this;
    }

    template<Chassis ChassisType>
    auto &
    ChassisBuilder<ChassisType>::withFeedForwardControllers(
            const typename ChassisType::Controllers_t::FeedForward_t &feedFwdControllers) {
        return *this;
    }


    template<Chassis ChassisType>
    std::shared_ptr<ChassisType>
    ChassisBuilder<ChassisType>::build() {

        if (this->driveSetting != nullptr &&
            this->pidControllerInited &&
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