/**
 * @file:	bzendlog.h
 * @brief:      Logging for bzend daemon.
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

#ifndef _BZEND_LOG_H_
#define _BZEND_LOG_H_

#include <config.h>

/* libzenc includes */
#include "bzenlog.h"

/**
 * Max chars for messages.
 */
#define BZEND_MAX_MESSAGE_SIZE BZEN_LOG_MESSAGE_MAX_CHARS

/**
 * Error/Warning log name.
 */
#define BZEND_LOG_ERRORS "bzend-error.log"

/**
 * Status/info log name.
 */
#define BZEND_LOG_STATUS "bzend.log"

/**
 * Debug log name.
 */
#define BZEND_LOG_DEBUG "bzend-debug.log"

/**
 * Initializes the logs for reading and writing.
 */
static void bzend_log_init();

/**
 * Flushes log buffers, closes open files etc on shutdown.
 */
void bzend_log_shutdown();

/**
 * Returns the lowest priority level severity code being logged.
 *
 * @return unsigned int The lowest priority level severity code currently being logged.
 */
unsigned int bzend_log_severity_level();

/**
 * Set  lowest priority level severity code to log.
 *
 * Must be one of BZENLOG_SEVERITY_CODE. Defaults to info.
 * @todo: Prefer bit mask so we can switch any and all levels on/off.
 *
 * @param unsigned int level The lowest priority level severity code to log.
 *
 */
void bzend_log_severity_level_set(unsigned int level);

#endif /* _BZEND_LOG_H_ */
