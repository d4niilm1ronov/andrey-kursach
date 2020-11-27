QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PharmaCOre
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        dashboard.cpp \
        detailsdisplay.cpp \
        main.cpp \
        login.cpp \
        order.cpp \
        regular.cpp \
        selldetails.cpp \
        stocks.cpp \
        userreg.cpp \
        wholesalers.cpp

HEADERS += \
        dashboard.h \
        detailsdisplay.h \
        login.h \
        order.h \
        regular.h \
        selldetails.h \
        stocks.h \
        userreg.h \
        wholesalers.h

FORMS += \
        dashboard.ui \
        detailsdisplay.ui \
        login.ui \
        order.ui \
        regular.ui \
        selldetails.ui \
        stocks.ui \
        userreg.ui \
        wholesalers.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
