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
int ack_number = 0;
int seq_number = 0;
int tamano;
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
	if (VALIDATE_CHECKSUM(pkt) == 0){
		printf("%s\n", "Wrong checksum");
	}else{
		if(pkt->type == DATA){
			if(pkt->seqno == ack_number){
				printf("%s\n", "llega trama");
				if(ACCEPT_DATA(pkt->data,n - 10) != -1){
					seq_number++;
					SEND_ACK_PACKET(pkt->ackno);
				}else{
					printf("%s\n", "Wrong data");
				}
			}else{
				printf("%s %d %s %d\n", "seq ESPERADO",ack_number % 2, "seq LLEGADO",pkt->seqno % 2);
			}
		}else if(pkt->type == ACK){
			printf("%s %d\n", "recibo ack", pkt->ackno % 2);
			if ((pkt->ackno) == ack_number % 2){
				++ack_number;
				CLEAR_TIMER(0);
				RESUME_TRANSMISSION();
				printf("%s\n", "Todo correcto");
			}else{
				printf("%s\n", "La trama ack no es la correcta");
				printf("%s %d %s %d\n", "ACK ESPERADO",seq_number % 2, "ACK LLEGADO",pkt->ackno % 2);
			}
		}
	}
}

/* Callback called when the application wants to send data to the other end*/
void send_callback() {
	 tamano = READ_DATA_FROM_APP_LAYER(buffer,500);
	if (tamano == -1){
		printf("%s\n","ERROR READ" );
	}else{
		uint16_t length = tamano + 10;
		SEND_DATA_PACKET(DATA,length,ack_number % 2, seq_number % 2, &buffer);
		SET_TIMER(0,timeout);
		PAUSE_TRANSMISSION();
	}
}

/*
* This function gets called when timer with index "timerNumber" expires.
* The function of this timer depends on the protocol programmer
*/
void timer_callback(int timerNumber) {
	CLEAR_TIMER(0);
	printf("Reenviando trama %d\n",seq_number % 2);
	SEND_DATA_PACKET(DATA, tamano+10, ack_number % 2, seq_number % 2, &buffer);
	SET_TIMER(0, timeout);
	PAUSE_TRANSMISSION();
}
