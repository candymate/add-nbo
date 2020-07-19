#!/bin/bash

make all

echo -n -e \\x00\\x00\\x03\\xe8 > thousand.bin
echo -n -e \\x00\\x00\\x01\\xf4 > five-hundred.bin
RESULT="$(./add-nbo thousand.bin five-hundred.bin)"
if [ "$RESULT" != "1000(0x3e8) + 500(0x1f4) = 1500(0x5dc)" ]
then
  echo -e "TEST FAILED\nRESULT : " $RESULT
else
  echo -e  "TEST SUCCESS\n"
fi

make clean
rm *.bin
