#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Fixtures
#include <boost/test/unit_test.hpp>

struct Massive
{
    int m;

    Massive() : m(2)
    {
        BOOST_TEST_MESSAGE("setup mass");
    }

    ~Massive()
    {
        BOOST_TEST_MESSAGE("teardown mass");
    }
};

struct Massive2
{
    int n;

    Massive2() : n(2)
    {
        BOOST_TEST_MESSAGE("setup nass");
    }

    ~Massive2()
    {
        BOOST_TEST_MESSAGE("teardown nass");
    }
};

BOOST_FIXTURE_TEST_SUITE(Physics, Massive)
BOOST_GLOBAL_FIXTURE(Massive2)

BOOST_AUTO_TEST_CASE(specialTheory)
{
    int e = 32;
    int c = 4;

    BOOST_CHECK(e == m * c * c);
}
BOOST_AUTO_TEST_CASE(newton2)
{
    int f = 10;
    int a = 5;

    BOOST_CHECK(f == m * a);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(two)

BOOST_AUTO_TEST_CASE(newton2)
{
    int f = 10;
    int a = 5;

    BOOST_CHECK(f == 2 * a);
}

BOOST_AUTO_TEST_SUITE_END()


