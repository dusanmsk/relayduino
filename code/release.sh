#!/bin/bash

mkdir firmware

echo > src/release.h
pio run -e nano_input && cp .pioenvs/nano_input/firmware.hex firmware/nano_input.hex
pio run -e nano_output && cp .pioenvs/nano_output/firmware.hex firmware/nano_output.hex

echo "#define DEBUG_BUILD" > src/release.h
pio run -e nano_input && cp .pioenvs/nano_input/firmware.hex firmware/nano_input_debug.hex
pio run -e nano_output && cp .pioenvs/nano_output/firmware.hex firmware/nano_output_debug.hex

for i in `seq 0 4`; do
  echo "#define MEGA_BOARD_ID ${i}" > src/release.h
  pio run -e mega_input && cp .pioenvs/nano_input/firmware.hex firmware/mega_input_${i}.hex
  pio run -e mega_output && cp .pioenvs/nano_output/firmware.hex firmware/mega_output_${i}.hex

  echo "#define DEBUG_BUILD" >> src/release.h
  pio run -e mega_input && cp .pioenvs/nano_input/firmware.hex firmware/mega_input_${i}_debug.hex
  pio run -e mega_output && cp .pioenvs/nano_output/firmware.hex firmware/mega_output_${i}_debug.hex

done
