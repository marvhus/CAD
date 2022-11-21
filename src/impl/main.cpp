#include <string>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <iostream>

enum Action
{
    NONE,
    MOVE_NODE,
    CREATE_SHAPE
};
std::string ActionToString(Action action)
{

    switch (action)
    {
        case Action::CREATE_SHAPE:
            return "Create Shape";
        case Action::MOVE_NODE:
            return "Move Node";
        default:
            return "None";
    }
}

enum Shape
{
    LINE,
    BOX,
    CIRCLE,
    SPLINE,
};
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

struct Keybindings
{
    static const olc::Key create  = olc::Key::W;
    static const olc::Key move    = olc::Key::E;
    static const olc::Key exit    = olc::Key::ESCAPE;
    static const olc::Key line    = olc::Key::K1;
    static const olc::Key box     = olc::Key::K2;
    static const olc::Key cicle   = olc::Key::K3;
    static const olc::Key spline  = olc::Key::K4;
    static const uint32_t select  = 0;
    static const uint32_t pan     = 1;
    static const olc::Key zoomIn  = olc::Key::Q;
    static const olc::Key zoomOut = olc::Key::A;
    bool isZoomingIn(olc::PixelGameEngine *pge)
    {
        return pge->GetMouseWheel() > 0;
    }
    bool isZoomingOut(olc::PixelGameEngine *pge)
    {
        return pge->GetMouseWheel() < 0;
    }
};

struct sShape;

struct sNode 
{
    sShape *parrent;
    olc::vf2d pos;
};

struct sShape
{
    std::vector<sNode> vecNodes;
    uint32_t nMaxNodes = 0;
    olc::Pixel col = olc::GREEN;

    static float fWorldScale;
    static olc::vf2d vWorldOffset;

    // Convert coordinates from World Space -> Screen Space
    void WorldToScreen(const olc::vf2d &v, int &nScreenX, int &nScreenY)
    {
        nScreenX = (int)((v.x - vWorldOffset.x) * fWorldScale);
        nScreenY = (int)((v.y - vWorldOffset.y) * fWorldScale);
    }

    virtual void DrawYourself(olc::PixelGameEngine *pge) = 0;

    sNode* GetNextNode(const olc::vf2d &p)
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

    sNode* HitNode(olc::vf2d &p)
    {
        for (auto &n : vecNodes)
        {
            if ((p - n.pos).mag() < 0.01f)
                return &n;
        }

        return nullptr;
    }

    void DrawNodes(olc::PixelGameEngine *pge)
    {
        for (auto &n : vecNodes)
        {
            int sx, sy;
            WorldToScreen(n.pos, sx, sy);
            pge->FillCircle(sx, sy, 2, olc::RED); 
        }
    }
};

float sShape::fWorldScale = 1.0f;
olc::vf2d sShape::vWorldOffset = { 0, 0 };






struct sLine : public sShape
{
    sLine() 
    {
        nMaxNodes = 2;
        vecNodes.reserve(nMaxNodes);
        // We're gonna be getting pointers to vector elements
		// though we have defined already how much capacity our vector will have. This makes
		// it safe to do this as we know the vector will not be maniupulated as we add nodes
		// to it. Is this bad practice? Possibly, but as with all thing programming, if you
		// know what you are doing, it's ok :D
    }

    void DrawYourself(olc::PixelGameEngine *pge) override
    {
        int sx, sy, ex, ey;
        WorldToScreen(vecNodes[0].pos, sx, sy);
        WorldToScreen(vecNodes[1].pos, ex, ey);
        pge->DrawLine(sx, sy, ex, ey, col);
    }
};






struct sBox : public sShape
{
    sBox()
    {
        nMaxNodes = 2;
        vecNodes.reserve(nMaxNodes);
    }

    void DrawYourself(olc::PixelGameEngine *pge) override
    {
        int sx, sy, ex, ey;
        WorldToScreen(vecNodes[0].pos, sx, sy);
        WorldToScreen(vecNodes[1].pos, ex, ey);
        pge->DrawRect(sx, sy, ex - sx, ey - sy, col);
    }
};







struct sCircle : public sShape
{
    sCircle()
    {
        nMaxNodes = 2;
        vecNodes.reserve(nMaxNodes);
    }

    void DrawYourself(olc::PixelGameEngine *pge) override
    {
        float fRadius = (vecNodes[0].pos - vecNodes[1].pos).mag();

        int sx, sy, ex, ey;
        WorldToScreen(vecNodes[0].pos, sx, sy);
        WorldToScreen(vecNodes[1].pos, ex, ey);
        pge->DrawLine(sx, sy, ex, ey, col, 0xFF00FF00);
        pge->DrawCircle(sx, sy, fRadius * fWorldScale, col);
    }
};





struct sCurve : public sShape
{
    sCurve()
    {
        nMaxNodes = 3;
        vecNodes.reserve(nMaxNodes);
    }

    void DrawYourself(olc::PixelGameEngine *pge) override
    {
        int sx, sy, ex, ey;

        // Can draw line from first to second
        WorldToScreen(vecNodes[0].pos, sx, sy);
        WorldToScreen(vecNodes[1].pos, ex, ey);
        pge->DrawLine(sx, sy, ex, ey, col, 0xFF00FF00);

        if (vecNodes.size() == 3) 
        {
            // Can draw second structural line
            WorldToScreen(vecNodes[1].pos, sx, sy);
            WorldToScreen(vecNodes[2].pos, ex, ey);
            pge->DrawLine(sx, sy, ex, ey, col, 0xFF00FF00);

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
};






class olcPGEtest : public olc::PixelGameEngine
{
public:
	olcPGEtest()
	{
		sAppName = "olcPGE test";
	}

private:
    olc::vf2d vOffset = { 0.0f, 0.0f };
    olc::vf2d vStartPan = { 0.0f, 0.0f };
    float fScale = 10.0f;
    float fGrid = 1.0f;

    sShape* tempShape = nullptr;
    std::list<sShape*> listShapes;
    sNode *selectedNode = nullptr;

    olc::vf2d vCursor = { 0, 0 };

    Action currentAction = Action::NONE;
    Shape currentShape = Shape::LINE;

    Keybindings keybindings = Keybindings();







    // Convert coordinates from World Space -> Screen Space
    void WorldToScreen(const olc::vf2d &v, int &nScreenX, int &nScreenY)
    {
        nScreenX = (int)((v.x - vOffset.x) * fScale);
        nScreenY = (int)((v.y - vOffset.y) * fScale);
    }

    // Convert coordinates from Screen Space -> World Space
    void ScreenToWorld(int nScreenX, int nScreenY, olc::vf2d &v) 
    {
        v.x = (float)(nScreenX) / fScale + vOffset.x;
        v.y = (float)(nScreenY) / fScale + vOffset.y;
    }

    // Handle paning
    void HandlePan(olc::vf2d vMouse)
    {
        if (GetMouse(keybindings.pan).bPressed)
        {
            vStartPan = vMouse;
        }

        if (GetMouse(keybindings.pan).bHeld)
        {
            vOffset -= (vMouse - vStartPan) / fScale;
            vStartPan = vMouse;
        }
    }

    // Handle zooming
    void HandleZoom(olc::vf2d vMouse, olc::vf2d &vMouseAfterZoom)
    {
        olc::vf2d vMouseBeforeZoom;
        ScreenToWorld((int)vMouse.x, (int)vMouse.y, vMouseBeforeZoom);

        if (GetKey(keybindings.zoomIn).bHeld || keybindings.isZoomingIn(this))
        {
            fScale *= 1.1f;
        }
        if (GetKey(keybindings.zoomOut).bHeld || keybindings.isZoomingOut(this))
        {
            fScale *= 0.9f;
        }

        ScreenToWorld((int)vMouse.x, (int)vMouse.y, vMouseAfterZoom);
        vOffset += (vMouseBeforeZoom - vMouseAfterZoom);
    }

    // Handle cursor
    void HandleCursor(olc::vf2d vMouse) {
        vCursor = {
            floorf((vMouse.x + 0.5f) * fGrid),
            floorf((vMouse.y + 0.5f) * fGrid)
        };
    }

    // Handle mouse input
    void HandleMouse()
    {
        olc::vf2d vMouse = {
            (float)GetMouseX(),
            (float)GetMouseY()
        };

        // Paning
        HandlePan(vMouse);

        // Zooming
        olc::vf2d vMouseAfterZoom;
        HandleZoom(vMouse, vMouseAfterZoom);

        // Handle cursor
        HandleCursor(vMouseAfterZoom);
    }

    void DrawCursor(int sx, int sy) 
    {
        WorldToScreen(vCursor, sx, sy);
        DrawCircle(sx, sy, 3, olc::YELLOW);
    }

    void DrawCursorPosition()
    {
        DrawString(
            10, 10,
            "X=" + std::to_string(vCursor.x)
            + ", Y=" + std::to_string(vCursor.y),
            olc::YELLOW
        );
    }

    void DrawGridDots(int sx, int sy, olc::vf2d vWorldTopLeft, olc::vf2d vWorldBottomRight) 
    {
       for (float x = vWorldTopLeft.x; x < vWorldBottomRight.x; x += fGrid)
           for (float y = vWorldTopLeft.y; y < vWorldBottomRight.y; y += fGrid)
           {
               WorldToScreen({ x, y }, sx, sy);
               Draw(sx, sy, olc::BLUE);
           }
    }

    void DrawWorldAxis(int &sx, int &sy, int &ex, int &ey, olc::vf2d vWorldTopLeft, olc::vf2d vWorldBottomRight)
    {
        WorldToScreen({ 0, vWorldTopLeft.y }, sx, sy);
        WorldToScreen({ 0, vWorldBottomRight.y }, ex, ey);

        DrawLine(sx, sy, ex, ey, olc::GREY, 0xF0F0F0F0);

        WorldToScreen({ vWorldTopLeft.x, 0 }, sx, sy);
        WorldToScreen({ vWorldBottomRight.x, 0 }, ex, ey);

        DrawLine(sx, sy, ex, ey, olc::GREY, 0xF0F0F0F0);
    }

    void DrawVisibleWorld()
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

    void HandleShapes()
    {

        // ============= SHAPE SELECTION ============
        if (GetKey(keybindings.line).bPressed) 
        {
            currentShape = Shape::LINE;
        }

        if (GetKey(keybindings.box).bPressed) 
        {
            currentShape = Shape::BOX;
        }
        if (GetKey(keybindings.cicle).bPressed) 
        {
            currentShape = Shape::CIRCLE;
        }
        if (GetKey(keybindings.spline).bPressed) 
        {
            currentShape = Shape::SPLINE;
        }

        // ============= CREATE SHAPE ===============
        if (GetKey(keybindings.create).bPressed && currentAction == Action::NONE)
        {
            switch (currentShape)
            {
                case Shape::LINE:
                    tempShape = new sLine();
                    break;
                case Shape::BOX:
                    tempShape = new sBox();
                    break;
                case Shape::CIRCLE:
                    tempShape = new sCircle();
                    break;
                case Shape::SPLINE:
                    tempShape = new sCurve();
                    break;
            }

            // Place first node at location of keypress
            selectedNode = tempShape->GetNextNode(vCursor);

            // Get seccond node
            selectedNode = tempShape->GetNextNode(vCursor);

            currentAction = Action::CREATE_SHAPE;
        }

        // ============ MOVE NODE ===================
        if (GetKey(keybindings.move).bReleased && currentAction == NONE)
        {
            //std::cout << "M pressed" << std::endl;
            tempShape == nullptr;
            for (auto &shape : listShapes)
            {
                selectedNode = shape->HitNode(vCursor);
                if (selectedNode != nullptr) {
                    //std::cout << "Found node" << std::endl;
                    tempShape = shape;
                    tempShape->col = olc::GREEN;
                    currentAction = Action::MOVE_NODE;
                    break;
                }
            }
        }

        // ============ SNAP NODE TO CURSOR ===========
        if (currentAction != Action::NONE)
        {
            selectedNode->pos = vCursor;
        }

        // ============ ADD NODE TO SHAPE, AND COMPLETE SHAPE ============
        if (GetMouse(keybindings.select).bPressed && currentAction != Action::NONE) {
            selectedNode = tempShape->GetNextNode(vCursor);
            if (selectedNode == nullptr)
            {
                tempShape->col = olc::WHITE;
                if (currentAction == Action::CREATE_SHAPE) {
                    listShapes.push_back(tempShape);
                }
                currentAction = Action::NONE;
            }
        }

        // ============ UPDATE SHAPE STATIC VALUES ======================
        // Update shape translation coefficients
        sShape::fWorldScale = fScale;
        sShape::vWorldOffset = vOffset;

        // ============= DRAW ALL SHAPES ========================
        // Draw all existing shapes
        for (auto &shape : listShapes)
        {
            shape->DrawYourself(this);
            shape->DrawNodes(this);
        }

        // ============== DRAW TEMP SHAPE ===================
        // Draw the wip shape.. if there is one
        if (currentAction != Action::NONE) {
            tempShape->DrawYourself(this);
            tempShape->DrawNodes(this);
        }
    }

    // Tell the user what mode they are in at the moment
    void DisplayMode()
    {
        DrawString(10, ScreenHeight() - 15, "Action: " + ActionToString(currentAction), olc::YELLOW);
        DrawString(10, ScreenHeight() - 35, "Shape: " + ShapeToString(currentShape), olc::YELLOW);
    }

public:
	bool OnUserCreate() override
	{

        vOffset = {
            (float)(-ScreenWidth() / 2) / fScale,
            (float)(-ScreenHeight() / 2) / fScale
        };
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
        // Clear Screen
        Clear(olc::DARK_BLUE);
        
        // Handle mouse input
        HandleMouse();

        // Draw the visible world
        DrawVisibleWorld();

        // Handle all the shape drawing, creating, and modifying
        HandleShapes();

        // Tell the user what mode/action they are in/doing
        DisplayMode();

        // Exit when escape has been pressed
		return !GetKey(keybindings.exit).bPressed;
	}
};


int main()
{
	olcPGEtest instance;
	if (instance.Construct(1280, 720, 1, 1))
	    instance.Start();

	return 0;
}
