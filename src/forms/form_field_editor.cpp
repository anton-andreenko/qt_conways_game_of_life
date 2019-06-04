// forms/form_field_editor.cpp

#include "forms/form_field_editor.hpp"

FormFieldEditor::FormFieldEditor(edit_buffer_t & arg, QWidget * parent) :
    QDialog(parent),
    ui(new Ui::FormFieldEditor),
    r_edit_buffer(arg)
{
    ui->setupUi(this);
    InitForm();
    FixTableSelection();

    // signals & slots

    connect(ui->PushButton_Cancel, SIGNAL(released()), SLOT(Slot_PushButton_Cancel()));
    connect(ui->PushButton_Ok, SIGNAL(released()), SLOT(Slot_PushButton_Ok()));
    connect(ui->RadioButton_ToolNone, SIGNAL(clicked(bool)), SLOT(Slot_RadioButton_ToolNone()));
    connect(ui->RadioButton_ToolOff, SIGNAL(clicked(bool)), SLOT(Slot_RadioButton_ToolOff()));
    connect(ui->RadioButton_ToolOn, SIGNAL(clicked(bool)), SLOT(Slot_RadioButton_ToolOn()));
    connect(ui->TableWidget_Field, SIGNAL(currentCellChanged(int, int, int, int)), SLOT(Slot_TableWidget_Field(int, int)));
}

FormFieldEditor::~FormFieldEditor()
{
    delete ui;
}

bool FormFieldEditor::IsFormAccept()
{
    bool result = flag.form_accept;

    return result;
}

void FormFieldEditor::InitForm()
{
    flag.form_accept = false;
    param.tool_type = EDIT_TOOL_NONE;

    // UI config

    ui->RadioButton_ToolNone->setChecked(true);
    ui->TableWidget_Field->setRowCount(FIELD_SIZE_Y);
    ui->TableWidget_Field->setColumnCount(FIELD_SIZE_X);
    ui->TableWidget_Field->setStyleSheet("QTableWidget { selection-background-color: #FA9600; }");

    for (int y = 0; (y < FIELD_SIZE_Y); y++)
    {
        for (int x = 0; (x < FIELD_SIZE_X); x++)
        {
            ui->TableWidget_Field->setItem(y, x, new QTableWidgetItem());

            if (r_edit_buffer[y * FIELD_SIZE_X + x] == CELL_ON)
            {
                ui->TableWidget_Field->item(y, x)->setBackground(Qt::darkGreen);
            }
            else
            {
                ui->TableWidget_Field->item(y, x)->setBackground(Qt::white);
            }
        }
    }
}

void FormFieldEditor::FixTableSelection()
{
    QModelIndex model_index = ui->TableWidget_Field->model()->index(-1, -1);
    ui->TableWidget_Field->blockSignals(true);
    ui->TableWidget_Field->setCurrentIndex(model_index);
    ui->TableWidget_Field->clearSelection();
    ui->TableWidget_Field->blockSignals(false);
}

void FormFieldEditor::closeEvent(QCloseEvent * e)
{
    flag.form_accept = false;
    e->accept();
}
