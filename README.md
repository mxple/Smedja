# Smedja
Smedja is a work-in-progress game engine I'm developing while following along with The Cherno's Game Engine series.

Prounounced smee-ah-dee-ah, Smedja means "forge" or "smithery" in Swedish.

## Getting started
Currently tested on ~~Mac~~ and Linux, and it *should* work on Windows.

*Mac build currently does not support batch 2D rendering due to OpenGL 4.3 being unsupported :(

To build, first download [premake5](https://premake.github.io/download).

#### Linux / MacOSX
```
git clone --recursive https://github.com/Mxple/Smedja.git
cd Smedja
premake5 gmake2
make
./bin/Debug-linux-x86_64/Sandbox/Sandbox
```
Use `chmod +x ./bin/Debug-linux-x86_64/Sandbox/Sandbox` if the compiled binary is not already executable. 

Windows build instructions to come.
