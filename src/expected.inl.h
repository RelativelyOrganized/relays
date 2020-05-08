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

#ifndef RELAYS_EXPECTED_INL_H
#define RELAYS_EXPECTED_INL_H

#include "./expected.h"

namespace Relays
{

template <typename T>
constexpr Expected<T>::Expected()
    : _value{}
    , _exc_ptr{}
{
}

template <typename T>
constexpr Expected<T>::Expected(const T& value)
    : _value{value}
    , _exc_ptr{}
{
}

template <typename T>
constexpr Expected<T>::Expected(const Expected<T>& other) noexcept
    : _value{other._value}
    , _exc_ptr{other._exc_ptr}
{
}

template <typename T>
constexpr Expected<T>::Expected(Expected<T>&& other) noexcept
    : _value{std::move(other._value)}
    , _exc_ptr{std::move(other._exc_ptr)}
{
}

template <typename T>
Expected<T>& Expected<T>::operator=(const Expected<T>& other)
{
    if (this != &other)
    {
        _value = other._value;
        _exc_ptr = other._exc_ptr;
    }

    return *this;
}

template <typename T>
Expected<T>& Expected<T>::operator=(Expected<T>&& other)
{
    if (this != &other)
    {
        _value = std::move(other._value);
        _exc_ptr = std::move(other._exc_ptr);
    }

    return *this;
}

template <typename T>
template <typename E>
Expected<T> Expected<T>::fail(const E& exc)
{
    Expected<T> result;
    result._exc_ptr = std::make_exception_ptr(exc);
    return result;
}

template <typename T>
Expected<T> Expected<T>::fail(std::exception_ptr ptr)
{
    Expected<T> result;
    result._exc_ptr = ptr;
    return result;
}

template <typename T>
bool Expected<T>::succeeded() const
{
    return (_value.has_value() && !_exc_ptr.has_value());
}

template <class T>
void Expected<T>::check() const
{
    if (_exc_ptr.has_value())
        std::rethrow_exception(_exc_ptr.value());

    if (!_value.has_value())
        throw std::exception{};
}

template <typename T>
const T& Expected<T>::get() const&
{
    check();
    return _value.value();
}

template <typename T>
T& Expected<T>::get() &
{
    check();
    return _value.value();
}

template <typename T>
const T&& Expected<T>::get() const&&
{
    check();
    return std::move(_value.value());
}

template <typename T>
T&& Expected<T>::get() &&
{
    check();
    return std::move(_value.value());
}

constexpr Expected<void>::Expected()
    : _exc_ptr{}
{
}

constexpr Expected<void>::Expected(const Expected<void>& other) noexcept
    : _exc_ptr{other._exc_ptr}
{
}

constexpr Expected<void>::Expected(Expected<void>&& other) noexcept
    : _exc_ptr{std::move(other._exc_ptr)}
{
}

Expected<void>& Expected<void>::operator=(const Expected<void>& other)
{
    if (this != &other)
    {
        _exc_ptr = other._exc_ptr;
    }

    return *this;
}

Expected<void>& Expected<void>::operator=(Expected<void>&& other)
{
    if (this != &other)
    {
        _exc_ptr = std::move(other._exc_ptr);
    }

    return *this;
}

template <typename E>
Expected<void> Expected<void>::fail(const E& exc)
{
    Expected<void> result;
    result._exc_ptr = std::make_exception_ptr(exc);
    return result;
}

Expected<void> Expected<void>::fail(std::exception_ptr ptr)
{
    Expected<void> result;
    result._exc_ptr = ptr;
    return result;
}

bool Expected<void>::succeeded() const
{
    return !_exc_ptr.has_value();
}

void Expected<void>::check() const
{
    if (_exc_ptr.has_value())
        std::rethrow_exception(_exc_ptr.value());
}

} // namespace Relays

#endif // RELAYS_EXPECTED_INL_H
