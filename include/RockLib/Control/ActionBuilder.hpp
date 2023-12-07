//
// Created by Rocky Chen on 2023/10/17.
//

#pragma once

#include <map>
#include <functional>
#include <optional>
#include "RockLib/Control/TrajectoryRunner.hpp"
#include "RockLib/Util/Flags.hpp"
#include "RockLib/Util/Point.hpp"

namespace RockLib {
    class TrajectoryRunner;

    class ActionBuilder {
        friend class TrajectoryRunner;

    public:
        struct MotionConstraints_t {
            std::optional<double> velocity = std::nullopt;
            std::optional<double> acceleration = std::nullopt;
            std::optional<double> jerk = std::nullopt;

            explicit operator bool() const {
                return this != &const_cast<MotionConstraints_t &>(DEFAULT_CONSTRAINT);
            }

            const static MotionConstraints_t DEFAULT_CONSTRAINT;
        };

        struct ActionContainer {
            std::function<void()> lambda;
            std::vector<Pose> intendedPath;
            Flags flags;
            std::optional<MotionConstraints_t> constraint = std::nullopt;
        };

        ActionBuilder(TrajectoryRunner *parent);

        ActionBuilder &delay(double msec);

        ActionBuilder &turn(double angle, Flags flags = Flag::NONE,
                            const ActionBuilder::MotionConstraints_t &constraint = MotionConstraints_t::DEFAULT_CONSTRAINT);

        ActionBuilder &turnTo(Point target, Flags flags = Flag::NONE,
                              const ActionBuilder::MotionConstraints_t &constraint = MotionConstraints_t::DEFAULT_CONSTRAINT);

        ActionBuilder &move(double distance, Flags flags = Flag::NONE,
                            const ActionBuilder::MotionConstraints_t &constraint = MotionConstraints_t::DEFAULT_CONSTRAINT);

        ActionBuilder &moveTo(Point target, Flags flags = Flag::NONE,
                              const ActionBuilder::MotionConstraints_t &constraint = MotionConstraints_t::DEFAULT_CONSTRAINT);

        ActionBuilder &moveToArc(Point target, double radius, Flags flags = Flag::NONE,
                                 const ActionBuilder::MotionConstraints_t &constraint = MotionConstraints_t::DEFAULT_CONSTRAINT);

        ActionBuilder &splineTo(Point target, Point c1, Point c2, Flags flags = Flag::NONE,
                                const ActionBuilder::MotionConstraints_t &constraint = MotionConstraints_t::DEFAULT_CONSTRAINT);

        ActionBuilder &splineTo(Point target, Point c1, Flags flags = Flag::NONE,
                                const ActionBuilder::MotionConstraints_t &constraint = MotionConstraints_t::DEFAULT_CONSTRAINT);

        ActionBuilder &splineTo(const std::initializer_list<Point> &target, Flags flags = Flag::NONE,
                                const ActionBuilder::MotionConstraints_t &constraints = MotionConstraints_t::DEFAULT_CONSTRAINT);

        void run(bool waitUntilSettled = false);

    private:
        void reset();

        void setConstraint(const ActionBuilder::MotionConstraints_t &constraint);

        TrajectoryRunner *parent;

        uint32_t actionID;
        std::map<uint32_t, ActionContainer> holder;
    };

} // namespace RockLib
