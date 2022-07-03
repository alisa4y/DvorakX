#pragma once
#include <iostream>
#include <map>
#include "sendKey.h"

using namespace std;

bool hook = true;
bool xKeyDown = false;
bool shiftDown = false;
bool ctrlDown = false;
vector<WORD> ret{ 'R','E','T','U','R','N',VK_SPACE };

void stopHook() {
	hook = false;
	xKeyDown = false;
	//Beep(800, 200);
}
void startHook() {
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
	{221,VK_END}, // [

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
	{222,187},

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

};
map<char, void (*)()> mapSpecialKeys{
	//{219, [] {sendSKey(52); }}, // [  to $
	{'Q', [] {sendSKey(222); }}
};
map<char, void (*)()> mapConsumers{
	{VK_LMENU, [] {xKeyDown = true; }},
	{VK_CAPITAL, [] {sendCKey(VK_BACK); }},
	{VK_RMENU, [] {sendInputDown(VK_RCONTROL); } },
	{VK_RCONTROL, [] {sendInputDown(VK_LMENU); } },
	{VK_LSHIFT, [] {if (!shiftDown) { shiftDown = true; sendInputDown(VK_SHIFT); } }},
	{VK_RSHIFT, [] {if (!shiftDown) { shiftDown = true; sendInputDown(VK_SHIFT); } }},
	/*{VK_LCONTROL, [] {if (!ctrlDown) { ctrlDown = true; sendInputDown(VK_CONTROL); } }},
	{VK_RCONTROL, [] {if (!ctrlDown) { ctrlDown = true; sendInputDown(VK_CONTROL); } }},*/

};
map<char, void (*)()> mapShiftedKeys{
	//{219, [] {sendUsKey(191); }}, // / 
	{222, [] {sendKey(191); }},
	{'Q', [] {sendUsKey(222); }},
	{VK_CAPITAL, [] {sendKey(VK_CAPITAL); }}
};
map<char, void (*)()> mapXKeys{
	{'Q', [] {sendKey(192); }  },
	{'W',[] {sendSKey(49); } },
	{'E',[] {sendKey(VK_UP); } },
	{'R',[] {sendSKey(51); } },
	{'T',[] {sendSKey(54); } },
	{'Y',[] {sendKey(220); } },
	{'U',[] {sendSKey(49); sendKey(187); sendKey(187); }},
	{'I',[] {sendSKey(220); sendSKey(220); } },
	{'O',[] {sendKey(187); sendSKey(190); } },
	{'P',[] {sendSKey(189); } },
	{219,[] {sendSKey(52); }}, // [
	{221,[] {sendSKey(53); } },

	{'A',[] {sendKey(VK_HOME); } },
	{'S',[] {sendKey(VK_LEFT); } },
	{'D',[] {sendKey(VK_DOWN); } },
	{'F',[] {sendKey(VK_RIGHT); } },
	{'G',[] {sendKey(VK_SUBTRACT); } }, // -
	{'H',[] {sendKey(VK_ADD); } },
	{'J',[] {sendSKey(57); } },
	{'K',[] {sendSKey(219); } }, // {
	{'L',[] {sendKey(219); } }, // [
	{186 ,[] {sendKey(187); sendKey(187); sendKey(187); } },  // ;
	{222, [] {sendCKey(VK_DELETE); } }, //  ` 

	{'Z',[] {stopHook(); }},
	{'X',[] {sendSKey(220); } },
	{'C',[] { sendKey(VK_SUBTRACT); sendSKey(190); }},
	{'V',[] {sendSKey(56); } },
	{'B',[] {sendSKey(55); } },
	{'N',[] {sendSKey(55); sendSKey(55); } },
	{'M',[] {sendSKey(48); } },
	{188,[] {sendSKey(221); } },
	{190,[] {sendKey(221); } },
	{191, [] {sendSKey(50); } }, //  


	{VK_CAPITAL,[] {sendInputDown(VK_LMENU); } },
	{VK_RMENU, [] {sendInputDown(VK_RCONTROL); }},
	{VK_RETURN,[] {sendKeys(&ret); } },

};
//map<char, void (*)()> mapCtrlKeys{
//	{191, [] {sendKey(191); }}
//};
map<char, void (*)()> mapKeyUp{
	{VK_LMENU, [] {xKeyDown = false; sendInputUp(VK_MENU); }},
	{VK_CAPITAL, [] {sendInputUp(VK_LMENU);  }},
	{VK_RMENU, [] {sendInputUp(VK_RCONTROL); } },
	{VK_RCONTROL, [] {sendInputUp(VK_LMENU); } },

	{VK_LSHIFT, [] { shiftDown = false; sendInputUp(VK_SHIFT); }},
	{VK_RSHIFT, [] { shiftDown = false; sendInputUp(VK_SHIFT); } },
	/*{VK_LCONTROL, [] { ctrlDown = false; sendInputUp(VK_CONTROL); } },
	{VK_RCONTROL, [] { ctrlDown = false; sendInputUp(VK_CONTROL); } },*/

};
