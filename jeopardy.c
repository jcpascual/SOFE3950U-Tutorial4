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
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define MAX_PLAYERS 4

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players)
{
    // Sort the players by score
    for (int i = 0; i < num_players; i++)
    {
        for (int j = i + 1; j < num_players; j++)
        {
            if (players[i].score < players[j].score)
            {
                player temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }

    printf("Final Scores:\n");

    // Display the results
    for (int i = 0; i < num_players; i++)
    {
        printf("%s: %d\n", players[i].name, players[i].score);
    }
}


int main(int argc, char *argv[])
{
    // An array of players
    player players[MAX_PLAYERS];
    
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();

    int num_players = 0;

    // Prompt for players names
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        printf("Enter player %d name (empty for no player): ", i + 1);
        fgets(buffer, BUFFER_LEN, stdin);

        // Strip the newline character from the end of the string
        size_t len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }

        // Check if this is an empty string
        len = strlen(buffer);
        if (len == 0)
        {
            // If this is the first player, prompt again. There can never be zero players.
            if (i == 0)
            {
                i--;

                printf("You must enter at least one player\n");

                continue;
            }

            num_players = i;

            break;
        }

        // Initialize the player name and score
        strncpy(players[i].name, buffer, MAX_LEN);
        players[i].score = 0;
    }

    // Initialize all remaining players with an empty name
    for (int i = num_players; i < MAX_PLAYERS; i++)
    {
        players[i].name[0] = '\0';
        players[i].score = 0;
    }

    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Call functions from the questions and players source files

        // Execute the game until all questions are answered

        // Display the final results and exit
    }
    return EXIT_SUCCESS;
}
