#include <arch/boot/asm.h>
#include <arch/serial.h>

int setBaudRate(u16 port, u32 rate) {
  u16 divisor = SERIAL_BASE_CLOCK / rate;
  u8 lcr = in8(port + SERIAL_LINE_CONTROL_REGISTER_OFFSET);

  out8(port + SERIAL_LINE_CONTROL_REGISTER_OFFSET, lcr | SERIAL_DLBA_MASK);
  out8(port + SERIAL_DIVISOR_LOW_OFFSET, divisor & 0xff);
  out8(port + SERIAL_DIVISOR_HIGH_OFFSET, (divisor >> 8) & 0xff);
  out8(port + SERIAL_LINE_CONTROL_REGISTER_OFFSET, lcr);

  return 0;
}

int setDataBits(u16 port, u8 bits) {
  out8(port + SERIAL_LINE_CONTROL_REGISTER_OFFSET, bits);
  return 0;
}
