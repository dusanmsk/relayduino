#!/bin/bash

pio run -e nano_input && cp .pioenvs/nano_input/firmware.hex firmware/nano_input.hex
pio run -e nano_output && cp .pioenvs/nano_output/firmware.hex firmware/nano_output.hex

for i in `seq 0 4`; do
  echo "#define MEGA_BOARD_ID ${i}" > src/mega_board_id.h
  pio run -e mega_input && cp .pioenvs/nano_input/firmware.hex firmware/mega_input_${i}.hex
  pio run -e mega_output && cp .pioenvs/nano_output/firmware.hex firmware/mega_output_${i}.hex
done
