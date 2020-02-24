/*
 * udp_serv.c
 *
 *  Created on: 7 oct. 2017
 *      Author: dubreuil
 */


#include "lwip/sys.h"
#include "lwip/sockets.h"

//
void udp_serv1_task(void){
	int sock, port;
	struct sockaddr_in address;
	struct sockaddr from;
	//struct lwip_sock *socket;

	socklen_t fromlen;
	fromlen=sizeof(from);

	char data_buf[10]; // 1000 erreur ???
	int recv_data;

	 /* create a UDP socket */


	 if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		 my_printf("erreur sock %d\n\r",sock);
		 while(1);
	 }

	 //vu pour initialiser a 0 ?
	 memset(&from, 0, sizeof(struct sockaddr_in));
	 /* bind to port 5000 at any interface */
	 address.sin_family = AF_INET;
	 address.sin_port = htons(6000);
	 address.sin_addr.s_addr = INADDR_ANY;

	 if (bind(sock, (struct sockaddr *)&address, sizeof (address)) < 0){
	    return;
	 }


	 while (1)
	 {
		 my_printf("attente sur 6000\r\n");

		 recv_data=recvfrom(sock,data_buf,sizeof(data_buf),0,&from,&fromlen);
		 if (recv_data>0)
		 {
			 my_printf("data recu :%d   data1:%s\r\n",recv_data,data_buf);

			 if (*data_buf=='R') BSP_LED_Toggle(3);
	         if (*data_buf=='V') BSP_LED_Toggle(1);
	         if (*data_buf=='B') BSP_LED_Toggle(2);

			 port=from.sa_data[0]<<8;
			 port+=from.sa_data[1];
			 //TODO  a tester
			 //port= PP_HTONS((uint16_t *)from.sa_data);

			 my_printf("IPclient :%s   Port Client:%d\r\n",ip4addr_ntoa(&(from.sa_data[2])),port);

			 //TODO : pas de recu si message broadcast
			 sendto(sock,"recu\n\r",6,0,&from,fromlen);
		 }

		 vTaskDelay(100);
	 }
}
