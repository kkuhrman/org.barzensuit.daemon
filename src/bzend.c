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
#include "bzend.h"

int main (int argc, char *argv[])
{
  FILE* flog = NULL;
  pid_t process_id = 0;
  pid_t sid = 0;

  /* @todo: libzenc logging facilities. */
  flog = fopen ("bzend.log", "w+");
  if (flog == NULL)
    {
      fprintf(stderr, "\n\tFailed to start bzend. Could not open logging.\n");
      goto LOG_FAIL;
    }

  /* Create child process */
  process_id = fork();

  /* Exit with fail code if fork() fails  */
  if (process_id < 0)
    {
      fprintf(flog, "Failed to start bzend. fork() returned %d", process_id);
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
      fprintf(flog, "Failed to start bzend. setsid() returned %d", sid);
      goto DAEMON_FAIL;
    }

  /* Change pwd to root. */
  chdir("/");

  /* Close stdin. stdout and stderr. */
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  fprintf(flog, "\n\tStarting bzend... process id is %d.\n", process_id);
  do
    {
      sleep(1);
      /* @todo: */
    } while(1);

 DAEMON_FAIL:
  fflush(flog);
  fclose(flog);

 LOG_FAIL:

  return (0);
}
