/**
 * @file Definition.hpp
 * Interface to class @c Definition that handles rendering of definition text.
 *
 *
 * @author Andrzej Ciarkowski (a.ciarkowski@interia.pl)
 */
#ifndef __DEFINITION_HPP__
#define __DEFINITION_HPP__

#include "Debug.hpp"
#include <list>
#include <vector>
#include "Geometry.hpp"
#include "Rendering.hpp"

class DefinitionElement;

/**
 * Handles rendering and user interactions (clicking parts of, selecting etc.) with definition text .
 */
class Definition
{
    /**
     * @internal
     * Type used to store @c DefinitonElement objects that represent various parts of definition.
     */
    typedef std::list<DefinitionElement*, ArsLexis::Allocator<DefinitionElement*> > Elements_t;
    
    /**
     * @internal
     * Stores definition parts in their order of appearance from top-left to bottom-right.
     */
    Elements_t elements_;
    
    typedef Elements_t::iterator ElementPosition_t;

    /**
     * @internal
     * Stores useful information about each line of text, so that we can render each line without the need to
     * recalculate the whole content.
     */    
    struct LineHeader
    {
        /**
         * @internal 
         * Initializes members to default values.
         */
        LineHeader():
            renderingProgress(0),
            height(0),
            baseLine(0)
        {}
        
        /**
         * @internal
         * Index of first element in line.
         */
        ElementPosition_t firstElement;
        
        /**
         * @internal
         * Rendering progress of @c firstElement that line starts with.
         */
        UInt16 renderingProgress;
        
        /**
         * @internal
         * Line height.
         */
        Coord height;
        
        /**
         * @internal
         * Position of baseline ralative to height.
         */
        Coord baseLine;
    };
    
    typedef std::vector<LineHeader, ArsLexis::Allocator<LineHeader> > Lines_t;
    typedef Lines_t::iterator LinePosition_t;
    
    /**
     * @internal
     * Caches information about lines of text.
     */
    Lines_t lines_;
    
    /**
     * @internal
     * First currently displayed line index.
     */
    UInt16 firstLine_;
    
    /**
     * @internal
     * Index of one-past-last currently displayed line.
     */
    UInt16 lastLine_;
    
    /**
     * @internal
     * Bounds that definition is displayed within.
     */
    ArsLexis::Rectangle bounds_;
    
    Coord topOffset_;
    
public:

    /**
     * Hot spot is a place in definition that allows to execute some action on clicking it.
     * It's made of one or more rectangular areas, that represent the space in which 
     * some @c DefinitionElement is rendered.
     */
    class HotSpot 
    {
        typedef std::list<ArsLexis::Rectangle, ArsLexis::Allocator<ArsLexis::Rectangle> > Rectangles_t;
        
        /**
         * @internal 
         * Stores rectangles belonging to @c element_.
         */
        Rectangles_t rectangles_;
        
        /**
         * @internal
         * @c DefinitionElement associated with this @c HotSpot.
         */
        DefinitionElement& element_;
     
     public:
     
        HotSpot(const ArsLexis::Rectangle& rect, DefinitionElement& element);
        
        void addRectangle(const ArsLexis::Rectangle& rect)
        {rectangles_.push_back(rect);}
        
        Boolean hitTest(const PointType& point) const;
        
        DefinitionElement& element()
        {return element_;}
        
        /**
         * @return @c true if any part of @c HotSpot is still in @c validArea, @c false otherwise.
         */
        Boolean move(const PointType& delta, const ArsLexis::Rectangle& validArea);
        
        ~HotSpot();
        
    };
    
    /**
     * Renders (paints) this @c Definition into bounds.
     */
    void render(const ArsLexis::Rectangle& bounds, const RenderingPreferences& preferences);
    
    UInt16 totalLinesCount() const
    {return lines_.size();}
    
    UInt16 firstShownLine() const
    {return firstLine_;}
    
    UInt16 shownLinesCount() const
    {return lastLine_-firstLine_;}
    
    /**
     * Scrolls this @c Definition by @c delta lines, bounding it as neccessary.
     */
    void scroll(Int16 delta);

    Definition();
    
    ~Definition();
    
    void swap(Definition& other);
    
    void appendElement(DefinitionElement* element);
    
    void addHotSpot(HotSpot* hotSpot);
    
    const ArsLexis::Rectangle& bounds() const
    {return bounds_;}
    
    void hitTest(const PointType& point);
    
private:

    RenderingPreferences preferences_;

    typedef std::list<HotSpot*, ArsLexis::Allocator<HotSpot*> > HotSpots_t;
    HotSpots_t hotSpots_;
    
    /**
     * Deletes all currently registered hot spots.
     */
    void clearHotSpots();

    /**
     * Clears lines cache.
     */
    void clearLines();

    void clear();
    
    void calculateLayout(const ElementPosition_t& firstElement, UInt16 renderingProgress);
    
    void calculateVisibleRange(UInt16& firstLine, UInt16& lastLine, Int16 delta=0);
    
    void renderLine(RenderingContext& renderContext, const LinePosition_t& line);
    
    void renderLineRange(const LinePosition_t& begin, const LinePosition_t& end, Coord topOffset);

    //! @todo Apply background according to RenderingPreferences.
    void renderLayout()
    {
        WinEraseRectangle(bounds_, 0);
        renderLineRange(lines_.begin()+firstLine_, lines_.begin()+lastLine_, 0);
    }
    
    void moveHotSpots(const PointType& delta);
    
};

template<> 
inline void std::swap(Definition& def1, Definition& def2)
{def1.swap(def2);}

#endif