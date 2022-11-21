#include "../shapes.hpp"

#include <string>

std::string ShapeToString(Shape shape)
{
    switch (shape)
    {
        case Shape::LINE:
            return "Line";
        case Shape::BOX:
            return "Box";
        case Shape::CIRCLE:
            return "Circle";
        case Shape::SPLINE:
            return "Spline";
        default:
            return "None";
    }
}

void sShape::WorldToScreen(const olc::vf2d &v, int &nScreenX, int &nScreenY)
{
    nScreenX = (int)((v.x - vWorldOffset.x) * fWorldScale);
    nScreenY = (int)((v.y - vWorldOffset.y) * fWorldScale);
}

sNode* sShape::GetNextNode(const olc::vf2d &p)
{
    if (vecNodes.size() == nMaxNodes)
        return nullptr; // Shape is complete so no new nodes to be issued

    // else create new node and add to shapes node vector
    sNode n;
    n.parrent = this;
    n.pos = p;
    vecNodes.push_back(n);
    return &vecNodes[vecNodes.size() - 1];
}

sNode* sShape::HitNode(olc::vf2d &p)
{
    for (auto &n : vecNodes)
    {
        if ((p - n.pos).mag() < 0.01f)
            return &n;
    }

    return nullptr;
}

void sShape::DrawNodes(olc::PixelGameEngine *pge, bool showHUD)
{
    if (!showHUD) { return; }
    for (auto &n : vecNodes)
    {
        int sx, sy;
        WorldToScreen(n.pos, sx, sy);
        pge->FillCircle(sx, sy, 2, olc::RED); 
    }
}

float sShape::fWorldScale = 1.0f;
olc::vf2d sShape::vWorldOffset = { 0, 0 };

