/*
 * gcs.h
 *
 *  Created on: 03/set/2012
 *      Author: saverio
 */

#ifndef FC_GCS_H_
#define FC_GCS_H_

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/time.h>
#include <time.h>
#include <arpa/inet.h>


#define GCS_GC_IP	 	"10.0.2.159"	// ground control default addr
#define GCS_GC_PORT 	14550			// UDP port of ground control
#define GCS_LOC_PORT	14551			// local port for receiving messages

struct sockaddr_in gcAddr; 	// sock to gcs
struct sockaddr_in locAddr; // local sock

int gcs_udp_open(void);
int gcs_udp_close (int sock);
int gcs_udp_send(int sock, void *buffer, size_t len);

#endif /* FC_GCS_H_ */
