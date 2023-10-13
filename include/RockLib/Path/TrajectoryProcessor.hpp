//
// Created by Rocky Chen on 2023/10/3.
//

#pragma once

namespace RockLib {

    class TrajectoryProcessor {
    public:
        friend class TrajectoryRunner;

    private:
        TrajectoryProcessor() = default;

        void process();

        double maxVelocity;
        double acceleration;
        double deceleration;
        double jerk;

    };

} // RockLib
