Sokoban
===================

This is a simple Sokoban game implementation running in console mode.
It's writen in C++ with object-based data structures.
The plan was to also include a solver for arbitrary sokoban levels but this was not implemented because of the lack of time.

Makefile Targets
-------------

 1. make compile
> Compiles the game to the desired platform.
> A lot of additional compile / warning switches are activated to provide the best error minimizing support.
> If you want to use MINGW with Cygwin on Windows (Program running outside the bash shell) use the following command:
>> make compile CROSS_COMPILE_PREFIX=x86_64-w64-mingw32- CROSS_COMPILE_SWITCHES="-static-libstdc++"
>
> You'll then also have to copy the ncrusesw6.dll (64-bit version) library into the program directory.

 2. make checkstyle
> Runs a checkstyle.py script in the parent directory syntax-checing all .h and .cpp files.

 3. make run
> Runs the main game with the level folder set to "Levels".

Requirements
-------------

 - Google test library (gtest)
 - C++11
 - Curses / ncurses library
 - Make
