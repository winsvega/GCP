TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../GCP.cpp \
    ../GCP_Button.cpp \
    ../GCP_CheckBox.cpp \
    ../GCP_ContextMenu.cpp \
    ../GCP_Draw.cpp \
    ../GCP_Edit.cpp \
    ../GCP_Form.cpp \
    ../GCP_Genetic.cpp \
    ../GCP_Graph.cpp \
    ../GCP_Label.cpp \
    ../GCP_Math.cpp \
    ../main.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    ../GCP.h \
    ../GCP_Button.h \
    ../GCP_CheckBox.h \
    ../GCP_Constants.h \
    ../GCP_ContextMenu.h \
    ../GCP_Delegate.h \
    ../GCP_Draw.h \
    ../GCP_Edit.h \
    ../GCP_Form.h \
    ../GCP_FormComponent.h \
    ../GCP_Graph.h \
    ../GCP_IO.h \
    ../GCP_Label.h \
    ../GCP_Math.h \
    ../GCP_MessageBox.h \
    ../GCP_Select.h \
    ../GCP_SPointer.h \
    ../GCP_Style.h \
	../GCP_Vector.h

INCLUDEPATH  += \
	../../SDL2-2.0.3/include \
	../../SDL2_ttf-2.0.12 \
	../../SDL2_gfx-1.0.0

LIBS += \
	-L/usr/local/lib -lSDL2 \
	-L/usr/local/lib -lSDL2_ttf \
	-L/usr/local/lib -lSDL2_gfx
