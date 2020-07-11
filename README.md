# vscode-cuda-cmake

This workspace setup allows you to seperate CPU C++ code with GPU Cuda code in different files. 
Look at the square example for reference. I have only tested it on an Arch Linux system. 

- Debug mode is accessed by pressing `f5`
- Normal mode by pressing `f6`
- Cleaning the project is done by pressing `f4`

## Requirements

Also see: https://wiki.archlinux.org/index.php/GPGPU#CUDA

- cmake >= 3.5.2
- `nvidia` and `opencl-nvidia` properitory drivers (should be installed by default)
- `cuda` installed
- `ccache` installed
- `/opt/cuda/bin` added to PATH
- `vscode-cudacpp` extention installed

## Folder Layout
The workspace has the following folder structure with their uses:
```bash
├───.vscode // main folder where vscode puts it settings
│   └───c_cpp_properties.json // file where settings of the c++ intellisense are configured
│   └───launch.json // file where debugging settings are configured
│   └───settings.json // file where user defined settings on the workspace are configured
│   └───tasks.json // file where the settings of running and compile commands are configured 
├───build // folder with target subfolder where the build files made by cmake will be outputted (dont modify)
├───lib // folder with target subfolder where external libraries used in cmake are
└───src // folder where your sandbox application is 
    └───cuda // cmake settings file that apply settings on the include and libraries used
        └───square.hpp // C++ wrapper over Cuda code
        └───square.cu // cuda code implementation run on GPU
    └───CmakeList.txt // cmake settings file that apply settings libraries used
    └───main.cpp
└───CmakeList.txt // generic cmake settings file
└───cuda-tutorial.code-workspace // file where generic settings on the workspace are configured
```

## Before using

Add keybinding to code workspace

Be sure to add this keyboard shortcuts to your `keybinding.json` by following this [guide](https://dzone.com/articles/setting-custom-shortcuts-in-visual-studio-code).
// Place your key bindings in this file to override the defaults
[
    {"key": "f6",
        "command": "workbench.action.tasks.runTask",
        "args": "normalRun"
    },
    {"key": "f4",
        "command": "workbench.action.tasks.runTask",
        "args": "cleanTask"
    },
]
