#pragma once
#include <Windows.h>
#include <vector>

using namespace std;

void sendInputDown(WORD key) {
    INPUT inputs[1] = {};
    ZeroMemory(inputs, sizeof(inputs));

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = key;
    inputs[0].ki.wScan = MapVirtualKey(key, 0);
    inputs[0].ki.dwFlags = 1;

    UINT uSent = SendInput(1, inputs, sizeof(INPUT));
}
void sendInputUp(WORD key) {
    INPUT inputs[1] = {};
    ZeroMemory(inputs, sizeof(inputs));

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = key;
    inputs[0].ki.wScan = MapVirtualKey(key, 0);
    inputs[0].ki.dwFlags = 1 | KEYEVENTF_KEYUP;

    UINT uSent = SendInput(1, inputs, sizeof(INPUT));
}
void sendKey(WORD key) {
    INPUT inputs[2];
    ZeroMemory(inputs, sizeof(inputs));

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = key;
    inputs[0].ki.wScan = MapVirtualKey(key, 0);
    inputs[0].ki.dwFlags = KEYEVENTF_UNICODE;

    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = key;
    inputs[1].ki.wScan = MapVirtualKey(key, 0);
    inputs[1].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;



    UINT uSent = SendInput(2, inputs, sizeof(INPUT));

    /*if (uSent != ARRAYSIZE(inputs))
    {
        printf("SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
    }*/
}
void sendKeys(vector<WORD>* keys) {
    UINT size = keys->size();
    UINT arrSize = size * 2;
    INPUT* inputs = new INPUT[arrSize];
    ZeroMemory(inputs, sizeof(INPUT) * arrSize);

    WORD key;
    size_t i2;
    for (size_t i = 0; i < size; i++)
    {
        key = (*keys)[i];
        inputs[i].type = INPUT_KEYBOARD;
        inputs[i].ki.wVk = key;
        inputs[i].ki.wScan = MapVirtualKey(key, 0);
        inputs[i].ki.dwFlags = KEYEVENTF_UNICODE;

        i2 = i + size;
        inputs[i2].type = INPUT_KEYBOARD;
        inputs[i2].ki.wVk = key;
        inputs[i2].ki.wScan = MapVirtualKey(key, 0);
        inputs[i2].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
    }


    UINT uSent = SendInput(arrSize, inputs, sizeof(INPUT));

    /*if (uSent != ARRAYSIZE(inputs))
    {
        printf("SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
    }*/
}
void sendSKey(WORD key) {
    sendInputDown(VK_SHIFT);
    sendKey(key);
    sendInputUp(VK_SHIFT);
}
void sendUsKey(WORD key) {
    sendInputUp(VK_SHIFT);
    sendKey(key);
    sendInputDown(VK_SHIFT);
}
void sendCKey(WORD key) {
    sendInputDown(VK_CONTROL);
    sendKey(key);
    sendInputUp(VK_CONTROL);
}
void sendAKey(WORD key) {
    sendInputDown(VK_MENU);
    sendKey(key);
    sendInputUp(VK_MENU);
}