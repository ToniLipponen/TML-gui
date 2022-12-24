#include <TML/Interface/Components/DropMenu.h>

namespace tml::Interface
{
    DropMenu::DropMenu(const tml::String &text) noexcept
    : Button(text)
    {
        AddChild(m_optionsList = new VerticalLayout);

        AddListener("Click", [&](Component* c, const Event& e)
        {
            m_optionsList->ToggleEnabled();
            return true;
        });
    }
}