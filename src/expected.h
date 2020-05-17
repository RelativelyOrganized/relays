/*
 * This file is part of Relays.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Relays is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Relays.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef RELAYS_EXPECTED_H
#define RELAYS_EXPECTED_H

#include <exception>
#include <optional>

namespace Relays
{

template <class T>
class Expected
{
  public:
    // Constructors & destructor
    constexpr Expected();
    constexpr Expected(const T& value);
    constexpr Expected(const Expected& other) noexcept;
    constexpr Expected(Expected&& other) noexcept;
    ~Expected() = default;

    // Operators
    Expected& operator=(const Expected& other);
    Expected& operator=(Expected&& other);

    // Initialization with exception
    template <typename E>
    static Expected<T> fail(const E& exc);
    static Expected<T> fail(std::exception_ptr ptr);

    // Do we have a valid value?
    bool succeeded() const;

    // Checks whether this contains a valid value, otherwise throws
    void check() const;

    // Getters
    T& get() &;
    const T& get() const&;

    T&& get() &&;
    const T&& get() const&&;
    ;

  private:
    // The (optional) value contained by this
    std::optional<T> _value;

    // The (optional) exception pointer contained by this
    std::optional<std::exception_ptr> _exc_ptr;
};

template <>
class Expected<void>
{
  public:
    // Constructors & destructor
    constexpr Expected();
    constexpr Expected(const Expected<void>& other) noexcept;
    constexpr Expected(Expected<void>&& other) noexcept;
    ~Expected() = default;

    // Operators
    Expected& operator=(const Expected<void>& other);
    Expected& operator=(Expected<void>&& other);

    // Initialization with exception
    template <typename E>
    static Expected<void> fail(const E& exc);
    static Expected<void> fail(std::exception_ptr ptr);

    // Do we have a valid value?
    bool succeeded() const;

    // Checks whether this contains a valid value, otherwise throws
    void check() const;

  private:
    // The (optional) exception pointer contained by this
    std::optional<std::exception_ptr> _exc_ptr;
};

} // namespace Relays

#include "./expected.inl.h"

#endif // RELAYS_EXPECTED_INL_H