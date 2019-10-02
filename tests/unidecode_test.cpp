//
// Created by Marek on 30.9.2019.
//

#define BOOST_TEST_MODULE unidecode_tests
#include <boost/test/unit_test.hpp>
#include <iostream>

#include "unidecode.hpp"
#include "utf8_string_iterator.hpp"


BOOST_AUTO_TEST_SUITE(unidecode_test)

BOOST_AUTO_TEST_CASE(basic_test) {

    const char input_text[] = u8"mačka žuvačka je náhle hovädo s dôverou zlých šľahúňov";
    unidecode::Utf8StringIterator begin = input_text;
    unidecode::Utf8StringIterator end = input_text + strlen(input_text);
    std::string output;
    unidecode::Unidecode(begin, end, std::back_inserter(output));

    BOOST_CHECK_EQUAL(output, std::string("macka zuvacka je nahle hovado s doverou zlych slahunov"));

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

void test_codepoint_decoding(const char* input) {
    size_t length = 0;
    while (*input != 0) {
        BOOST_CHECK_EQUAL(GetCodePointGT(input), unidecode::GetCodePoint(input));

        uint32_t input_size_gt = GetCodePointSizeGT(*input);
        uint32_t input_size = unidecode::GetCodePointSize(*input);
        BOOST_CHECK_EQUAL(input_size_gt, input_size);

        input += input_size;
        length++;
    }
    std::cout << "text length: " << length << std::endl;
}

BOOST_AUTO_TEST_CASE(iterator_test) {

    size_t length = 0;
    const char* slovak_text = u8"mačka žuvačka je náhle hovädo s dôverou zlých šľahúňov";

    unidecode::Utf8StringIterator it = slovak_text;
    while (*it != 0) {
        ++it;
        length++;
    }

    BOOST_CHECK_EQUAL(length, 54);

    test_codepoint_decoding(slovak_text);
    test_codepoint_decoding(u8"𩸽"); // expected length == 1
    test_codepoint_decoding(u8"🧠"); // expected length == 1 (brain)
    test_codepoint_decoding(u8"👨‍🦳"); // expected length == 3 (man: white hair)
    test_codepoint_decoding(u8"👮‍♀️🕵");  // expected length == 5 (woman police officer + detective)


    for (uint8_t i = 0; i < UINT8_MAX; i++) {
        BOOST_CHECK_EQUAL(GetCodePointSizeGT(i), unidecode::GetCodePointSize(i));
    }

}


BOOST_AUTO_TEST_SUITE_END()
