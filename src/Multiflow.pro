QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0




SOURCES += \
    TView/mulitem.cpp \
    TView/tarrow.cpp \
#    TView/tflowlineitem.cpp \
    TView/tgraphicsscene.cpp \
    TView/tgraphicsview.cpp \
#    TView/tmultiflowitem.cpp \
#    TView/tsinkitem.cpp \
#    TView/tsourceitem.cpp \
#    TView/twellitem.cpp \
    TWidget/ttabwidget.cpp \
    TWidget/ttreewidget.cpp \
    entity/component/flowline/mflowlinepar.cpp \
    entity/component/well/mdeviationpar.cpp \
    entity/component/well/mwellcasing.cpp \
    entity/component/well/mwellpacker.cpp \
    entity/component/well/mwelldeviation.cpp \
    entity/component/well/mwellreservoir.cpp \
    entity/component/well/mwelltunbing.cpp \
    entity/mflowline.cpp \
    entity/mjunction.cpp \
    entity/msink.cpp \
    entity/msource.cpp \
    entity/mwell.cpp \
    entity/component/well/mwellheat.cpp \
    main.cpp \
    mainwindow.cpp \
    parUI/mflowlinedialog.cpp \
    parUI/mjunctiondialog.cpp \
    parUI/msinkdialog.cpp \
    parUI/msourcedialog.cpp \
 \#    parUI/sinkdialog.cpp
 \#    parUI/mwellwidget.cpp
    parUI/mwellwindow.cpp \
    util/delegate/comphiprdelegate.cpp \
    util/delegate/compviprdelegate.cpp \
    util/delegate/editabledelegate.cpp \
    util/delegate/geometrydelegate.cpp \
    util/delegate/gradedelegate.cpp \
    util/delegate/readonlydelegate.cpp \
    util/validator/doublevalidator.cpp

HEADERS += \
    TView/mulitem.h \
    TView/tarrow.h \
#    TView/tflowlineitem.h \
    TView/tgraphicsscene.h \
    TView/tgraphicsview.h \
#    TView/tmultiflowitem.h \
#    TView/tsinkitem.h \
#    TView/tsourceitem.h \
#    TView/twellitem.h \
    TWidget/ttabwidget.h \
    TWidget/ttreewidget.h \
    common.h \
    entity/component/flowline/mflowlinepar.h \
    entity/component/well/mdeviationpar.h \
    entity/component/well/mwellcasing.h \
    entity/component/well/mwellpacker.h \
    entity/component/well/mwelldeviation.h \
    entity/component/well/mwellreservoir.h \
    entity/component/well/mwelltunbing.h \
    entity/mflowline.h \
    entity/mjunction.h \
    entity/msink.h \
    entity/msource.h \
    entity/mwell.h \
    entity/component/well/mwellheat.h \
    mainwindow.h \
    parUI/mflowlinedialog.h \
    parUI/mjunctiondialog.h \
    parUI/msinkdialog.h \
    parUI/msourcedialog.h \
 \#    parUI/sinkdialog.h
 \#    parUI/mwellwidget.h
    parUI/mwellwindow.h \
    util/delegate/comphiprdelegate.h \
    util/delegate/compviprdelegate.h \
    util/delegate/editabledelegate.h \
    util/delegate/geometrydelegate.h \
    util/delegate/gradedelegate.h \
    util/delegate/readonlydelegate.h \
    util/validator/doublevalidator.h

FORMS += \
    mainwindow.ui \
#    parUI/mwellwidget.ui \
 \#    parUI/sinkdialog.ui
    parUI/mwellwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc
