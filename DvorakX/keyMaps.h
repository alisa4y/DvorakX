#pragma once
#include <iostream>
#include <map>
#include "sendKey.h"

using namespace std;

bool hook = true;
bool xKeyDown = false;
bool shiftDown = false;
bool ctrlDown = false;
bool cmsTrigger = false;
vector<WORD> ret{ 'R','E','T','U','R','N',VK_SPACE };
vector<WORD> elseS{ 'E','L','S','E',VK_SPACE };
vector<WORD> trueS{ 'T','R','U','E' };
vector<WORD> falseS{ 'F','A','L','S','E' };
vector<WORD> breakS{ 'B','R','E','A','K' };
vector<WORD> continueS{ 'C','O','N','T','I','N','U','E' };

void stopHook() {
	hook = false;
	xKeyDown = false;
	//Beep(800, 200);
}
void startHook() {
	if (hook) sendKey(VK_SPACE);
	hook = true;
	//Beep(300, 400);
}


map<char, WORD> mapKeys{
	//{'Q','Q'},  //  handled in consumers
	{'W',188},
	{'E',190},
	{'R','P'},
	{'T','Y'},
	{'Y','F'},
	{'U','G'},
	{'I','C'},
	{'O','R'},
	{'P','L'},
	{219, 191}, // [
	{221,VK_END}, // ]

	//{'A','A'},
	{'S','O'},
	{'D','E'},
	{'F','U'},
	{'G', 'I'},
	{'H','D'},
	{'J','H'},
	{'K','T'},
	{'L','N'},
	{186 ,'S'},  // ;
	//{222,187},

	{'Z',186},
	{'X','Q'},
	{'C','J'},
	{'V','K'},
	{'B','X'},
	{'N','B'},
	//{'M','M'},
	{188,'W'}, // ,
	{190,'V'}, // .
	{191, 'Z'},

	{187, 221}, // =
	{189, 219}, // -

	{VK_F1, VK_F2},
};
map<char, void (*)()> mapKeysFn{
	//{219, [] {sendSKey(52); }}, // [  to $
	{222, [] { cmsTrigger = true;  }},
	{'Q', [] {sendSKey(222); }}
};
map<char, void (*)()> mapConsumers{
	{VK_LMENU, [] { xKeyDown = true; }},
	{VK_CAPITAL, [] {sendCKey(VK_BACK); }},
	{VK_RMENU, [] {sendInputDown(VK_RCONTROL); } },
	{VK_RCONTROL, [] {sendInputDown(VK_LMENU); } },
	{VK_LSHIFT, [] { sendInputDown(VK_SHIFT); }}, // to control shift pressing without being sent to a thread and be able to send keyUp for shift
	{VK_RSHIFT, [] { sendInputDown(VK_SHIFT); }}

	/*{VK_LSHIFT, [] {if (!shiftDown) { shiftDown = true; sendInputDown(VK_SHIFT); } }},
	{VK_RSHIFT, [] {if (!shiftDown) { shiftDown = true; sendInputDown(VK_SHIFT); } }},*/
	/*{VK_LCONTROL, [] {if (!ctrlDown) { ctrlDown = true; sendInputDown(VK_CONTROL); } }},
	{VK_RCONTROL, [] {if (!ctrlDown) { ctrlDown = true; sendInputDown(VK_CONTROL); } }},*/

};
map<char, void (*)()> mapShiftedKeys{
	//{219, [] {sendUsKey(191); }}, // / 
	{222, [] { sendInputUp(VK_SHIFT); sendKeys(&trueS); }}, // 
	{'Q', [] {sendUsKey(222); }},  // '
	//{VK_TAB, [] {sendKey(VK_TAB); sendUsKey(VK_RIGHT); }},
	{VK_CAPITAL, [] {sendKey(VK_CAPITAL); }}
};
map<char, void (*)()> mapXKeys{
	{'Q', [] {sendKey(192); }  },
	{'W',[] {sendSKey(49); } },
	{'E',[] {sendKey(VK_UP);  if (GetKeyState(VK_MENU) & 0x8000) sendKey(VK_BACK); } },
	{'R',[] {sendSKey(51); } },
	{'T',[] {sendSKey(54); } },
	{'Y',[] {sendKey(220); } },
	{'U',[] {sendKey(VK_SPACE); sendSKey(49); sendKey(187); sendKey(187); sendKey(VK_SPACE); }},
	{'I',[] {sendKey(VK_SPACE); sendSKey(220); sendSKey(220); sendKey(VK_SPACE); }},
	{'O',[] {sendKeys(&falseS); } },
	{'P',[] {sendSKey(189); } },
	{219,[] {sendSKey(52); }}, // [
	{221,[] {sendSKey(53); } },

	{'A',[] {sendKey(VK_HOME); } },
	{'S',[] {sendKey(VK_LEFT); if (GetKeyState(VK_MENU) & 0x8000) sendKey(VK_BACK); } },
	{'D',[] {sendKey(VK_DOWN); if (GetKeyState(VK_MENU) & 0x8000) sendKey(VK_BACK); } },
	{'F',[] {sendKey(VK_RIGHT); if (GetKeyState(VK_MENU) & 0x8000) sendKey(VK_BACK); } },
	{'G',[] {sendKey(VK_SUBTRACT); } }, // -
	{'H',[] {sendKey(VK_ADD); } },
	{'J',[] {sendSKey(57); } }, // (
	{'K',[] {sendSKey(219); } }, // {
	{'L',[] {sendKey(219); } }, // [
	{186 ,[] {sendKey(VK_SPACE); sendKey(187); sendKey(187); sendKey(187); sendKey(VK_SPACE); }},  // ;
	{222, [] {sendCKey(VK_DELETE); } }, //  ` 

	{'Z',[] {stopHook(); }},
	{'X',[] {sendSKey(220); } },
	{'C',[] {sendKey(VK_SUBTRACT); sendSKey(190); }}, // ->
	{'V',[] {sendSKey(56); } },
	{'B',[] {sendSKey(55); } },
	{'N',[] {sendKey(VK_SPACE); sendSKey(55); sendSKey(55); sendKey(VK_SPACE); }},
	{'M',[] {sendSKey(48); } },
	{188,[] {sendSKey(221); } },
	{190,[] {sendKey(221); } },
	{191, [] {sendSKey(50); } },

	{VK_CAPITAL,[] {sendInputDown(VK_LMENU); } },
	{VK_RMENU, [] {sendInputDown(VK_RCONTROL); }},
	{VK_RETURN,[] {sendKeys(&ret); } },
	{VK_LMENU, [] { xKeyDown = true; }},
	{VK_LSHIFT, [] { sendInputDown(VK_LSHIFT); }},
	{VK_SPACE, [] { startHook(); }},
};
//map<char, void (*)()> mapCtrlKeys{
//	{191, [] {sendKey(191); }}
//};
map<char, void (*)()> mapKeyUp{
	{222, [] { if (cmsTrigger) {
		sendKey(187);  cmsTrigger = false;
		 }
		else {
			sendCMSUp();
		}
	}},
	{VK_LMENU, [] {xKeyDown = false; if (cmsDown)sendCMSUp(); sendInputUp(VK_MENU); }},
	{VK_CAPITAL, [] {sendInputUp(VK_LMENU);  }},
	{VK_RMENU, [] {sendInputUp(VK_RCONTROL); } },
	{VK_RCONTROL, [] {sendInputUp(VK_LMENU); } },

	{VK_LSHIFT, [] { sendInputUp(VK_SHIFT); }},
	{VK_RSHIFT, [] { sendInputUp(VK_SHIFT); } },
	/*{VK_LCONTROL, [] { ctrlDown = false; sendInputUp(VK_CONTROL); } },
	{VK_RCONTROL, [] { ctrlDown = false; sendInputUp(VK_CONTROL); } */
};

