//
// Created by Marek on 1.10.2019.
//


#pragma once

#include <stdint.h>

namespace unidecode {

    typedef uint32_t unicode_char;

    static const uint8_t kMask0[] = {0xff};
    static const uint8_t kMask1[] = {0x3f, 0x1f};
    static const uint8_t kMask2[] = {0x3f, 0x3f, 0x0f};
    static const uint8_t kMask3[] = {0x3f, 0x3f, 0x3f, 0x07};

    static const uint8_t* kCodePointMasks[] = {
        kMask0,
        kMask1,
        kMask2,
        kMask3,
    };

    inline uint32_t GetCodePointSize(uint8_t value) {
        uint32_t result = 0;
        result += 1 * ((value & 0x80) == 0);
        result += 2 * ((value & 0xE0) == 0xC0);
        result += 3 * ((value & 0xF0) == 0xE0);
        result += 4 * ((value & 0xF8) == 0xF0);
        result += 1 * (result == 0);

        return result;
    }

    inline unicode_char GetCodePoint(const char* ptr) {
        uint32_t code_point_size = GetCodePointSize(*ptr);
        const uint8_t* mask = kCodePointMasks[code_point_size - 1];
        unicode_char result = 0;
        for (uint32_t i = code_point_size; i-->0; ptr++) {
            result |= (*ptr & mask[i]) << 6 * i;
        }
        return result;
    }

}
