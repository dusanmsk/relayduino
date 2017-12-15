cd code
pio run
cp .pioenvs/nanoatmega328/firmware.hex ../firmware_nano328.hex
cp .pioenvs/megaatmega2560/firmware.hex ../firmware_mega2560.hex
git add firmware*.hex
