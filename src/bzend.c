/**
 * @file:	bzend.c
 * @brief:	bzend daemon main().
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
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "bzenthread.h"
#include "bzend.h"
#include "bzendlog.h"
#include "bzendmq.h"

int main (int argc, char *argv[])
{
  pid_t process_id = 0;
  pid_t sid = 0;
  pthread_t mq_thread;
  int thread_status;
  bzen_mqopt_t mqopt = {
    BZEND_MQ_DEFAULT_SBUF_SIZE, 
    BZEND_MQ_DEFAULT_QUEUE_LENGTH, 
    BZEND_MQ_DEFAULT_PORT};
  int exit_code;
  int* result = &exit_code;

  /* Create child process */
  process_id = fork();

  /* Exit with fail code if fork() fails  */
  if (process_id < 0)
    {
      /* @todo: error logging*/
      exit_code = -1;
      goto DAEMON_FAIL;
    }

  /* Terminate parent process. */
  if (process_id > 0)
    {
      exit(0);
    }

  /* Unmask file mode. */
  umask(0);

  /* Set new session. */
  sid = setsid();
  if(sid < 0)
    {
      /* @todo: error logging */
      exit_code = -1;
      goto DAEMON_FAIL;
    }

  /* Change pwd to root. */
  chdir("/");

  /* Close stdin. stdout and stderr. */
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  /* @todo: if this cannot be option it must come from /etc/conf. */
  bzend_log_severity_level_set(BZENLOG_ERROR);

  /* Open message queue for processing. */
  thread_status = bzen_thread_create(&mq_thread, NULL, bzend_mq_listen, &mqopt);
  if (thread_status != 0)
    {
      /* @todo: error logging */
      exit_code = -1;
      goto DAEMON_FAIL;
    }

  thread_status = bzen_thread_join(mq_thread, (void**) &result);
  if (thread_status != 0)
    {
      /* @todo: error logging */
      exit_code = -1;
      goto DAEMON_FAIL;
    }

  /* Shutdown the log service. */
  bzend_log_shutdown();

 DAEMON_FAIL:

  return exit_code;
}
