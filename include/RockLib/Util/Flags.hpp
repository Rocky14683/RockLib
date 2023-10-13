//
// Created by Rocky Chen on 2023/10/6.
//

#pragma once

#include <cstdint>

namespace RockLib {
    using Flags = uint8_t;

    namespace controller::flag {
        const Flags NONE = 0x00;      // 00000000
        const Flags REVERSE = 0x01;       // 00000001
        const Flags CONNECT = 0x02;     // 00000010
    };

    namespace trajectory::flag{
        const Flags NONE = 0x00; // 00000000
        const Flags WIGGLE = 0x01; // 00000001
        const Flags RELATIVE = 0x02; // 00000010
    }

} // RockLib

