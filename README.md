![Hazel](/Resources/Branding/Hazel_Logo_Text_Light_Square.png?raw=true "Hazel")

Hazel is primarily an early-stage interactive application and rendering engine for Windows. Currently not much is implemented, however (almost) everything inside this repository is being created within YouTube videos, found at [thecherno.com/engine](https://thecherno.com/engine). 

## Getting Started
Visual Studio 2019 is recommended with toolset v143, Hazel is officially untested on other development environments whilst we focus on a Windows build.

## Install 

You can clone the repository to a local destination using git:
```console
$ git clone --recursive https://github.com/Scudf/Hazel.git
```
Make sure that you do a `--recursive` clone to fetch all of the submodules!

* Download [premake5.exe](https://github.com/gabime/spdlog/blob/v1.x/example/CMakeLists.txt) and put in root folder with path "vendor\bin\premake5\"
* Run GenerateProjects.bat
