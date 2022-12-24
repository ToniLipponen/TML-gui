#include <TML/Interface/NinePatchSprite.h>
#include <TML/Graphics/RenderTarget.h>

namespace tml::Interface
{
    NinePatchSprite::NinePatchSprite() noexcept
	: m_mode(Mode::Stretch)
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                auto tl = Vector2f(1.0 / 3 * j, 1.0 / 3 * i);

                m_rects[i * 3 + j] = UVRect{tl, tl + Vector2f(1.0 / 3)};
            }
        }
    }

    void NinePatchSprite::SetTexture(const Texture& texture) noexcept
    {
        m_texture = std::make_shared<Texture>();
        *m_texture = texture;
    }

    void NinePatchSprite::SetTexture(const std::shared_ptr<Texture>& texture) noexcept
    {
        m_texture = texture;
    }

    void NinePatchSprite::SetRect(UVRect rect) noexcept
    {
        rect.bottomRight = rect.bottomRight - rect.topLeft;
        const Vector2f patchSize = rect.bottomRight / 3;

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                const auto mult = Vector2f(j, i);
                m_rects[i * 3 + j].topLeft = patchSize * mult + rect.topLeft;
                m_rects[i * 3 + j].bottomRight = m_rects[i * 3 + j].topLeft + patchSize;
            }
        }
    }

    void NinePatchSprite::SetPatches(const std::array<UVRect, 9>& patchRects) noexcept
    {
        m_rects = patchRects;
    }

    void NinePatchSprite::SetScaleMode(Mode mode) noexcept
    {
        m_mode = mode;
    }

    void NinePatchSprite::OnDraw(RenderTarget* target, class Texture*) noexcept
    {
        if(m_texture)
        {
            const auto _1over3 = 1.0f / 3.0f;
            const auto texSize = (m_rects[8].bottomRight - m_rects[0].topLeft) * Vector2f(m_texture->GetWidth(), m_texture->GetHeight());
            const auto scale = m_scale * texSize;

            Vector2f pos = 0;
            Vector2f size = 0;

            for(int i = 0; i < 3; i++)
            {
                pos.x = 0;

                if(i == 0 || i == 2)
                {
                    size.y = _1over3 * scale.y;
                }
                else
                {
                    size.y = Math::Max(_1over3 * scale.y + Math::Max<float>(m_size.y, 0) - texSize.y, 0.f);
                }

                for(int j = 0; j < 3; j++)
                {
                    if(j == 0 || j == 2)
                    {
                        size.x = _1over3 * texSize.x * m_scale.x;
                    }
                    else
                    {
                        size.x = Math::Max(_1over3 * scale.x + Math::Max<float>(m_size.x, 0) - texSize.x, 0.f);
                    }

                    target->DrawTextureRect(*m_texture,
                                            m_pos + pos,
                                            size,
                                            0,
                                            m_rects[i * 3 + j].topLeft,
                                            m_rects[i * 3 + j].bottomRight);

                    pos.x += size.x;
                }

                pos.y += size.y;
            }
        }
    }
}