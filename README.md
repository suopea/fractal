This is a browser for the [mandelbrot](https://en.wikipedia.org/wiki/Mandelbrot_set) [set](https://www.youtube.com/watch?v=FFftmWSzgmk). What makes this different from other browsers out there is the fact that instead of seeing a still image of the set, you get to see it grow! 

# Installation

The project depends on [MLX42](https://github.com/codam-coding-college/MLX42). The MLX42 library is downloaded and compiled by the makefile of this project, so you don't need to worry about that, but you do need to install the dependencies for MLX42 first (instructions below). Then run `make` and `./mandelbrot`.

## MacOS

```bash
brew install glfw
brew install cmake
```

## Linux

### Debian (ubuntu etc)

```bash
sudo apt update
sudo apt install build-essential libx11-dev libglfw3-dev libglfw3 xorg-dev
```

### Arch

```bash
sudo pacman -S glfw-x11
```
or for wayland:
```bash
sudo pacman -S glfw-wayland
```

## Windows

Haven't tried this, but [follow these instructions](https://github.com/codam-coding-college/MLX42?tab=readme-ov-file#for-windows-with-windows-subsystem-for-linux-2-wsl2).
