#include "../CAD.hpp"

CAD::CAD()
{
	sAppName = "olcPGE test";
}

bool CAD::OnUserCreate()
{
    vOffset = {
        (float)(-ScreenWidth()) / 2 / fScale,
        (float)(-ScreenHeight()) / 2 / fScale
    };
	return true;
}

bool CAD::OnUserUpdate(float fElapsedTime)
{
    // Clear Screen
    Clear(olc::DARK_BLUE);

    // toggle HUD
    if (keybindings.hud(this).bPressed)
    {
        showHUD = !showHUD;
    }

    // Handle mouse input
    HandleMouse();

    // Handle all the shape drawing, creating, and modifying
    HandleShapes();

    if (showHUD)
    {
        // Draw the visible world
        DrawVisibleWorld();
        // Tell the user what mode/action they are in/doing
        DisplayMode();
    }

    // Exit when escape has been pressed
	return !keybindings.exit(this).bPressed;
}
