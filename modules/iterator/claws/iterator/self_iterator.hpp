#pragma once

#include <utility>

namespace claws
{
  template<class value_type>
  class self_iterator
  {
    value_type value;

  public:
    constexpr self_iterator(value_type value) noexcept
      : value(std::move(value))
    {}

    constexpr self_iterator() = default;
    constexpr self_iterator(self_iterator const &) = default;
    constexpr self_iterator(self_iterator &&) = default;
    constexpr self_iterator &operator=(self_iterator const &) = default;
    constexpr self_iterator &operator=(self_iterator &&) = default;

#define CLAWS_SELF_ITERATOR_UNARY_PREFIX_OP(OP) \
  constexpr auto &operator OP() noexcept        \
  {                                             \
    OP value;                                   \
    return *this;                               \
  }

    CLAWS_SELF_ITERATOR_UNARY_PREFIX_OP(++);
    CLAWS_SELF_ITERATOR_UNARY_PREFIX_OP(--);

#undef CLAWS_SELF_ITERATOR_UNARY_PREFIX_OP

#define CLAWS_SELF_ITERATOR_UNARY_SUFFIX_OP(OP) \
  constexpr auto operator OP(int) noexcept      \
  {                                             \
    auto copy{*this};                           \
                                                \
    OP value;                                   \
    return copy;                                \
  }

    CLAWS_SELF_ITERATOR_UNARY_SUFFIX_OP(++);
    CLAWS_SELF_ITERATOR_UNARY_SUFFIX_OP(--);

#undef CLAWS_SELF_ITERATOR_UNARY_SUFFIX_OP

#define CLAWS_SELF_ITERATOR_BINARY_ASSIGN_OP(OP)       \
  constexpr auto &operator OP(value_type val) noexcept \
  {                                                    \
    value OP val;                                      \
    return *this;                                      \
  }

    CLAWS_SELF_ITERATOR_BINARY_ASSIGN_OP(+=);
    CLAWS_SELF_ITERATOR_BINARY_ASSIGN_OP(-=);

#undef CLAWS_SELF_ITERATOR_BINARY_ASSIGN_OP

#define CLAWS_SELF_ITERATOR_BINARY_OP(OP)             \
  constexpr auto operator OP(value_type val) noexcept \
  {                                                   \
    return self_iterator(value OP val);               \
  }

    CLAWS_SELF_ITERATOR_BINARY_OP(+);
    CLAWS_SELF_ITERATOR_BINARY_OP(-);

#undef CLAWS_SELF_ITERATOR_BINARY_OP

#define CLAWS_SELF_ITERATOR_COMPARE_OP(OP)                        \
  constexpr auto operator OP(self_iterator const &other) noexcept \
  {                                                               \
    return value OP other.value;                                  \
  }

    CLAWS_SELF_ITERATOR_COMPARE_OP(==);
    CLAWS_SELF_ITERATOR_COMPARE_OP(!=);
    CLAWS_SELF_ITERATOR_COMPARE_OP(<=);
    CLAWS_SELF_ITERATOR_COMPARE_OP(>=);
    CLAWS_SELF_ITERATOR_COMPARE_OP(<);
    CLAWS_SELF_ITERATOR_COMPARE_OP(>);

#undef CLAWS_SELF_ITERATOR_COMPARE_OP

    constexpr auto operator-(self_iterator const &other) const noexcept
    {
      return value - other.value;
    }

    constexpr auto operator*() const noexcept
    {
      return value;
    }

    constexpr auto operator[](value_type index) const noexcept
    {
      return value + index;
    }
  };

  template<class value_type>
  class range
  {
    self_iterator<value_type> p_begin;
    self_iterator<value_type> p_end;

  public:
    constexpr range(value_type begin, value_type end) noexcept
      : p_begin(begin)
      , p_end(end)
    {}

    constexpr auto const &begin() const noexcept
    {
      return p_begin;
    }

    constexpr auto const &end() const noexcept
    {
      return p_end;
    }
  };
}
