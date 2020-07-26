#!/bin/bash

#Upload to arduino board on /dev/ttyUSB0

arduino --upload $1 --port /dev/ttyUSB0

