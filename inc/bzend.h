/**
 * @file:	bzend.h
 * @brief:	bzend global settings.
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

#ifndef _BZEND_H_
#define _BZEND_H_

#include <config.h>
#include <stdint.h>

/* Default size of stream buffer for message queue. */
const uint32_t BZEND_MQ_DEFAULT_SBUF_SIZE = 1024;
#define BZEND_MQ_DEFAULT_SBUF_SIZE BZEND_MQ_DEFAULT_SBUF_SIZE

/* Default number of connections permitted on message queue. */
const uint32_t BZEND_MQ_DEFAULT_QUEUE_LENGTH = 8;
#define BZEND_MQ_DEFAULT_QUEUE_LENGTH BZEND_MQ_DEFAULT_QUEUE_LENGTH

/* Default port on which message queue will listen. */
const uint32_t BZEND_MQ_DEFAULT_PORT = 7100;
#define  BZEND_MQ_DEFAULT_PORT BZEND_MQ_DEFAULT_PORT

#endif /* _BZEND_H_ */
