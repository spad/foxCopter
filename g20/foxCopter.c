/*
 * foxCopter.c
 *
 *  Created on: 11/mar/2012
 *      Author: saverio pieri
 */

#include <unistd.h>
#include "imu/fc_i2c.h"
#include "imu/lis331dlh.h"
#include "gcs/gcs.h"
#include "mavlink/common/mavlink.h"

int lis331_init(int fd) {
	// select device
	i2c_opendevice(fd,LIS331DLH_ADDR);
	// setting REG1: power_normal, 400Hz, xyz enabled
	i2c_write_byte(fd, LIS331DLH_CTRL_REG1, LIS331DLH_NOR_400_XYZ);
	// setting scale: 2g (not needed)
	i2c_write_byte(fd, LIS331DLH_CTRL_REG4, LIS331DLH_FS_8G);
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
	return(0);
}
/**
 * send a heartbeat message.
 */
int gcs_heartbeat(int sock) {
	int bytes_sent;
	mavlink_message_t msg;
	uint8_t buf[512];
	uint16_t len;

	mavlink_msg_heartbeat_pack(1, 200, &msg, MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_ARMED, 0, MAV_STATE_ACTIVE);
	len = mavlink_msg_to_send_buffer(buf, &msg);
	bytes_sent = gcs_udp_send(sock, buf, len);
	return(bytes_sent);
}

uint64_t microsSinceEpoch(){

	struct timeval tv;

	uint64_t micros = 0;

	gettimeofday(&tv, NULL);
	micros =  ((uint64_t)tv.tv_sec) * 1000000 + tv.tv_usec;

	return micros;
}

int gcs_raw_imu(int sock, lis331dlh_output *data) {
	int bytes_sent;
	mavlink_message_t msg;
	uint8_t buf[512];
	uint16_t len;

	mavlink_msg_raw_imu_pack(1, 200, &msg, microsSinceEpoch(),(int16_t)data->raw_x,(int16_t) data->raw_y,(int16_t) data->raw_z,0,0,0,0,0,0);
	len = mavlink_msg_to_send_buffer(buf, &msg);
	bytes_sent = gcs_udp_send(sock, buf, len);
	return(bytes_sent);
}


int main(int argc, char *argv[]) {
	int fd;
	int sock;


	sock = gcs_udp_open();
	if (sock==0) return(-1);
	printf("Socket opened %d\n",sock);
	lis331dlh_output lis_data;
	printf("Starting...\n");
	// init i2c
	fd = i2c_open(I2C_G20_DEVICE);
	if (!(fd<0)) {
		// i2c opened. Init lis331
		lis331_init(fd);
		while(1) {
			lis331_readall(fd, &lis_data);
			gcs_heartbeat(sock);

			printf("Xraw: %6d\tYraw: %6d\tZraw: %6d --- mav bytes sent: %d\r",lis_data.raw_x,lis_data.raw_y,lis_data.raw_z,
						gcs_raw_imu(sock,&lis_data));
			usleep(20000);
		}
	}
	gcs_udp_close(sock);
	return(0);
}

