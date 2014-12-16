/*
 * Copyright (c) 2014 ARM. All rights reserved.
 */
#include "at24mac.h"
#include "mbed.h"

/* Device addressing */
#define AT24MAC_EEPROM_ADDRESS		(0x0A<<4)
#define AT24MAC_RW_PROTECT_ADDRESS	(0x06<<4)
#define AT24MAC_SERIAL_ADDRESS		(0x0B<<4)

/* Known memory blocks */
#define AT24MAC_SERIAL_OFFSET	(0x80)
#define AT24MAC_EUI64_OFFSET	(0x98)
#define AT24MAC_EUI48_OFFSET	(0x98)

#define SERIAL_LEN 16
#define EUI64_LEN 8
#define EUI48_LEN 6

I2C i2c(D14, D15);

/**
 * Read unique serial number from chip.
 * \param buf pointer to write serial number to. Must have space for 16 bytes.
 * \return zero on success, negative number on failure
 */
extern "C" int at24mac_read_serial(void *buf)
{
	char offset = AT24MAC_SERIAL_OFFSET;
	if (!i2c.write(AT24MAC_SERIAL_ADDRESS, &offset, 1, true))
		return -1; //No ACK
	return i2c.read(AT24MAC_SERIAL_ADDRESS, (char*)buf, SERIAL_LEN);
}

/**
 * Read EUI-64 from chip.
 * \param buf pointer to write EUI-64 to. Must have space for 8 bytes.
 * \return zero on success, negative number on failure
 */
extern "C" int at24mac_read_eui64(void *buf)
{
	char offset = AT24MAC_EUI64_OFFSET;
	if (!i2c.write(AT24MAC_SERIAL_ADDRESS, &offset, 1, true))
		return -1; //No ACK
	return i2c.read(AT24MAC_SERIAL_ADDRESS, (char*)buf, EUI64_LEN);
}

/**
 * Read EUI-48 from chip.
 * \param buf pointer to write EUI-48 to. Must have space for 6 bytes.
 * \return zero on success, negative number on failure
 */
extern "C" int at24mac_read_eui48(void *buf)
{
	char offset = AT24MAC_EUI48_OFFSET;
	if (!i2c.write(AT24MAC_SERIAL_ADDRESS, &offset, 1, true))
		return -1; //No ACK
	return i2c.read(AT24MAC_SERIAL_ADDRESS, (char*)buf, EUI48_LEN);
}
