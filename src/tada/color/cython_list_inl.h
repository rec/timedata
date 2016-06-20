#pragma once

#include <algorithm>
#include <tada/color/cython_inl.h>
#include <tada/color/spread.h>

namespace tada {
namespace color {

template <typename ColorList>
size_t count(ColorList const& c, ValueType<ColorList> const& s) {
    return std::count(c.begin(), c.end(), s);
}

template <typename ColorList>
size_t count(ColorList const& c, ValueType<ColorList> const& s) {
    return std::count(c.begin(), c.end(), s);
}

template <typename ColorList>
void extend(ColorList const& in, ColorList& out) {
    in.insert(in.end(), out.begin(), out.end());
}

template <typename ColorList>
int index(ColorList const& c, ValueType<ColorList> const& s) {
    auto i = std::find(c.begin(), c.end(), s);
    return i != c.end() ? c - c.begin() : -1;
}

template <typename ColorList>
void insert(int key, ValueType<ColorList> const& color, ColorList& out) {
    if (not fixKey(key, out.size()))
        key = std::max(0, std::min(static_cast<int>(out.size()), key));
    out.insert(out.begin() + key, color);
}

template <typename ColorList>
bool pop(ColorList& colors, int key, ValueType<ColorList>& result) {
    if (not fixKey(key, out.size()))
        return false;
    result = colors[key];
    colors.erase(colors.begin() + key);
    return true;
}

template <typename ColorList>
void rotate(ColorList& colors, int pos) {
    tada::rotate(colors, pos);
}

template <typename ColorList>
void sort(ColorList const& colors) {
    using Color = ValueType<ColorList>
    auto comp = [](Color const& x, Color const& y) { return cmp(x, y) < 0.0f; };
    std::sort(colors.begin(), colors.end(), comp);
}

template <typename ColorList>
void round_cpp(ColorList const& c, size_t digits) {
}

template <typename ColorList>
ValueType<ColorList> max_cpp(ColorList const& c) {
}

template <typename ColorList>
ValueType<ColorList> min_cpp(ColorList const& c) {
}

template <typename ColorList>
void spreadAppend(ColorList& out, size_t size, ValueType<ColorList> const& end) {
    return tada::spreadAppend(out, size, end);
}

} // color
} // tada