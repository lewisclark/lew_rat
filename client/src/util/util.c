#include "util.h"

void log_message(const char* log) {
	FILE* log_file = fopen("lewrat_client.log", "a");

	fprintf(log_file, "[%s - %s] %s", __DATE__, __TIME__, log); // TODO: Write encrypted log to file, decrypt on server
	fclose(log_file);

	printf("%s\n", log);
}

void log_message_wstr(const wchar_t* log) {
	FILE* log_file = fopen("lewrat_client.log", "a");

	fprintf(log_file, "[%s - %s] %S", __DATE__, __TIME__, log); // TODO: Write encrypted log to file, decrypt on server
	fclose(log_file);

	printf("%S\n", log);
}
