# Plotting wrapper for C++
CMake wrapper lib for dear ImGUI and ImPlot fast and easy setup.

## Platforms
* Windows
* Linux


## Requirements
* CMake version >= 3.1 
* OpenGL version 2.0 - 4.3

## Dependencies
The dependencies are added as git submodules.
* [GLFW](https://github.com/glfw/glfw)
* [Dear ImGUI](https://github.com/ocornut/imgui)
* [ImPlot](https://github.com/epezent/implot)




## Build
### Linux
Install deps
``` 
sudo apt install xorg-dev libglu1-mesa-dev freeglut3-dev mesa-common-dev
``` 
Git Clone
``` 
$ git submodule update --init --recursive
``` 

Run initialize script (will move cmake files to imgui and implot)
``` 
$ cd plotter_lib
$ chmod +x INIT.sh
$ ./INIT.sh
```

Bash (from project root directory)
``` 
$ mkdir build && cd build
$ cmake ..
$ cmake --build .
```

### Windows
Powershell
``` 
$ mkdir build && cd build
$ cmake ..
$ cmake --build .
```

