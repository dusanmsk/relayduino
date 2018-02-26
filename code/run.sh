#!/bin/bash
export PLATFORMIO_UPLOAD_PORT=$2
pio run -e $1 --target upload && pio device monitor -p $2