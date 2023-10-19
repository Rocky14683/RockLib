//
// Created by Rocky Chen on 2023/10/17.
//

#include "RockLib/Control/ActionBuilder.hpp"

namespace RockLib {

    ActionBuilder::ActionBuilder(TrajectoryRunner* parent): parent(parent){
        this->action = Action();
        this->actionID = 0;
        this->holder.clear();
    }

    ActionBuilder& ActionBuilder::delay(double sec){
        this->holder[++this->actionID] = new std::function<void()>([&, this](){
            this->action.delay(sec);
        });

        return *this;
    }

    ActionBuilder& ActionBuilder::turn(double angle, Flags flags, Action::MotionConstraints_t constraint){
        this->holder[++this->actionID] = new std::function<void()>([&, this](){
            this->action.turn(angle, flags, constraint);
        });

        return *this;
    }

    ActionBuilder& ActionBuilder::turnTo(Point target, Flags flags, Action::MotionConstraints_t constraint){
        this->holder[++this->actionID] = new std::function<void()>([&, this](){
            this->action.turnTo(target, flags, constraint);
        });

        return *this;
    }

    ActionBuilder& ActionBuilder::moveToArc(Point target, double radius, RockLib::Flags flags, Action::MotionConstraints_t constraint) {
        this->holder[++this->actionID] = new std::function<void()>([&, this](){
            this->action.moveToArc(target, radius, flags, constraint);
        });

        return *this;
    }

    ActionBuilder& ActionBuilder::move(double distance, Flags flags, Action::MotionConstraints_t constraint){
        this->holder[++this->actionID] = new std::function<void()>([&, this](){
            this->action.move(distance, flags, constraint);
        });

        return *this;
    }

    ActionBuilder& ActionBuilder::moveTo(Point target, Flags flags, Action::MotionConstraints_t constraint){
        this->holder[++this->actionID] = new std::function<void()>([&, this](){
            this->action.moveTo(target, flags, constraint);
        });

        return *this;
    }

    ActionBuilder& ActionBuilder::splineTo(Point target, Point c1, Point c2, Flags flags, Action::MotionConstraints_t constraint){
        this->holder[++this->actionID] = new std::function<void()>([&, this](){
            this->action.splineTo(target, c1, c2, flags, constraint);
        });

        return *this;
    }

    ActionBuilder& ActionBuilder::splineTo(Point target, Point c1, Flags flags, Action::MotionConstraints_t constraint){
        this->holder[++this->actionID] = new std::function<void()>([&, this](){
            this->action.splineTo(target, c1, flags, constraint);
        });

        return *this;
    }

    ActionBuilder& ActionBuilder::splineTo(std::vector<Point> target, RockLib::Flags flags,
                                           Action::MotionConstraints_t constraints) {
        this->holder[++this->actionID] = new std::function<void()>([&, this](){
            this->action.splineTo(target, flags, constraints);
        });

        return *this;
    }


    void ActionBuilder::build(){
        this->parent->build();//call trajectory runner to send actions to the trajectory processor
    }
} // RockLib