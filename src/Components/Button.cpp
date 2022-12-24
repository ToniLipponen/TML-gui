#include <TML/Interface/Components/Button.h>
#include <TML/System/Clock.h>
#include "../Utilities/Align.h"

using namespace tml::Interface;

Button::Button(const String& text, uint32_t h, uint32_t w, int32_t x, int32_t y, bool expand)
: Component(x, y, w, h)
{
    m_hSizePolicy = expand ? SizePolicy::Dynamic : SizePolicy::Fixed;
    m_vSizePolicy = SizePolicy::Fixed;
    m_text.SetString(text);
    m_text.SetColor(s_defaultTextColor);
    m_text.SetSize(static_cast<float>(h) * 0.6f);

    if(w == 0)
    {
        m_size.x = m_text.GetDimensions().x + 10;
        m_size.y = h;
    }
    else
    {
        m_size = Vector2f(w, h);
    }

    m_minimumSize = Vector2f(m_size.y);

    AddListener("MouseDown", [&](Component* c, const Event& e)
    {
        m_mouseDown = true;
        return true;
    });

    AddListener("MouseUp", [&](Component* c, const Event& e)
    {
        m_mouseDown = false;
        return false;
    });

    AddListener("Moved", [&](Component* c, const Event& e)
    {
        m_text.SetPosition(Align(m_text.GetDimensions(), m_pos, m_size, m_hAlignment, m_vAlignment));
        return true;
    });

    AddListener("Resized", [&](Component* c, const Event& e)
    {
        m_text.SetSize(m_size.y * 0.6f);
        m_text.SetPosition(Align(m_text.GetDimensions(), m_pos, m_size, m_hAlignment, m_vAlignment));
        return true;
    });

    AddListener("Drawn", [&](Component* c, const Event& e)
    {
        static tml::Clock clock;
        double delta = clock.Reset();

        if(m_state.MouseOver || m_state.Focused)
        {
            m_borderAnimationProgress = Math::Clamp<double>(m_borderAnimationProgress + delta * s_animationSpeed, 0, 1);
        }
        else
        {
            m_borderAnimationProgress = Math::Clamp<double>(m_borderAnimationProgress - delta * s_animationSpeed, 0, 1);
        }

        if(m_mouseDown)
        {
            m_bodyAnimationProgress = 1;
        }
        else
        {
            m_bodyAnimationProgress = Math::Clamp<double>(m_bodyAnimationProgress - delta * s_animationSpeed, 0, 1);
        }

        m_borderColor = Math::Lerp(m_sColor, m_activeColor, m_borderAnimationProgress);
        m_bodyColor = Math::Lerp(m_pColor, m_activeColor, m_bodyAnimationProgress);
        return true;
    });

    SetPosition(x, y);
    SetSize(m_size);
}

void Button::SetText(const String& str)
{
    m_text.SetString(str);
}

void Button::SetTextSize(float s) noexcept
{
    m_text.SetSize(s);
}

void Button::SetTextColor(const Color &color) noexcept
{
    m_text.SetColor(color);
}

const tml::String& Button::GetText() const noexcept
{
    return m_text.GetString();
}

void Button::SetTextAlignment(AlignPolicy horizontal, AlignPolicy vertical) noexcept
{
    m_hAlignment = horizontal;
    m_vAlignment = vertical;
    m_text.SetPosition(Align(m_text.GetDimensions(), m_pos, m_size, m_hAlignment, m_vAlignment));
}

void Button::pDraw(RenderTarget& target) noexcept
{
    target.DrawRect(m_pos, m_size, m_borderColor, m_roundness);
    target.DrawRect(m_pos + Vector2f(1,1), m_size - Vector2f(2,2), m_bodyColor, m_roundness);

    target.SetBounds(m_pos, m_size);
    target.Draw(m_text);
    target.ResetBounds();
}