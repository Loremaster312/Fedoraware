#include "../Hooks.h"


// https://www.unknowncheats.me/forum/team-fortress-2-a/520739-custom-particle-colors.html
typedef union
{
    float m128_f32[4];
    uint32_t m128_u32[4];
} fltx4;

struct SpriteRenderInfo_t
{
    size_t m_nXYZStride{};
    fltx4* m_pXYZ{};
    size_t m_nRotStride{};
    fltx4* m_pRot{};
    size_t m_nYawStride{};
    fltx4* m_pYaw{};
    size_t m_nRGBStride{};
    fltx4* m_pRGB{};
    size_t m_nCreationTimeStride{};
    fltx4* m_pCreationTimeStamp{};
    size_t m_nSequenceStride{};
    fltx4* m_pSequenceNumber{};
    size_t m_nSequence1Stride{};
    fltx4* m_pSequence1Number{};
    float m_flAgeScale{};
    float m_flAgeScale2{};
    void* m_pSheet{};
    int m_nVertexOffset{};
    void* m_pParticles{};
};

MAKE_HOOK(C_OP_RenderSprites_RenderSpriteCard, g_Pattern.Find(L"client.dll", L"55 8B EC 83 EC 28 56 8B 75 10 57 8B 7D 14 8B C7 99 83 E7 03 83 E2 03"), void, __fastcall, 
        void* ecx, void* edx, void* meshBuilder, void* pCtx, SpriteRenderInfo_t& info, int hParticle, void* pSortList, void* pCamera)
{
    #define colors Colors::ParticleColor
    #define CALL_ORIGINAL Hook.Original<FN>()

    if(Vars::Visuals::ParticleColors.Value = true && Vars::Visuals::ParticleColorsRGB.Value = false)
    {
	    info.m_pRGB[((hParticle / 4) * info.m_nRGBStride) + 0].m128_f32[hParticle & 0x3] = Color::TOFLOAT(colors.r); //red
	    info.m_pRGB[((hParticle / 4) * info.m_nRGBStride) + 1].m128_f32[hParticle & 0x3] = Color::TOFLOAT(colors.g); //green
	    info.m_pRGB[((hParticle / 4) * info.m_nRGBStride) + 2].m128_f32[hParticle & 0x3] = Color::TOFLOAT(colors.b); //blue
    }

    // Rainbow
    if(Vars::Visuals::ParticleColors.Value = true && Vars::Visuals::RGBParticles.Value = true)
    {
	    info.m_pRGB[((hParticle / 4) * info.m_nRGBStride) + 0].m128_f32[hParticle & 0x3] = Color::TOFLOAT(Utils::Rainbow().r);
	    info.m_pRGB[((hParticle / 4) * info.m_nRGBStride) + 1].m128_f32[hParticle & 0x3] = Color::TOFLOAT(Utils::Rainbow().g);
	    info.m_pRGB[((hParticle / 4) * info.m_nRGBStride) + 2].m128_f32[hParticle & 0x3] = Color::TOFLOAT(Utils::Rainbow().b);
    }

    CALL_ORIGINAL(ecx, edx, meshBuilder, pCtx, info, hParticle, pSortList, pCamera);
}