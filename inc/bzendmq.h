/**
 * @file:	bzendmq.h
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

#ifndef _BZEND_MQ_H_
#define _BZEND_MQ_H_

#include <config.h>
#include "bzensbuf.h"

/**
 * @typedef bzen_mqopt_t
 */
typedef struct _bzen_mqopt_s
{
  size_t buffer_size;
  size_t queue_length;
  uint32_t port;
} bzen_mqopt_t;

/**
 * Process inbound/outbound Barzensuit module messages.
 *
 * @param void* arg Must be cast to bzen_mqopt_t.
 *
 * @return void* returns arg.
 */
void* bzend_mq_listen(void* arg);

/**
 * Receive incoming message from client connection.
 * 
 * @param bzen_cbuflock_t* cbuflock Pointer to lock for buffer
 * @param int client_fd File descriptor of the client connection.
 *
 * @return 0 on SUCCESS otherwise non-zero.
 */
int bzend_mq_recv(bzen_cbuflock_t* cbuflock, int client_fd);

#endif /* _BZEND_MQ_H_ */
