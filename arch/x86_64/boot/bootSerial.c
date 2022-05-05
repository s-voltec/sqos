#include <arch/boot/asm.h>
#include <arch/serial.h>

int initBootSerial(u16 port) {
  if(setBaudRate(port, SERIAL_RATE_115200) != 0) {
    return -1;
  }
  if(setDataBits(port, SERIAL_DB_8N1) != 0) {
    return -1;
  }

  return 0;
}

static u8 isWriteReady(u16 port) {
  return in8(port + SERIAL_LINE_STATUS_REGISTER_OFFSET) & SERIAL_LS_WREADY;
}

void bootSerialPrint(u16 port, const char *s) {
  for(;*s != '\0';s++) {
    while(isWriteReady(port) == 0);
    out8(port, *s);
  }
}
