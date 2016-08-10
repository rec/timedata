#pragma once

#include <timedata/signal/convert_inl.h>

namespace timedata {
namespace color_list {

template <typename ColorList>
struct RGBAdaptor {
    RGBAdaptor(ColorList const& ls) : list(ls) {}
    ColorList const& list;

    ColorRGB operator[](size_t i) const {
        ColorRGB result;
        converter::convertSample(list[i], result);
        return result;
    };

    size_t size() const { return list.size(); }
};

}  // timedata
}  // color_list
