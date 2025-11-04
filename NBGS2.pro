QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
TEMPLATE = app

# VTK Components
INCLUDEPATH += C:/msys64/home/jimmy/vtk-install/include/vtk-9.5
LIBS += -LC:/msys64/home/jimmy/vtk-install/lib

LIBS += -lvtkRenderingQt-9.5 \
        -lvtkGUISupportQt-9.5 \
        -lvtkRenderingOpenGL2-9.5 \
        -lvtkInteractionStyle-9.5 \
        -lvtkRenderingCore-9.5 \
        -lvtkCommonCore-9.5 \
        -lvtkCommonDataModel-9.5 \
        -lvtkCommonExecutionModel-9.5 \
        -lvtkCommonColor-9.5 \
        -lvtkFiltersGeneral-9.5 \
        -lvtksys-9.5

INCLUDEPATH += /ucrt64/include/qt6
LIBS += -L/ucrt64/lib -lQt6Widgets -lQt6OpenGL -lQt6OpenGLWidgets


INCLUDEPATH += /ucrt64/include/qt6/QtWidgets \
               /ucrt64/include/qt6/QtOpenGLWidgets \
               /ucrt64/include/qt6

LIBS += -L/ucrt64/lib -lQt6Widgets -lQt6OpenGL -lQt6OpenGLWidgets


DESTDIR = $$OUT_PWD/bin
HOME = /c/msys64/home/jimmy

VTK_DLLS = \
    $$HOME/vtk-install/bin/libvtkRenderingQt-9.5.dll \
    $$HOME/vtk-install/bin/libvtkGUISupportQt-9.5.dll \
    $$HOME/vtk-install/bin/libvtkRenderingOpenGL2-9.5.dll \
    $$HOME/vtk-install/bin/libvtkInteractionStyle-9.5.dll \
    $$HOME/vtk-install/bin/libvtkInteractionWidgets-9.5.dll \
    $$HOME/vtk-install/bin/libvtkRenderingCore-9.5.dll \
    $$HOME/vtk-install/bin/libvtkCommonColor-9.5.dll \
    $$HOME/vtk-install/bin/libvtkCommonComputationalGeometry-9.5.dll \
    $$HOME/vtk-install/bin/libvtkCommonCore-9.5.dll \
    $$HOME/vtk-install/bin/libvtkCommonDataModel-9.5.dll \
    $$HOME/vtk-install/bin/libvtkCommonMath-9.5.dll \
    $$HOME/vtk-install/bin/libvtkCommonMisc-9.5.dll \
    $$HOME/vtk-install/bin/libvtkCommonSystem-9.5.dll \
    $$HOME/vtk-install/bin/libvtkCommonTransforms-9.5.dll \
    $$HOME/vtk-install/bin/libvtkCommonExecutionModel-9.5.dll \
    $$HOME/vtk-install/bin/libvtkFiltersCore-9.5.dll \
    $$HOME/vtk-install/bin/libvtkFiltersExtraction-9.5.dll \
    $$HOME/vtk-install/bin/libvtkFiltersGeneral-9.5.dll \
    $$HOME/vtk-install/bin/libvtkFiltersGeometry-9.5.dll \
    $$HOME/vtk-install/bin/libvtkFiltersHybrid-9.5.dll \
    $$HOME/vtk-install/bin/libvtkFiltersHyperTree-9.5.dll \
    $$HOME/vtk-install/bin/libvtkFiltersModeling-9.5.dll \
    $$HOME/vtk-install/bin/libvtkFiltersSources-9.5.dll \
    $$HOME/vtk-install/bin/libvtkFiltersStatistics-9.5.dll \
    $$HOME/vtk-install/bin/libvtkFiltersTexture-9.5.dll \
    $$HOME/vtk-install/bin/libvtkImagingCore-9.5.dll \
    $$HOME/vtk-install/bin/libvtksys-9.5.dll \
    $$HOME/vtk-install/bin/libvtkfmt-9.5.dll \
    $$HOME/vtk-install/bin/libvtkloguru-9.5.dll \
    $$HOME/vtk-install/bin/libvtkscn-9.5.dll \
    $$HOME/vtk-install/bin/libvtktoken-9.5.dll \
    $$HOME/vtk-install/bin/libvtkpugixml-9.5.dll \
    $$HOME/vtk-install/bin/libvtkParallelCore-9.5.dll \
    $$HOME/vtk-install/bin/libvtkParallelDIY-9.5.dll

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clcommon.cpp \
    cldataset.cpp \
    clparticle.cpp \
    main.cpp \
    mainwindow.cpp \
    vtkwidget.cpp

HEADERS += \
    clcommon.h \
    cldataset.h \
    clparticle.h \
    constants.h \
    mainwindow.h \
    vtkwidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# must deploy VTK dlls with exe
win32 {
        for(dll, VTK_DLLS) {
        COPY_COMMANDS += $$quote("cp -f $$dll $$DESTDIR")$$escape_expand(\\n\\t)

        }
        QMAKE_POST_LINK += $$COPY_COMMANDS
        message("Copy command:  $$escape_expand(\\n\\t) $$COPY_COMMANDS")
}
