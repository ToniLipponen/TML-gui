#pragma once
#include <TML/Interface/Component.h>
#include <TML/Interface/Layouts/HorizontalLayout.h>

namespace tml::Interface
{
    class TML_API Menubar : public HorizontalLayout
    {
    public:
        explicit Menubar(RenderWindow& window) noexcept;
        std::string_view GetType() const noexcept override { return "Menubar"; }

    private:
        void pDraw(RenderTarget& renderer) noexcept override;
    };
}