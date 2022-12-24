#pragma once
#include <TML/Interface/Component.h>
#include <TML/Interface/Components/Button.h>
#include <TML/Interface/Layouts/VerticalLayout.h>

namespace tml::Interface
{
    class DropMenu : public Button
    {
    public:
        DropMenu(const String& text) noexcept;

    private:
        VerticalLayout* m_optionsList;
    };
}