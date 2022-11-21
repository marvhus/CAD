#include "keybindings.hpp"
#include "olcPixelGameEngine.h"

olc::HWButton Keybindings::create(olc::PixelGameEngine *pge)
{
    return pge->GetKey(olc::Key::W);
}

olc::HWButton Keybindings::move   (olc::PixelGameEngine *pge)
{ 
    return pge->GetKey(olc::Key::E);
}

olc::HWButton Keybindings::hud    (olc::PixelGameEngine *pge)
{ 
    return pge->GetKey(olc::Key::S);
}

olc::HWButton Keybindings::exit   (olc::PixelGameEngine *pge)
{ 
    return pge->GetKey(olc::Key::ESCAPE);
}

olc::HWButton Keybindings::line   (olc::PixelGameEngine *pge)
{ 
    return pge->GetKey(olc::Key::K1);
}

olc::HWButton Keybindings::box    (olc::PixelGameEngine *pge)
{ 
    return pge->GetKey(olc::Key::K2);
}

olc::HWButton Keybindings::circle (olc::PixelGameEngine *pge)
{ 
    return pge->GetKey(olc::Key::K3);
}

olc::HWButton Keybindings::spline (olc::PixelGameEngine *pge)
{ 
    return pge->GetKey(olc::Key::K4);
}

olc::HWButton Keybindings::select (olc::PixelGameEngine *pge)
{ 
    return pge->GetMouse(0);
}

olc::HWButton Keybindings::pan    (olc::PixelGameEngine *pge)
{ 
    return pge->GetMouse(1);
}

bool Keybindings::zoomIn (olc::PixelGameEngine *pge) 
{ 
    return pge->GetMouseWheel() > 0 
        || pge->GetKey(olc::Key::Q).bHeld; 
}

bool Keybindings::zoomOut(olc::PixelGameEngine *pge) 
{ 
    return pge->GetMouseWheel() < 0 
        || pge->GetKey(olc::Key::A).bHeld; 
}
