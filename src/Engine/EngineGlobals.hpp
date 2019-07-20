#ifndef ENGINEGLOBALS_H_DEFINED
#define ENGINEGLOBALS_H_DEFINED

#include <Engine/Graphics/Colors.hpp>

// Settings for the whole Engine.
// Mostly related to the appearance.
namespace EngineGlobals {
    namespace Screen {
        extern bool center_horizontally;
        extern bool center_vertically;
        
        extern bool show_borders;
        extern bool fancy_borders;
        extern bool outer_border;
    };

    namespace Theme {
        extern ColorPair text;
        extern ColorPair hilite_text;
        extern ColorPair textbox;
    };

    void init();
};

#endif