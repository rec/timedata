#pragma once

#include <array>
#include <utility>
#include <vector>

#include <timedata/base/enum.h>
#include <timedata/signal/ranged.h>

namespace timedata {

template <typename Model, typename Range>
using SampleBase = std::array<Ranged<Range>, enumSize<Model>()>;

template <typename Model, typename Range>
struct Sample : SampleBase<Model, Range> {
    using base_type = SampleBase<Model, Range>;
    using model_type = Model;
    using range_type = Range;
    using value_type = ValueType<base_type>;
    using sample_type = Sample;
    using number_type = ValueType<value_type>;

    using base_type::base_type;

    // TODO: need to use std::initializer_list!
    Sample(value_type r, value_type g, value_type b)
            : base_type{{r, g, b}} {
    }
    Sample() {
        base_type::fill(0);
    }

    // TODO?: this could be offloaded from this class into free functions.
    template <typename Function>
    Sample forEach(Function f) const {
        Sample result;
        for (size_t i = 0; i < result.size(); ++i)
            result[i] = f((*this)[i]);
        return result;
    }

    using FunctionPointer = number_type (*)(number_type);
    Sample forEachF(FunctionPointer f) const {
        return forEach(f);
    }

    Sample scale() const {
        return forEachF(timedata::scale<Range>);
    }

    Sample unscale() const {
        return forEachF(timedata::unscale<Range>);
    }

    static Sample infinity() {
        auto inf = value_type::infinity();
        return {inf, inf, inf};
    }

    using ListBase = std::vector<Sample>;
    struct List : ListBase {
        using ListBase::ListBase;

        using model_type = Model;
        using number_type = Sample::number_type;
        using range_type = Range;
        using sample_type = Sample;
        using value_type = ValueType<ListBase>;
    };
};

template <typename T>
using NumberType = typename T::number_type;

template <typename T>
using SampleType = typename T::sample_type;

}  // timedata