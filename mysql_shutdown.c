/* Copyright (C) 2005, 2006 Hartmut Holzgraefe

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
*/

/*
 * MySQL C client API example: mysql_shutdown()
 *
 * see also http://mysql.com/mysql_shutdown
*/

#include <stdlib.h>
#include <stdio.h>

#include <mysql.h>

/* TODO doesn't work like expected */

int main(int argc, char **argv) 
{
	MYSQL *mysql = NULL;

	mysql = mysql_init(mysql);

	if (!mysql) {
		puts("Init faild, out of memory?");
		return EXIT_FAILURE;
	}
	
	if (!mysql_real_connect(mysql,       /* MYSQL structure to use */
							"localhost", /* server hostname or IP address */ 
							"root",      /* mysql user */
							"",          /* password */
							"test",      /* default database to use, NULL for none */
							0,           /* port number, 0 for default */
							NULL,        /* socket file or named pipe name */
							CLIENT_FOUND_ROWS /* connection flags */ )) {
		puts("Connect failed\n");
	} else {
		if (mysql_shutdown(mysql, SHUTDOWN_DEFAULT)) {
		  printf("Error on Shutdown: %s\n", mysql_error(mysql));
    } else {
		  puts("Shutdown succeeded, testing Ping now\n");
			if (mysql_ping(mysql)) {
			  printf("Shutdown really succeeded, Ping failed with %s\n", mysql_error(mysql));
			} else {
			  puts("Shutdown missed, thread is still alive\n");
      }
		}
	}
	
	mysql_close(mysql);

	return EXIT_SUCCESS;
}
