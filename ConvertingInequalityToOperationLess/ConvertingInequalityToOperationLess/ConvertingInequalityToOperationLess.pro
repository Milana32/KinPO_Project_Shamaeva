QT += core
QT += testlib
CONFIG += console
CONFIG -= app_bundle


TEMPLATE = app
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        error.cpp \
        functions.cpp \
        main.cpp \
        tests.cpp \
        tree.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    error.h \
    functions.h \
    tests.h \
    tree.h
