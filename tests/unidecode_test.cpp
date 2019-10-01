//
// Created by Marek on 30.9.2019.
//

#define BOOST_TEST_MODULE unidecode_tests
#include <boost/test/unit_test.hpp>
#include <iostream>


#include "utf8_string_iterator.hpp"


BOOST_AUTO_TEST_SUITE(unidecode_test)

BOOST_AUTO_TEST_CASE(basic_test) {

    // TODO: ...

    const char input_text[] = u8"mačka žuvačka je náhle hovädo s dôverou zlých šľahúňov";
    for (char ch : input_text) {
        std::cout << ch << ": 0x" << std::hex << (static_cast<int>(ch) & 0xff) << "\n";
    }

    std::cout << std::endl;

    // unidecode::Unidecode();

}

// GT as ground truth ;)
static uint32_t GetCodePointSizeGT(uint8_t value)
{
    if ((value & 0x80) == 0) {
        return 1;

    } else if ((value & 0xE0) == 0xC0) {
        return 2;

    } else if ((value & 0xF0) == 0xE0) {
        return 3;

    } else if ((value & 0xF8) == 0xF0) {
        return 4;

    }

    return 1;
}

static uint32_t GetCodePointGT(const char* iter) {
    uint32_t value = 0;
    uint8_t  tmp   = *iter;

    if ((tmp & 0x80) == 0)  {
        value = tmp;

    } else if ((tmp & 0xE0) == 0xC0) {
        value = (tmp & 0x1F) << 6;

        tmp    = iter[1];
        value |= (tmp & 0x3F);


    } else if ((tmp & 0xF0) == 0xE0) {
        value = (tmp & 0x0F) << 12;

        tmp    =  iter[1];
        value |= (tmp & 0x3F) << 6;

        tmp    =  iter[2];
        value |= (tmp & 0x3F);

    } else {
        value = (tmp & 0x07) << 18;

        tmp    =  iter[1];
        value |= (tmp & 0x3F) << 12;

        tmp    =  iter[2];
        value |= (tmp & 0x3F) << 6;

        tmp    =  iter[3];
        value |= (tmp & 0x3F);
    }

    return value;
}

BOOST_AUTO_TEST_CASE(iterator_test) {

    size_t length = 0;
    const char* input_text = u8"mačka žuvačka je náhle hovädo s dôverou zlých šľahúňov";
    unidecode::Utf8StringIterator it = input_text;
    while (*it != 0) {
        ++it;
        length++;
    }

    BOOST_CHECK_EQUAL(length, 54);

    const char* input = input_text;
    while (*input != 0) {

        BOOST_CHECK_EQUAL(GetCodePointGT(input), unidecode::GetCodePoint(input));

        uint32_t input_size_gt = GetCodePointSizeGT(*input);
        uint32_t input_size = unidecode::GetCodePointSize(*input);
        BOOST_CHECK_EQUAL(input_size_gt, input_size);

        input += input_size;
    }


    for (uint8_t i = 0; i < UINT8_MAX; i++) {
        BOOST_CHECK_EQUAL(GetCodePointSizeGT(i), unidecode::GetCodePointSize(i));
    }

}


BOOST_AUTO_TEST_SUITE_END()
