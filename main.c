#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define LPLAYER 0xDB75DC
#define FLAGS 0x104
#define HEALTH 0x100
#define FORCEJUMP 0x527D360
/*
/  gcc -c -m32 -std=c99 -pedantic main.c
/  gcc --shared -m32 -std=c99 -pedantic main.c -o cheat.dll
*/

typedef struct {
  uintptr_t entity;
  int health;
  int flags;
} entity_t;

void hack(HINSTANCE hinstDLL) {
  AllocConsole();
  FILE* fp = freopen("CONOUT$", "w+", stdout);

  HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hcon, 4);
  printf("b1g hack! \n");

  uintptr_t module = (uintptr_t)GetModuleHandle("client.dll");
  entity_t local_player = {0};
  local_player.entity = *(uintptr_t*)(module + 0xDB75DC);
  
  /* main loop */
  for (;;) {
    if(GetKeyState(VK_END) & 0x1000)
      break;

    if(local_player.entity) {
      local_player.health = *(int*)(local_player.entity + HEALTH);
      printf("local player health: %d\n", local_player.health);

      local_player.flags = *(int*)(local_player.entity + FLAGS);
      if(GetAsyncKeyState(VK_SPACE) & 0x8000 && local_player.flags == 257) {
	
      }
    }
    
    
    /*
    // do meme shit
    */

    Sleep(5);
  }
  
  fclose(fp);
  FreeConsole();
  FreeLibraryAndExitThread(hinstDLL, 0);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
  if(fdwReason == DLL_PROCESS_ATTACH) {
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)hack, hinstDLL, 0, 0);
  }

  return TRUE;
}







