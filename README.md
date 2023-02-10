# berzerk
My clone of the popular arcade game "Berzerk", originally published by Stern Electronics in 1980. It took around around a month and a half to develop (from pen-and-paper prototyping to the version seen here). The clone is mostly faithful to the original arcade game, with some minor corner-cutting. 

- [Demo video of this code](https://www.youtube.com/watch?v=c3lEDQdlAEc)
- [Footage of the original game](https://www.youtube.com/watch?v=DFSQ0Pl4KDk)
- [An advertisement](https://www.youtube.com/watch?v=HHlYWY1dcqs) for the Atari 2600 port (complete with a questionable theme song)



## Building
Presently, Berzerk only builds on MacOS and Linux. To run Berzerk locally, you will need to install GNU Make (obtain via `brew install make`or `apt-get install make`), Clang (obtain via `brew install clang` or `apt-get install clang`), and SDL / SDL_Image / SDL_Mixer. I have included the relevant headers and libraries for SDL on MacOS. In the event that you need to build a new version, obtain the libraries and headers following:
- [SDL 2.26.3](https://github.com/libsdl-org/SDL/releases/tag/release-2.26.3)
- [SDL_Image 2.26.3](https://github.com/libsdl-org/SDL_image/releases/tag/release-2.6.3)
- [SDL_Mixer 2.26.3](https://github.com/libsdl-org/SDL_mixer/releases/tag/release-2.6.3)

Berzerk expects that `3rdparty/SDL2/` will contain all necessary SDL headers and shared libraries from the above releases for your platform. You can either download the pre-build libraries and drop them into `3rdparty/SDL2/`, or you can build from source (usually via `./configure && make` in each SDL repository, then copying the `include/` directories and built libraries into `3rdparty/SDL2/`; you may need to look for the libraries with `find`). 

Then run `make -j berzerk`. 

If you have any issues building, please contact me at joshua.goller@hey.com. 

## Gameplay
- Arrow keys: movement
- Spacebar: shoot
- P: pause

## Special thanks
- [Elliott Jin](https://github.com/robot-dreams) for moral support
