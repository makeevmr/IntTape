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
USAGE: ./int_pape <INPUT_FILE> <OUTPUT_FILE> <MAX_RAM_USED> <CONFIG_FILE>
EXAMPLE: ./int_tape ../input/input1.txt ../output/output1.txt 100 ../config/delay.txt
```

## Run tests
```
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --target tape_tests
./tape_tests
```