#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <poll.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <netinet/in.h>

#include "library.h"
#include "global.h"

/*
 * SECTION 1: GLOBAL DATA
 * ----------------------
 * Add your own data fields below this
 *
 */

int window_size;
long timeout;
void* buffer[500];
int chk_validation;

/*
 * SECTION 2: CALLBACK FUNCTIONS
 * -----------------------------
 * The following functions are called on the corresponding event
 *
 */


/*
 * Creates a new connection. You should declare any variable needed in the upper section, DO NOT DECLARE
 * ANY VARIABLES HERE. This function should only make initializations as required.
 *
 * You should save the input parameters in some persistant global variable (defined in Section 1) so it can be
 * accessed later
 */
void connection_initialization(int _windowSize, long timeout_in_ns) {
  window_size = _windowSize;
  timeout = timeout_in_ns;
  *buffer = (void*) malloc(500);
}

/* This callback is called when a packet pkt of size n is received*/
void receive_callback(packet_t *pkt, size_t n) {
  int chk_validation = VALIDATE_CHECKSUM(pkt);
  if (chk_validation == 0){
    printf("%s\n", "Wrong");
  }else{
    printf("%s\n", "Correct");
  }
  int size = pkt->len;
  ACCEPT_DATA(buffer,size);
}

/* Callback called when the application wants to send data to the other end*/
void send_callback() {
  int prueba = READ_DATA_FROM_APP_LAYER(buffer,500);
  packetType_t type = DATA;
  uint32_t ackNo = 1;
  uint32_t seqNo = 1;
  uint16_t length = 100;
  SEND_DATA_PACKET(type,length,ackNo, seqNo, &buffer);
}

/*
 * This function gets called when timer with index "timerNumber" expires.
 * The function of this timer depends on the protocol programmer
 */
void timer_callback(int timerNumber) {

}
