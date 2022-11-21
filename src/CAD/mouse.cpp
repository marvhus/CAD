#include "../CAD.hpp"

void CAD::HandlePan(olc::vf2d vMouse)
{
    if (keybindings.pan(this).bPressed)
    {
        vStartPan = vMouse;
    }

    if (keybindings.pan(this).bHeld)
    {
        vOffset -= (vMouse - vStartPan) / fScale;
        vStartPan = vMouse;
    }
}

void CAD::HandleZoom(olc::vf2d vMouse, olc::vf2d &vMouseAfterZoom)
{
    olc::vf2d vMouseBeforeZoom;
    ScreenToWorld((int)vMouse.x, (int)vMouse.y, vMouseBeforeZoom);

    if (keybindings.zoomIn(this))
    {
        fScale *= 1.1f;
    }
    if (keybindings.zoomOut(this))
    {
        fScale *= 0.9f;
    }

    ScreenToWorld((int)vMouse.x, (int)vMouse.y, vMouseAfterZoom);
    vOffset += (vMouseBeforeZoom - vMouseAfterZoom);
}

void CAD::HandleCursor(olc::vf2d vMouse) 
{
    vCursor = {
        floorf((vMouse.x + 0.5f) * fGrid),
        floorf((vMouse.y + 0.5f) * fGrid)
    };
}

void CAD::HandleMouse()
{
    olc::vf2d vMouse = {
        (float)GetMouseX(),
        (float)GetMouseY()
    };

    // Paning
    HandlePan(vMouse);

    // Zooming
    olc::vf2d vMouseAfterZoom;
    HandleZoom(vMouse, vMouseAfterZoom);

    // Handle cursor
    HandleCursor(vMouseAfterZoom);
}
