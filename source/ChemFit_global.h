#ifndef CHEMFIT_GLOBAL_H
#define CHEMFIT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CHEMFIT_LIBRARY)
#  define CHEMFITSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CHEMFITSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CHEMFIT_GLOBAL_H
