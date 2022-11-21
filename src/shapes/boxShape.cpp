#include "../shapes.hpp"

sBox::sBox()
{
    nMaxNodes = 2;
    vecNodes.reserve(nMaxNodes);
}


void sBox::DrawYourself(olc::PixelGameEngine *pge, bool showHUD)
{
    int sx, sy, ex, ey;
    WorldToScreen(vecNodes[0].pos, sx, sy);
    WorldToScreen(vecNodes[1].pos, ex, ey);
    pge->DrawRect(sx, sy, ex - sx, ey - sy, col);
}
