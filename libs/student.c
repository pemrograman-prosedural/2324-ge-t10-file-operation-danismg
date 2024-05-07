#include <stdio.h>
#include <string.h>
#include "student.h"

/**
 * @brief Define the complete function definition here. Be sure to enlist the prototype of each function
 * defined here in the corresponding header file.
 *
 */

struct student_t create_student(char *_id, char *_name, char *_year, enum gender_t _gender)
{
    struct student_t std;

    strcpy(std.id, _id);
    strcpy(std.name, _name);
    strcpy(std.year, _year);
    std.gender = _gender;
    std.dorm = NULL;

    return std;
}

short find_student_index_by_id(struct student_t *_students, unsigned short _student_size, char *_id)
{
    for (unsigned short i = 0; i < _student_size; ++i)
    {
        if (strcmp(_students[i].id, _id) == 0)
        {
            return i;
        }
    }

    return -1;
}

short disband_student_from_dorm(struct student_t **_students, unsigned short _student_size, struct dorm_t *_dorm)
{
    for (unsigned short i = 0; i < _student_size; ++i)
    {
        if ((*_students)[i].dorm != NULL && strcmp((*_students)[i].dorm->name, _dorm->name) == 0)
        {
            _dorm->residents_num--;
            (*_students)[i].dorm = NULL;
        }
    }

    return 1;
}

short assign_student_to_dorm(struct student_t *_student, struct dorm_t *_dorm)
{
    if (_dorm->residents_num >= _dorm->capacity || _student->gender != _dorm->gender)
    {
        return 0;
    }

    _dorm->residents_num++;
    _student->dorm = _dorm;

    return 1;
}

short move_student_to_dorm(struct student_t *_student, struct dorm_t *_dorm)
{
    if (_dorm->residents_num >= _dorm->capacity || _student->gender != _dorm->gender)
    {
        return 0;
    }

    _student->dorm->residents_num--;
    _dorm->residents_num++;
    _student->dorm = _dorm;

    return 1;
}

void print_student(struct student_t _student, unsigned short _is_detailed)
{
    char *text_gender = gender_to_text(_student.gender);

    if (!_is_detailed)
    {
        printf("%s|%s|%s|%s\n",
               _student.id, _student.name, _student.year, text_gender);
        return;
    }

    char dorm_name[20];
    dorm_name[0] = '\0';

    strcpy(dorm_name, "unassigned");

    if (_student.dorm != NULL)
    {
        strcpy(dorm_name, (*_student.dorm).name);
    }

    printf("%s|%s|%s|%s|%s\n",
           _student.id, _student.name, _student.year, text_gender, dorm_name);
}

void print_students(struct student_t *_students, unsigned short _student_size, unsigned short _is_detailed)
{
    for (unsigned short i = 0; i < _student_size; ++i)
    {
        print_student(_students[i], _is_detailed);
    }
}
