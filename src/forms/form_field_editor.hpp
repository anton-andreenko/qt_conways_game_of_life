// forms/form_field_editor.hpp

#ifndef FORM_FIELD_EDITOR_H
#define FORM_FIELD_EDITOR_H

#include "ui_form_field_editor.h" // generated header

#include "aux_header.hpp"

namespace Ui
{
    class FormFieldEditor;
}

class FormFieldEditor : public QDialog
{
    Q_OBJECT

public:

    explicit FormFieldEditor(edit_buffer_t & arg, QWidget * parent = nullptr);
    ~FormFieldEditor();
    bool IsFormAccept();

private:

    Ui::FormFieldEditor * ui;
    edit_buffer_t & r_edit_buffer;

    struct
    {
        bool form_accept;
    } flag;

    struct
    {
        enum_t tool_type;
    } param;

    void InitForm();
    void FixTableSelection();
    void closeEvent(QCloseEvent * e); // override method

private slots:

    void Slot_PushButton_Ok();
    void Slot_PushButton_Cancel();
    void Slot_RadioButton_ToolNone();
    void Slot_RadioButton_ToolOn();
    void Slot_RadioButton_ToolOff();
    void Slot_TableWidget_Field(int row, int column);
};

#endif // FORM_FIELD_EDITOR_H
