#include "util.h"

void log_message(const char* log) {
	FILE* log_file = fopen("lewrat_client.log", "a");

	fprintf(log_file, "[%I64u] %s", time(NULL), log); // TODO: Write encrypted log to file, decrypt on server
	fclose(log_file);

	printf("%s\n", log);
}

void log_message_wstr(const wchar_t* log) {
	FILE* log_file = fopen("lewrat_client.log", "a");

	fprintf(log_file, "[%I64u] %S", time(NULL), log); // TODO: Write encrypted log to file, decrypt on server
	fclose(log_file);

	printf("%S\n", log);
}
