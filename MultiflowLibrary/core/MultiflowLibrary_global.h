#ifndef MULTIFLOWLIBRARY_GLOBAL_H
#define MULTIFLOWLIBRARY_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MULTIFLOWLIBRARY_LIBRARY)
#  define MULTIFLOWLIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define MULTIFLOWLIBRARY_EXPORT Q_DECL_IMPORT
#endif

#endif // MULTIFLOWLIBRARY_GLOBAL_H