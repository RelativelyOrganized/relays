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
Expected<T>::Expected(const T& value)
    : _hasValue{true}
{
}

template <typename T>
Expected<T>::Expected(const Expected<T>& other)
    : _hasValue{other._hasValue}
{
    if (other._hasValue)
        result = other.result;
    else
        exc_ptr = other.exc_ptr;
}

template <typename T>
Expected<T>::Expected(Expected<T>&& other)
    : _hasValue{other._hasValue}
{
    if (other._hasValue)
        result = std::move(other.result);
    else
        exc_ptr = std::move(other.exc_ptr);
}

template <typename T>
Expected<T>::Expected()
    : _hasValue{false}
{
}

template <typename T>
Expected<T>::~Expected()
{
}

template <typename T>
Expected<T>& Expected<T>::operator=(const Expected<T>& other)
{
    if (this != &other)
    {
        _hasValue = other._hasValue;
        if (other._hasValue)
            result = other.result;
        else
            exc_ptr = other.exc_ptr;
    }

    return *this;
}

template <typename T>
Expected<T>& Expected<T>::operator=(Expected<T>&& other)
{
    if (this != &other)
    {
        _hasValue = other._hasValue;
        if (other._hasValue)
            result = std::move(other.result);
        else
            exc_ptr = std::move(other.exc_ptr);
    }

    return *this;
}

template <typename T>
template <typename E>
Expected<T> Expected<T>::fail(const E& exc)
{
    Expected<T> result;
    result.exc_ptr = std::make_exception_ptr(exc);
    result._hasValue = false;
    return result;
}

template <typename T>
Expected<T> Expected<T>::fail(std::exception_ptr ptr)
{
    Expected<T> result;
    result.exc_ptr = ptr;
    result._hasValue = false;
    return result;
}

template <typename T>
bool Expected<T>::succeeded() const
{
    return _hasValue;
}

template <typename T>
const T& Expected<T>::get() const
{
    if (!_hasValue)
        std::rethrow_exception(exc_ptr);
    return result;
}

template <typename T>
T& Expected<T>::get()
{
    if (!_hasValue)
        std::rethrow_exception(exc_ptr);
    return result;
}

} // namespace Relays

#endif // RELAYS_EXPECTED_INL_H
