#!/bin/bash

#Upload to arduino board on /dev/ttyUSB0

# arduino --upload $1 --port /dev/ttyUSB0

arduino-cli compile --fqbn arduino:avr:nano
arduino-cli upload -p /dev/ttyUSB0 --fqbn arduino:avr:nano
