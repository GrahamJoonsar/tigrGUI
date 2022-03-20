#include "tigr.h"

class GUIObject{
    public:
        virtual void draw (Tigr*) const = 0;
        virtual void update (Tigr*) = 0;
};