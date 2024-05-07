#include <stdio.h>
#include <string.h>
#include "gender.h"
#include "dorm.h"

/**
 * @brief Define the complete function definition here. Be sure to enlist the prototype of each function
 * defined here in the corresponding header file.
 *
 */

struct dorm_t create_dorm(char *_name, unsigned short _capacity, enum gender_t _gender)
{
    struct dorm_t dorm;

    strcpy(dorm.name, _name);
    dorm.capacity = _capacity;
    dorm.gender = _gender;
    dorm.residents_num = 0;

    return dorm;
}

short find_dorm_index_by_name(struct dorm_t *_dorms, unsigned short _dorm_size, char *_name)
{
    for (unsigned short i = 0; i < _dorm_size; ++i)
    {
        if (strcmp(_dorms[i].name, _name) == 0)
        {
            return i;
        }
    }

    return -1;
}

void print_dorm(struct dorm_t _dorm, unsigned short _is_detailed)
{
    char *text_gender = gender_to_text(_dorm.gender);

    if (!_is_detailed)
    {
        printf("%s|%hu|%s\n",
               _dorm.name, _dorm.capacity, text_gender);
        return;
    }

    printf("%s|%hu|%s|%hu\n",
           _dorm.name, _dorm.capacity, text_gender, _dorm.residents_num);
}

void print_dorms(struct dorm_t *_dorms, unsigned short _dorm_size, unsigned short _is_detailed)
{
    for (unsigned short i = 0; i < _dorm_size; ++i)
    {
        print_dorm(_dorms[i], _is_detailed);
    }
}
