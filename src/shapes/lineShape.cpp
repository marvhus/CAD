#include "../shapes.hpp"

sLine::sLine()
{
    nMaxNodes = 2;
    vecNodes.reserve(nMaxNodes);
}

void sLine::DrawYourself(olc::PixelGameEngine *pge, bool showHUD)
{
    int sx, sy, ex, ey;
    WorldToScreen(vecNodes[0].pos, sx, sy);
    WorldToScreen(vecNodes[1].pos, ex, ey);
    pge->DrawLine(sx, sy, ex, ey, col);
}
