/*
 * lis331dlh.h
 *
 *  Gestione dell'accelerometro LIS331DLH della daisy-7
 *
 *  Created on: 11/mar/2012
 *      Author: Saverio Pieri
 *      email: saveriop (at) gmail (dot) com
 */

#ifndef LIS331DLH_H_
#define LIS331DLH_H_

// DEVICE ADDRESS
#define LIS331DLH_ADDR 				(unsigned char) 0x18
// DEVICE REGISTER ADDRESS MAP
#define LIS331DLH_WHOAMI_REG		(unsigned char) 0x0F	// rw | default: 00000111
#define LIS331DLH_CTRL_REG1			(unsigned char) 0x20	// rw | default: 00000000
#define LIS331DLH_CTRL_REG2			(unsigned char) 0x21	// rw | default: 00000000
#define LIS331DLH_CTRL_REG3			(unsigned char) 0x22	// rw | default: 00000000
#define LIS331DLH_CTRL_REG4			(unsigned char) 0x23	// rw | default: 00000000
#define LIS331DLH_CTRL_REG5			(unsigned char) 0x24	// rw | default: 00000000
#define LIS331DLH_HP_FILTER_RESET	(unsigned char) 0x25	// r  | dummy register
#define LIS331DLH_REFERENCE			(unsigned char) 0x26	// rw | default: 00000000
#define LIS331DLH_STATUS_REG		(unsigned char) 0x27	// r  | default: 00000000
#define LIS331DLH_OUT_X_L			(unsigned char) 0x28	// r  | output
#define LIS331DLH_OUT_X_H			(unsigned char) 0x29	// r  | output
#define LIS331DLH_OUT_Y_L			(unsigned char) 0x2A	// r  | output
#define LIS331DLH_OUT_Y_H			(unsigned char) 0x2B	// r  | output
#define LIS331DLH_OUT_Z_L			(unsigned char) 0x2C	// r  | output
#define LIS331DLH_OUT_Z_H			(unsigned char) 0x2D	// r  | output
/******************************/
/* (interrupts not used here) */
/******************************/

// CTRL_REG1
#define LIS331DLH_PM_DOWN			(unsigned char) 0b00000000	// power down, default
#define LIS331DLH_PM_NORMAL			(unsigned char) 0b00100000	// power normal
#define LIS331DLH_PM_LOW_05			(unsigned char) 0b01000000	// low power 0.5Hz
#define LIS331DLH_PM_LOW_1			(unsigned char) 0b01100000	// low power 1Hz
#define LIS331DLH_PM_LOW_2			(unsigned char) 0b10000000	// low power 2Hz
#define LIS331DLH_PM_LOW_5			(unsigned char) 0b10100000	// low power 5Hz
#define LIS331DLH_PM_LOW_10			(unsigned char) 0b11000000	// low power 10Hz
#define LIS331DLH_DR_50				(unsigned char) 0b00000000	// Output Data Rate 50Hz
#define LIS331DLH_DR_100			(unsigned char) 0b00001000	// Output Data Rate 100Hz
#define LIS331DLH_DR_400			(unsigned char) 0b00010000	// Output Data Rate 400Hz
#define LIS331DLH_DR_1000			(unsigned char) 0b00011000	// Output Data Rate 1000Hz
#define LIS331DLH_Z_EN(x)			(unsigned char) x<<3		// Z axis 1:enabled
#define LIS331DLH_Y_EN(x)			(unsigned char) x<<2		// Y axis 1:enabled
#define LIS331DLH_X_EN(x)			(unsigned char) x			// X axis 1:enabled
#define LIS331DLH_XYZ_EN			(unsigned char) 0b00000111	// All axis enabled
// CTRL_REG4
																// FS0	FS1 (bit 00xx0000 in REG4)
#define LIS331DLH_FS_2G				(unsigned char) 0x00		//   0    0 = +- 2g
#define LIS331DLH_FS_4G				(unsigned char) 0x10		//   0    1 = +- 4g
#define LIS331DLH_FS_8G				(unsigned char) 0x30		//   1    1 = +- 8g
// COMMON MODES
#define LIS331DLH_NOR_400_XYZ		(unsigned char) LIS331DLH_PM_NORMAL|LIS331DLH_DR_400|LIS331DLH_XYZ_EN // normal power, 400Hz, all axis enabled

// MACROS
#define lis_compact_bytes(x,y)		(unsigned short) (x << 8) | y

// Datatypes
typedef struct {
	signed short raw_x;	// raw data for x-accel
	signed short raw_y;	// raw data for y-accel
	signed short raw_z;	// raw data for z-accel
} lis331dlh_output;


#endif /* LIS331DLH_H_ */
