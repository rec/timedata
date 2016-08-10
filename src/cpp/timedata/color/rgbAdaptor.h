#pragma once

#include <functional>

#include <timedata/signal/convert_inl.h>

namespace timedata {
namespace color_list {

using RGBIndexer = std::function<ColorRGB (size_t index)>;

template <typename ColorList>
RGBIndexer getIndexer(ColorList const& colors) {
    return [&] (size_t i) {
        ColorRGB result;
        converter::convertSample(colors[i], result);
        return result;
    };
}

template <typename ColorList>
struct RGBAdaptor {
    RGBAdaptor(ColorList const& ls) : colors(ls) {}
    ColorList const& colors;

    ColorRGB operator[](size_t i) const {
        ColorRGB result;
        converter::convertSample(colors[i], result);
        return result;
    };

    size_t size() const { return colors.size(); }
};

}  // timedata
}  // color_list
