#include <TML/Interface/Layout.h>

namespace tml::Interface
{
    Layout::Layout() noexcept
    : Component()
    {
        m_hSizePolicy = SizePolicy::Dynamic;
        m_vSizePolicy = SizePolicy::Dynamic;
//        m_surfaceTexture.SetClearColor(m_sColor);
//        m_surfaceTexture.SetClearColor(Color(230,230,230,100));

        AddListener("ChildAdded", [&](Component* c, const Event& e)
        {
            ScaleChildren();
            AlignChildren();
            return true;
        });

        AddListener("Resized", [&](Component* c, const Event& e)
        {
            ScaleChildren();
            AlignChildren();
            m_surfaceTexture.Create(m_size.x, m_size.y);
            return true;
        });

        AddListener("Moved", [&](Component* c, const Event& e)
        {
//            ScaleChildren();
            AlignChildren();
            return true;
        });

        AddListener("Attached", [&](Component* c, const Event& e)
        {
            ScaleChildren();
            AlignChildren();
            m_surfaceTexture.Create(m_size.x, m_size.y);
            return true;
        });

        AddListener("MouseMoved", [&](Component* c, const Event& e)
        {
            return ContainsPoint(Vector2i(e.pos.x, e.pos.y));
        });

        AddListener("Dragged", [&](Component* c, const Event& e)
        {
            return ContainsPoint({e.drag.beginX, e.drag.beginY});
        });
    }

    Vector2i Layout::SetPadding(const Vector2i &padding) noexcept
    {
        return m_padding = padding;
    }

    Vector2i Layout::SetMargin(const Vector2i& margin) noexcept
    {
        return m_margin = margin;
    }

    Vector2i Layout::GetPadding() const noexcept
    {
        return m_padding;
    }

    Vector2i Layout::GetMargin() const noexcept
    {
        return m_margin;
    }

    void Layout::pDraw(RenderTarget& target) noexcept
    {
        m_surfaceTexture.Clear();
        m_surfaceTexture.SetView(m_pos, m_size);

        for(auto& child : m_children)
        {
            child->pDraw(m_surfaceTexture);
        }

        m_surfaceTexture.Display();

        target.DrawTexture(m_surfaceTexture.GetTexture(), m_pos, m_size);
    }
}