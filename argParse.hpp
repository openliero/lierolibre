#ifndef ARG_PARSE_HPP
#define ARG_PARSE_HPP

#include <boost/program_options.hpp>

class ArgParse
{
public:
	ArgParse(int argc, char* argv[]);
	boost::program_options::variables_map vm;
	boost::program_options::options_description desc;
};

#endif // ARG_PARSE_HPP
