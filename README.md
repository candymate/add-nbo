# add-nbo
This repository is for lecture in BOB 9th. Please ignore this repository.
## Description
The goal of this program is to convert network byte order to host byte order.
## Build
`make`
## Run
`./add-nbo <file 1> <file 2>`
where file 1, 2 are generated with
```
echo -n -e \\x00\\x00\\x03\\xe8 > thousand.bin
echo -n -e \\x00\\x00\\x01\\xf4 > five-hundred.bin
```
## Check Example
You can check the validity of the program with example.
`./check-example.sh`