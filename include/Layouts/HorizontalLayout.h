#pragma once
#include <TML/Interface/Component.h>
#include <TML/Interface/Layout.h>

namespace tml::Interface
{
    class TML_API HorizontalLayout : public Layout
    {
    public:
        HorizontalLayout() noexcept;
        HorizontalLayout(int32_t x, int32_t y, uint32_t w, uint32_t h) noexcept;
        explicit HorizontalLayout(const std::vector<Component*>& components, int32_t x = 0, int32_t y = 0, uint32_t h = 0) noexcept;
        bool SetCenterVertically(bool value) noexcept;
        bool GetCenterVertically() const noexcept;
        std::string_view GetType() const noexcept override { return "HorizontalLayout"; }

    private:
        void ScaleChildren() noexcept final;
        void AlignChildren() noexcept final;

    private:
        bool m_verticallyCenter = true;
    };
}