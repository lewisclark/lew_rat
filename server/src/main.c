#include "networking/networking.h"

int main(int argc, char* argv[]) {
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init_networking, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)client_loop, 0, 0, 0);

	getchar();

	return 0;
}