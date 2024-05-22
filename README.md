# IntTape
A project simulating working with a tape device via file

## Installation
Run ```bash scripts/MakeDirs.sh``` to create necessary folders and files.

## Run
1. To start the project, run ```make IntTape```,
    then ```./IntTape input/input_file output/output_file config/delay```.
    For example ```./IntTape input/input1.txt output/output1.txt config/delay.txt```.

2. To run tests execute ```make TestTape```, then run ```./TestTape```