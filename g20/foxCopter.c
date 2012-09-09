/*
 * foxCopter.c
 *
 *  Created on: 11/mar/2012
 *      Author: saverio pieri
 */

#include <unistd.h>
#include "imu/fc_i2c.h"
#include "imu/daisy7.h"
#include "gcs/gcs.h"
#include "mavlink/common/mavlink.h"

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

int gcs_raw_imu(int sock, daisy7_imu data) {
	int bytes_sent;
	mavlink_message_t msg;
	uint8_t buf[512];
	uint16_t len;

	mavlink_msg_raw_imu_pack(1, 200, &msg, microsSinceEpoch(),
			data.acc.raw_x, data.acc.raw_y, data.acc.raw_z,
			data.gyro.raw_x,data.gyro.raw_y,data.gyro.raw_z,
			0,0,0);
	len = mavlink_msg_to_send_buffer(buf, &msg);
	bytes_sent = gcs_udp_send(sock, buf, len);
	return(bytes_sent);
}


int main(int argc, char *argv[]) {
	int fd;
	int sock;
	daisy7_imu imu_data;

	sock = gcs_udp_open();
	if (sock==0) return(1);

	printf("Starting...sock %X\n", sock);
	// init i2c
	fd = i2c_open(I2C_G20_DEVICE);
	if (!(fd<0)) {
		// i2c opened. Init daisy7
		daisy7_init(fd);
		while(1) {
			daisy7_readall(fd, &imu_data);
			gcs_heartbeat(sock);
			gcs_raw_imu(sock,imu_data);
//			printf("acc(%5d - %5d - %5d) gyro(%5d - %5d - %5d)     \r",
//					imu_data.acc.raw_x,imu_data.acc.raw_y,imu_data.acc.raw_z,
//					imu_data.gyro.raw_x,imu_data.gyro.raw_y,imu_data.gyro.raw_z);
			usleep(2500);
		}
	}
	gcs_udp_close(sock);
	return(0);
}

