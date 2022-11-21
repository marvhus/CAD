#include "../shapes.hpp"

sCircle::sCircle()
{
    nMaxNodes = 2;
    vecNodes.reserve(nMaxNodes);
}

void sCircle::DrawYourself(olc::PixelGameEngine *pge, bool showHUD) 
{
    float fRadius = (vecNodes[0].pos - vecNodes[1].pos).mag();

    int sx, sy, ex, ey;
    WorldToScreen(vecNodes[0].pos, sx, sy);
    WorldToScreen(vecNodes[1].pos, ex, ey);
    if (showHUD) 
    {
        pge->DrawLine(sx, sy, ex, ey, col, 0xFF00FF00);
    }
    pge->DrawCircle(sx, sy, fRadius * fWorldScale, col);
}
