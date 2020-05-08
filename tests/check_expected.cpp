#undef NDEBUG // get assert in release mode

#include <cassert>
#include <string>

#include "./expected.h"

#define ASSERT_EXCEPTION_THROWN(x)                                                                                     \
    {                                                                                                                  \
        try                                                                                                            \
        {                                                                                                              \
            x;                                                                                                         \
            assert(false);                                                                                             \
        }                                                                                                              \
        catch (...)                                                                                                    \
        {                                                                                                              \
        }                                                                                                              \
    }

#define ASSERT_EXCEPTION_NOT_THROWN(x)                                                                                 \
    {                                                                                                                  \
        try                                                                                                            \
        {                                                                                                              \
            x;                                                                                                         \
        }                                                                                                              \
        catch (...)                                                                                                    \
        {                                                                                                              \
            assert(false);                                                                                             \
        }                                                                                                              \
    }

int main()
{
    using namespace Relays;

    // Simple type
    {
        Expected<bool> value;
        ASSERT_EXCEPTION_THROWN(value.get());
        ASSERT_EXCEPTION_THROWN(std::move(value).get());
        assert(!value.succeeded());

        Expected<bool> copy1{value};
        ASSERT_EXCEPTION_THROWN(copy1.get());
        assert(!copy1.succeeded());

        Expected<bool> copy2{std::move(value)};
        ASSERT_EXCEPTION_THROWN(copy2.get());
        assert(!copy2.succeeded());
    }

    {
        Expected<bool> value{true};
        ASSERT_EXCEPTION_NOT_THROWN(value.get());
        assert(value.succeeded());
        assert(value.get());

        Expected<bool> copy1{value};
        ASSERT_EXCEPTION_NOT_THROWN(copy1.get());
        assert(value.get() == copy1.get());

        Expected<bool> copy2{std::move(value)};
        ASSERT_EXCEPTION_NOT_THROWN(copy2.get());
        assert(value.get() == copy2.get());
    }

    {
        auto value = Expected<bool>::fail(123);
        try
        {
            value.get();
            assert(false);
        }
        catch (int e)
        {
            assert(true);
        }
        catch (...)
        {
            assert(false);
        }

        Expected<void> result;
        assert(result.succeeded());

        try
        {
            throw 456;
        }
        catch (...)
        {
            result = Expected<void>::fail(std::current_exception());
        }

        assert(!result.succeeded());
    }

    // Complex type
    {
        std::string str{"toto"};
        Expected<std::string> value{str};
        assert(value.succeeded());
        ASSERT_EXCEPTION_NOT_THROWN(value.get());
        assert(value.get() == str);
    }

    // Void
    {
        Expected<void> value;
        ASSERT_EXCEPTION_NOT_THROWN(value.check());
        assert(value.succeeded());

        Expected<void> copy1{value};
        ASSERT_EXCEPTION_NOT_THROWN(copy1.check());
        assert(copy1.succeeded());

        Expected<void> copy2{std::move(value)};
        ASSERT_EXCEPTION_NOT_THROWN(copy2.check());
        assert(copy2.succeeded());
    }

    return 0;
}
