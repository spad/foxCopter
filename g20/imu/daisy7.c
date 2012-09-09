/*
 * daisy7.c
 *
 *  Created on: 04/set/2012
 *      Author: saverio
 */
#include "daisy7.h"

int daisy7_init(int fd) {
	if (0!=lis331_init(fd)) {
		perror("error initializing lis331dlh [daisy7_init()]");
		return(-1);
	}
	if (0!=l3g4200d_init(fd)) {
		perror("error initializing l3g4200d [daisy7_init()]");
		return(-1);
	}

	return(0);
}

int daisy7_readall(int fd,daisy7_imu *data) {
	lis331_read(fd, &(data->acc));
	l3g4200d_read(fd, &(data->gyro));
	return(0);
}

int lis331_init(int fd) {
	// select device
	i2c_opendevice(fd,LIS331DLH_ADDR);
	// setting REG1: power_normal, 400Hz, xyz enabled
	i2c_write_byte(fd, LIS331DLH_CTRL_REG1, LIS331DLH_NOR_400_XYZ);
	// setting scale: 2g (not needed)
	i2c_write_byte(fd, LIS331DLH_CTRL_REG4, LIS331DLH_FS_8G);
	return(0);
}
int lis331_read(int fd, lis331dlh_output *data) {
	unsigned char buffH=0x00, buffL=0x00;
	// select device
	i2c_opendevice(fd,LIS331DLH_ADDR);
	// x axis
	buffH = i2c_read_byte(fd, LIS331DLH_OUT_X_H);
	buffL = i2c_read_byte(fd, LIS331DLH_OUT_X_L);
	data->raw_x = imu_compact_bytes(buffH, buffL);
	// y axis
	buffH = i2c_read_byte(fd, LIS331DLH_OUT_Y_H);
	buffL = i2c_read_byte(fd, LIS331DLH_OUT_Y_L);
	data->raw_y = imu_compact_bytes(buffH, buffL);
	// z axis
	buffH = i2c_read_byte(fd, LIS331DLH_OUT_Z_H);
	buffL = i2c_read_byte(fd, LIS331DLH_OUT_Z_L);
	data->raw_z = imu_compact_bytes(buffH, buffL);
	return(0);
}

int l3g4200d_init(int fd) {
	// select device
	i2c_opendevice(fd,L3G4200D_ADDR);
	// setting REG1: power_normal, 400Hz, 50lpf , xyz enabled
	i2c_write_byte(fd, L3G4200D_CTRL_REG1, L3G4200D_400HZ_50LPF_XYZ);
	// setting scale: 250 dps
	i2c_write_byte(fd, L3G4200D_CTRL_REG4, L3G4200D_FS_250);
	return(0);
}

int l3g4200d_read(int fd, l3g4200d_output *data) {
	unsigned char buffH=0x00, buffL=0x00;
	// select device
	i2c_opendevice(fd,L3G4200D_ADDR);
	// x axis
	buffH = i2c_read_byte(fd, L3G4200D_OUT_X_H);
	buffL = i2c_read_byte(fd, L3G4200D_OUT_X_L);
	data->raw_x = imu_compact_bytes(buffH, buffL);
	// y axis
	buffH = i2c_read_byte(fd, L3G4200D_OUT_Y_H);
	buffL = i2c_read_byte(fd, L3G4200D_OUT_Y_L);
	data->raw_y = imu_compact_bytes(buffH, buffL);
	// z axis
	buffH = i2c_read_byte(fd, L3G4200D_OUT_Z_H);
	buffL = i2c_read_byte(fd, L3G4200D_OUT_Z_L);
	data->raw_z = imu_compact_bytes(buffH, buffL);
	return(0);
}

