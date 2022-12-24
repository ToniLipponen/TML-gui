#pragma once
#include "../Component.h"
#include <TML/Graphics/Drawable/Text.h>

namespace tml::Interface
{
    class TML_API Button : public Component
    {
    public:
        explicit Button(
                const String& text,
                uint32_t height = 24,
                uint32_t width = 0,
                int32_t x = 0,
                int32_t y = 0,
                bool expand = false);

        void SetText(const String& str);
        void SetTextSize(float s) noexcept;
        void SetTextColor(const Color& color) noexcept override;
        const String& GetText() const noexcept;
        std::string_view GetType() const noexcept override { return "Button"; }
        void SetTextAlignment(AlignPolicy horizontal, AlignPolicy vertical) noexcept;
    private:
        void pDraw(RenderTarget& renderer) noexcept override;
        AlignPolicy m_hAlignment = AlignPolicy::Center;
        AlignPolicy m_vAlignment = AlignPolicy::Center;
        Text m_text;
        Color m_borderColor, m_bodyColor;
        bool m_mouseDown = false;
        double m_borderAnimationProgress = 0, m_bodyAnimationProgress = 0;
    };
}