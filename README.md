# PROS Shell - Interactive Autonomous Scripting

## Installing:
1. Donwload the [latest release]().
2. Open a terminal and navigate to where you downloaded the template. 
3. Fetch it with the PROS CLI: `pros c fetch shell@<version>.zip`
4. Navigate to your project's directory
5. Apply the template to the project: `pros c apply shell`

## Getting Started
To get started, create an instance of the `shell::Shell` class, and call the `runInteractive` method:
```cpp
#include "shell/api.hpp"

void opcontrol() {
    shell::Shell myShell;

    myShell.runInteractive();
}
```
If you want to use commands for one of the supported templates, you can add their commands like this:
```cpp
shell::bindings::installArmsBindings(myShell);
```

Then you can open up a PROS terminal, and type commands into it in real time and watch your robot do things:

```py
goto (12, 12) maxSpeed=12.0 
```

## Documentation:
The full documentation for PROS Shell can be found [here]().

## Contributing:
If you would like to contribute to the project, see the [contibution guide]().

## Special Thanks
- My two attempts at Purdue's compilers class for ~~forcing~~ helping me to learn how to implement compilers and interpreters
- The contributers of [Bison](https://www.gnu.org/software/bison/) and [Flex](https://github.com/westes/flex) for making their parsing tools.
- Chris Narkiewicz (ezaquarii) for his [bison and flex C++ example](https://github.com/ezaquarii/bison-flex-cpp-example)