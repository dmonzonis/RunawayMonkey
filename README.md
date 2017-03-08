# Runaway Monkey

Simple game made with C++11 using the SFML library. It's still a **WIP** so even the basic mechanics may not work properly yet or they may change drastically in the future.

See the project's documentation [here] (https://monzo94.github.io/RunawayMonkey/).

Installation
--------------------
Until there's a release version with a binary including all the requirements, the only way to play the game is to compile it from source.
You will first need to download the SFML development library. To get it, simply download it from the SFML page or, if using Linux, get it from your distro's repositories.
In Ubuntu/Debian:
```
apt-get install libsfml-dev
```
In Arch:
```
pacman -S sfml
```
You can compile the game either using the provided Makefile, or by using CMake.

###Make
At the project's root directory, simply run
```
make
```
To run a clean build, simply run
```
make clean && make
```
This will remove all the previously compiled object files as well as the executable and rebuild them.

###CMake
At the project's root directory, run
```
mkdir build && cd build && cmake ..
```
You can then use your build system to build the game. In the case of make, simply run make.

###Running the game
To run the game, while at the project's root directory, run
```
bin/monkey.
```
It's important to execute the game from the root directory, since the game currently uses relative paths to search for resources, and will fail to load them if in another directory. 
