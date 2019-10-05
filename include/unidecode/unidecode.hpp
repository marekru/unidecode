//
// Created by Marek on 30.9.2019.
//


#pragma once

#include "common.hpp"
#include "sections.hpp"

namespace unidecode {


    template<typename InputIterator, typename OutputIterator>
    void Unidecode(const InputIterator& in_begin, const InputIterator& in_end, OutputIterator out_it) {
        for (auto it = in_begin; it != in_end; ++it) {
            unicode_char codepoint = *it;

            // TODO: function from this !
            if (codepoint < 0x80) {
                *out_it = static_cast<char>(codepoint);
                ++out_it;
            } else if (codepoint <= 0xeffff) {  // Characters in Private Use Area and above are ignored

                uint32_t section = codepoint >> 8;
                uint32_t position = codepoint & 0xff; // only ast two hex digits
                // TODO: assert section < then xyz

                auto table = kUnidecodeData[section];
                if (table != nullptr) {  // TODO: check if position < table size
                    const char* symbol = table[position];
                    while (*symbol != 0) {
                        *out_it = *symbol;
                        ++out_it;
                        symbol++;
                    }
                }
            }
        }

    }

}
