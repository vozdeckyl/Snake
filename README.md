![example workflow](https://github.com/vozdeckyl/Snake/actions/workflows/ci.yml/badge.svg)
[![shellsnake](https://snapcraft.io/shellsnake/badge.svg)](https://snapcraft.io/shellsnake)

# Snake
A simple terminal based game for Linux

## Install using snap
```bash
snap install shellsnake --beta
```

## Install from the source code
Install the dependencies
```bash
sudo apt install libncurses5-dev libgtest-dev
```

Download the source code
```bash
git clone https://github.com/vozdeckyl/Snake.git
```

Create the build directory

```bash
cd Snake
mkdir build
cd build
```

Compile

```bash
cmake ..
cmake --build .
```
The app then can be run from the `build` directory
```bash
./snake
```
or it can be installed using
```bash
sudo make install
```
and run from anywhere using
```bash
snake
```

## Generate documentation
From the root directory
```bash
mkdir docs
cd src
doxygen ../dconfig
```
