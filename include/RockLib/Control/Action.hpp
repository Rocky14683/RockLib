//
// Created by Rocky Chen on 2023/10/12.
//
#pragma once
#include <any>
#include <vector>
#include <map>
#include "RockLib/Util/Flags.hpp"
#include "RockLib/Util/Point.hpp"

namespace RockLib {

    class Action{
    public:
        Action() noexcept = default;
        Action(const Action&) noexcept = default;
        Action(Action&& other) noexcept = delete;
        Action& operator=(const Action&) noexcept = default;

        struct MotionConstraints_t{
            double velocity;
            double acceleration;
            double jerk;
        };

    private:
        friend class ActionBuilder;

        void delay(double sec);

        void turn(double angle, Flags flags = flag::NONE, MotionConstraints_t constraint = {0, 0, 0});

        void turnTo(Point target, Flags flags = flag::NONE, MotionConstraints_t constraint = {0, 0, 0});

        void move(double distance, Flags flags = flag::NONE, MotionConstraints_t constraint = {0, 0, 0});

        void moveTo(Point target, Flags flags = flag::NONE, MotionConstraints_t constraint = {0, 0, 0});

        void moveToArc(Point target, double radius, Flags flags = flag::NONE, MotionConstraints_t constraint = {0, 0, 0});

        void splineTo(Point target, Point c1, Point c2, Flags flags = flag::NONE, MotionConstraints_t constraint = {0, 0, 0});

        void splineTo(Point target, Point c1, Flags flags = flag::NONE, MotionConstraints_t constraint = {0, 0, 0});

        void splineTo(std::vector<Point> target, Flags flags = flag::NONE, MotionConstraints_t constraints = {0, 0, 0});
    };

} // RockLib
