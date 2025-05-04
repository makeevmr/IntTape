# IntTape
A project simulating working with a tape device via file

## Installation
To create necessary folders and files run:
```
chmod +x scripts/make_dirs.sh
bash scripts/make_dirs.sh
```

## Run on input file
```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --target int_tape
USAGE: ./int_pape <INPUT_FILE> <OUTPUT_FILE> <MAX_RAM_USED> <CONFIG_FILE>
EXAMPLE: ./int_tape ../input/input1.txt ../output/output1.txt 100 ../config/delay.txt
```

## Generate input file
```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --target generator
USAGE: ./generator <TOTAL_NUMBERS> <MIN_NUMBER> <MAX_NUMBER> <FILE_NAME>
EXAMPLE: ./generator 5000 0 4294967295 tmp_input.txt
```

## Run tests
### With GTest
```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --target tape_tests
./tape_tests
```

### With bash script
```
cd scripts
chmod +x check_solution.sh
USAGE: ./check_solution.sh <NUMBER_OF_TESTS>
EXAMPLE: ./check_solution.sh 5
```