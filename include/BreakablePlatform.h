#pragma once

#include "Platform.h"

class BreakablePlatform : public Platform {
public:
    BreakablePlatform(float x, float y);

    void update(float deltaTime) override;
    void breakPlatform();
    bool isBroken() const;

private:
    bool m_isBroken;
};
