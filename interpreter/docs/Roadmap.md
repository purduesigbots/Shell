# PROS Shell Development Version Roadmap:
This is a rough overview of the planned features for the PROS Shell, and which versions will contain which features. The initial development versions (0.1-0.x) are not aimed at maintaining backwards compatability or stability, but rather experimenting and developing the featureset of the shell. 

Version 1.0 will mark the first stable release of the shell. It will revise any features/API design choices from the development versions, based on community feedback.

This roadmap may be subject to changes as the priority of features change, or as features are added/removed due to need and time requried.

## Development Versions

### Version 0.1 (The MVP Update)
- Basic Command Execution:
  - ARMS Example:
    ```py
    # Goto a point on the field
    goto (12, 23) async nopid maxspeed=100
    ```
  - PROS Example:
    ```py
    motor 2 goto 240deg
    motor 3 goto 240deg
    wait 12s
    adi "a" analog=12.00
    adi "b" digital=true
    ```
- C++ Api
  - Shell class
  - Custom command binding
  - Command callback helper classes
  - Run interactively
  - Run from files
- Builtin Commands:
  - Echo
  - Run File
  - Record Start
  - Record Stop
  - Wait for a specified time
- Library Support
  - ARMS
    - Goto/Move
    - Face/Turn
    - SetPID
    - SetPose
    - Wait until settled
  - PROS
    - Motor move commands
    - ADI Set analog
    - ADI Set digital

### Version 0.2 (The storage update)
- Variables
  - Can be set with literals:
  ```py
  let myPid = (0.5, 0.25, 0.001)
  ```
  - Can be set with other variables
  ```py
  let copyPid = $myPid
  ```
  - Can be modified from C++
  - Can be evaluated for in command arguments:
  ```py
  goto (12, 23) linearPid=$myPid
  ```
- C++ API 
  - Add, set, remove global variables
  ```cpp
  shell.setGlobal("robot", "2024 Vex 15")
  ```
- Scopes
  - Scopes can be created that will automatically remove variables once it ends:
  ```py
  goto (12, 23)
  {
    let localPid = (0.5, 0.25, 0.0001)

    goto (24, 23) linearPid=$localPid
  }
  ```
- Library Support
  - ARMS
    - Get current linear/angular PID
    - 

### Version 0.3 (The scope creep update)
- Namespaces
  - Commands and global variables prefixed to prevent name clashing:
    ```py
    arms:goto (12, 23, 252deg) 
    ```
  - "use" statment to bring a namespace into global scope:
  ```py
  use arms
  goto (12, 23, 252deg)
  ```
  - import files:
  ```py
  import "sd/globals"
  ```
  - export variables from a file
  ```py
  let pid = (12, 13, 42)
  export pid
  ```


### Version 0.4 (The mutant update)
- Variable mutation
  - Can reassign variables
- Scalar Expressions
  - Numeric operations on single numbers
  - Logical expressions on boolean values
  - Concatination and interpolation for strings

### Version 0.5 (The decision update)
- Conditionals
  - If/else statements
  - If/else expressions
  - For loop statements
  - While loop statement
  - Until loop statements
    - Same as a do while
  - loop statments
    - Infinite loops
  - Coninue/break keywords

### Version 0.6 (The order and magnitude update)
- Vector expressions
  - Apply operations uniformly across all elements in a tuple
  - Cross/Dot product on tuples of numbers
- Named Tuple unpacking

### Version 0.7 (The DIY update)
- Commands can now take blocks of code to do what they want with.
  - Lets them implement sublanguages inside the shell
  - Ex: Broadcast json data to other bots on vexnet
    ```
    broadcast to="all" {
        "x": "12.0",
        "y": "24.0",
        "theta":"0.0",

        "auton-state": "DiskSearch",
        "timestamp": "0:01:2532",
    }
    ```
  - These act as multi-line strings
  - Still not sure about this feature. Could be dangerous to give users this power

### Version 0.8 (The convienence update)
- THIS UPDATE MIGHT BREAK COMPATABILITY
- Improved C++ api for commands
  - Command builder
  - Automated checking for command arguments
  - Automatic help functionality?
- 

### Version 0.9 (The functional update)
- Adds functions to the shell language
  - Not sure how exactly to handle this
  - Maybe make functions look just like commands?

### Version 0.10 ()

## Stable Releases

### Version 1.0 (The "You Broke My Programs Update")
- First stable release
- All the following 1.x.x updates will maintain compatability
- Library support
  - PROS
  - ARMS
  - Lemlib
  - SyLib





  - Legs (If it exists)
