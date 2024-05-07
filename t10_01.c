// NIM - Daniel
// NIM - Name

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./libs/dorm.h"
#include "./libs/student.h"
#include "./libs/repository.h"

int main(int _argc, char **_argv)
{
    char input[101];
    char cinput[101];
    const char *separator = "#";

    // sentinel variable
    unsigned short int student_size = 0;
    unsigned short int dorm_size = 0;

    // pointer-types structure variable
    struct student_t *students = NULL;
    struct dorm_t *dorms = NULL;

    // load from the repositories
    dorm_size = load_dorms_from_repository(&dorms);
    student_size = load_students_from_repository(&students);

    while (1)
    {
        get_string(input, 100);
        strcpy(cinput, input);

        char *command = strtok(cinput, separator);
        if (strcmp("---", command) == 0)
        {
            break;
        }

        if (strcmp("student-add", command) == 0)
        {
            //<student id>#<student name>#<year>#<gender>
            char *id = strtok(NULL, separator);
            char *name = strtok(NULL, separator);
            char *year = strtok(NULL, separator);
            char *str_gender = strtok(NULL, separator);
            enum gender_t gender = text_to_gender(str_gender);

            struct student_t new_student =
                create_student(id, name, year, gender);

            // allocate the students as array
            ++student_size;
            if (student_size == 1)
            {
                students = malloc(sizeof(struct student_t) * student_size);
            }
            else
            {
                students = realloc(students, sizeof(struct student_t) * student_size);
            }

            students[student_size - 1] = new_student;
        }
        else if (strcmp("student-print-all-detail", command) == 0)
        {
            // T09.01.b
            unsigned short is_detailed = 1;

            print_students(students, student_size, is_detailed);
        }
        else if (strcmp("student-print-all", command) == 0)
        {
            unsigned short is_detailed = 0;

            print_students(students, student_size, is_detailed);
        }
        else if (strcmp("dorm-add", command) == 0)
        {
            // dorm-add#Pniel#4#female
            char *name = strtok(NULL, separator);
            char *str_capacity = strtok(NULL, separator);
            char *str_gender = strtok(NULL, separator);
            unsigned short capacity = atoi(str_capacity);
            enum gender_t gender = text_to_gender(str_gender);

            struct dorm_t new_dorm =
                create_dorm(name, capacity, gender);

            // allocate the students as array
            ++dorm_size;
            if (dorm_size == 1)
            {
                dorms = malloc(sizeof(struct dorm_t) * dorm_size);
            }
            else
            {
                dorms = realloc(dorms, sizeof(struct dorm_t) * dorm_size);
            }

            dorms[dorm_size - 1] = new_dorm;
        }
        else if (strcmp("dorm-print-all", command) == 0)
        {
            unsigned short is_detailed = 0;

            print_dorms(dorms, dorm_size, is_detailed);
        }
        else if (strcmp("dorm-empty", command) == 0)
        {
            char *name = strtok(NULL, separator);

            short dorm_index = find_dorm_index_by_name(dorms, dorm_size, name);

            if (dorm_index == -1)
            {
                continue;
            }

            struct dorm_t *dorm = &dorms[dorm_index];
            disband_student_from_dorm(&students, student_size, dorm);
        }
        else if (strcmp("dorm-print-all-detail", command) == 0)
        {
            // T09.01.b
            unsigned short is_detailed = 1;

            print_dorms(dorms, dorm_size, is_detailed);
        }
        else if (strcmp("assign-student", command) == 0 || strcmp("move-student", command) == 0)
        {
            // T09.02 & T09.03
            char *id = strtok(NULL, separator);
            char *name = strtok(NULL, separator);

            short student_index = find_student_index_by_id(students, student_size, id);

            if (student_index == -1)
            {
                continue;
            }

            short dorm_index = find_dorm_index_by_name(dorms, dorm_size, name);

            if (dorm_index == -1)
            {
                continue;
            }

            struct student_t *student = &students[student_index];
            struct dorm_t *dorm = &dorms[dorm_index];

            // pointer to function
            short (*pf)(struct student_t * _student, struct dorm_t * _dorm) = NULL;

            pf = (student->dorm == NULL) ? assign_student_to_dorm : move_student_to_dorm;

            pf(student, dorm);
        }
    }

    // save_dorms_to_repository(dorms, dorm_size);
    // save_students_to_repository(students, student_size);

    return 0;
}
