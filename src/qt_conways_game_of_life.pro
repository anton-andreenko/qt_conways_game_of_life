# qt_conways_game_of_life.pro

QT += core gui widgets

TARGET = qt_conways_game_of_life

TEMPLATE = app

CONFIG += c++11

HEADERS += \
    aux_header.hpp \
    main_window.hpp \
    forms/form_field_editor.hpp \
    widgets/widget_paint_area.hpp \
    classes/class_field.hpp

SOURCES += \
    main.cpp \
    main_window.cpp \
    main_window_slots.cpp \
    forms/form_field_editor.cpp \
    forms/form_field_editor_slots.cpp \
    widgets/widget_paint_area.cpp \
    classes/class_field.cpp

FORMS += \
    main_window.ui \
    forms/form_field_editor.ui

RESOURCES += \
    resources.qrc
