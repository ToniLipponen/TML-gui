#include <TML/Interface/Component.h>

namespace tml::Interface
{
    inline Vector2f Align(const Vector2f& size,
                          const Vector2f& alignPos,
                          const Vector2f& alignSize,
                          AlignPolicy horizontalPolicy,
                          AlignPolicy verticalPolicy) noexcept
    {
        Vector2f result{};

        switch(horizontalPolicy)
        {
            case AlignPolicy::Near:
                result.x = alignPos.x;
                break;

            case AlignPolicy::Center:
                result.x = alignPos.x + (alignSize.x - size.x) / 2;
                break;

            case AlignPolicy::Far:
                result.x = alignPos.x + alignSize.x - size.x;
                break;

            default:break;
        }

        switch(verticalPolicy)
        {
            case AlignPolicy::Near:
                result.y = alignPos.y;
                break;

            case AlignPolicy::Center:
                result.y = alignPos.y + (alignSize.y - size.y) / 2;
                break;

            case AlignPolicy::Far:
                result.y = alignPos.y + alignSize.y - size.y;
                break;

            default:break;
        }

        return result;
    }
}