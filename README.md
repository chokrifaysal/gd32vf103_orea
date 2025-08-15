# gd32vf103_orea
Minimal C++ framework for reverse-engineering GD32VF103-based boards.

## build
make

## usage

id
    ./orea -c id

dump flash
    ./orea -c dump -a 0x08000000 -l 0x10000 -f fw.bin

erase
    ./orea -c erase -a 0x08000000 -l 0x10000

flash
    ./orea -c flash -a 0x08000000 -f fw.bin

## options
-d <tty>    serial port (default /dev/ttyUSB0)
-b <num>    baud      (default 1000000)

## wiring
tx -> swdio
rx -> swclk
gnd common

## license
NOTHING License uwu
