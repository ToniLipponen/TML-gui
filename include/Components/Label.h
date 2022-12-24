#pragma once
#include <TML/Interface/Component.h>
#include <TML/Graphics/Drawable/Text.h>

namespace tml::Interface
{
    class TML_API Label : public Component
    {
    public:
        explicit Label(const String& labelText, uint32_t s = 20, uint32_t width = 0, int32_t x = 0, int32_t y = 0) noexcept;
        void SetValue(const String& str) noexcept;
        bool ContainsPoint(const Vector2i& p) noexcept override;
        void SetTextColor(const Color& color) noexcept override;
        std::string_view GetType() const noexcept override { return "Label"; }

    private:
        void pDraw(RenderTarget& renderer) noexcept override;
        Text m_text;
    };
}