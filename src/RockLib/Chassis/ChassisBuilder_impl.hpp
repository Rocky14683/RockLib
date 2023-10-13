//
// Created by Rocky Chen on 2023/10/2.
//

#include "RockLib/Chassis/ChassisBuilder.hpp"

namespace RockLib {
    template <typename ChassisType> template <typename... Args>
    const ChassisType& ChassisBuilder<ChassisType>::buildSFINAE(std::true_type, Args... args) {
        return ChassisType(args...);
    }

    template <typename ChassisType> template <typename... Args>
    const ChassisType& ChassisBuilder<ChassisType>::buildSFINAE(std::false_type, Args... args) {
        throw std::runtime_error("ChassisBuilder: Invalid constructor arguments");
    }

    template <class ChassisType> ChassisBuilder<ChassisType>::ChassisBuilder() {
        static_assert(std::is_base_of<AbstractChassis, ChassisType>::value,
                      "\nError: ChassisBuilder<Parameter>\n"
                      "                          ^^^Parameter must be a chassis type \n");
        this->hasSetting = false;
        this->hasLocalizer = false;
    }

    template <class ChassisType>
    ChassisBuilder<ChassisType>& ChassisBuilder<ChassisType>::withSetting(const typename ChassisType::DriveSetting_t& driveSetting) {
        this->driveSetting = driveSetting;
        this->hasSetting = true;
        return *this;
    }

    template <class ChassisType>
    ChassisBuilder<ChassisType>& ChassisBuilder<ChassisType>::withLocalizer(const RockLib::Localizer &localizer) {
        this->localizer = localizer;
        this->hasLocalizer = true;
        return *this;
    }

    template <class ChassisType> std::shared_ptr<ChassisType> ChassisBuilder<ChassisType>::build() {
        if (this->hasSetting && this->hasLocalizer) {
            return std::make_shared<ChassisType>(this->buildSFINAE(
                    std::is_constructible<ChassisType, typename ChassisType::DriveSetting_t, Localizer>(),
                    this->driveSetting, this->localizer));
        }else if(this->hasSetting){
            return std::make_shared<ChassisType>(this->buildSFINAE(
                    std::is_constructible<ChassisType, typename ChassisType::DriveSetting_t>(),
                    this->driveSetting));
        }else{
            throw std::runtime_error("ChassisBuilder: Not all parameters supplied, failed to build");
        }
    }

} // RockLib