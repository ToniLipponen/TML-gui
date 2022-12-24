#pragma once
#include <TML/Interface/Component.h>

namespace tml::Interface
{
    class TML_API Spacer : public Component
    {
    public:
        Spacer() noexcept;
        Spacer(ComponentAxis axis, int min, int max = 10000) noexcept;
        std::string_view GetType() const noexcept override { return "Spacer"; }

    private:
        void pDraw(RenderTarget& renderer) noexcept override {}
    };
}