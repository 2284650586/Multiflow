#ifndef CORE_H
#define CORE_H

#include "MultiflowLibrary_global.h"

class MULTIFLOWLIBRARY_EXPORT MultiflowLibrary
{
private:
    MultiflowLibrary();

public:
    static void initialize();
    static int add(int x, int y);
};

typedef MultiflowLibrary ML;

#endif // CORE_H
