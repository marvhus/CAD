#pragma once

#include "olcPixelGameEngine.h"
#include "shapes.hpp"
#include "actions.hpp"
#include "keybindings.hpp"

class CAD : public olc::PixelGameEngine
{
public:
	CAD();
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

private:
    olc::vf2d vOffset = { 0.0f, 0.0f };
    olc::vf2d vStartPan = { 0.0f, 0.0f };
    float fScale = 10.0f;
    float fGrid = 1.0f;
    sShape* tempShape = nullptr;
    std::list<sShape*> listShapes;
    sNode *selectedNode = nullptr;
    olc::vf2d vCursor = { 0, 0 };
    Action currentAction = Action::NONE;
    Shape currentShape = Shape::LINE;
    Keybindings keybindings = Keybindings();
    bool showHUD = true;

    // CAD/util.cpp
    void WorldToScreen(const olc::vf2d &v, int &nScreenX, int &nScreenY);
    void ScreenToWorld(int nScreenX, int nScreenY, olc::vf2d &v);
    // CAD/mouse.cpp
    void HandlePan(olc::vf2d vMouse);
    void HandleZoom(olc::vf2d vMouse, olc::vf2d &vMouseAfterZoom);
    void HandleCursor(olc::vf2d vMouse);
    void HandleMouse();
    // CAD/hud.cpp
    void DrawCursor(int sx, int sy);
    void DrawCursorPosition();
    void DrawGridDots(int sx, int sy, olc::vf2d vWorldTopLeft, olc::vf2d vWorldBottomRight);
    void DrawWorldAxis(int &sx, int &sy, int &ex, int &ey, olc::vf2d vWorldTopLeft, olc::vf2d vWorldBottomRight);
    void DrawVisibleWorld();
    void DisplayMode();
    // CAD/shapes.cpp
    void HandleShapes();
};
