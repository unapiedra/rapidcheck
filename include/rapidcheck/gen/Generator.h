#pragma once

#include <stdexcept>

#include "rapidcheck/shrink/Shrink.h"

namespace rc {
namespace gen {

//! Thrown to indicate that an appropriate value couldn't be generated.
class GenerationFailure : public std::runtime_error
{
public:
    explicit GenerationFailure(std::string msg);
};

//! Prints a sample value to stdout for the given generator.
//!
//! @param sz         The size to sample.
//! @param generator  The generator.
template<typename Gen>
void sample(int sz, Gen generator);

//! Returns the current size that is being generated.
int currentSize();

//! The reference size. This is not a max limit on the generator size parameter
//! but serves as a guideline. In general, genenerators for which there is a
//! natural limit which is not too expensive to generate should max out at this.
//! This applies to, for example, generation of numbers but not to the
//! generation of collection where there is an associated cost to generating
//! large collections.
constexpr int kNominalSize = 100;

//! Base class for generators of value of type `T`.
template<typename T>
class Generator
{
public:
    //! The generated type.
    typedef T GeneratedType;

    //! Generates a value.
    T operator*() const;

    //! Generates a value. This method should not be called directly, use the
    //! dereferencing operator (i.e. `*someGenerator`) instead. This makes
    //! shrinking work properly.
    virtual T generate() const = 0;

    //! Returns a \c ShrinkIterator which yields the possible shrinks for the
    //! given value. The default impelemtation returns a \c NullIterator.
    virtual shrink::IteratorUP<T> shrink(T value) const;

    virtual ~Generator() = default;

    static_assert(!std::is_same<T, void>::value,
                  "Generated type cannot be void");
};

//! Yields the type generated by the generator `Gen`. The same as
//! `typename Gen::GeneratedType` but shorter.
template<typename Gen>
using GeneratedT = typename Gen::GeneratedType;

} // namespace gen
} // namespace rc

#include "Generator.hpp"
