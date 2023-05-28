
shopt -s globstar

# Compile the program
g++ -o terminal terminal.cpp ../src/shell/**/*.cpp -I../include/ --std=c++2a
GCC_EXIT="$?"

if [[ "$GCC_EXIT" == "0" ]]; then
    ./terminal
fi
