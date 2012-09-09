/*
 * l3g4200d.h
 *
 *  Created on: 04/set/2012
 *      Author: saverio
 */

#ifndef L3G4200D_H_
#define L3G4200D_H_

// DEVICE ADDRESS
#define L3G4200D_ADDR 				(unsigned char) 0x68
// DEVICE REGISTER ADDRESS MAP
#define L3G4200D_WHOAMI_REG			(unsigned char) 0x0F	// rw | default: 11010011
#define L3G4200D_CTRL_REG1			(unsigned char) 0x20	// rw | default: 00000111
#define L3G4200D_CTRL_REG2			(unsigned char) 0x21	// rw | default: 00000000
#define L3G4200D_CTRL_REG3			(unsigned char) 0x22	// rw | default: 00000000
#define L3G4200D_CTRL_REG4			(unsigned char) 0x23	// rw | default: 00000000
#define L3G4200D_CTRL_REG5			(unsigned char) 0x24	// rw | default: 00000000
#define L3G4200D_OUT_TEMP			(unsigned char) 0x26	// r  | output
#define L3G4200D_STATUS_REG			(unsigned char) 0x27	// r  | output
#define L3G4200D_OUT_X_L			(unsigned char) 0x28	// r  | output
#define L3G4200D_OUT_X_H			(unsigned char) 0x29	// r  | output
#define L3G4200D_OUT_Y_L			(unsigned char) 0x2A	// r  | output
#define L3G4200D_OUT_Y_H			(unsigned char) 0x2B	// r  | output
#define L3G4200D_OUT_Z_L			(unsigned char) 0x2C	// r  | output
#define L3G4200D_OUT_Z_H			(unsigned char) 0x2D	// r  | output

// CTRL_REG1
#define L3G4200D_PD_ON				(unsigned char) 0b00000000		// power down, default
#define L3G4200D_PD_OFF				(unsigned char) 0b00001000		// power normal

/* For table combination of DR<1:0> and BW<1:0> refer to DS table 22 (pag.29) */

#define L3G4200D_100HZ_12			(unsigned char) 0x00			// 100HZ - 12.5 CutOFF
#define L3G4200D_100HZ_25A			(unsigned char) 0x10			// 100HZ - 25 CutOFF
#define L3G4200D_100HZ_25B			(unsigned char) 0x20			// 100HZ - 25 CutOFF
#define L3G4200D_100HZ_25C			(unsigned char) 0x30			// 100HZ - 25 CutOFF

#define L3G4200D_200HZ_12			(unsigned char) 0x40			// 200HZ - 12.5 CutOFF
#define L3G4200D_200HZ_25			(unsigned char) 0x50			// 200HZ - 25 CutOFF
#define L3G4200D_200HZ_50			(unsigned char) 0x60			// 200HZ - 50 CutOFF
#define L3G4200D_200HZ_70			(unsigned char) 0x70			// 200HZ - 70 CutOFF

#define L3G4200D_400HZ_20			(unsigned char) 0x80			// 400HZ - 20 CutOFF
#define L3G4200D_400HZ_25			(unsigned char) 0x90			// 400HZ - 25 CutOFF
#define L3G4200D_400HZ_50			(unsigned char) 0xA0			// 400HZ - 50 CutOFF
#define L3G4200D_400HZ_110			(unsigned char) 0xB0			// 400HZ - 110 CutOFF

#define L3G4200D_800HZ_30			(unsigned char) 0xC0			// 800HZ - 30 CutOFF
#define L3G4200D_800HZ_35			(unsigned char) 0xD0			// 800HZ - 35 CutOFF
#define L3G4200D_800HZ_50			(unsigned char) 0xE0			// 800HZ - 50 CutOFF
#define L3G4200D_800HZ_110			(unsigned char) 0xF0			// 800HZ - 110 CutOFF

#define L3G4200D_POWER_DOWN			(unsigned char) 0b00000000		// Power Down
#define L3G4200D_POWER_UP			(unsigned char) 0b00001000		// Power UP

#define L3G4200D_Z_EN				(unsigned char) 0b00000001		// Z axis 1:enabled
#define L3G4200D_Y_EN				(unsigned char) 0b00000010		// Y axis 1:enabled
#define L3G4200D_X_EN				(unsigned char) 0b00000100		// X axis 1:enabled
#define L3G4200D_XYZ_EN				(unsigned char) 0b00000111		// All axis enabled

// CTRL_REG4
#define L3G4200D_FS_250				(unsigned char) 0x00			// 250 dps
#define L3G4200D_FS_500				(unsigned char) 0x10			// 500 dps
#define L3G4200D_FS_2000			(unsigned char) 0x20			// 2000 dps

// COMMON MODES
#define L3G4200D_400HZ_50LPF_XYZ	(unsigned char) L3G4200D_POWER_UP|L3G4200D_400HZ_50|L3G4200D_XYZ_EN // normal power, 400Hz 50lpf, all axis enabled


// Datatypes
typedef struct {
	signed short raw_x;	// raw data for x-gyro
	signed short raw_y;	// raw data for y-gyro
	signed short raw_z;	// raw data for z-gyro
} l3g4200d_output;


#endif /* L3G4200D_H_ */
