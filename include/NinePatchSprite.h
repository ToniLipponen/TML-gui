#pragma once
#include <TML/Graphics/Drawable/Sprite.h>
#include <TML/Graphics/Drawable/Drawable.h>
#include <TML/Export.h>
#include <memory>
#include <array>

namespace tml::Interface
{
    class TML_API NinePatchSprite : public Drawable
    {
    public:
        enum class Mode
        {
            Stretch, Repeat
        };

    public:
        NinePatchSprite() noexcept;
        void SetTexture(const Texture& texture) noexcept;
        void SetTexture(const std::shared_ptr<Texture>& texture) noexcept;
        void SetRect(UVRect rect) noexcept;
        void SetPatches(const std::array<UVRect, 9>& patchRects) noexcept;
        void SetScaleMode(Mode mode) noexcept;

    private:
        void OnDraw(class RenderTarget*, class Texture*) noexcept override;

    private:
        std::shared_ptr<Texture> m_texture = nullptr;
        std::array<UVRect, 9> m_rects;
        Mode m_mode;
    };
}