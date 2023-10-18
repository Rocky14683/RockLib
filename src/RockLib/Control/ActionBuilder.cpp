//
// Created by Rocky Chen on 2023/10/17.
//

#include "RockLib/Control/ActionBuilder.hpp"

namespace RockLib {

    ActionBuilder::ActionBuilder(){
        actionID = 0;
        this->holder.clear();
    }

    ActionBuilder& ActionBuilder::delay(double sec){
        this->holder[actionID] = new std::function<void()>([sec](){
            action.delay(sec);
        });
        actionID++;

        return *this;
    }

    ActionBuilder& ActionBuilder::turn(double angle, Flags flags, Action::MotionConstraints_t constraint){
        this->holder[actionID] = new std::function<void()>([angle, flags, constraint](){
            action.turn(angle, flags, constraint);
        });
        actionID++;

        return *this;
    }

    ActionBuilder& ActionBuilder::turnTo(Point target, Flags flags, Action::MotionConstraints_t constraint){
        this->holder[actionID] = new std::function<void()>([target, flags, constraint](){
            action.turnTo(target, flags, constraint);
        });
        actionID++;

        return *this;
    }

    ActionBuilder& ActionBuilder::moveToArc(Point target, double radius, RockLib::Flags flags, Action::MotionConstraints_t constraint) {
        this->holder[actionID] = new std::function<void()>([target, radius, flags, constraint](){
            action.moveToArc(target, radius, flags, constraint);
        });
        actionID++;

        return *this;
    }

    ActionBuilder& ActionBuilder::move(double distance, Flags flags, Action::MotionConstraints_t constraint){
        this->holder[actionID] = new std::function<void()>([distance, flags, constraint](){
            action.move(distance, flags, constraint);
        });
        actionID++;

        return *this;
    }

    ActionBuilder& ActionBuilder::moveTo(Point target, Flags flags, Action::MotionConstraints_t constraint){
        this->holder[actionID] = new std::function<void()>([target, flags, constraint](){
            action.moveTo(target, flags, constraint);
        });
        actionID++;

        return *this;
    }

    ActionBuilder& ActionBuilder::splineTo(Point target, Point c1, Point c2, Flags flags, Action::MotionConstraints_t constraint){
        this->holder[actionID] = new std::function<void()>([target, c1, c2, flags, constraint](){
            action.splineTo(target, c1, c2, flags, constraint);
        });
        actionID++;

        return *this;
    }

    ActionBuilder& ActionBuilder::splineTo(Point target, Point c1, Flags flags, Action::MotionConstraints_t constraint){
        this->holder[actionID] = new std::function<void()>([target, c1, flags, constraint](){
            action.splineTo(target, c1, flags);
        });
        actionID++;

        return *this;
    }

    void ActionBuilder::build(){

    }
} // RockLib