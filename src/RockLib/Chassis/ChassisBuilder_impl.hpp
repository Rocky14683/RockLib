//
// Created by Rocky Chen on 2023/10/2.
//
#pragma once
#include <type_traits>
#include "RockLib/Chassis/ChassisBuilder.hpp"

namespace RockLib {

    template<Chassis ChassisType>
    ChassisBuilder<ChassisType>::ChassisBuilder() {
        this->hasSetting = false;
        this->hasLocalizer = false;
    }

    template<Chassis ChassisType>
    ChassisBuilder<ChassisType> &
    ChassisBuilder<ChassisType>::withSetting(const typename ChassisType::DriveSetting_t &driveSetting) {
        this->driveSetting = &driveSetting;
        this->hasSetting = true;
        return *this;
    }

    template<Chassis ChassisType>
    ChassisBuilder<ChassisType> &
    ChassisBuilder<ChassisType>::withLocalizer(const RockLib::Localizer &localizer) {
        this->localizer = &localizer;
        this->hasLocalizer = true;
        return *this;
    }

    template<Chassis ChassisType>
    std::shared_ptr<ChassisType>
    ChassisBuilder<ChassisType>::build() {
        if(this->hasSetting && this->hasLocalizer && std::is_constructible<ChassisType, decltype(*this->driveSetting), decltype(*this->localizer)>::value){
            return std::make_shared<ChassisType>(*this->driveSetting, *this->localizer);
        } else if (this->hasSetting && std::is_constructible<ChassisType, decltype(*this->driveSetting)>::value) {
            return std::make_shared<ChassisType>(*this->driveSetting);
        } else {
            throw std::runtime_error("ChassisBuilder: Not all parameters supplied, failed to build");
        }
    }

};// RockLib