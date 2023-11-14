//
// Created by Rocky Chen on 2023/10/17.
//

#pragma once
#include <map>
#include <functional>
#include "RockLib/Control/TrajectoryRunner.hpp"
#include "RockLib/Util/Flags.hpp"
#include "RockLib/Util/Point.hpp"
#include "RockLib/Control/Action.hpp"


namespace RockLib {
    class TrajectoryRunner;

    class ActionBuilder {
        friend class TrajectoryRunner;
    public:

        ActionBuilder(TrajectoryRunner* parent);

        ActionBuilder& delay(double sec);

        ActionBuilder& turn(double angle, Flags flags = flag::NONE, Action::MotionConstraints_t constraint = {0, 0, 0});

        ActionBuilder& turnTo(Point target, Flags flags = flag::NONE, Action::MotionConstraints_t constraint = {0, 0, 0});

        ActionBuilder& move(double distance, Flags flags = flag::NONE, Action::MotionConstraints_t constraint = {0, 0, 0});

        ActionBuilder& moveTo(Point target, Flags flags = flag::NONE, Action::MotionConstraints_t constraint = {0, 0, 0});

        ActionBuilder& moveToArc(Point target, double radius, Flags flags = flag::NONE, Action::MotionConstraints_t constraint = {0, 0, 0});

        ActionBuilder& splineTo(Point target, Point c1, Point c2, Flags flags = flag::NONE, Action::MotionConstraints_t constraint = {0, 0, 0});

        ActionBuilder& splineTo(Point target, Point c1, Flags flags = flag::NONE, Action::MotionConstraints_t constraint = {0, 0, 0});

        ActionBuilder& splineTo(std::vector<Point> target, Flags flags = flag::NONE, Action::MotionConstraints_t constraints = {0, 0, 0});

        void run(bool waitUntilSettled = false);

    private:
        void reset();

        TrajectoryRunner* parent;

        Action action;

        uint32_t actionID;
        std::map<uint32_t, void*> holder;
    };

} // RockLib

