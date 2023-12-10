#include <stdio.h>

#include <iostream> 
#include <thread>
#include <chrono>

#include "shell/shell.hpp"
#include "shell/data.hpp"

bool exitCallback(shell::CommandArgs args)
{
    std::cout << "Goodbye..." << std::endl;

    exit(0);

    return false;
}

bool delayCallback(shell::CommandArgs args)
{
    if(auto timeOpt = args.getNumber(0)) {
        shell::Number delay = timeOpt.value();
        
        int microseconds = 0;

        if(delay.suffix == "ms")
            microseconds = delay.value * 1000;
        else if (delay.suffix == "s")
            microseconds = delay.value * 1000000;
        else if (delay.suffix == "m")
            microseconds = delay.value * 60000000;
        else if (delay.suffix == "us") 
            microseconds = delay.value;
        else {
            std::cerr << "Invalid delay unit: \"" << delay.suffix << "\"" << std::endl;
            return false;
        }

        std::this_thread::sleep_for(std::chrono::microseconds(microseconds));

        return true;
    }
    else {
        std::cerr << "No delay specified. Command format:\n"
            << args.commandName() << " <number: delay ammount>" 
            << std::endl;

        return false;
    }
}

std::string numberToInchesString(std::optional<shell::Number>& numOpt) {
    if(numOpt.has_value()) {
        shell::Number value = numOpt.value();

         double scalar = 1.0;

        if(value.suffix == "in")        scalar = 1.0;
        else if (value.suffix == "ft")  scalar = 12.0;
        else if (value.suffix == "ti")  scalar = 24.0;
        else return "<invalid units>";

        return std::to_string(value.value * scalar) + "in";
    }
    else {
        return "<default>";
    }

   
}

bool gotoCallback(shell::CommandArgs args)
{
    auto toString = [](bool val) {return val ? "true" : "false"; };

    auto numToString = [](std::optional<double> val) -> std::string {
        return val.has_value() ? std::to_string(val.value()) : "<default>";
    };

    bool async = args.getBoolean("async");
    bool noPid = args.getBoolean("nopid") | args.getBoolean("thru");
    bool reverse = args.getBoolean("reverse");
    
    auto maxLinear = args.getNewNumber("linMax");
    auto maxAngular = args.getNewNumber("angMax");
    auto linExitError = args.getNewNumber("linExit", "ft");
    auto angExitError = args.getNewNumber("angExit", "rad");


    std::cout << "Running goto command:\n" 
        << "    async               = " << toString(async) << "\n" 
        << "    noPid               = " << toString(noPid) << "\n" 
        << "    reverse             = " << toString(reverse) << "\n"
        << "    maxLinearSpeed      = " << numToString(maxLinear) << "\n"
        << "    maxAngular          = " << numToString(maxAngular) << "\n"
        << "    linearExitError     = " << numToString(linExitError) << "ft\n"
        << "    angularExitError    = " << numToString(angExitError) << "rad\n"
        ;

    return true;
}

bool echoCallback(shell::CommandArgs args)
{
    return false;
}

int main(int argc, char** argv)
{
    printf("running yyparse\n");

    shell::Shell shell;

    shell.addUnitSystem("distance", "in");
    shell.addUnitSuffix("distance", "ft",
        [](double ft) -> double { return ft * 12.0; },
        [](double in) -> double { return in / 12.0; }
    );
    shell.addUnitSuffix("distance", "ti",
        [](double ti) -> double { return ti * 24.0; },
        [](double in) -> double { return in / 24.0; }
    );
    
    shell.addUnitSystem("time", "s");
    shell.addUnitSuffix("time", "ms",
        [](double ms) -> double { return ms / 1000.0; },
        [](double s) -> double { return s * 1000.0; }
    );
    shell.addUnitSuffix("time", "us",
        [](double us) -> double { return us / 1e-6; },
        [](double s) -> double { return s * 1e6; }
    );
    shell.addUnitSuffix("time", "min",
        [](double m) -> double { return m * 60.0; },
        [](double s) -> double { return s / 60.0; }
    );

    shell.registerCommand("exit", exitCallback);
    shell.registerCommand("wait", delayCallback);
    shell.registerCommand("goto", gotoCallback);
    shell.registerCommand("echo", echoCallback);

    shell.runInteractive();
}