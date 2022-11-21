#include "../CAD.hpp"

void CAD::DisplayMode()
{
    DrawString(10, ScreenHeight() - 15, "Action: " + ActionToString(currentAction), olc::YELLOW);
    DrawString(10, ScreenHeight() - 35, "Shape: " + ShapeToString(currentShape), olc::YELLOW);
}

void CAD::DrawVisibleWorld()
{
    int sx, sy;
    int ex, ey;

    // Get visible world
    olc::vf2d vWorldTopLeft, vWorldBottomRight;
    ScreenToWorld(0, 0, vWorldTopLeft);
    ScreenToWorld(ScreenWidth(), ScreenHeight(), vWorldBottomRight);

    // Add some padding
    vWorldTopLeft.x = floor(vWorldTopLeft.x);
    vWorldTopLeft.y = floor(vWorldTopLeft.y);
    vWorldBottomRight.x = ceil(vWorldBottomRight.x);
    vWorldBottomRight.y = ceil(vWorldBottomRight.y);

    // Draw Grid dots
    DrawGridDots(sx, sy ,vWorldTopLeft, vWorldBottomRight);

    // Draw World Axis
    DrawWorldAxis(sx, sy, ex, ey, vWorldTopLeft, vWorldBottomRight);

    // Draw Cursor
    DrawCursor(sx, sy);

    // Draw Cursor Position
    DrawCursorPosition();
}

void CAD::DrawGridDots(int sx, int sy, olc::vf2d vWorldTopLeft, olc::vf2d vWorldBottomRight) 
{
    for (float x = vWorldTopLeft.x; x < vWorldBottomRight.x; x += fGrid)
        for (float y = vWorldTopLeft.y; y < vWorldBottomRight.y; y += fGrid)
        {
            WorldToScreen({ x, y }, sx, sy);
            Draw(sx, sy, olc::BLUE);
        }
}

void CAD::DrawWorldAxis(int &sx, int &sy, int &ex, int &ey, olc::vf2d vWorldTopLeft, olc::vf2d vWorldBottomRight)
{
    WorldToScreen({ 0, vWorldTopLeft.y }, sx, sy);
    WorldToScreen({ 0, vWorldBottomRight.y }, ex, ey);

    DrawLine(sx, sy, ex, ey, olc::GREY, 0xF0F0F0F0);

    WorldToScreen({ vWorldTopLeft.x, 0 }, sx, sy);
    WorldToScreen({ vWorldBottomRight.x, 0 }, ex, ey);

    DrawLine(sx, sy, ex, ey, olc::GREY, 0xF0F0F0F0);
}

void CAD::DrawCursorPosition()
{
    DrawString(
        10, 10,
        "X=" + std::to_string(vCursor.x)
      + ", Y=" + std::to_string(vCursor.y),
        olc::YELLOW
    );
}

void CAD::DrawCursor(int sx, int sy) 
{
    WorldToScreen(vCursor, sx, sy);
    DrawCircle(sx, sy, 3, olc::YELLOW);
}
