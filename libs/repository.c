// NIM - Name
// NIM - Name

#include "repository.h"
#include "dorm.h"
#include "gender.h"
#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_string(char *_buffer, unsigned short _size) {
  get_line(stdin, _buffer, _size);
}

void get_line(FILE *_stream, char *_buffer, unsigned short _size) {
  char ch = '\0';
  unsigned int i = 0;
  _buffer[i] = '\0';

  while (i < _size && (ch = fgetc(_stream)) != EOF) {
    if (ch == '\r') {
      continue;
    }

    if (ch == '\n') {
      break;
    }

    _buffer[i++] = ch;
    _buffer[i] = '\0';
  }
}

short int load_dorms_from_repository(struct dorm_t **_dorms)
{
  FILE *repository = fopen(DEFAULT_DORM_REPOSITORY, "r");

  if (repository == NULL)
  {
    printf("Opps, something went wrong when trying to open the stream.\n");
    return -1;
  }

  char input[101];
  char cinput[101];
  const char *separator = "|";

  // sentinel variable
  unsigned short int dorm_size = 0;

  while (1)
  {
    get_line(repository, input, 100);

    if (strlen(input) == 0)
    {
      break;
    }

    strcpy(cinput, input);
    char *name = strtok(cinput, separator);
    char *scapacity = strtok(NULL, separator);
    char *sgender = strtok(NULL, separator);
    unsigned short capacity = atoi(scapacity);
    enum gender_t gender = text_to_gender(sgender);

    struct dorm_t new_dorm =
        create_dorm(name, capacity, gender);

    // allocate the students as an array
    ++dorm_size;
    if (dorm_size == 1)
    {
      *_dorms = malloc(sizeof(struct dorm_t) * dorm_size);
    }
    else
    {
      *_dorms = realloc(*_dorms, sizeof(struct dorm_t) * dorm_size);
    }

    (*_dorms)[dorm_size - 1] = new_dorm;
  }

  int closing_err = fclose(repository);
  if (closing_err != 0)
  {
    printf("Opps, something went wrong when trying to close the stream.\n");
    return closing_err;
  }

  return dorm_size;
}

short int load_students_from_repository(struct student_t **_students)
{
  FILE *repository = fopen(DEFAULT_STUDENT_REPOSITORY, "r");

  if (repository == NULL)
  {
    printf("Opps, something went wrong when trying to open the stream.\n");
    return -1;
  }

  char input[101];
  char cinput[101];
  const char *separator = "|";

  // sentinel variable
  unsigned short int student_size = 0;

  while (1)
  {
    get_line(repository, input, 100);

    if (strlen(input) == 0)
    {
      break;
    }

    strcpy(cinput, input);
    char *id = strtok(cinput, separator);
    char *name = strtok(NULL, separator);
    char *year = strtok(NULL, separator);
    char *sgender = strtok(NULL, separator);
    enum gender_t gender = text_to_gender(sgender);

    struct student_t new_student =
        create_student(id, name, year, gender);

    // allocate the students as an array
    ++student_size;
    if (student_size == 1)
    {
      *_students = malloc(sizeof(struct student_t) * student_size);
    }
    else
    {
      *_students = realloc(*_students, sizeof(struct student_t) * student_size);
    }

    (*_students)[student_size - 1] = new_student;
  }

  int closing_err = fclose(repository);
  if (closing_err != 0)
  {
    printf("Opps, something went wrong when trying to close the stream.\n");
    return closing_err;
  }

  return student_size;
}

void save_dorms_to_repository(struct dorm_t *_dorms,
                              unsigned short _dorm_size)
{
  FILE *repository = fopen(DEFAULT_DORM_REPOSITORY, "w");

  if (repository == NULL)
  {
    printf("Opps, something went wrong when trying to open the stream.\n");
  }

  for (short int index = 0; index < _dorm_size; ++index)
  {
    fprintf(repository, "%s|%d|%s\n", _dorms[index].name,
            _dorms[index].capacity, gender_to_text(_dorms[index].gender));
  }

  fflush(repository);

  int closing_err = fclose(repository);
  if (closing_err != 0)
  {
    printf("Opps, something went wrong when trying to close the stream.\n");
  }
}

void save_students_to_repository(struct student_t *_students,
                                 unsigned short _student_size)
{
  FILE *repository = fopen(DEFAULT_STUDENT_REPOSITORY, "w");

  if (repository == NULL)
  {
    printf("Opps, something went wrong when trying to open the stream.\n");
  }

  for (short int index = 0; index < _student_size; ++index)
  {
    fprintf(repository, "%s|%s|%s|%s\n", _students[index].id,
            _students[index].name, _students[index].year,
            gender_to_text(_students[index].gender));
  }

  fflush(repository);

  int closing_err = fclose(repository);
  if (closing_err != 0)
  {
    printf("Opps, something went wrong when trying to close the stream.\n");
  }
}
