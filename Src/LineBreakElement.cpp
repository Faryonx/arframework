#include "LineBreakElement.hpp"
#include "Graphics.hpp"

using ArsLexis::Graphics;

void LineBreakElement::setSize(int mult, int div)
{
    mult_ = mult;
    div_ = div;
}

void LineBreakElement::calculateOrRender(LayoutContext& layoutContext, bool render)
{
    assert(0==layoutContext.usedWidth);
    if (!render)
    {
        const RenderingPreferences::StyleFormatting& style=layoutContext.preferences.styleFormatting(styleDefault);
        Graphics::FontSetter setFont(layoutContext.graphics, style.font);
        uint_t reqHeight = layoutContext.graphics.fontHeight();
        reqHeight = reqHeight * mult_;
        reqHeight = reqHeight / div_;
        uint_t baseLine = layoutContext.graphics.fontBaseline();
        baseLine = baseLine * mult_;
        baseLine = baseLine / div_;
        layoutContext.extendHeight(reqHeight, baseLine);
    }
    layoutContext.markElementCompleted(0);
}

LineBreakElement::~LineBreakElement()
{}

uint_t LineBreakElement::charIndexAtOffset(LayoutContext& lc, uint_t offset) {
    return offsetOutsideElement;
}
