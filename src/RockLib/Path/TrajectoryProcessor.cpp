//
// Created by Rocky Chen on 2023/10/3.
//

#include "RockLib/Path/TrajectoryProcessor.hpp"

namespace RockLib {
    TrajectoryProcessor::TrajectoryProcessor(RockLib::TrajectoryRunner *parent) {
        this->parent = parent;
    }
} // RockLib