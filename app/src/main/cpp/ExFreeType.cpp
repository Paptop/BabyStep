#include "ExFreeType.h"
#include <iostream>

ExFreeType::ExFreeType()
{
}

void ExFreeType::Init() {
    FT_Error error = FT_Init_FreeType(&m_library);

    if(error)
    {
        std::cout << ("Error\n") << std::endl;
    }
}

