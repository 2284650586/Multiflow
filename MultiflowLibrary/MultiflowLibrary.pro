QT -= gui

TEMPLATE = lib
DEFINES += MULTIFLOWLIBRARY_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core/core.cpp \
    expression/add.cpp \
    expression/constant.cpp \
    expression/expression.cpp \
    expression/variable.cpp \
    logging/logging.cpp \
    math/math.cpp

HEADERS += \
    MultiflowLibrary_global.h \
    core/core.h \
    expression/add.h \
    expression/constant.h \
    expression/expression.h \
    expression/variable.h \
    logging/logging.h \
    math/math.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
