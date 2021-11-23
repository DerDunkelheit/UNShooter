#pragma once

class GameDebuggerNew
{
public:
	bool static  IsDebugWeaponEnable();
	bool static  IsDebugInteractionEnable();
};

namespace ConsoleDebug
{
	bool IsDebugHighlightDrawingEnable();
}