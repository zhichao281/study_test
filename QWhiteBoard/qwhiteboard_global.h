#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QWHITEBOARD_LIB)
#  define QWHITEBOARD_EXPORT Q_DECL_EXPORT
# else
#  define QWHITEBOARD_EXPORT Q_DECL_IMPORT
# endif
#else
# define QWHITEBOARD_EXPORT
#endif
