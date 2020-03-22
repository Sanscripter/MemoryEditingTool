#include "pch.h"
#include <iostream>
#include <windows.h>
#include <TlHelp32.h>

void logger(const char* message);
void logger(const int message);
void logger(const double message);
void logger(const DWORD message);


HANDLE processHandle; //interface tor read and write memory with the process
DWORD processId;

bool attachProcess(char* processName) {
	PROCESSENTRY32 procEntry32;

	//Defining  data structure size 
	procEntry32.dwSize = sizeof(PROCESSENTRY32);

	// assigning auto-typed list of all process currently running
	auto processHandlerSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (processHandlerSnap == INVALID_HANDLE_VALUE)
	{
		logger("Failed to recuperate process snapshot value.");
		return false;
	}

	//loop over processes in the list while there are still processes
	while (Process32Next(processHandlerSnap, &procEntry32))
	{
		logger(procEntry32.szExeFile);

		if (strcmp(processName, procEntry32.szExeFile)) {
			logger("FOUND PROCESS NAMED:");
			logger(procEntry32.szExeFile);
			logger("WITH ID:");
			logger(procEntry32.th32ProcessID);

			// once we find the process we populate the process handler
			processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, procEntry32.th32ProcessID);
			processId = procEntry32.th32ProcessID;

			if (!processHandle) {
				logger("Failed to get handle to the process!");
				CloseHandle(processHandlerSnap);
				return false;
			}

			CloseHandle(processHandlerSnap);
			return true;
		}
	}
	logger("Unable to find process by name");
	CloseHandle(processHandlerSnap);
	return false;
}

//wrapppers for R/W of process memory
template <class dataType>
void writeProcMem(dataType valToWirte, DWORD addressToWrite) {
	WriteProcessMemory(processHandle, (PVOID)addressToWrite, &valToWirte, sizeof(dataType), 0);
}

template <class dataType>
void readProcMem(DWORD addressToRead) {
	dataType readProcMemBuffer;
	ReadProcessMemory(processHandle, (PVOID)addressToRead, &readProcMemBuffer, sizeof(dataType), 0);
	return readProcMemBuffer;
}


int main()
{
	DWORD memAdd = 0x000000; //replace with the proper memory address value
	if (attachProcess((char*)"ProgramName.exe")) { // replace with your desired process name
		logger("START EDITING PROCESS MEMORY");
		logger("now...");
		std::cin.get();
		while (true) {
			//... run whatever code you want in here (change HP, Ammo, Strings)
		}
	};
	std::cin.get();

}