rm -f parser parser.y.cpp parser.y.hpp scanner.l.cpp

bison -o parser.y.cpp --defines=parser.y.hpp ../src/shell/Parser/parser.y
if [[ "$?" != 0 ]]; then
    echo "Failed to generate parser.y.cpp"
    exit 1
fi

flex -o scanner.l.cpp ../src/shell/Parser/scanner.l
if [[ "$?" != 0 ]]; then
    echo "Failed to generate scanner.y.cpp"
    exit 1
fi

SOURCES="parser.cpp scanner.l.cpp parser.y.cpp ../src/shell/shell.cpp"

g++ -g -std=c++17 -o parser parser.cpp scanner.l.cpp parser.y.cpp -I../include  -Wl,--demangle
if [[ "$?" != 0 ]]; then 
    echo "Failed to compile parser"
    exit 1
fi

echo "Running parser test"
./parser
