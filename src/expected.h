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

namespace Relays
{

template <class T>
class Expected
{
  public:
    // Constructors & destructor
    Expected(const T& value);
    Expected(const Expected& other);
    Expected(Expected&& other);
    ~Expected();

    // Operators
    Expected& operator=(const Expected& other);
    Expected& operator=(Expected&& other);

    // Initialization with exception
    template <typename E>
    static Expected<T> fail(const E& exc);
    static Expected<T> fail(std::exception_ptr ptr);

    // Do we have a valid value?
    bool succeeded() const;

    // Getters
    const T& get() const;
    T& get();

  private:
    // Empty constructor
    Expected();

  private:
    // Our content: either a value or an exception ptr
    union
    {
        T result;
        std::exception_ptr exc_ptr;
    };

    // Do we have a value?
    bool _hasValue;
};

} // namespace Relays

#include "./expected.inl.h"

#endif // RELAYS_EXPECTED_INL_H