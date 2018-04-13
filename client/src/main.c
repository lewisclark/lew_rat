#define WIN32_LEAN_AND_MEAN

#include "networking/networking.h"
#include <windows.h>
#include "payload/heartbeat.h"

int main(int argc, char* argv[]) {
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init_networking, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)heartbeat_loop, 0, 0, 0);

	// How to run silently: https://stackoverflow.com/questions/9618815/i-dont-want-console-to-appear-when-i-run-c-program
	while (1) // Keep alive
		Sleep(10000);

	return 0;
}
