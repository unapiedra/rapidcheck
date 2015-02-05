#pragma once

#include "rapidcheck/detail/ImplicitParam.h"
#include "rapidcheck/detail/GenerationParams.h"
#include "rapidcheck/detail/RoseNode.h"

namespace rc {
namespace gen {

//! Generates a value.
template<typename T>
T Generator<T>::operator*() const
{
    auto currentNode = detail::ImplicitParam<detail::param::CurrentNode>::value();
    if (currentNode != nullptr) {
        return currentNode->pick(*this);
    } else {
        return generate();
    }
}

template<typename Gen>
void sample(int sz, Gen generator, uint64_t seed)
{
    using namespace detail;

    ImplicitParam<param::Size> size(sz);

    RandomEngine engine(seed);
    ImplicitParam<param::RandomEngine> randomEngine(&engine);

    show(generator(), std::cout);
    std::cout << std::endl;
}

template<typename T>
shrink::IteratorUP<T> Generator<T>::shrink(T value) const
{
    return shrink::nothing<T>();
}

} // namespace gen
} // namespace rc
