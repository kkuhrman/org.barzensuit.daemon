/**
 * @file:	bzendmq.c
 * @brief:      Processes message queue.
 * 
 * @copyright:	Copyright (C) 2017 Kuhrman Technology Solutions LLC
 * @license:	GPLv3+: GNU GPL version 3
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <config.h>
#include <pthread.h>
#include <stdio.h>
#include "bzensock.h"
#include "bzendmq.h"

const size_t MQ_BUFFER_SIZE = 1028;

static int server_socket_fd;
static struct sockaddr_in* server_address;
static size_t server_address_size;
static bzen_cbuflock_t* mq_recv_buffer;
static bzen_cbuflock_t* mq_send_buffer;

/* Process inbound/outbound Barzensuit module messages. */
void* bzend_mq_listen(void* arg)
{
  fd_set active_fd_set;
  fd_set read_fd_set;
  struct sockaddr_in client_address;
  size_t client_address_size;
  int connection_fd;
  int new_connection_fd;
  int status;

  /* @todo: type safety error handling */
  bzen_mqopt_t* mqopt = (arg != NULL) ? (bzen_mqopt_t*)arg : NULL;

  /* construct server address */
  server_address =   bzen_socket_address_in(INADDR_ANY, mqopt->port);
  server_address_size = sizeof(*server_address);

  /* create server socket */
  server_socket_fd = bzen_socket_open(PF_INET, SOCK_STREAM, 0);
  if (server_socket_fd < 0)
    {
      /* @todo: error logging. */
      goto MQ_LISTEN_FAIL;
    }

  /* bind server socket to address */
  status = bzen_socket_bind(server_socket_fd, 
			    (struct sockaddr*)server_address, 
			    server_address_size);
  if (status < 0)
    {
      /* @todo: error logging. */
      goto MQ_LISTEN_FAIL;
    }

  /* Enable connection requests */
  status = bzen_socket_listen(server_socket_fd, mqopt->queue_length);
  if (status < 0)
    {
      /* @todo: error logging. */
      goto MQ_LISTEN_FAIL;
    }

  /* Initialize the set of active sockets. */
  FD_ZERO (&active_fd_set);
  FD_SET (server_socket_fd, &active_fd_set);
  
  /* Other socket support initializations. */
  client_address_size = sizeof(client_address);

  /* Initialzie the send and receive buffers. */
  mq_recv_buffer = bzen_sbuf_create(MQ_BUFFER_SIZE);
  mq_send_buffer = bzen_sbuf_create(MQ_BUFFER_SIZE);

  /* Enter endless loop to serve incoming connections. */
  while (1)
    {
      read_fd_set = active_fd_set;
      status = select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL);
      if (status < 0)
	{
	  /* @todo: error logging. */ 
	  goto MQ_LISTEN_FAIL;
	}

      /* Service all sockets with incoming connection. */
      for (connection_fd = 0; connection_fd < FD_SETSIZE; connection_fd++)
	{
	  if (FD_ISSET(connection_fd, &read_fd_set))
	    {
	      /* Is this a connection request on the server socket? */
	      if (connection_fd == server_socket_fd)
		{
		  /* @todo: which requests to accept, which to reject? */
		  new_connection_fd = accept(server_socket_fd,
					     (struct sockaddr*)&client_address, 
					     &client_address_size);
		  if (new_connection_fd < 0)
		    {
		      /* @todo: log error but we continue serving */
		    }

		  /* @todo: log new connection */

		  /* Add new connection to current set. */
		  FD_SET(new_connection_fd, &active_fd_set);
		}
	      else
		{
		  /* Data arriving on an already-connected socket. */
                  status =  bzend_mq_recv(mq_recv_buffer, connection_fd);
		  if (status < 0)
		    {
		      /* @todo: log error but we continue serving */
		    }
		}
	    }
	}
    }

 MQ_LISTEN_FAIL:

  /* Close the sockets. */
  status = bzen_socket_close(server_socket_fd, SHUT_RDWR);

  return mqopt;
}

/* Receive incoming message from client connection. */
int bzend_mq_recv(bzen_cbuflock_t* cbuflock, int client_fd)
{
  char tempbuf[MQ_BUFFER_SIZE];
  char char_in;
  char char_out;
  int nbytes;
  int nchar;
  int result;

  /* @todo: once we read data from socket, it's gone. we need to peek at
     incoming message to detrmine if buffer is big enough and decide what 
     to do if not. */
  nbytes = read(client_fd, tempbuf, MQ_BUFFER_SIZE);
  if (nbytes < 0)
    {
      result = -1;
      goto RECV_FAIL;
    }

  for (nchar = 0; nchar < nbytes; nchar++)
    {
      char_in = tempbuf[nchar];
      char_out = bzen_sbuf_putc(char_in, cbuflock);
      if (char_out == EOF)
	{
	  if (nchar < nbytes)
	    {
	      /* Indicates a write error. */
	      /* @todo: error logging. */
	      result = -1;
	      goto RECV_FAIL;
	    }
	}
    }

  /* Received all incoming data. */
  result = 0;

 RECV_FAIL:

  return result;
}
