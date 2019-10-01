//
// Created by Marek on 30.9.2019.
//


#pragma once

#include <iterator>
#include "common.hpp"

namespace unidecode {


    // TODO: make const and non-const version !
    class Utf8StringIterator {
      public:
        typedef ptrdiff_t difference_type; //almost always ptrdiff_t
        typedef unicode_char value_type; //almost always T
        typedef const unicode_char& reference; //almost always T& or const T&
        typedef const unicode_char* pointer; //almost always T* or const T*
        typedef std::bidirectional_iterator_tag iterator_category;  //usually std::forward_iterator_tag or similar

        Utf8StringIterator(const char* data);

        Utf8StringIterator();

        Utf8StringIterator(const Utf8StringIterator& it);

        ~Utf8StringIterator();

        Utf8StringIterator& operator=(const Utf8StringIterator& it);

        friend void swap(Utf8StringIterator& lhs, Utf8StringIterator& rhs);

        Utf8StringIterator& operator++();

        Utf8StringIterator operator++(int);

        value_type operator*() const;

//        pointer operator->() const;

        friend bool operator==(const Utf8StringIterator&, const Utf8StringIterator&);

        friend bool operator!=(const Utf8StringIterator&, const Utf8StringIterator&);

        Utf8StringIterator& operator--();

        Utf8StringIterator operator--(int);

      private:

        const char* it_;

        void StepForward();

        void StepBackward();
    };

}

namespace std {
    template<> struct iterator_traits<unidecode::Utf8StringIterator> {
        typedef unidecode::Utf8StringIterator::difference_type difference_type;
        typedef unidecode::Utf8StringIterator::value_type value_type;
        typedef unidecode::Utf8StringIterator::reference reference;
        typedef unidecode::Utf8StringIterator::pointer pointer;
        typedef unidecode::Utf8StringIterator::iterator_category iterator_category;
    };
}

