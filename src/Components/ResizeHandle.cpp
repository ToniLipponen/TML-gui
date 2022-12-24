#include <TML/Interface/Components/ResizeHandle.h>

namespace tml::Interface
{
    template<>
    ResizeHandle<ComponentAxis::Horizontal>::ResizeHandle()
    {
        m_size = {2,2};
        m_vSizePolicy = SizePolicy::Dynamic;
        m_hSizePolicy = SizePolicy::Fixed;

        TML_GUI_ON_EVENT("Click", );

        AddListener("Attached", [this](Component*, const Event& event)
        {
            auto parent = GetParent();
            auto index = parent->GetIndex(this);

            if(index > 0)
            {
                auto neighbor = parent->GetChildByIndex(index - 1);

                if(neighbor)
                {
                    m_neighborMinSize = neighbor->GetMinimumSize();
                }
            }

            return true;
        });

        AddListener("MouseDown", [this](Component*, const Event& event)
        {
            auto parent = GetParent();
            auto index = parent->GetIndex(this);

            if(index > 0)
            {
                auto neighbor = parent->GetChildByIndex(index-1);

                if(neighbor)
                {
                    m_neighborOldSize = neighbor->GetSize();
                }
            }
            else
            {
                m_neighborOldSize = {0};
            }

            return true;
        });

        AddListener("Dragged", [this](Component*, const Event& event)
        {
            auto parent = GetParent();
            auto index = parent->GetIndex(this);

            if(index > 0)
            {
                auto neighbor = parent->GetChildByIndex(index-1);

                if(neighbor)
                {
					const auto type = neighbor->GetType();

					if(type.find("Layout") != std::string::npos)
					{
						auto newMaxSize = Vector2f(
								Math::Max<float>(m_neighborOldSize.x + event.drag.x - event.drag.beginX, neighbor->GetMinimumSize().x),
								m_neighborOldSize.y);

						neighbor->SetMaximumSize(newMaxSize);
					}
                }

                parent->SetSize(parent->GetSize());
            }

            return true;
        });

        TML_GUI_ON_EVENT("KeyPressed",
        {
            if(EVENT.key.value == Keyboard::Key::LeftArrow || EVENT.key.value == Keyboard::Key::RightArrow)
            {
                auto offset = EVENT.key.value == Keyboard::Key::LeftArrow ? -10 : 10;
                auto parent = GetParent();
                auto index = parent->GetIndex(this);

                if(index > 0)
                {
                    auto neighbor = parent->GetChildByIndex(index-1);

                    if(neighbor)
                    {
                        auto newMaxSize = Vector2f(
                                Math::Max<float>(m_neighborOldSize.x + offset, neighbor->GetMinimumSize().x),
                                m_neighborOldSize.y);

                        neighbor->SetMaximumSize(newMaxSize);
                    }

                    parent->SetSize(parent->GetSize());
                }
            }
        });
    }

    template<>
    ResizeHandle<ComponentAxis::Vertical>::ResizeHandle()
    {
        m_size = {2,2};
        m_vSizePolicy = SizePolicy::Fixed;
        m_hSizePolicy = SizePolicy::Dynamic;

        AddListener("Attached", [this](Component*, const Event& event)
        {
            auto parent = GetParent();
            auto index = parent->GetIndex(this);

            if(index > 0)
            {
                auto neighbor = parent->GetChildByIndex(index - 1);

                if(neighbor)
                {
                    m_neighborMinSize = neighbor->GetMinimumSize();
                }
            }

            return true;
        });

        AddListener("MouseDown", [this](Component*, const Event& event)
        {
            auto parent = GetParent();
            auto index = parent->GetIndex(this);

            if(index > 0)
            {
                if(auto neighbor = parent->GetChildByIndex(index-1))
                {
                    m_neighborOldSize = neighbor->GetSize();
                }
            }
            else
            {
                m_neighborOldSize = {0};
            }

            return true;
        });

        AddListener("Dragged", [this](Component*, const Event& event)
        {
            auto parent = GetParent();
            auto index = parent->GetIndex(this);

            if(index > 0)
            {
                if(auto neighbor = parent->GetChildByIndex(index-1))
                {
					const auto type = neighbor->GetType();

					if(type.find("Layout") != std::string::npos)
					{
						auto newMaxSize = Vector2f(m_neighborOldSize.x,
								Math::Max(m_neighborOldSize.y + event.drag.y - event.drag.beginY, m_neighborMinSize.y));

						neighbor->SetMaximumSize(newMaxSize);
						parent->SetSize(parent->GetSize());
					}
                }
            }

            return true;
        });
    }

    template<>
    void ResizeHandle<ComponentAxis::Horizontal>::pDraw(RenderTarget& renderer) noexcept
    {
        if(m_state.MouseOver || m_state.Dragged)
        {
            renderer.DrawLine(m_pos + Vector2f(m_size.x / 2, 0), m_pos + Vector2f(m_size.x / 2, m_size.y), 1, m_activeColor);
        }
        else
        {
            renderer.DrawLine(m_pos + Vector2f(m_size.x / 2, 0), m_pos + Vector2f(m_size.x / 2, m_size.y), 1, m_pColor);
        }
    }

    template<>
    void ResizeHandle<ComponentAxis::Vertical>::pDraw(RenderTarget& renderer) noexcept
    {
        if(m_state.MouseOver || m_state.Dragged)
        {
            renderer.DrawLine(m_pos + Vector2f(0, m_size.y / 2), m_pos + Vector2f(m_size.x, m_size.y / 2), 1, m_activeColor);
        }
        else
        {
            renderer.DrawLine(m_pos + Vector2f(0, m_size.y / 2), m_pos + Vector2f(m_size.x, m_size.y / 2), 1, m_pColor);
        }
    }

    template class ResizeHandle<ComponentAxis::Vertical>;
    template class ResizeHandle<ComponentAxis::Horizontal>;
}