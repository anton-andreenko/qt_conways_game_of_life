// aux_header.hpp

#ifndef AUX_HEADER_H
#define AUX_HEADER_H

#include <QApplication>
#include <QBrush>
#include <QCloseEvent>
#include <QColor>
#include <QDialog>
#include <QIcon>
#include <QMainWindow>
#include <QMessageBox>
#include <QModelIndex>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QRect>
#include <QSize>
#include <QString>
#include <QTableWidgetItem>
#include <QTimer>
#include <QWidget>

#include <cstdlib>
#include <ctime>
#include <vector>

// aliases

typedef int enum_t;
typedef int cell_t;
typedef cell_t ** field_t;
typedef std::vector<cell_t> edit_buffer_t;

// constants

const int FIELD_SIZE_X = 120;
const int FIELD_SIZE_Y = 120;

const int MATRIX_SIZE_X = FIELD_SIZE_X + 2;
const int MATRIX_SIZE_Y = FIELD_SIZE_Y + 2;

const int X_BEGIN = 1;
const int X_END = FIELD_SIZE_X + 1;
const int Y_BEGIN = 1;
const int Y_END = FIELD_SIZE_Y + 1;

const cell_t CELL_OFF = 0;
const cell_t CELL_ON = 1;

const enum_t APP_STATE_DEFAULT = 1;
const enum_t APP_STATE_PLAY = 2;
const enum_t APP_STATE_PAUSE = 3;
const enum_t APP_STATE_STOP = 4;
const enum_t APP_STATE_NEXT = 5;

const enum_t PAINT_COLOR_RED = 1;
const enum_t PAINT_COLOR_GREEN = 2;
const enum_t PAINT_COLOR_BLUE = 3;
const enum_t PAINT_COLOR_DEFAULT = PAINT_COLOR_GREEN;

const enum_t EDIT_TOOL_NONE = 1;
const enum_t EDIT_TOOL_ON = 2;
const enum_t EDIT_TOOL_OFF = 3;

#endif // AUX_HEADER_H
