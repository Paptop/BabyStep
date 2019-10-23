#ifndef BABYSTEP2_EXFREETYPE_H
#define BABYSTEP2_EXFREETYPE_H

#include <ft2build.h>
#include FT_FREETYPE_H

class ExFreeType{

public:
    ExFreeType();
    void Init();

private:
    FT_Library m_library;
};


#endif //BABYSTEP2_EXFREETYPE_H
