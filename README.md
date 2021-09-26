![example workflow](https://github.com/vozdeckyl/Snake/actions/workflows/ci.yml/badge.svg)
# Snake
A simple terminal based game for Linux

## Install the ncurses library
```bash
sudo apt install libncurses5-dev
```

## Installation from the source code
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

## Run
From the `build` directory
```bash
./snake
```

## Generate documentation
From the root directory
```bash
mkdir docs
cd src
doxygen ../dconfig
```
