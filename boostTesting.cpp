#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE DataPath
#include <boost/test/unit_test.hpp>

#include "dataPath.hpp"

BOOST_AUTO_TEST_CASE(data_path_test)
{
	DataPath data_path;

	BOOST_CHECK(data_path.path_readonly("") == "");
}
