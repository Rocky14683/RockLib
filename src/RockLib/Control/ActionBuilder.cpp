//
// Created by Rocky Chen on 2023/10/17.
//

#include "RockLib/Control/ActionBuilder.hpp"

namespace RockLib {

    ActionBuilder::ActionBuilder(TrajectoryRunner *parent) : parent(parent) {
        this->actionID = 0;
        this->holder.clear();
    }

    ActionBuilder &ActionBuilder::delay(double msec) {
        this->holder[++this->actionID] = new std::function<void()>([&, this]() {
            pros::delay(msec);
        });

        return *this;
    }

    ActionBuilder &ActionBuilder::turn(double angle, Flags flags, ActionBuilder::MotionConstraints_t constraint) {
        this->holder[++this->actionID] = new std::function<void()>([&, this]() {

        });

        return *this;
    }

    ActionBuilder &ActionBuilder::turnTo(Point target, Flags flags, ActionBuilder::MotionConstraints_t constraint) {
        this->holder[++this->actionID] = new std::function<void()>([&, this]() {

        });

        return *this;
    }

    ActionBuilder &ActionBuilder::moveToArc(Point target, double radius, RockLib::Flags flags,
                                            ActionBuilder::MotionConstraints_t constraint) {
        this->holder[++this->actionID] = new std::function<void()>([&, this]() {

        });

        return *this;
    }

    ActionBuilder &ActionBuilder::move(double distance, Flags flags, ActionBuilder::MotionConstraints_t constraint) {
        this->holder[++this->actionID] = new std::function<void()>([&, this]() {

        });

        return *this;
    }

    ActionBuilder &ActionBuilder::moveTo(Point target, Flags flags, ActionBuilder::MotionConstraints_t constraint) {
        this->holder[++this->actionID] = new std::function<void()>([&, this]() {

        });

        return *this;
    }

    ActionBuilder &ActionBuilder::splineTo(Point target, Point c1, Point c2, Flags flags,
                                           ActionBuilder::MotionConstraints_t constraint) {
        this->holder[++this->actionID] = new std::function<void()>([&, this]() {

        });

        return *this;
    }

    ActionBuilder &
    ActionBuilder::splineTo(Point target, Point c1, Flags flags, ActionBuilder::MotionConstraints_t constraint) {
        this->holder[++this->actionID] = new std::function<void()>([&, this]() {

        });

        return *this;
    }

    ActionBuilder &ActionBuilder::splineTo(std::vector<Point> target, RockLib::Flags flags,
                                           ActionBuilder::MotionConstraints_t constraints) {
        this->holder[++this->actionID] = new std::function<void()>([&, this]() {

        });

        return *this;
    }


    void ActionBuilder::run(bool waitUntilSettled) {
        this->parent->build();//call trajectory runner to send actions to the trajectory processor
        this->parent->run(waitUntilSettled);
    }

    void ActionBuilder::reset() {
        this->actionID = 0;
        this->holder.clear();
    }

} // RockLib