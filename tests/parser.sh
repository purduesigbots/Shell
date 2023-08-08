rm -f parser parser.y.cpp parser.y.hpp lexer.l.cpp

bison -o parser.y.cpp --defines=../include/shell/parser/parser.y.hpp ../src/shell/Parser/parser.y --report=all
if [[ "$?" != 0 ]]; then
    echo "Failed to generate parser.y.cpp"
    exit 1
fi

flex -o lexer.l.cpp ../src/shell/Parser/lexer.l
if [[ "$?" != 0 ]]; then
    echo "Failed to generate lexer.l.cpp"
    exit 1
fi

SOURCES="parser.cpp lexer.l.cpp parser.y.cpp "
SOURCES+=$(find ../src/shell -name "*.cpp")

g++ -g -std=c++17 -o parser $SOURCES -I../include/ -I../tools/parser/ -I../include/shell/parser/ -Wl,--demangle 
if [[ "$?" != 0 ]]; then 
    echo "Failed to compile parser"
    exit 1
fi

echo "Running parser test"
./parser
