// widgets/widget_paint_area.hpp

#ifndef WIDGET_PAINT_AREA_H
#define WIDGET_PAINT_AREA_H

#include "aux_header.hpp"
#include "classes/class_field.hpp"

class WidgetPaintArea : public QWidget
{
    Q_OBJECT

public:

    explicit WidgetPaintArea(QWidget * parent = nullptr);
    ~WidgetPaintArea();
    void SetField(ClassField * arg);
    void SetPaintColor(enum_t paint_color);

private:

    ClassField * p_field;

    struct
    {
        QColor background_black;
        QColor background_white;
        QColor black;
        QColor red;
        QColor green;
        QColor blue;
    } color;

    struct
    {
        QPen background;
        QPen black;
    } pen;

    struct
    {
        QBrush background;
        QBrush red;
        QBrush green;
        QBrush blue;
    } brush;

    struct
    {
        int polygon_size_x;
        int polygon_size_y;
        int scene_margin;
    } area;

    struct
    {
        enum_t paint_color;
    } param;

    void paintEvent(QPaintEvent * e); // override method
};

#endif // WIDGET_PAINT_AREA_H
