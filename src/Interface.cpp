#include <TML/Interface/Interface.h>
#include <TML/System/Clock.h>

namespace tml::Interface
{
    Interface::Interface(Interface&& layer) noexcept
    {
        std::swap(m_processingQueue, layer.m_processingQueue);
        m_enabled = layer.m_enabled;
    }

    void Interface::Attach(Component* rootNode) noexcept
    {
        std::function<void(Component*)> registerFunc;

        registerFunc = [&](Component* node) noexcept -> void
        {
            node->m_root = this;
            m_processingQueue.push_front(node);

            for(auto& i : node->m_children)
            {
                registerFunc(i.get());
            }
        };

        registerFunc(rootNode);
        m_roots.emplace_back(rootNode);

        for(auto* node : m_processingQueue)
        {
            Event e{};
            node->CallUIFunc("Attached", e);
        }
    }

    void Interface::Detach(Component* component) noexcept
    {
        std::function<void(Component*)> unregisterFunc;

        unregisterFunc = [&](Component* node) noexcept -> void
        {
            const auto end = m_processingQueue.end();
            const auto beg = m_processingQueue.begin();
            const auto it = std::find(beg, end, node);

            if(it != end)
            {
                node->m_root = nullptr;
                m_processingQueue.erase(it);
            }

            for(auto& i : node->m_children)
            {
                unregisterFunc(i.get());
            }
        };

        unregisterFunc(component);

        for(int i = 0; i < m_roots.size(); i++)
        {
            if(m_roots.at(i).get() == component)
            {
                m_roots.erase(m_roots.begin() + i);
                break;
            }
        }
    }

    void Interface::Focus(Component *component) noexcept
    {
        for(auto* i : m_processingQueue)
        {
            if(i == component)
            {
                if(!i->m_state.Focused)
                {
                    i->m_state.Focused = true;

                    Event e{};
                    i->CallUIFunc("GainedFocus", e);
                }
            }
            else
            {
                i->UnFocus();
            }
        }
    }

    void Interface::ClearFocused() noexcept
    {
        for(auto* i : m_processingQueue)
        {
            i->UnFocus();
        }
    }

    void Interface::ClearDragged() noexcept
    {
        for(auto* i : m_processingQueue)
        {
            i->m_state.Dragged = false;
        }
    }

    void Interface::ClearMouseOver() noexcept
    {
        for(auto* i : m_processingQueue)
        {
            i->m_state.MouseOver = false;
        }
    }

    void Interface::Update(Event &event) noexcept
    {
        static Clock clock;
        const double delta = clock.Reset();

        if(!m_processingQueue.empty())
        {
            if(event.type == Event::WindowResized)
            {
                for(auto* i : m_processingQueue)
                {
                    i->CallUIFunc("WindowResized", event);
                }
            }

            HandleEvent(event);
        }
    }

    void Interface::SetEnabled(bool enabled) noexcept
    {
        m_enabled = enabled;
    }

    bool Interface::IsEnabled() const noexcept
    {
        return m_enabled;
    }

    void Interface::OnDraw(RenderTarget *renderer, Texture*) noexcept
    {
        if(m_enabled)
        {
            if(m_roots.empty())
            {
                return;
            }

            for(auto& i : m_roots)
            {
                i->pDraw(*renderer);
            }

            static Clock clock;

            Event event{};

            auto i = m_processingQueue.rbegin();
            auto end = m_processingQueue.rend();

            for(; i != end; i++)
            {
                auto* item = *i;

                if(item->Enabled())
                {
                    item->CallUIFunc("Drawn", event);
                }
            }
        }
    }

    void Interface::HandleEvent(Event &event) noexcept
    {
        if(m_enabled)
        {
            for(auto* i : m_processingQueue)
            {
                if(i->Enabled() && i->HandleEvent(event))
                {
                    event = {};
                    break;
                }
            }

            switch(event.type)
            {
                case Event::MouseButtonReleased:
                {
                    ClearFocused();
                } break;

                case Event::MouseLeft:
                {
                    ClearMouseOver();
                } break;

                default:
                    break;
            }
        }
    }
}