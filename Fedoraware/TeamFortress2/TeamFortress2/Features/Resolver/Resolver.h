#pragma once
#include "../../SDK/SDK.h"

struct ResolveData {
    
    bool enabled = false;

    // Bruteforce data
    int yawIndex = 0;

    // Logical data
    std::pair<int, float> lastSniperPitch = {0, 0.f};
    float pitchNoise = 0.f;
    int pitchNoiseSteps = 0;

    // Historical data
    std::pair<std::pair<int, bool>, Vec3> lastFireAngles = {{0, false}, {}};
    Vec2 originalAngles = {0.f, 0.f};
};

class PResolver {
private:
    // Sniper dots
    void updateSniperDots();
    std::optional<float> getPitchForSniperDot(CBaseEntity* entity);

    // Logic
    std::optional<float> predictBaseYaw(CBaseEntity* entity);

    // Misc
    bool shouldRun();
    bool shouldRunEntity(CBaseEntity* entity);
    bool keepOnShot(CBaseEntity* entity);
    bool isOnShotPitchReliable(const float pitch);
    float getRealPitch(const float pitch);
    void setAngles(const Vec3 angles, CBaseEntity* entity);
    int getPitchMode(CBaseEntity* entity);
    int getYawMode(CBaseEntity* entity);
    void onDormancy(CBaseEntity* entity);

    // Data
    std::unordered_map<CBaseEntity*, CBaseEntity*> sniperDots;
    std::unordered_map<CBaseEntity*, ResolveData> resolverData;
    std::pair<int, std::pair<CBaseEntity*, bool>> waiting = {0, {nullptr, false}};

public:
    void aimbot(CBaseEntity* entity, const bool headshot);
    void frameStageNotify();
    void createMove();
    void fxFireBullet(int index, const Vec3 angles);
    void onPlayerHurt(CGameEvent* event);
    std::unordered_map<uint32_t, std::pair<int, int>> resolverMode;
};

ADD_FEATURE(PResolver, Resolver)
