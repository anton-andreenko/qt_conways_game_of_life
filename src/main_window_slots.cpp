// main_window_slots.cpp

#include "main_window.hpp"

void MainWindow::Slot_Action_File_Exit()
{
    QApplication::quit();
}

void MainWindow::Slot_Action_Help_About()
{
    QString title;
    QString text;
    title.append("About");
    text.append("<div><b>Conway's Game of Life</b><hr/>Author: Anton Andreenko</div>");
    ShowMessageBox(title, text);
}

void MainWindow::Slot_PushButton_Play()
{
    if (false == flag.simulation)
    {
        flag.simulation = true;
        p_timer->start(
            static_cast<int>(1000 / param.ips)
        );
        EnableWidgets(APP_STATE_PLAY);
    }
}

void MainWindow::Slot_PushButton_Pause()
{
    if (true == flag.simulation)
    {
        flag.simulation = false;
        p_timer->stop();
        EnableWidgets(APP_STATE_PAUSE);
    }
}

void MainWindow::Slot_PushButton_Stop()
{
    if (true == flag.simulation)
    {
        flag.simulation = false;
        p_timer->stop();
    }

    p_field->LoadField();
    info.generation_number = 1;
    info.cell_count = p_field->GetCellCount();
    EnableWidgets(APP_STATE_STOP);
    UpdateWidgetsInfo();
    DrawGraphicScene();
}

void MainWindow::Slot_PushButton_Next()
{
    if (false == flag.simulation)
    {
        p_field->DoNextGeneration();
        info.generation_number += 1;
        info.cell_count = p_field->GetCellCount();
        EnableWidgets(APP_STATE_NEXT);
        UpdateWidgetsInfo();
        DrawGraphicScene();
    }
}

void MainWindow::Slot_PushButton_Clear()
{
    if (false == flag.simulation)
    {
        p_field->ClearField();
        info.generation_number = 1;
        info.cell_count = 0;
        UpdateWidgetsInfo();
        DrawGraphicScene();
    }
}

void MainWindow::Slot_PushButton_Random()
{
    if (false == flag.simulation)
    {
        p_field->RandomField();
        info.generation_number = 1;
        info.cell_count = p_field->GetCellCount();
        UpdateWidgetsInfo();
        DrawGraphicScene();
    }
}

void MainWindow::Slot_PushButton_Edit()
{
    if (false == flag.simulation)
    {
        WriteEditBuffer();
        FormFieldEditor * p_form = new FormFieldEditor(edit_buffer, this);
        Qt::WindowFlags window_flags =
            Qt::Window |
            Qt::WindowMaximizeButtonHint |
            Qt::WindowCloseButtonHint;
        p_form->setWindowFlags(window_flags);
        p_form->exec();

        if (true == p_form->IsFormAccept())
        {
            ReadEditBuffer();
            info.cell_count = p_field->GetCellCount();
            UpdateWidgetsInfo();
            DrawGraphicScene();
        }

        delete p_form;
    }
}

void MainWindow::Slot_PushButton_SaveState()
{
    if (false == flag.simulation)
    {
        p_field->SaveField();
        info.generation_number = 1;
        UpdateWidgetsInfo();
    }
}

void MainWindow::Slot_SpinBox_IPS(int value)
{
    param.ips = value;
    p_timer->setInterval(
        static_cast<int>(1000 / param.ips)
    );
}

void MainWindow::Slot_ComboBox_CellColor(int index)
{
    enum_t paint_color = PAINT_COLOR_DEFAULT;

    if (index == 0)
    {
        paint_color = PAINT_COLOR_RED;
    }
    else if (index == 1)
    {
        paint_color = PAINT_COLOR_GREEN;
    }
    else if (index == 2)
    {
        paint_color = PAINT_COLOR_BLUE;
    }

    ui->WidgetPaintArea_GraphicScene->SetPaintColor(paint_color);

    if (false == flag.simulation)
    {
        DrawGraphicScene();
    }
}

void MainWindow::Slot_Timer()
{
    p_field->DoNextGeneration();
    info.generation_number += 1;
    info.cell_count = p_field->GetCellCount();
    UpdateWidgetsInfo();
    DrawGraphicScene();
}
