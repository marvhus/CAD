#include "../shapes.hpp"

sCurve::sCurve()
{
    nMaxNodes = 3;
    vecNodes.reserve(nMaxNodes);
}

void sCurve::DrawYourself(olc::PixelGameEngine *pge, bool showHUD)
{
    int sx, sy, ex, ey;
        
    // Can draw line from first to second
    WorldToScreen(vecNodes[0].pos, sx, sy);
    WorldToScreen(vecNodes[1].pos, ex, ey);
    if (showHUD) 
    {
        pge->DrawLine(sx, sy, ex, ey, col, 0xFF00FF00);
    }

    if (vecNodes.size() == 3) 
    {
        // Can draw second structural line
        WorldToScreen(vecNodes[1].pos, sx, sy);
        WorldToScreen(vecNodes[2].pos, ex, ey);
        if (showHUD)
        {
            pge->DrawLine(sx, sy, ex, ey, col, 0xFF00FF00);
        }

        // Add bezier curve
        olc::vf2d op = vecNodes[0].pos;
        olc::vf2d np = op;
        for (float t = 0; t < 1.0f; t += 0.01f)
        {
            np = (1 - t) * (1 - t) * vecNodes[0].pos + 2 * (1 - t) * t * vecNodes[1].pos + t * t * vecNodes[2].pos;
            WorldToScreen(op, sx, sy);
            WorldToScreen(np, ex, ey);
            pge->DrawLine(sx, sy, ex, ey, col);
            op = np;
        }
    }
}
