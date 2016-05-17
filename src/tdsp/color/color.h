#pragma once

#include <tdsp/base/enum.h>
#include <tdsp/signal/signal.h>

namespace tdsp {

enum class RGB { red, green, blue, last = blue };
enum class RGBW { red, green, blue, white, last = white };
enum class HSB { hue, saturation, brightness, last = brightness };
// enum class Stereo { left, right };

using Color = Sample<RGB>;
using Color256 = Sample<RGB, uint8_t>;

struct ColorS {
    float red = 0, green = 0, blue = 0;

    ColorS() = default;
    ColorS(float r, float g, float b) : red(r), green(g), blue(b) {}
    ColorS(Color const& c) : red(c[0]), green(c[1]), blue(c[2]) {}

    operator Color() const { return {{red, green, blue}}; }
};

inline Color makeColor(float r, float g, float b) {
    return {{r, g, b}};
}

/** Computational base - 0..1 float or 0..255 integer? */
enum class Base {normal, integer, last = integer};

} // tdsp
