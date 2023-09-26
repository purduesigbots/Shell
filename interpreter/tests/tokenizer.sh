
flex -o scanner.l.cpp ../src/shell/Parser/scanner.l
if [[ "$?" != 0 ]]; then
    echo "Failed to generate scanner.cpp"
    exit 1
fi

g++ -std=c++17 -o tokenizer tokenizer.cpp scanner.l.cpp
if [[ "$?" != 0 ]]; then
    echo "Failed to compile tokenizer.exe"
    exit 1
fi

echo "Running tokenizer test"
./tokenizer
