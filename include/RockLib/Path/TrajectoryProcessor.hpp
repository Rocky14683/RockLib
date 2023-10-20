//
// Created by Rocky Chen on 2023/10/3.
//

#pragma once

#include <map>
#include "RockLib/Control/TrajectoryRunner.hpp"

namespace RockLib {
    class TrajectoryRunner;
    class TrajectoryProcessor {
    public:
        friend class TrajectoryRunner;

    private:
        TrajectoryProcessor(TrajectoryRunner* parent);

        void actionInit(const std::map<uint32_t, void*>& actions);

        void process();

        std::map<uint32_t, void*> actions;
        TrajectoryRunner* parent;
    };

} // RockLib
