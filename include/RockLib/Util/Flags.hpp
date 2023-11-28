//
// Created by Rocky Chen on 2023/10/6.
//

#pragma once

#include <cstdint>

namespace RockLib {

    using Flags = uint8_t;

    namespace Flag{
        constexpr Flags NONE = 0x00; // 00000000
        constexpr Flags WIGGLE = 0x01; // 00000001
        constexpr Flags RELATIVE = 0x02; // 00000010
        constexpr Flags REVERSE = 0x03; // 00000100
    }

} // RockLib

