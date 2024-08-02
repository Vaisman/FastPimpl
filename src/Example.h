#pragma once

struct Example {
    int value;
    Example() : value(0) {}
    Example(int v) : value(v) {}
    Example(const Example& other) : value(other.value) {}
    Example(Example&& other) noexcept : value(other.value) { other.value = 0; }
    Example& operator=(const Example& other) {
        if (this != &other) {
            value = other.value;
        }
        return *this;
    }
    Example& operator=(Example&& other) noexcept {
        if (this != &other) {
            value = other.value;
            other.value = 0;
        }
        return *this;
    }
    ~Example() = default;
};