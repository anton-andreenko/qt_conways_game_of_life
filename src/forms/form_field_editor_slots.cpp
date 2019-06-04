// forms/form_field_editor_slots.cpp

#include "forms/form_field_editor.hpp"

void FormFieldEditor::Slot_PushButton_Ok()
{
    flag.form_accept = true;
    QDialog::accept();
}

void FormFieldEditor::Slot_PushButton_Cancel()
{
    flag.form_accept = false;
    QDialog::reject();
}

void FormFieldEditor::Slot_RadioButton_ToolNone()
{
    param.tool_type = EDIT_TOOL_NONE;
    FixTableSelection();
}

void FormFieldEditor::Slot_RadioButton_ToolOn()
{
    param.tool_type = EDIT_TOOL_ON;
    FixTableSelection();
}

void FormFieldEditor::Slot_RadioButton_ToolOff()
{
    param.tool_type = EDIT_TOOL_OFF;
    FixTableSelection();
}

void FormFieldEditor::Slot_TableWidget_Field(int row, int column)
{
    if (param.tool_type == EDIT_TOOL_ON)
    {
        r_edit_buffer[row * FIELD_SIZE_X + column] = CELL_ON;
        ui->TableWidget_Field->item(row, column)->setBackground(Qt::darkGreen);
    }
    else if (param.tool_type == EDIT_TOOL_OFF)
    {
        r_edit_buffer[row * FIELD_SIZE_X + column] = CELL_OFF;
        ui->TableWidget_Field->item(row, column)->setBackground(Qt::white);
    }
}
