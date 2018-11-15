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

}

/* This callback is called when a packet pkt of size n is received*/
void receive_callback(packet_t *pkt, size_t n) {

}

/* Callback called when the application wants to send data to the other end*/
void send_callback() {

}

/*
 * This function gets called when timer with index "timerNumber" expires.
 * The function of this timer depends on the protocol programmer
 */
void timer_callback(int timerNumber) {

}

