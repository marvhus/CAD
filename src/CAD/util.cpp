#include "../CAD.hpp"

// Convert coordinates from World Space -> Screen Space
void CAD::WorldToScreen(const olc::vf2d &v, int &nScreenX, int &nScreenY)
{
    nScreenX = (int)((v.x - vOffset.x) * fScale);
    nScreenY = (int)((v.y - vOffset.y) * fScale);
}

// Convert coordinates from Screen Space -> World Space
void CAD::ScreenToWorld(int nScreenX, int nScreenY, olc::vf2d &v) 
{
    v.x = (float)(nScreenX) / fScale + vOffset.x;
    v.y = (float)(nScreenY) / fScale + vOffset.y;
}
