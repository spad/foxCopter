/*
 * fc_i2c.c
 *
 *  Created on: 11/mar/2012
 *      Author: saverio
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "fc_i2c.h"
#include <unistd.h>


int i2c_open(int device) {
	int fd;
	char filename[20];
	sprintf(filename,"/dev/i2c-%d",device);

	fd = open(filename,O_RDWR);
	if (fd<0) {
		// TODO configurare il metodo di debug
		printf("Cannot open i2c bus\n");
	}
	return fd;
}

int i2c_close(int fd) {
	return close(fd);
}

int i2c_opendevice(int fd, char address) {
	int io_res;
	io_res = ioctl(fd, I2C_SLAVE,address);
	if (io_res<0) {
		printf ("Can't set device at address %2X as i2c slave.\n",address);
	}
	return io_res; // 0 on success, -1 on error
}

char i2c_read_byte(int fd, char reg) {

	char buf[1];
	buf[0] = reg;
	// select the register
	if ((write(fd,buf,1))!=1) {
		printf("Error i2c on select the High Byte\n");
	}
	// read from register
	if ((read(fd,buf,1))!=1) {
		printf("Error i2c on read the  High Byte\n");
	}
	return buf[0];
}

void i2c_write_byte(int fd, char reg, char data) {
	char buf[2];
	buf[0] = reg;
	buf[1] = data;
	if ((write(fd,buf,2))!=2)
	{
		printf("Error i2c send the read command\n");
	}
}
