#pragma once
#include <TML/Interface/Component.h>
#include <TML/Export.h>

namespace tml::Interface
{
    template<ComponentAxis axis>
    class TML_API ResizeHandle : public Component
    {
    public:
        ResizeHandle();
        std::string_view GetType() const noexcept override { return "ResizeHandle"; }
    private:
        void pDraw(RenderTarget& renderer) noexcept override;
        Vector2i m_neighborOldSize;
        Vector2i m_neighborMinSize;
    };

    using HResizeHandle = ResizeHandle<ComponentAxis::Horizontal>;
    using VResizeHandle = ResizeHandle<ComponentAxis::Vertical>;
}