/*
 * foxCopter.c
 *
 *  Created on: 11/mar/2012
 *      Author: saverio pieri
 */

#include "imu/fc_i2c.h"
#include "imu/lis331dlh.h"
#include <unistd.h>

int lis331_init(int fd) {
	// select device
	i2c_opendevice(fd,LIS331DLH_ADDR);
	// setting REG1: power_normal, 400Hz, xyz enabled
	i2c_write_byte(fd, LIS331DLH_CTRL_REG1, LIS331DLH_NOR_400_XYZ);
	// setting scale: 2g (not needed)
	i2c_write_byte(fd, LIS331DLH_CTRL_REG4, LIS331DLH_FS_2G);
	return(0);
}

int lis331_readall(int fd, lis331dlh_output *data) {
	unsigned char buffH=0x00, buffL=0x00;
	// select device
	i2c_opendevice(fd,LIS331DLH_ADDR);
	// x axis
	buffH = i2c_read_byte(fd, LIS331DLH_OUT_X_H);
	buffL = i2c_read_byte(fd, LIS331DLH_OUT_X_L);
	data->raw_x = lis_compact_bytes(buffH, buffL);
	// y axis
	buffH = i2c_read_byte(fd, LIS331DLH_OUT_Y_H);
	buffL = i2c_read_byte(fd, LIS331DLH_OUT_Y_L);
	data->raw_y = lis_compact_bytes(buffH, buffL);
	// z axis
	buffH = i2c_read_byte(fd, LIS331DLH_OUT_Z_H);
	buffL = i2c_read_byte(fd, LIS331DLH_OUT_Z_L);
	data->raw_z = lis_compact_bytes(buffH, buffL);
	printf("0x%2X - 0x%2X =>0x%2X => %d                           \r",buffH,buffL,data->raw_z,data->raw_z);
	return(0);
}

int main(int argc, char *argv[]) {
	int fd;
	lis331dlh_output lis_data;
	printf("Starting...\n");
	// init i2c
	fd = i2c_open(I2C_G20_DEVICE);
	if (!(fd<0)) {
		// i2c opened. Init lis331
		lis331_init(fd);
		while(1) {
			lis331_readall(fd, &lis_data);
//			printf("Xraw: %6d\tYraw: %6d\tZraw: %6d\r",lis_data.raw_x,lis_data.raw_y,lis_data.raw_z);
			usleep(20000);
		}
	}
	return(0);
}

