// main_window.hpp

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "ui_main_window.h" // generated header

#include "aux_header.hpp"
#include "forms/form_field_editor.hpp"
#include "classes/class_field.hpp"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget * parent = nullptr);
    ~MainWindow();

private:

    Ui::MainWindow * ui;
    QTimer * p_timer;
    ClassField * p_field;
    edit_buffer_t edit_buffer;

    struct
    {
        bool simulation;
    } flag;

    struct
    {
        int ips; // iterations per second
    } param;

    struct
    {
        int generation_number;
        int cell_count;
    } info;

    void InitApplication();
    void EnableWidgets(enum_t app_state);
    void UpdateWidgetsInfo();
    void DrawGraphicScene();
    void ShowMessageBox(QString title, QString text);
    void ReadEditBuffer();
    void WriteEditBuffer();

private slots:

    void Slot_Action_File_Exit();
    void Slot_Action_Help_About();
    void Slot_PushButton_Play();
    void Slot_PushButton_Pause();
    void Slot_PushButton_Stop();
    void Slot_PushButton_Next();
    void Slot_PushButton_Clear();
    void Slot_PushButton_Random();
    void Slot_PushButton_Edit();
    void Slot_PushButton_SaveState();
    void Slot_SpinBox_IPS(int value);
    void Slot_ComboBox_CellColor(int index);
    void Slot_Timer();
};

#endif // MAIN_WINDOW_H
