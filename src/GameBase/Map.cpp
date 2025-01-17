#include "Map.h"
#include <iostream>

Map::Map()
    : m_height(0), m_batTimer(0), m_blackHoleTimer(0), m_giftTimer(0),
    m_trampolineTimer(0), m_wingGiftTimer(0), m_heartGiftTimer(0), m_batActive(false),
    m_blackHoleActive(false), m_bat(-100, -100), m_playerStartX(0), m_playerStartY(0), m_platformCount(0) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Map::initialize(sf::RenderWindow& window) {
    const int platformCount = 6;
    const float gap = static_cast<float>(window.getSize().y / 2) / platformCount;

    for (int i = 0; i < platformCount; ++i) {
        float x = static_cast<float>(std::rand() % (window.getSize().x - 60));
        float y = window.getSize().y - i * gap;
        m_platforms.push_back(std::make_unique<Platform>(x, y));
    }
    size_t pos = std::rand() % m_platforms.size();
    m_playerStartX = m_platforms[pos]->getBounds().left + m_platforms[pos]->getBounds().width / 2 - 25;
    m_playerStartY = m_platforms[pos]->getBounds().top - 100;
}

void Map::update(float deltaTime, sf::RenderWindow& window, Player& player) {
    m_height = m_playerStartY - player.getPosition().y;
    updatePlatform(deltaTime, window, player);
    updateObjects(deltaTime, window, player);
}

void Map::render(sf::RenderWindow& window) {
    for (auto& platform : m_platforms) {
        platform->draw(window);
    }
    for (auto& object : m_objects) {
        object->draw(window);
    }
    m_bat.draw(window);
}

void Map::addNewPlatform(sf::RenderWindow& window) {
    float x = static_cast<float>(std::rand() % static_cast<int>(window.getSize().x - 60));
    float y = m_platforms.back()->getBounds().top - static_cast<float>(window.getSize().y / 2) / 6;

    Platform::Type type;

    if (m_height < 1000) {
        type = Platform::Type::NORMAL;
    }
    else if (m_height < 1500) {
        if (m_platformCount % 2 == 0) {
            type = Platform::Type::NORMAL;
        }
        else {
            type = Platform::Type::MOVING;
        }
    }
    else if (m_height < 2500) {
        type = Platform::Type::MOVING;
    }
    else if (m_height < 3500) {
        if (m_platformCount % 3 == 0) {
            type = Platform::Type::NORMAL;
        }
        else if (m_platformCount % 3 == 1) {
            type = Platform::Type::MOVING;
        }
        else {
            type = Platform::Type::BREAKABLE;
        }
    }
    else if (m_height < 4500) {
        if (m_platformCount % 2 == 0) {
            type = Platform::Type::MOVING;
        }
        else {
            type = Platform::Type::BREAKABLE;
        }
    }
    else if (m_height < 5500) {
        if (m_platformCount % 4 == 0) {
            type = Platform::Type::NORMAL;
        }
        else if (m_platformCount % 4 == 1) {
            type = Platform::Type::MOVING;
        }
        else if (m_platformCount % 4 == 2) {
            type = Platform::Type::BREAKABLE;
        }
        else {
            type = Platform::Type::MOVING_BREAKABLE;
        }
    }
    else if (m_height < 6500) {
        if (m_platformCount % 3 == 0) {
            type = Platform::Type::MOVING;
        }
        else if (m_platformCount % 3 == 1) {
            type = Platform::Type::BREAKABLE;
        }
        else {
            type = Platform::Type::MOVING_BREAKABLE;
        }
    }
    else if (m_height < 7500) {
        type = Platform::Type::BREAKABLE;
    }
    else if (m_height < 8500) {
        if (m_platformCount % 2 == 0) {
            type = Platform::Type::BREAKABLE;
        }
        else {
            type = Platform::Type::MOVING_BREAKABLE;
        }
    }
    else {
        type = Platform::Type::MOVING_BREAKABLE;
    }

    switch (type) {
    case Platform::Type::NORMAL:
        m_platforms.push_back(std::make_unique<Platform>(x, y));
        break;
    case Platform::Type::MOVING:
        m_platforms.push_back(std::make_unique<MovingPlatform>(x, y));
        break;
    case Platform::Type::BREAKABLE:
        m_platforms.push_back(std::make_unique<BreakablePlatform>(x, y));
        break;
    case Platform::Type::MOVING_BREAKABLE:
        m_platforms.push_back(std::make_unique<MovingBreakablePlatform>(x, y));
        break;
    }

    m_platformCount++;
}

void Map::spawnObjects(float deltaTime, sf::RenderWindow& window, const Player& player) {
    auto objectExists = [&](const std::string& type) -> bool {
        for (const auto& object : m_objects) {
            if (object->getType() == type) {
                return true;
            }
        }
        return false;
        };

    if (m_height > MEDIUM_HEIGHT) {
        m_batTimer += deltaTime;
        if (m_batTimer >= BAT_SPAWN_INTERVAL) {
            m_batTimer = 0;
            m_bat.resetPosition(static_cast<float>(window.getSize().x), static_cast<float>(player.getPosition().y - 300));
            Singleton::instance().getSoundManager().playSound("rock");
        }
        m_bat.update(deltaTime);
    }

    if (m_height > HARD_HEIGHT && !objectExists("BlackHole")) {
        m_blackHoleTimer += deltaTime;
        if (m_blackHoleTimer >= BLACK_HOLE_SPAWN_INTERVAL) {
            m_blackHoleTimer = 0;
            m_objects.push_back(std::make_unique<BlackHole>(static_cast<float>(rand() % window.getSize().x - 60), player.getPosition().y - 350));
        }
    }

    if (!objectExists("HeartGift")) {
        m_heartGiftTimer += deltaTime;
        if (m_heartGiftTimer >= GIFT_SPAWN_INTERVAL) {
            m_heartGiftTimer = 0;
            m_objects.push_back(std::make_unique<HeartGift>(static_cast<float>(rand() % window.getSize().x - 60), player.getPosition().y - 350));
        }
    }

    if (!objectExists("Trampoline")) {
        m_trampolineTimer += deltaTime;
        if (m_trampolineTimer >= TRAMPOLINE_SPAWN_INTERVAL) {
            m_trampolineTimer = 0;
            if (!m_platforms.empty()) {
                int randomIndex = std::rand() % m_platforms.size();
                auto& platform = m_platforms[randomIndex];
                if (platform->getType() != Platform::Type::MOVING && platform->getType() != Platform::Type::MOVING_BREAKABLE) {
                    m_objects.push_back(std::make_unique<Trampoline>(platform->getPosition().x, platform->getPosition().y - 20));
                }
            }
        }
    }

    if (!objectExists("WingGift")) {
        m_wingGiftTimer += deltaTime;
        if (m_wingGiftTimer >= WING_GIFT_SPAWN_INTERVAL) {
            m_wingGiftTimer = 0;
            m_objects.push_back(std::make_unique<WingGift>(static_cast<float>(rand() % window.getSize().x - 60), player.getPosition().y - 350));
        }
    }
}

void Map::updatePlatform(float deltaTime, sf::RenderWindow& window, Player& player) {
    if (player.getPosition().y < m_platforms.back()->getBounds().top + 300) {
        addNewPlatform(window);
    }

    for (auto& platform : m_platforms) {
        platform->update(deltaTime);
    }

    auto platformIt = m_platforms.begin();
    while (platformIt != m_platforms.end()) {
        if ((*platformIt)->getBounds().top > player.getPosition().y + 400) {
            platformIt = m_platforms.erase(platformIt);
            player.increaseScore();
        }
        else {
            if ((*platformIt)->isBreakable() && dynamic_cast<BreakablePlatform*>(platformIt->get())->isBroken()) {
                platformIt = m_platforms.erase(platformIt);
            }
            else {
                ++platformIt;
            }
        }
    }
}

void Map::updateObjects(float deltaTime, sf::RenderWindow& window, const Player& player) {
    spawnObjects(deltaTime, window, player);

    auto objectIt = m_objects.begin();
    while (objectIt != m_objects.end()) {
        if ((*objectIt)->getBounds().top > player.getPosition().y + 400) {
            objectIt = m_objects.erase(objectIt);
        }
        else {
            ++objectIt;
        }
    }
}

void Map::collision(Player& player) {
    for (auto& object : m_objects) {
        if (object->checkCollision(player)) {
            object->onCollision(player);
        }
    }
    if (m_bat.checkCollision(player)) {
        m_bat.onCollision(player);
    }

    auto platformIt = m_platforms.begin();
    while (platformIt != m_platforms.end()) {
        sf::FloatRect platformBounds = (*platformIt)->getBounds();
        sf::FloatRect playerBounds = player.getBounds();

        if (playerBounds.top + playerBounds.height >= platformBounds.top &&
            playerBounds.top + playerBounds.height <= platformBounds.top + platformBounds.height &&
            player.getVelocity() > 0) {
            float minX = platformBounds.left - playerBounds.width;
            float maxX = platformBounds.left + platformBounds.width;
            if (playerBounds.left >= minX && playerBounds.left <= maxX) {
                if ((*platformIt)->isBreakable()) {
                    if (auto breakable = dynamic_cast<BreakablePlatform*>(platformIt->get())) {
                        breakable->breakPlatform();
                        Singleton::instance().getSoundManager().playSound("glassshatter");
                    }
                    platformIt = m_platforms.erase(platformIt);
                }
                else if (auto movingBreakable = dynamic_cast<MovingBreakablePlatform*>(platformIt->get())) {
                    movingBreakable->breakPlatform();
                    Singleton::instance().getSoundManager().playSound("glassshatter");
                    platformIt = m_platforms.erase(platformIt);
                }
                else {
                    ++platformIt;
                }
                player.jump();
                Singleton::instance().getSoundManager().playSound("jump");
            }
            else {
                ++platformIt;
            }
        }
        else {
            ++platformIt;
        }
    }
}

std::vector<Map::PlatformState> Map::getPlatformStates() const {
    std::vector<PlatformState> states;
    for (const auto& platform : m_platforms) {
        PlatformState state;
        state.position = platform->getPosition();
        state.type = platform->getType();
        state.isBroken = platform->isBreakable() && dynamic_cast<BreakablePlatform*>(platform.get())->isBroken();
        states.push_back(state);
    }
    return states;
}

void Map::setPlatformStates(const std::vector<PlatformState>& states) {
    m_platforms.clear();
    for (const auto& state : states) {
        switch (state.type) {
        case Platform::Type::NORMAL:
            m_platforms.push_back(std::make_unique<Platform>(state.position.x, state.position.y));
            break;
        case Platform::Type::MOVING:
            m_platforms.push_back(std::make_unique<MovingPlatform>(state.position.x, state.position.y));
            break;
        case Platform::Type::BREAKABLE: {
            auto platform = std::make_unique<BreakablePlatform>(state.position.x, state.position.y);
            if (state.isBroken) {
                platform->breakPlatform();
            }
            m_platforms.push_back(std::move(platform));
        }
                                      break;
        case Platform::Type::MOVING_BREAKABLE: {
            auto movingBreakablePlatform = std::make_unique<MovingBreakablePlatform>(state.position.x, state.position.y);
            if (state.isBroken) {
                movingBreakablePlatform->breakPlatform();
            }
            m_platforms.push_back(std::move(movingBreakablePlatform));
        }
                                             break;
        }
    }
}

std::vector<Map::ObjectState> Map::getObjectStates() const {
    std::vector<ObjectState> states;
    for (const auto& object : m_objects) {
        ObjectState state;
        state.position = object->getPosition();
        state.type = object->getType();
        states.push_back(state);
    }
    return states;
}

void Map::setObjectStates(const std::vector<ObjectState>& states) {
    m_objects.clear();
    for (const auto& state : states) {
        if (state.type == "Bat") {
            m_bat.resetPosition(state.position.x, state.position.y);
        }
        else if (state.type == "BlackHole") {
            m_objects.push_back(std::make_unique<BlackHole>(state.position.x, state.position.y));
        }
        else if (state.type == "HeartGift") {
            m_objects.push_back(std::make_unique<HeartGift>(state.position.x, state.position.y));
        }
        else if (state.type == "Trampoline") {
            m_objects.push_back(std::make_unique<Trampoline>(state.position.x, state.position.y));
        }
        else if (state.type == "WingGift") {
            m_objects.push_back(std::make_unique<WingGift>(state.position.x, state.position.y));
        }
    }
}
