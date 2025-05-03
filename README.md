# IntTape
A project simulating working with a tape device via file

## Installation
Run 
```
chmod +x scripts/make_dirs.sh
bash scripts/make_dirs.sh
```
to create necessary folders and files.

## Run on input file
```
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --target int_tape
./int_tape ../input/input_file ../output/output_file ../config/delay.txt
./int_tape ../input/input1.txt ../output/output1.txt ../config/delay.txt
```

## Run tests
```
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --target tape_tests
./tape_tests
```