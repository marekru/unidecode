//
// Created by Marek on 30.9.2019.
//


#pragma once

#include "common.hpp"

namespace unidecode {


    // TODO: study string interator of csstring implementation
    // https://github.com/copperspice/cs_string/blob/master/src/cs_char.h

    template<typename Iterator>
    void Unidecode(const Iterator& in_begin, const Iterator& in_end, Iterator& out_begin, Iterator& out_end) {
        // TODO: check input & output size !

        for (auto it = in_begin; it != in_end; ++it) {



        }

    }

}
