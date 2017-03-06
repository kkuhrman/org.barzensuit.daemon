/**
 * @file:	bzendlog.c
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

#include <config.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* bzend package includes */
#include "bzendlog.h"

/**
 * Lowest priority level severity code to log.
 */
static unsigned int log_severity = BZENLOG_INFO;

/* Initializes the logs for reading and writing. */
static void bzend_log_init()
{
  char msgbuf[BZEND_MAX_MESSAGE_SIZE];
  int status;

  /* If we are only logging errors, warnings or status we only open log file on 
     demand. If logging info and or debug, we open all logs for life of process.
  */
  if (log_severity >= BZENLOG_INFO)
    {
      status = bzen_log_open(BZEND_LOG_ERRORS, BZEN_LOG_FOPEN_DEFAULT_ATTR);
      if (status != 0)
	{
	  /* @todo: fallback? */
	  goto LOG_INIT_FAIL;
	}

      status = bzen_log_open(BZEND_LOG_STATUS, BZEN_LOG_FOPEN_DEFAULT_ATTR);
      if (status != 0)
	{
	  /* @todo: fallback? */
	  goto LOG_INIT_FAIL;
	}

      status = bzen_log_open(BZEND_LOG_DEBUG, BZEN_LOG_FOPEN_DEFAULT_ATTR);
      if (status != 0)
	{
	  /* @todo: fallback? */
	  goto LOG_INIT_FAIL;
	}

      /* Log opening status. */
      snprintf(msgbuf, 
	       BZEND_MAX_MESSAGE_SIZE, 
	       "Initialized log service. Severity level is %d", 
	       log_severity);
      status = bzen_log_write(BZEND_LOG_STATUS, 
			      BZENLOG_STATUS,
			      msgbuf);
    }
  else 
    {
      status = bzen_log_open(BZEND_LOG_STATUS, BZEN_LOG_FOPEN_DEFAULT_ATTR);
      if (status != 0)
	{
	  goto LOG_INIT_FAIL;
	}

      /* Log opening status. */
      snprintf(msgbuf, 
	       BZEND_MAX_MESSAGE_SIZE, 
	       "Initialized log service. Severity level is %d", 
	       log_severity);

      status = bzen_log_write(BZEND_LOG_STATUS, 
			      BZENLOG_STATUS,
			      msgbuf);

      status = bzen_log_close(BZEND_LOG_STATUS);
    }

 LOG_INIT_FAIL:

  return;
}

/* Flushes log buffers, closes open files etc on shutdown. */
void bzend_log_shutdown()
{
  int status;

  /* Log closing  status. */
  status = bzen_log_write_stat(BZEND_LOG_STATUS, 
			  BZENLOG_STATUS,
			  "Shutting down log service.");

  /* Close any open logs. */
  status = bzen_log_close(BZEND_LOG_DEBUG);
  status = bzen_log_close(BZEND_LOG_STATUS);
  status = bzen_log_close(BZEND_LOG_ERRORS);
}

/* Returns the lowest priority level severity code being logged. */
unsigned int bzend_log_severity_level()
{
  return log_severity;
}

/* Set lowest priority level severity code to log. */
void bzend_log_severity_level_set(unsigned int level)
{
  switch (level)
    {
    default:
      log_severity = BZENLOG_INFO;
      break;
    case BZENLOG_ERROR:
    case BZENLOG_WARNING:
    case BZENLOG_STATUS:
    case BZENLOG_INFO:
    case BZENLOG_DEBUG:
      log_severity = level;
      break;
    }

  /* Initialize log(s). */
  bzend_log_init();
}
