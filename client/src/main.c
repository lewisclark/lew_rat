#define WIN32_LEAN_AND_MEAN

#include "networking/networking.h"
#include <windows.h>
#include "payload/heartbeat.h"

int main(int argc, char* argv[]) {
	init_networking();

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)heartbeat_loop, 0, 0, 0);

	return 0;
}
