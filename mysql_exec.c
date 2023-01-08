/* 
  Loadable User Defined Function based REST API access via libcurl for MySQL

  Author: Ersin ESEN
  Email: ersinesen@gmail.com
  Website: https://ersinesen.appspot.com
  Date: 2023-01-08

*/

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mysql.h"  // IWYU pragma: keep
#include "mysql/udf_registration_types.h"


/*
  Init function: shell_exec
*/
bool shell_exec_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {
  if (args->arg_count != 1 || args->arg_type[0] != STRING_RESULT) {
    strcpy(message, "Argument error. Usage: shell_exec(command)");
    return true;
  }

  return false;
}

/*
  Deinit function: shell_exec
*/
void shell_exec_deinit(UDF_INIT *) {

}

/*
  Main function: shell_exec
*/
char *shell_exec(UDF_INIT *, UDF_ARGS *args, char *result,
                          unsigned long *length, unsigned char *is_null,
                          unsigned char *) {
  
  const char *command = args->args[0];

  FILE *pipe;
	char *line;
	unsigned long outlen, linelen;

  pipe = popen(command, "r");
  
  if (!pipe) {
    fprintf(stdout, "[mysql_exec] ERROR: popen call was unsuccessful. \n");
    strcpy(result, "shell_exec error. Consult log.");
    *length = (unsigned long) strlen(result);
    //*is_null = 1;
    return result;
  }

	line = (char *)malloc(1024);
	result = (char *)malloc(1);
	outlen = 0;
  result[0] = (char)0;

  while (fgets(line, sizeof(line), pipe) != NULL) {
		linelen = strlen(line);
		result = (char *)realloc(result, outlen + linelen);
		strncpy(result + outlen, line, linelen);
		outlen = outlen + linelen;
	}

	pclose(pipe);

	if (!(*result) || result == NULL) {
		*is_null = 1;
	} else {
		result[outlen-1] = 0x00;
		*length = strlen(result);
	}

	return result;
                          
}

