#include "../CAD.hpp"

void CAD::HandleShapes()
{
    // ============= SHAPE SELECTION ============
    if (keybindings.line(this).bPressed) 
    {
        currentShape = Shape::LINE;
    }

    if (keybindings.box(this).bPressed) 
    {
        currentShape = Shape::BOX;
    }
    if (keybindings.circle(this).bPressed) 
    {
        currentShape = Shape::CIRCLE;
    }
    if (keybindings.spline(this).bPressed) 
    {
        currentShape = Shape::SPLINE;
    }

    // ============= CREATE SHAPE ===============
    if (keybindings.create(this).bPressed && currentAction == Action::NONE)
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
    if (keybindings.move(this).bReleased && currentAction == NONE)
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
    if (keybindings.select(this).bPressed && currentAction != Action::NONE) {
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
        shape->DrawYourself(this, showHUD);
        shape->DrawNodes(this, showHUD);
    }

    // ============== DRAW TEMP SHAPE ===================
    // Draw the wip shape.. if there is one
    if (currentAction != Action::NONE) {
        tempShape->DrawYourself(this, showHUD);
        tempShape->DrawNodes(this, showHUD);
    }
}
