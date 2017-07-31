/* client-tls.c
 *
 * Copyright (C) 2006-2016 wolfSSL Inc.
 *
 * This file is part of wolfSSL.
 *
 * wolfSSL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * wolfSSL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */
#include "client-tls.h"

#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <errno.h>
#include    <arpa/inet.h>
#include    <wolfssl/ssl.h>          /* wolfSSL secure read/write methods */
#include    <wolfssl/certs_test.h>

#define MAXDATASIZE  4096           /* maximum acceptable amount of data */
#define SERV_PORT    11111          /* define default port number */

int client_connect(int id)
{
    int     sgxStatus;

    int     sockfd;                         /* socket file descriptor */
    struct  sockaddr_in servAddr;           /* struct for server address */
    int     ret = 0;                        /* variable for error checking */

    WOLFSSL_METHOD* method;
    WOLFSSL_CTX*    ctx;
    WOLFSSL*        ssl;


    /* data to send to the server, data recieved from the server */
    char    sendBuff[] = "Hello WolfSSL!";
    char rcvBuff[MAXDATASIZE] = {0};

    /* internet address family, stream based tcp, default protocol */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        printf("Failed to create socket. errno: %i\n", errno);
        return EXIT_FAILURE;
    }

    memset(&servAddr, 0, sizeof(servAddr)); /* clears memory block for use */
    servAddr.sin_family = AF_INET;          /* sets addressfamily to internet*/
    servAddr.sin_port = htons(SERV_PORT);   /* sets port to defined port */

    /* looks for the server at the entered address (ip in the command line) */
    if (inet_pton(AF_INET, "127.0.0.1", &servAddr.sin_addr) < 1) {
        /* checks validity of address */
        ret = errno;
        printf("Invalid Address. errno: %i\n", ret);
        return EXIT_FAILURE;
    }

    if (connect(sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
        ret = errno;
        printf("Connect error. Error: %i\n", ret);
        return EXIT_FAILURE;
    }

/*
#ifdef SGX_DEBUG
    enc_wolfSSL_Debugging_ON(id);
#else
    enc_wolfSSL_Debugging_OFF(id);
#endif
*/
//    enc_wolfSSL_Init(id, &sgxStatus);
    ret = wolfSSL_Init();   
    if (ret != SSL_SUCCESS) {
          printf("wolfSSL_Init() failure\n");
          return EXIT_FAILURE; 
     }



    method = wolfTLSv1_2_client_method();
    if (method == NULL) {
         printf("wolfTLSv1_2_client_method failure\n");
         return EXIT_FAILURE;     
     }
        
    ctx = wolfSSL_CTX_new(method);
    if (ctx == NULL) {
         printf("wolfSSL_CTX_new failure\n");
         return EXIT_FAILURE;
    }

    ret =  wolfSSL_CTX_use_certificate_chain_buffer_format(ctx,client_cert_der_2048, sizeof_client_cert_der_2048, SSL_FILETYPE_ASN1);
    if (ret != SSL_SUCCESS) {
      printf("wolfSSL_CTX_use_certificate_chain_buffer_format failure\n");
         return EXIT_FAILURE;
     } 
    

    ret =  wolfSSL_CTX_use_PrivateKey_buffer(ctx, client_key_der_2048, sizeof_client_key_der_2048, SSL_FILETYPE_ASN1);
    if (ret != SSL_SUCCESS) {
         printf("wolfSSL_CTX_use_PrivateKey_buffer failure\n");
         return EXIT_FAILURE;
     }

    ret = wolfSSL_CTX_load_verify_buffer(ctx, ca_cert_der_2048, sizeof_ca_cert_der_2048, SSL_FILETYPE_ASN1); 
       if (ret != SSL_SUCCESS)  {
        printf("Error loading cert\n");
        return EXIT_FAILURE;
     }
 
    ssl = wolfSSL_new(ctx); 
       if (ssl == NULL) {
          printf("wolfSSL_new error.\n");
          return EXIT_FAILURE;
       }

    ret = wolfSSL_set_fd(ssl, sockfd);
     if (ret != SSL_SUCCESS) {
         printf("wolfSSL_set_fd failure\n");
         return EXIT_FAILURE;
     }
 
    ret = wolfSSL_connect(ssl);
    if (ret != SSL_SUCCESS) {
         printf("Failed to connect to server\n");
         return EXIT_FAILURE;
     }
 
    ret = wolfSSL_write(ssl, sendBuff,strlen(sendBuff));
 
     if (ret != strlen(sendBuff)) {
         /* the message is not able to send, or error trying */
         ret = wolfSSL_get_error(ssl, 0);
         printf("Write error: Error: %i\n", ret);
         return EXIT_FAILURE;
     }
 
 
     ret = wolfSSL_read(ssl, rcvBuff, MAXDATASIZE); 
     if (ret < 0) {
         /* the server failed to send data, or error trying */
         ret = wolfSSL_get_error(ssl, 0);
         printf("Read error. Error: %i\n", ret);
         return EXIT_FAILURE;
     }
     printf("Recieved: \t%s\n", rcvBuff);


    /* frees all data before client termination */
    wolfSSL_free(ssl);
    wolfSSL_CTX_free(ctx);
    ret = wolfSSL_Cleanup();

    return ret;
}
