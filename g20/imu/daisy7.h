/*
 * daisy7.h
 *
 *  Created on: 04/set/2012
 *      Author: saverio
 */

#ifndef DAISY7_H_
#define DAISY7_H_

#include "../imu/fc_i2c.h"
#include "lis331dlh.h"
#include "l3g4200d.h"

// MACROS
#define imu_compact_bytes(x,y)		(unsigned short) (x << 8) | y

// Datatypes
typedef struct {
	lis331dlh_output 	acc;
	l3g4200d_output		gyro;
} daisy7_imu;


int daisy7_init(int fd);
int daisy7_readall(int fd,daisy7_imu *data);

int lis331_init(int fd);
int lis331_read(int fd, lis331dlh_output *data);

int l3g4200d_init(int fd);
int l3g4200d_read(int fd, l3g4200d_output *data);

#endif /* DAISY7_H_ */
