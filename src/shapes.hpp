#pragma once

#include "olcPixelGameEngine.h"

#include <string>

// Shape selection states
enum Shape {
    LINE,
    BOX,
    CIRCLE,
    SPLINE,
};

// Get string name of shape
std::string ShapeToString(Shape shape);

struct sShape;

struct sNode 
{
    sShape *parrent;
    olc::vf2d pos;
};

// ========== Base Shape ==========
struct sShape
{
    std::vector<sNode> vecNodes;
    uint32_t nMaxNodes = 0;
    olc::Pixel col = olc::GREEN;
    static float fWorldScale;
    static olc::vf2d vWorldOffset;
    // Convert coordinates from World Space -> Screen Space
    void WorldToScreen(const olc::vf2d &v, int &nScreenX, int &nScreenY);
    virtual void DrawYourself(olc::PixelGameEngine *pge, bool showHUD) = 0;
    sNode* GetNextNode(const olc::vf2d &p);
    sNode* HitNode(olc::vf2d &p);
    void DrawNodes(olc::PixelGameEngine *pge, bool showHUD);
};

// ========== Line Shape ==========
struct sLine : public sShape
{
    sLine(); 
    void DrawYourself(olc::PixelGameEngine *pge, bool showHUD) override;
};

// ========== Box Shape ==========
struct sBox : public sShape
{
    sBox();
    void DrawYourself(olc::PixelGameEngine *pge, bool showHUD) override;
};

// ========== Circle Shape ==========
struct sCircle : public sShape
{
    sCircle();
    void DrawYourself(olc::PixelGameEngine *pge, bool showHUD) override;
};

// ========== Curve Shape ==========
struct sCurve : public sShape
{
    sCurve();
    void DrawYourself(olc::PixelGameEngine *pge, bool showHUD) override;
};
