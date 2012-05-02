lierolibre is an old-school earthworm action game. It is a direct fork of Liero
(OpenLiero).

Features:
  * 2 worms, 40 weapons, great playability, two game modes: Kill'em All
    and Game of Tag, plus AI-players without true intelligence!
  * Dat nostalgia
  * Extensions via a hidden F1 menu
    + Replays
    + Game controller support
    + Powerlevel palettes
  * Ability to write game variables to plain text files
  * Ability to load game variables from both EXE and plain text files
  * New freely licensed audio

To switch between different window sizes, use F6, F7 and F8, to switch to
fullscreen, use F5 or Alt+Enter.

The copied file 'settings\lierocfg.txt' is a plain text file containing all the
game variables, this file is intented to be modified, go wild! Some things are
likely to not work (make the game refuse to start, or crash) though:
  ! Appending/Deleting elements
  ! Changing integers to strings, strings to integers, etc.
  ! Changing the sine and cosine tables

In order to make lierolibre load and write files differently you will need to
use the command line, to start a command line prompt in the lierolibre
directory run the lierolibre-cmd.bat script.

The available command-line options for lierolibre are:
  -f [ --file ] arg     read game variables from file or directory
  -d [ --dir ] arg      load game data from separate directory
  -w [ --write ] arg    write game variables to file
  -v [ --sdlvideo ] arg set the SDL_VIDEODRIVER environment variable
  -h [ --help ]         print this help message

In addition, positional arguments are automatically assigned to file, dir, and
write, in that order, hence executing
  lierolibre.exe foo.txt foodir bar.txt
is equivalent to
  lierolibre.exe -f foo.txt -d foodir -w bar.txt

To extract the game variables from a modded LIERO.EXE file, use
  lierolibre.exe -f path\to\LIERO.EXE -d path\to\data -w mod.txt
Note that the -d option can be omitted if the data files are in the same
directory as the LIERO.EXE file (and named correctly).

To load a custom game variables text file use
  lierolibre.exe -f path\to\mod.txt -d path\to\data
Again, if the data files are in the same directory as mod.txt, the -d option
can be omitted.

Please report bugs at https://bugs.launchpad.net/lierolibre/+filebug

For more information see the manual pages in the man/ direcory, and visit the
Launchpad page:
https://launchpad.net/lierolibre
