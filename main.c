/**
 * @file main.c
 * @brief Entry point for the card game program.
 *
 * This file contains the main function, which initializes and runs a simple card game.
 * It includes necessary header files, initializes decks, shuffles cards, and starts the game.
 *
 * @author Niamh Greally, Lucy Fogarty, Olamide ....
 * @date Last modified: 1-12-2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cardgame.h"

/**
 * @brief The main entry point for the card game program.
 *
 * The function initializes the random number generator, prompts the user for the number
 * of packs, initializes decks, shuffles cards, and starts the card game between two players.
 *
 * @return 0 on successful execution.
 */
int main() {
    srand(time(NULL)); // Seed the random number generator.

    // Prompt the user for the number of packs.
    int numPacks = getNumPacksFromUser();

    // Initialize the hidden deck and shuffle the cards.
    DeckOfCards hiddenDeck = initializeDeck(numPacks);
    shuffleDeck(&hiddenDeck);

    // Initialize player decks and the played deck.
    DeckOfCards player1 = { NULL, 0, {0} };
    DeckOfCards player2 = { NULL, 0, {0} };
    DeckOfCards playedDeck = { NULL, 0, {0} };

    // Draw initial cards for both players.
    for (int i = 0; i < 8; ++i) {
        addCardToDeck(&player1, drawCard(&hiddenDeck));
        addCardToDeck(&player2, drawCard(&hiddenDeck));
    }

    // Sort the initial cards for both players.
    customSort(&player1);
    customSort(&player2);

    // Display the initial cards for both players.
    printf("Player 1's cards:\n");
    displayDeck(player1);

    printf("\nPlayer 2's cards:\n");
    displayDeck(player2);

    // Start the card game with player turns.
    PlayerTurn currentPlayer = PlayerOne;
    startGame(&hiddenDeck, &player1, &player2, &playedDeck, &currentPlayer);

    // Free allocated memory for decks.
    free(hiddenDeck.cards);
    free(player1.cards);
    free(player2.cards);
    free(playedDeck.cards);

    return 0;
}
