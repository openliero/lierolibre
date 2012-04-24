#include "argParse.hpp"
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

ArgParse::ArgParse(int argc, char* argv[])
{
	// Declare the supported options.
	desc.add_options()
	("help,h", "produce help message")
	("file,f", po::value<string>(), "read game variables from file")
	("write,w", po::value<string>(), "write game variables to file")
	("sdlvideo,v", po::value<string>(), "set the SDL_VIDEODRIVER environemtn variable")
	;

	// First positional option is input file; second output file
	po::positional_options_description p;
	p.add("file", 1).add("write", 1);

	// Export to "vm"
	po::store(po::command_line_parser(argc, argv)
		.options(desc).positional(p).run(), vm);
	po::notify(vm);
}
