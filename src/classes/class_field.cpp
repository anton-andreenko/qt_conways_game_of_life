// classes/class_field.cpp

#include "classes/class_field.hpp"

ClassField::ClassField() :
    field{nullptr, nullptr, nullptr, nullptr}
{
    std::srand(std::time(0));
    field.simulation = CreateMatrix();
    field.base = CreateMatrix();
    field.next = CreateMatrix();
    field.io = CreateMatrix();
    ClearMatrix(field.simulation);
    ClearMatrix(field.base);
    ClearMatrix(field.next);
    ClearMatrix(field.io);
}

ClassField::~ClassField()
{
    DeleteMatrix(field.simulation);
    DeleteMatrix(field.base);
    DeleteMatrix(field.next);
    DeleteMatrix(field.io);
    field.simulation = nullptr;
    field.base = nullptr;
    field.next = nullptr;
    field.io = nullptr;
}

void ClassField::InRawData()
{
    CopyMatrix(field.simulation, field.io);
}

field_t ClassField::OutRawData()
{
    CopyMatrix(field.io, field.simulation);

    return field.io;
}

int ClassField::GetCellCount()
{
    int result = 0;

    for (int y = Y_BEGIN; (y < Y_END); y++)
    {
        for (int x = X_BEGIN; (x < X_END); x++)
        {
            if (field.simulation[y][x] == CELL_ON)
            {
                result += 1;
            }
        }
    }

    return result;
}

void ClassField::SaveField()
{
    CopyMatrix(field.base, field.simulation);
}

void ClassField::LoadField()
{
    CopyMatrix(field.simulation, field.base);
}

void ClassField::ClearField()
{
    ClearMatrix(field.simulation);
}

void ClassField::RandomField()
{
    int x_middle = static_cast<int>(MATRIX_SIZE_X / 2);
    int y_middle = static_cast<int>(MATRIX_SIZE_Y / 2);
    int max_rand_value_1 = std::rand() % 7 + 2;
    int max_rand_value_2 = std::rand() % 7 + 2;
    int max_rand_value_3 = std::rand() % 7 + 2;
    int max_rand_value_4 = std::rand() % 7 + 2;
    int rand_value = 0;

    for (int y = Y_BEGIN; (y < Y_END); y++)
    {
        for (int x = X_BEGIN; (x < X_END); x++)
        {
            if ((y >= y_middle) && (x >= x_middle))
            {
                rand_value = std::rand() % (max_rand_value_1 + 1);
            }
            else if ((y >= y_middle) && (x < x_middle))
            {
                rand_value = std::rand() % (max_rand_value_2 + 1);
            }
            else if ((y < y_middle) && (x < x_middle))
            {
                rand_value = std::rand() % (max_rand_value_3 + 1);
            }
            else if ((y < y_middle) && (x >= x_middle))
            {
                rand_value = std::rand() % (max_rand_value_4 + 1);
            }

            if (rand_value == 0)
            {
                field.simulation[y][x] = CELL_ON;
            }
            else
            {
                field.simulation[y][x] = CELL_OFF;
            }
        }
    }
}

void ClassField::DoNextGeneration()
{
    int cells_around = 0;

    for (int y = Y_BEGIN; (y < Y_END); y++)
    {
        for (int x = X_BEGIN; (x < X_END); x++)
        {
            cells_around =
                static_cast<int>(field.simulation[y - 1][x - 1]) +
                static_cast<int>(field.simulation[y - 1][x]) +
                static_cast<int>(field.simulation[y - 1][x + 1]) +
                static_cast<int>(field.simulation[y][x - 1]) +
                static_cast<int>(field.simulation[y][x + 1]) +
                static_cast<int>(field.simulation[y + 1][x - 1]) +
                static_cast<int>(field.simulation[y + 1][x]) +
                static_cast<int>(field.simulation[y + 1][x + 1]);

            if (field.simulation[y][x] == CELL_OFF)
            {
                if (cells_around == 3)
                {
                    field.next[y][x] = CELL_ON;
                }
                else
                {
                    field.next[y][x] = CELL_OFF;
                }
            }
            else if (field.simulation[y][x] == CELL_ON)
            {
                if ((cells_around == 2) || (cells_around == 3))
                {
                    field.next[y][x] = CELL_ON;
                }
                else
                {
                    field.next[y][x] = CELL_OFF;
                }
            }
        }
    }

    CopyMatrix(field.simulation, field.next);
}

field_t ClassField::CreateMatrix()
{
    cell_t ** pp_matrix = new cell_t * [MATRIX_SIZE_Y];

    for (int y = 0; (y < MATRIX_SIZE_Y); y++)
    {
        pp_matrix[y] = new cell_t [MATRIX_SIZE_X];
    }

    return pp_matrix;
}

void ClassField::DeleteMatrix(field_t pp_matrix)
{
    for (int y = 0; (y < MATRIX_SIZE_Y); y++)
    {
        delete[] pp_matrix[y];
    }

    delete[] pp_matrix;
}

void ClassField::ClearMatrix(field_t pp_matrix)
{
    for (int y = 0; (y < MATRIX_SIZE_Y); y++)
    {
        for (int x = 0; (x < MATRIX_SIZE_X); x++)
        {
            pp_matrix[y][x] = CELL_OFF;
        }
    }
}

void ClassField::CopyMatrix(field_t pp_matrix_dest, field_t pp_matrix_src)
{
    for (int y = 0; (y < MATRIX_SIZE_Y); y++)
    {
        for (int x = 0; (x < MATRIX_SIZE_X); x++)
        {
            pp_matrix_dest[y][x] = pp_matrix_src[y][x];
        }
    }
}
