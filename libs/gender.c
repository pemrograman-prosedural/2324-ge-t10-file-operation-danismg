#include <stdlib.h>
#include <string.h>
#include "gender.h"

/**
 * @brief Define the complete function definition here. Be sure to enlist the prototype of each function
 * defined here in the corresponding header file.
 *
 */

char *gender_to_text(enum gender_t _gender)
{
    char *text = malloc(8);
    text[0] = '\0';

    switch (_gender)
    {
    case GENDER_MALE:
        strcpy(text, "male");
        break;
    default:
        strcpy(text, "female");
    }

    return text;
}

enum gender_t text_to_gender(char *text)
{
    if (strcmp(DEFAULT_GENDER_MALE_TEXT, text) == 0)
    {
        return GENDER_MALE;
    }

    return GENDER_FEMALE;
}
