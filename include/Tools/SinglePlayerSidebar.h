#pragma once

#include "BaseSidebar.h"

class SinglePlayerSidebar : public BaseSidebar {
public:
    SinglePlayerSidebar(float width, float height);

    void update(int score, int height, int lives) override;
};