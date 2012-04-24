#include "argParse.hpp"
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

ArgParse::ArgParse(int argc, char* argv[])
{
	// Declare the supported options.
	desc.add_options()
	("help,h", "produce help message")
	("sdlvideo,v", po::value<string>(), "set the SDL_VIDEODRIVER environemtn variable")
	("file,f", po::value<string>(), "read game variables from file")
	("dir,d", po::value<string>(), "load game data from separate directory")
	("write,w", po::value<string>(), "write game variables to file")
	;

	// First positional option is input file
	// second is data dir, third is output file
	po::positional_options_description p;
	p.add("file", 1).add("dir", 1).add("write", 1);

	// Export to "vm"
	po::store(po::command_line_parser(argc, argv)
		.options(desc).positional(p).run(), vm);
	po::notify(vm);
}
