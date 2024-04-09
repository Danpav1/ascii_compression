#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/*
* @author Daniel Pavenko
* @date 04/08/24
* Utility class for wzip
*/

//Custom generic error message
void err(const char *errorMessage) {
	char error_message[30] = "An error has occurred\n";
	write(STDERR_FILENO, error_message, strlen(error_message)); 
	fprintf(stderr, "%s\n", errorMessage);
	exit(1);
}
