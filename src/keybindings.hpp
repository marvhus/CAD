#pragma once

#include "olcPixelGameEngine.h"

struct Keybindings
{
    olc::HWButton create (olc::PixelGameEngine *pge);
    olc::HWButton move   (olc::PixelGameEngine *pge);
    olc::HWButton hud    (olc::PixelGameEngine *pge);
    olc::HWButton exit   (olc::PixelGameEngine *pge);
    olc::HWButton line   (olc::PixelGameEngine *pge);
    olc::HWButton box    (olc::PixelGameEngine *pge);
    olc::HWButton circle (olc::PixelGameEngine *pge);
    olc::HWButton spline (olc::PixelGameEngine *pge);
    olc::HWButton select (olc::PixelGameEngine *pge);
    olc::HWButton pan    (olc::PixelGameEngine *pge);
    bool zoomIn (olc::PixelGameEngine *pge);
    bool zoomOut(olc::PixelGameEngine *pge);
};

