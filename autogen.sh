#!/bin/sh

autoreconf --force --install
if [ ! -f m4/sdl.m4 ]; then
	cp /usr/share/aclocal/sdl.m4 m4/
fi

