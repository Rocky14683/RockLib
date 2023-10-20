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

        this->action = std::make_unique<ActionBuilder>(ActionBuilder(this));
        this->trajectoryProcessor = std::make_unique<TrajectoryProcessor>(TrajectoryProcessor(this));


        this->chassis->getMutex()->take();

        this->start("TrajectoryRunner");
        this->pause();

        this->chassis->getMutex()->give();
    };

    void TrajectoryRunner::build() {
        this->trajectoryProcessor->actionInit(this->action->holder);
    };


    std::unique_ptr<ActionBuilder> TrajectoryRunner::buildAction() {
        if(this->actionHaveBeenBuilt){
            throw std::runtime_error("The action has already been built, do not build it again until you run it");
        }
        this->actionHaveBeenBuilt = true;
        return std::move(this->action);
    };

    void TrajectoryRunner::run(bool waitUntilSettled) {
        if (!this->actionHaveBeenBuilt || this->action->holder.empty()) {
            throw std::runtime_error("No action was assigned to the trajectory runner");
        }

        this->resume();

        while(waitUntilSettled && !this->isSettled()){
            pros::delay(10);
        }
    }

    void TrajectoryRunner::loop(){
        this->chassis->getMutex()->take();
        while(true){
            /**
            TODO: Implement the trajectory runner
            **/
            if(true){
                break;
            }
        }

        this->chassis->getMutex()->give();
        this->action->holder.clear();
    }


};