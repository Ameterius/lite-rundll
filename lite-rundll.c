// By Ametero

#include <windows.h>
#include <stdio.h>

HINSTANCE dll_buffer;
char error_buffer[2056]; // error messagebox buffer

int main(int argc, char *argv[]){
	switch (atoi(argv[1])){
		case 1: // use DLLMain as entrypoint
			dll_buffer = LoadLibraryA(argv[2]);
			if (dll_buffer == NULL){
				if(GetLastError() == 1114){
					sprintf(error_buffer, "[!!WARNING!!]\nDLLMain returned FALSE\n\nMode: 1 [entrypoint = DLLMain]\nDLL File: %s\n(Win) LastError: %i", argv[2], GetLastError());
					// Program executed ;c
					MessageBox(NULL, error_buffer, argv[0], 0x00000000L + 0x00000030L);
					FreeLibrary(dll_buffer);
					break;
				}
				sprintf(error_buffer, "[!!!ERROR!!!]\ndll_buffer is NULL\n\nMode: 1 [entrypoint = DLLMain]\nDLL File: %s\n(Win) LastError: %i", argv[2], GetLastError());
				MessageBox(NULL, error_buffer, argv[0], 0x00000010L + 0x00000000L);
				FreeLibrary(dll_buffer);
			}
			FreeLibrary(dll_buffer);
			break;
		case 2: // use custom function as entrypoint
			dll_buffer = LoadLibraryA(argv[2]); // executing w/ DLLMain 
			if (dll_buffer == NULL){
				if(GetLastError() == 1114){
					sprintf(error_buffer, "[!!WARNING!!]\nDLLMain returned FALSE\n\nMode: 1 [entrypoint = DLLMain]\nDLL File: %s\n(Win) LastError: %i", argv[2], GetLastError());
					MessageBox(NULL, error_buffer, argv[0], 0x00000000L + 0x00000030L);
				}
				if(GetLastError() != 1114){
					sprintf(error_buffer, "[!!!ERROR!!!]\ndll_buffer is NULL\n\nMode: 2 [entrypoint = %s]\nDLL File: %s\n(Win) LastError: %i", argv[3], argv[2], GetLastError());
					MessageBox(NULL, error_buffer, argv[0], 0x00000000L + 0x00000010L);
					FreeLibrary(dll_buffer);
				}
			}
			typedef void (*entrypoint)(void);
			entrypoint point = (entrypoint)GetProcAddress(dll_buffer, argv[3]);
			if (point == NULL){
				sprintf(error_buffer, "[!!!ERROR!!!]\nentrypoint is NULL\n\nMode: 2 [entrypoint = %s]\nDLL file: %s\nDLL hInstance: 0x%p\n(Win) LastError: %i", argv[3], argv[2],(void*)dll_buffer, GetLastError());
				MessageBox(NULL, error_buffer, argv[0], 0x00000000L + 0x00000010L);
				FreeLibrary(dll_buffer);
			}
			point(); // executing custom dll entrypoint
			FreeLibrary(dll_buffer);
			break;
		case 3:
			// 	w/o dll references!
			dll_buffer = LoadLibraryExA(argv[2], NULL, DONT_RESOLVE_DLL_REFERENCES);
			if (dll_buffer == NULL){
				sprintf(error_buffer, "[!!!ERROR!!!]\ndll_buffer is NULL\n\nMode: 1 [entrypoint = DLLMain]\nDLL File: %s\n(Win) LastError: %i", argv[2], GetLastError());
				MessageBox(NULL, error_buffer, argv[0], 0x00000010L + 0x00000000L);
				FreeLibrary(dll_buffer);
			}
			typedef void (*entrypoint)(void);
			entrypoint pointEx = (entrypoint)GetProcAddress(dll_buffer, argv[3]);
			if (pointEx == NULL){
				sprintf(error_buffer, "[!!!ERROR!!!]\nentrypoint is NULL\n\nMode: 2 [entrypoint = %s]\nDLL file: %s\nDLL hInstance: 0x%p\n(Win) LastError: %i", argv[3], argv[2],(void*)dll_buffer, GetLastError());
				MessageBox(NULL, error_buffer, argv[0], 0x00000000L + 0x00000010L);
				FreeLibrary(dll_buffer);
			}
			pointEx(); // executing custom dll entrypoint
			FreeLibrary(dll_buffer);
			break;
		default:
			sprintf(error_buffer, "lite-rundll32\nBy Ametero\n\nUsage:\n%s {TYPE} {DLLFile} [ENTRYPOINT]\nTypes:\n 1 - Loads the DLL file and executes the standard entry point: DLLMain\n 2 - Loads the DLL file and executes a custom entry point (the third argument)\n 3 - Loads the DLL file and executes a custom entry point (the third argument) (Imports - forbidden)\n\n\np.s. The 2nd method of execution: if the DLL file contains a DLLMain, it will execute it first, before the custom entry point. If the DLL file has a DLLMain but you need to call another part without triggering DLLMain, use the 3rd method. (Note: in the 3rd method, imports are forbidden and the export table is not populated, which may lead to unexpected behavior.)", argv[0]);
			MessageBox(NULL, error_buffer, "help", 0x00000000L);
			break;
	}

}
