from smbus import SMBus

addr = 0x8

bus = SMBus(1)

def writeByte(address, value):
    bus.write_byte(address, value)


while True:
    ledstate = int(input(">>>> "))
    if ledstate == 0:
        writeByte(addr, 0x0)
    elif ledstate == 1:
        writeByte(addr, 0x1)
    elif ledstate == 2:
        writeByte(addr, 0x2)
    elif ledstate == 3:
        writeByte(addr, 0x3)
    elif ledstate == 4:
        writeByte(addr, 0x4)
    else:
        break

