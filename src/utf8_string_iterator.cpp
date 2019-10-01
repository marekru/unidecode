//
// Created by Marek on 1.10.2019.
//

#include "utf8_string_iterator.hpp"

namespace unidecode {

    Utf8StringIterator::Utf8StringIterator(const char* data) : it_(data) {}

    Utf8StringIterator::Utf8StringIterator() : it_(nullptr) {};

    Utf8StringIterator::Utf8StringIterator(const Utf8StringIterator& it) : it_(it.it_) {}

    Utf8StringIterator::~Utf8StringIterator() {
        // for destruction of the data is responsible someone else ...
        // // TODO: maybe use some kind of smart ptr .. weak_ptr?
        it_ = nullptr;
    };

    Utf8StringIterator& Utf8StringIterator::operator=(const Utf8StringIterator& it) {
        it_ = it.it_;
        return *this;
    }


    void swap(Utf8StringIterator & lhs, Utf8StringIterator & rhs) {
        const char* old_it = lhs.it_;
        lhs.it_ = rhs.it_;
        rhs.it_ = old_it;
    }

    Utf8StringIterator& Utf8StringIterator::operator++() {
        StepForward();
        return *this;
    }

    Utf8StringIterator Utf8StringIterator::operator++(int) {
        Utf8StringIterator result = *this;
        StepForward();
        return result;
    }

    Utf8StringIterator::value_type Utf8StringIterator::operator*() const {
        return GetCodePoint(it_);
    }

//    pointer Utf8StringIterator::operator->() const {
//        // TODO:
//    }

    bool operator==(const Utf8StringIterator& lhs, const Utf8StringIterator& rhs) {
        return lhs.it_ == rhs.it_;
    }

    bool operator!=(const Utf8StringIterator& lhs, const Utf8StringIterator& rhs) {
        return !(lhs == rhs);
    }

    Utf8StringIterator& Utf8StringIterator::operator--() {
        StepBackward();
        return *this;
    }

    Utf8StringIterator Utf8StringIterator::operator--(int) {
        Utf8StringIterator result = *this;
        StepBackward();
        return result;
    }

    void Utf8StringIterator::StepForward() {
        size_t step_size = GetCodePointSize(*it_);
        it_ += step_size;
    }

    void Utf8StringIterator::StepBackward() {
        const char* it = it_;
        do {
            --it;
        } while ((*it & 0xC0) != 0x80); // stop at the beginning of a char
        it_ = it;
    }

}

