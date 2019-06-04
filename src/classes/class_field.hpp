// classes/class_field.hpp

#ifndef CLASS_FIELD_H
#define CLASS_FIELD_H

#include "aux_header.hpp"

class ClassField
{
public:

    ClassField();
    ~ClassField();
    void InRawData();
    field_t OutRawData();
    int GetCellCount();
    void SaveField();
    void LoadField();
    void ClearField();
    void RandomField();
    void DoNextGeneration();

private:

    struct
    {
        field_t simulation;
        field_t base;
        field_t next;
        field_t io;
    } field;

    field_t CreateMatrix();
    void DeleteMatrix(field_t pp_matrix);
    void ClearMatrix(field_t pp_matrix);
    void CopyMatrix(field_t pp_matrix_dest, field_t pp_matrix_src);
};

#endif // CLASS_FIELD_H
