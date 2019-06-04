// widgets/widget_paint_area.cpp

#include "widgets/widget_paint_area.hpp"

WidgetPaintArea::WidgetPaintArea(QWidget * parent) :
    QWidget(parent),
    p_field(nullptr)
{
    color.background_black = QColor(0, 0, 0);
    color.background_white = QColor(255, 255, 255);
    color.black = QColor(50, 50, 50);
    color.red = QColor(240, 120, 120);
    color.green = QColor(50, 200, 50);
    color.blue = QColor(100, 150, 250);
    pen.background = QPen(color.background_black, 1, Qt::SolidLine);
    pen.black = QPen(color.black, 1, Qt::SolidLine);
    brush.background = QBrush(color.background_white, Qt::SolidPattern);
    brush.red = QBrush(color.red, Qt::SolidPattern);
    brush.green = QBrush(color.green, Qt::SolidPattern);
    brush.blue = QBrush(color.blue, Qt::SolidPattern);
    area.polygon_size_x = 6;
    area.polygon_size_y = 6;
    area.scene_margin = 4;
    param.paint_color = PAINT_COLOR_DEFAULT;
}

WidgetPaintArea::~WidgetPaintArea()
{
    p_field = nullptr;
}

void WidgetPaintArea::SetField(ClassField * arg)
{
    p_field = arg;
}

void WidgetPaintArea::SetPaintColor(enum_t paint_color)
{
    param.paint_color = paint_color;
}

void WidgetPaintArea::paintEvent(QPaintEvent * e)
{
    QPainter painter;
    painter.begin(this);
    painter.setPen(pen.background);
    painter.setBrush(brush.background);
    painter.drawRect(
        QRect(0, 0, (this->width() - 1), (this->height() - 1))
    );

    if (nullptr != p_field)
    {
        field_t tmp_field = p_field->OutRawData();
        painter.setPen(pen.black);

        if (param.paint_color == PAINT_COLOR_RED)
        {
            painter.setBrush(brush.red);
        }
        else if (param.paint_color == PAINT_COLOR_GREEN)
        {
            painter.setBrush(brush.green);
        }
        else if (param.paint_color == PAINT_COLOR_BLUE)
        {
            painter.setBrush(brush.blue);
        }
        else
        {
            painter.setBrush(Qt::NoBrush);
        }

        for (int y = Y_BEGIN; (y < Y_END); y++)
        {
            for (int x = X_BEGIN; (x < X_END); x++)
            {
                if (tmp_field[y][x] == CELL_ON)
                {
                    painter.drawRect(
                        QRect(
                            ((x - 1) * area.polygon_size_x + area.scene_margin),
                            ((y - 1) * area.polygon_size_y + area.scene_margin),
                            area.polygon_size_x,
                            area.polygon_size_y
                        )
                    );
                }
            }
        }
    }

    painter.end();
}
