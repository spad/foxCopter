/*
 * gcs.c
 *
 *  Created on: 03/set/2012
 *      Author: saverio
 */

#include "gcs.h"

/**
 * Open and configure UPD socket for writing to and reading from GCS
 */
int gcs_udp_open(void) {
	int sock;

	char target_ip[100];

	if ((sock = socket(PF_INET,SOCK_DGRAM, IPPROTO_UDP))<0) {
		perror("error opening socket [udp_open()]");
		return 0;
	}

	memset(&locAddr, 0, sizeof(locAddr));
	locAddr.sin_family = AF_INET;
	locAddr.sin_addr.s_addr = INADDR_ANY;
	locAddr.sin_port = htons(GCS_LOC_PORT);

	/* Bind the socket to port 14551 - necessary to receive packets from qgroundcontrol */
	if (-1 == bind(sock,(struct sockaddr *)&locAddr, sizeof(struct sockaddr)))
    {
		perror("error bind failed. [udp_open()]");
		close(sock);
		exit(EXIT_FAILURE);
    }

	/* Attempt to make it non blocking */
	if (fcntl(sock, F_SETFL, O_NONBLOCK | FASYNC) < 0)
    {
		fprintf(stderr, "error setting nonblocking: %s [udp_open()]\n", strerror(errno));
		close(sock);
		exit(EXIT_FAILURE);
    }

	strcpy(target_ip, GCS_GC_IP);
	// TODO leggere ip su cui fare il bind da parametri
	// if (argc == 2)	strcpy(target_ip, argv[1]);

	memset(&gcAddr, 0, sizeof(gcAddr));
	gcAddr.sin_family = AF_INET;
	gcAddr.sin_addr.s_addr = inet_addr(target_ip);
	gcAddr.sin_port = htons(GCS_GC_PORT);

	return (sock);
}
/**
 * Close GCS upp socket
 */
int gcs_udp_close (int sock) {
	if (close(sock) != 0) {
		perror("error closing socket [close_udp_socket()]");
		return 0;
	}
	return 1;
}
/**
 * send data packet to GCS
 */
int gcs_udp_send(int sock, void *buffer, size_t len) {
	int bytes_sent = sendto(sock, buffer, len, 0, (struct sockaddr*)&gcAddr, sizeof(struct sockaddr_in));

	return(bytes_sent);
}
