# CHIP-8 Interpreter
CHIP-8 interpreter written in C++.

Embedded Implementation: https://github.com/aaxbas/EmbeddedCHIP-8

![](docs/images/PONG.png)

## Building
### Dependencies
- **SDL2 & SDL2_mixer** (video/audio/controls)
  - _Linux_: `apt install libsdl2-dev` & `apt install libsdl2-mixer-dev` (on Ubuntu)
  - _MacOS_: `brew install SDL2` & `brew install SDL2_mixer`
  - _Windows_:
    - Download dev libs from [here](https://www.libsdl.org/download-2.0.php) and
      unzip them somewhere.
    - EITHER: Set the `SDL` environment variable to point to the dev libs
    - OR: Unzip them to `C:\sdl2\` default location
    - OR: Modify the `SDL2_MORE_INCLUDE_DIR` variable in `CMakeLists.txt` to
      point to the SDL2 dev libs

### Compiling
__Note: Only tested in Ubuntu 18.04__
Linux/MacOS
```sh
mkdir build
cd build
cmake ..
make
```

TODO: add Windows build instructions


## Resources
* http://www.multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/
* http://en.wikipedia.org/wiki/CHIP-8
* http://devernay.free.fr/hacks/chip8/C8TECH10.HTM