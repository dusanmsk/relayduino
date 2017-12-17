cd code
pio run
cp .pioenvs/nanoatmega328/firmware.hex ../induino_firmware_nano328.hex
cp .pioenvs/megaatmega2560/firmware.hex ../induino_firmware_mega2560.hex
git add induino_firmware*.hex
