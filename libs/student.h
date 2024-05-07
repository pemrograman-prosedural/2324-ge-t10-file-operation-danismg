#ifndef STUDENT_H
#define STUDENT_H

#include "gender.h"
#include "dorm.h"

/**
 * @brief define your structure, enums, globally accessible variables, and function prototypes here.
 * The actual function implementation should be defined in the corresponding source file.
 *
 */

struct student_t
{
    char id[12];
    char name[40];
    char year[5];
    enum gender_t gender;
    struct dorm_t *dorm;
};

struct student_t create_student(char *_id, char *_name, char *_year, enum gender_t _gender);

short find_student_index_by_id(struct student_t *_students, unsigned short _student_size, char *_id);

short disband_student_from_dorm(struct student_t **_students, unsigned short _student_size, struct dorm_t *_dorm);

short assign_student_to_dorm(struct student_t *_student, struct dorm_t *_dorm);

short move_student_to_dorm(struct student_t *_student, struct dorm_t *_dorm);

void print_student(struct student_t _student, unsigned short _is_detailed);

void print_students(struct student_t *_students, unsigned short _student_size, unsigned short _is_detailed);

#endif
