//
// Created by Rocky Chen on 2023/10/3.
//

#include "RockLib/Control/TrajectoryRunner.hpp"
#include "pros/rtos.hpp"

namespace RockLib{
    TrajectoryRunner::TrajectoryRunner(std::shared_ptr<AbstractChassis> chassis, double defaultVelocity,
                                       double defaultAcceleration, double defaultJerk):
                                       chassis(std::move(chassis)),
                                       defaultVelocity(defaultVelocity),
                                       defaultAcceleration(defaultAcceleration),
                                       defaultJerk(defaultJerk){

    };

    void TrajectoryRunner::run(const RockLib::ActionHolder &actions, RockLib::Flags flags) {
        this->run(actions, {this->defaultVelocity, this->defaultAcceleration, this->defaultJerk}, flags);
    }

    void TrajectoryRunner::run(const RockLib::ActionHolder &actions, const RockLib::TrajectoryRunner::State_t &state,
                               RockLib::Flags flags) {
        this->actions = actions;
        this->tempState = state;

    }
};