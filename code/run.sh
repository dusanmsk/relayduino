#!/bin/bash
pio run -e $1 && pio run -e $1 --target upload && pio device monitor -p $2