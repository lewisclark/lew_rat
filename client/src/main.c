#define WIN32_LEAN_AND_MEAN

#include "networking.h"
#include "system.h"
#include "util.h"

int main(int argc, char* argv[]) {
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init_networking, 0, 0, 0);

	getchar();

	return 0;
}