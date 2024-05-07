// DO NOT EDIT
#include "dorm.h"
#include "student.h"
#include <stdio.h>

#ifndef REPOSITORY_H
#define REPOSITORY_H

#define DEFAULT_DORM_REPOSITORY "./storage/dorm-repository.txt"
#define DEFAULT_STUDENT_REPOSITORY "./storage/student-repository.txt"

void get_line(FILE *_stream, char *_buffer, unsigned short _size);
void get_string(char *_buffer, unsigned short _size);
short int load_dorms_from_repository(struct dorm_t **_dorms);
short int load_students_from_repository(struct student_t **_students);
void save_dorms_to_repository(struct dorm_t *_dorms,
                              unsigned short _dorm_size);
void save_students_to_repository(struct student_t *_students,
                                 unsigned short _student_size);

#endif
// DO NOT EDIT
