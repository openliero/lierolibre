#!/bin/sh

autoreconf --force --install
if [ ! -f src/m4/sdl.m4 ]; then
	cp /usr/share/aclocal/sdl.m4 src/m4/
fi

