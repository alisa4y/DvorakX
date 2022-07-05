#include "sendKey.h"
#include "keyMaps.h"


LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
	unsigned char key = p->vkCode;
	//printf("key %d scan: %d\n", key, p->scanCode);
	//return CallNextHookEx(NULL, nCode, wParam, lParam);
	if (nCode == HC_ACTION && !(p->flags & LLKHF_INJECTED))
	{
		switch (wParam)
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			//printf("processing %d \n", key);
			if ((GetKeyState(VK_LWIN) & 0x8000) && key == VK_SPACE) {
				if (hook) stopHook();
				else startHook();
				break;
			}
			if ((GetKeyState(VK_LMENU) & 0x8000) && key == VK_SPACE) {
				startHook();
				return 1;
			}
			if (xKeyDown) {
				if (mapXKeys.count(key)) {
					mapXKeys[key]();
					return 1;
				}
				else {
					sendInputDown(VK_LMENU);
					break;
				}
			}
			else if ((GetKeyState(VK_SHIFT) & 0x8000) && mapShiftedKeys.count(key)) {
				mapShiftedKeys[key]();
				return 1;
			}
			else if (GetKeyState(VK_CONTROL) & 0x8000 || GetKeyState(VK_LWIN) & 0x8000) {
				/*if (mapCtrlKeys.count(key)) {
					mapShiftedKeys[key]();
					return 1;
				}
				else*/
				break;
			}
			else if (mapConsumers.count(key)) {
				mapConsumers[key]();
				return 1;
			}
			else if (!hook)break;
			else if (mapKeys.count(key)) {
				sendInputDown(mapKeys[key]);
				return 1;
			}
			else if (mapSpecialKeys.count(key)) {
				mapSpecialKeys[key]();
				return 1;
			}
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			if (mapKeyUp.count(key)) {
				mapKeyUp[key]();
			}
			if (mapKeys.count(key)) {
				sendInputUp(mapKeys[key]);
			}
			break;
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main()
{

	// Install the low-level keyboard & mouse hooks
	HHOOK hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);

	// Keep this app running until we're told to stop
	MSG msg;
	while (!GetMessage(&msg, NULL, NULL, NULL)) {    //this while loop keeps the hook
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(hhkLowLevelKybd);
	return(0);
}