// main_window.cpp

#include "main_window.hpp"

MainWindow::MainWindow(QWidget * parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    p_timer(nullptr),
    p_field(nullptr)
{
    ui->setupUi(this);
    InitApplication();
    EnableWidgets(APP_STATE_DEFAULT);
    UpdateWidgetsInfo();
    DrawGraphicScene();

    // signals & slots

    connect(ui->Action_File_Exit, SIGNAL(triggered(bool)), SLOT(Slot_Action_File_Exit()));
    connect(ui->Action_Help_About, SIGNAL(triggered(bool)), SLOT(Slot_Action_Help_About()));
    connect(ui->ComboBox_CellColor, SIGNAL(currentIndexChanged(int)), SLOT(Slot_ComboBox_CellColor(int)));
    connect(ui->PushButton_Clear, SIGNAL(released()), SLOT(Slot_PushButton_Clear()));
    connect(ui->PushButton_Edit, SIGNAL(released()), SLOT(Slot_PushButton_Edit()));
    connect(ui->PushButton_Next, SIGNAL(released()), SLOT(Slot_PushButton_Next()));
    connect(ui->PushButton_Pause, SIGNAL(released()), SLOT(Slot_PushButton_Pause()));
    connect(ui->PushButton_Play, SIGNAL(released()), SLOT(Slot_PushButton_Play()));
    connect(ui->PushButton_Random, SIGNAL(released()), SLOT(Slot_PushButton_Random()));
    connect(ui->PushButton_SaveState, SIGNAL(released()), SLOT(Slot_PushButton_SaveState()));
    connect(ui->PushButton_Stop, SIGNAL(released()), SLOT(Slot_PushButton_Stop()));
    connect(ui->SpinBox_IPS, SIGNAL(valueChanged(int)), SLOT(Slot_SpinBox_IPS(int)));
    connect(p_timer, SIGNAL(timeout()), SLOT(Slot_Timer()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete p_timer;
    delete p_field;
}

void MainWindow::InitApplication()
{
    p_timer = new QTimer(this);
    p_timer->setTimerType(Qt::PreciseTimer);
    p_field = new ClassField();
    edit_buffer.clear();
    edit_buffer.resize(FIELD_SIZE_X * FIELD_SIZE_Y);
    flag.simulation = false;
    param.ips = 20;
    info.generation_number = 1;
    info.cell_count = 0;

    // UI config

    ui->ComboBox_CellColor->setCurrentIndex(1);
    ui->Label_CellCount->setText(
        QString("Cells: %1").arg(QString::number(info.cell_count))
    );
    ui->Label_FieldSize->setText(
        QString("Field size: %1 * %2").arg(QString::number(FIELD_SIZE_X), QString::number(FIELD_SIZE_Y))
    );
    ui->Label_GenerationNumber->setText(
        QString("Generation: %1").arg(QString::number(info.generation_number))
    );
    ui->PushButton_Clear->setIcon(QIcon(":/resources/icons/field_clear.png"));
    ui->PushButton_Clear->setIconSize(QSize(40, 40));
    ui->PushButton_Edit->setIcon(QIcon(":/resources/icons/field_edit.png"));
    ui->PushButton_Edit->setIconSize(QSize(40, 40));
    ui->PushButton_Next->setIcon(QIcon(":/resources/icons/simulation_next.png"));
    ui->PushButton_Next->setIconSize(QSize(40, 40));
    ui->PushButton_Pause->setIcon(QIcon(":/resources/icons/simulation_pause.png"));
    ui->PushButton_Pause->setIconSize(QSize(40, 40));
    ui->PushButton_Play->setIcon(QIcon(":/resources/icons/simulation_play.png"));
    ui->PushButton_Play->setIconSize(QSize(40, 40));
    ui->PushButton_Random->setIcon(QIcon(":/resources/icons/field_random.png"));
    ui->PushButton_Random->setIconSize(QSize(40, 40));
    ui->PushButton_SaveState->setIcon(QIcon(":/resources/icons/field_save.png"));
    ui->PushButton_SaveState->setIconSize(QSize(30, 30));
    ui->PushButton_Stop->setIcon(QIcon(":/resources/icons/simulation_stop.png"));
    ui->PushButton_Stop->setIconSize(QSize(40, 40));
    ui->SpinBox_IPS->setValue(param.ips);
    ui->WidgetPaintArea_GraphicScene->SetField(p_field);
}

void MainWindow::EnableWidgets(enum_t app_state)
{
    if (
        (app_state == APP_STATE_DEFAULT) ||
        (app_state == APP_STATE_PAUSE) ||
        (app_state == APP_STATE_STOP) ||
        (app_state == APP_STATE_NEXT)
    )
    {
        ui->PushButton_Clear->setEnabled(true);
        ui->PushButton_Edit->setEnabled(true);
        ui->PushButton_Next->setEnabled(true);
        ui->PushButton_Pause->setEnabled(false);
        ui->PushButton_Play->setEnabled(true);
        ui->PushButton_Random->setEnabled(true);
        ui->PushButton_SaveState->setEnabled(true);
        ui->PushButton_Stop->setEnabled(true);
    }
    else if (app_state == APP_STATE_PLAY)
    {
        ui->PushButton_Clear->setEnabled(false);
        ui->PushButton_Edit->setEnabled(false);
        ui->PushButton_Next->setEnabled(false);
        ui->PushButton_Pause->setEnabled(true);
        ui->PushButton_Play->setEnabled(false);
        ui->PushButton_Random->setEnabled(false);
        ui->PushButton_SaveState->setEnabled(false);
        ui->PushButton_Stop->setEnabled(true);
    }
}

void MainWindow::UpdateWidgetsInfo()
{
    ui->Label_CellCount->setText(
        QString("Cells: %1").arg(QString::number(info.cell_count))
    );
    ui->Label_GenerationNumber->setText(
        QString("Generation: %1").arg(QString::number(info.generation_number))
    );
}

void MainWindow::DrawGraphicScene()
{
    ui->WidgetPaintArea_GraphicScene->update();
}

void MainWindow::ShowMessageBox(QString title, QString text)
{
    QMessageBox message_box(QMessageBox::NoIcon, title, text);
    message_box.exec();
}

void MainWindow::ReadEditBuffer()
{
    field_t tmp_field = p_field->OutRawData();
    int index = 0;

    for (int y = Y_BEGIN; (y < Y_END); y++)
    {
        for (int x = X_BEGIN; (x < X_END); x++)
        {
            tmp_field[y][x] = edit_buffer[index];
            index += 1;
        }
    }

    p_field->InRawData();
}

void MainWindow::WriteEditBuffer()
{
    field_t tmp_field = p_field->OutRawData();
    int index = 0;
    edit_buffer.clear();
    edit_buffer.resize(FIELD_SIZE_X * FIELD_SIZE_Y);

    for (int y = Y_BEGIN; (y < Y_END); y++)
    {
        for (int x = X_BEGIN; (x < X_END); x++)
        {
            edit_buffer[index] = tmp_field[y][x];
            index += 1;
        }
    }
}
