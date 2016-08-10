#pragma once

#include <timedata/color/renderer.h>

#include <timedata/base/gammaTable.h>
#include <timedata/signal/convert_inl.h>
#include <timedata/color/cython_list_inl.h>
#include <timedata/color/rgbAdaptor.h>

namespace timedata {
namespace color_list {

inline CRenderer::CRenderer(Render3 r)
        : gammaTable_(makeGammaTable(r.gamma, r.min, r.max)),
          perm_(getPerm(r.permutation)) {
}

template <typename Colors>
void CRenderer::renderGeneric(
        float level, Colors const& colors, char* out) {
    for (size_t i = 0; i < colors.size(); ++i) {
        auto color = colors[i];
        for (size_t j = 0; j < color.size(); ++j, ++out) {
            auto component = level * color[perm_[j]];
            auto gamma = getGamma(gammaTable_, component);
            *out = static_cast<char>(gamma);
        }
    }
}

inline void CRenderer::render(
        float level, CColorListRGB const& colors, char* out) {
    return renderGeneric(level, RGBAdaptor<CColorListRGB>(colors), out);
}

inline CRenderer::Perm CRenderer::getPerm(Render3::Permutation perm) {
    static std::vector<Perm> const PERMS = {
        {{0, 1, 2}},
        {{0, 2, 1}},
        {{1, 0, 2}},
        {{1, 2, 0}},
        {{2, 0, 1}},
        {{2, 1, 0}}};
    return PERMS[static_cast<int>(perm)];
}

}
}
