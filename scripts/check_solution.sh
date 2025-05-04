#!/bin/bash
cd ../build/
cmake .. -DCMAKE_BUILD_TYPE=Release
echo "cmake .. -DCMAKE_BUILD_TYPE=Release"
cmake --build . --target int_tape
echo "cmake --build . --target int_tape"
cmake --build . --target generator
echo "cmake --build . --target generator"

all_tests_passed=true
for ((i=1; i<=$1; i++));
do
    echo "Test case: $i"
    ./generator 5000 0 4294967295 tmp_input.txt
    ./int_tape tmp_input.txt tmp_output.txt 6000 ../config/delay.txt
    sort -g tmp_input.txt > correct_output.txt
    if ! cmp -s correct_output.txt tmp_output.txt; then
        echo "Files are different. Breaking loop."
        all_tests_passed=false
        break
    fi
done

if [ "$all_tests_passed" = true ];
then
    echo "All tests passed!"
fi