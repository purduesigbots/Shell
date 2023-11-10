# PROS Shell - Scripting Language 

This is an overview for the scripting language for the PROS Shell. 

Here is an example autonomous program written using the ARMS template bindings:

```sh
use arms

# Reset the 
SetPose (0, 0, 45deg)

goto (12in, 12in, 0deg) nopid
```

## Data types:
The PROS Shell language contains the following primitive data types:
- boolean: Either true or false
- number: A numeric value such as `12.0`, and optionally a suffix such as `ft`, `in`, etc.
- string: A sequece of characters

The pros shell also 

## Statements:
Each statement in the PROS Shell is an individually executable piece of code.
Statements end either when a newline or semicolon is found. 

### Command/Function Call:
The heart of the PROS Shell is the command. Each command starts with the name of the commmand, and can contain a list of parameters to change how a command functions. For example, the ARMS bindings provide the `goto` command to tell a robot to go to a specific spot on the field. Here are some valid varants of the command:
```sh
# Goto the point (12, 12) on the field without using PID control
goto (12, 12) nopid     
goto (12, 12) nopid=true

# Goto the point (24, 12) on the field, end the movement facing 35 degrees, move no faster than 50% of the robot's speed, and don't stop moving until we are within 1/2 an inch of the target
goto (24, 12, 35) maxSpeed=50 exitError=0.5in
```



## Expressions: