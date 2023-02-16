/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questions.h"

int num_categories = 0;
int num_questions = 0;

// Initializes the array of questions for the game
void initialize_game(void)
{
    // open the categories file
    FILE* f = fopen("categories.txt", "r");

    // read the number of categories from the first line
    fscanf(f, "%d\n", &num_categories);

    // dynamically allocate memory for the categories array
    categories = calloc(num_categories, sizeof(char*));

    // read the categories from the file
    for (int i = 0; i < num_categories; i++)
    {
        categories[i] = calloc(MAX_LEN, sizeof(char));

        fgets(categories[i], MAX_LEN, f);

        // strip the newline character from the end of the string
        size_t len = strlen(categories[i]);
        if (categories[i][len - 1] == '\n')
        {
            categories[i][len - 1] = '\0';
        }
    }

    fclose(f);

    // open the questions file
    f = fopen("questions.txt", "r");

    // read the number of questions from the first line
    fscanf(f, "%d\n", &num_questions);

    // dynamically allocate memory for the questions array
    questions = calloc(num_questions, sizeof(question));
    
    int idx = 0;

    // fgets buffer - 3x the max length of a string + 10 for the separators and value
    char buffer[MAX_LEN_LINE];

    while (fgets(buffer, MAX_LEN_LINE, f) != NULL)
    {
        // strip the newline character from the end of the string
        size_t len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }

        // parse the line into the category, question, answer, and value
        char* token = strtok(buffer, ";");
        strncpy(questions[idx].category, token, MAX_LEN);

        if (!category_exists(questions[idx].category))
        {
            printf("Invalid category: %s\n", questions[idx].category);
            exit(1);
        }

        token = strtok(NULL, ";");
        strncpy(questions[idx].question, token, MAX_LEN);

        token = strtok(NULL, ";");
        strncpy(questions[idx].answer, token, MAX_LEN);

        token = strtok(NULL, ";");
        questions[idx].value = atoi(token);

        questions[idx].answered = false;

        idx++;
    }

    fclose(f);
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array

    for (int i = 0; i < num_questions; i++)
    {
        question* q = &questions[i];

        if (!q->answered)
        {
            printf("%s: %d\n", q->category, q->value);
        }
    }
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
    for (int i = 0; i < num_questions; i++)
    {
        if (strncmp(questions[i].category, category, MAX_LEN) == 0 && questions[i].value == value)
        {
            printf("%s:\n%s", questions[i].question, questions[i].question);
        }
    }
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions

    for (int i = 0; i < num_questions; i++)
    {
        if (strncmp(questions[i].category, category, MAX_LEN) == 0 && questions[i].value == value)
        {
            return strncmp(questions[i].answer, answer, MAX_LEN) == 0;
        }
    }

    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered

    for (int i = 0; i < num_questions; i++)
    {
        if (strncmp(questions[i].category, category, MAX_LEN) == 0 && questions[i].value == value)
        {
            return questions[i].answered;
        }
    }

    return false;
}

// Returns true if all questions have been answered
bool is_all_answered(void)
{
    for (int i = 0; i < num_questions; i++)
    {
        if (!questions[i].answered)
        {
            return false;
        }
    }

    return true;
}

bool category_exists(char* category)
{
    for (int i = 0; i < num_categories; i++)
    {
        if (strncmp(categories[i], category, MAX_LEN) == 0)
        {
            return true;
        }
    }

    return false;
}
