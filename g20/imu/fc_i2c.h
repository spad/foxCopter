/*
 * fc_i2c.h
 *
 *  Created on: 11/mar/2012
 *      Author: saverio
 */

#ifndef FC_I2C_H_
#define FC_I2C_H_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "linux/i2c-dev.h"

#define I2C_G20_DEVICE 0

int  i2c_open(int device);
int  i2c_close(int fd);
int  i2c_opendevice(int fd, char address);
void i2c_write_byte(int fd,char reg, char data);
char i2c_read_byte(int fd, char reg);

#endif /* FC_I2C_H_ */
