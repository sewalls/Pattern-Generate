QT += widgets
requires(qtConfig(combobox))

HEADERS     = renderarea.h \
              window.h \
    vec2d.h \
    shape.h \
    line.h \
    rectangle.h \
    ellipse.h \
    freedraw.h \
    colorwindow.h
SOURCES     = main.cpp \
              renderarea.cpp \
	      window.cpp \
    vec2d.cpp \
    shape.cpp \
    line.cpp \
    rectangle.cpp \
    ellipse.cpp \
    freedraw.cpp \
    colorwindow.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/painting/transformations
INSTALLS += target
