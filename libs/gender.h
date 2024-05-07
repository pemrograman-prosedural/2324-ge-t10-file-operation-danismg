#ifndef GENDER_H
#define GENDER_H

/**
 * @brief define your structure, enums, globally accessible variables, and function prototypes here.
 * The actual function implementation should be defined in the corresponding source file.
 *
 */

#define DEFAULT_GENDER_MALE_TEXT "male"
#define DEFAULT_GENDER_FEMALE_TEXT "female"

enum gender_t
{
    GENDER_MALE,
    GENDER_FEMALE
};

char *gender_to_text(enum gender_t _gender);

enum gender_t text_to_gender(char *text);

#endif
