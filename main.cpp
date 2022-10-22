#define NOMINMAX
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma warning ( disable : 4172 )

#include "Includes.h"

bool DllMain(HMODULE hModule, uint32_t nCallReason, LPVOID lpReserved) {
	if (nCallReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		HANDLE ThreadHandle = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, NULL, NULL, NULL);
		if (ThreadHandle) {
			CloseHandle(ThreadHandle);
		}
	}

	return true;
}