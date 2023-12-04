/**
 * @file cardgame.c
 * @brief Implementation of a simple card game.
 *
 * This file contains the implementation of a card game, including functions for
 * initializing, shuffling, and displaying decks of cards, as well as playing the game.
 *
 * @author Niamh Greally, Lucy Fogarty, Olamide .....
 * @date Last modified: 1-12-2023
 */

#include "cardgame.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Prompts the user to enter the number of packs of cards for the game.
 *
 * The user is prompted until a valid number of packs (between 1 and 10) is entered.
 *
 * @return The number of packs entered by the user.
 */
int getNumPacksFromUser() {
    int numPacks;
    do {
        printf("Enter the number of packs of cards from one to ten: ");
        scanf_s("%u", &numPacks);
    } while (numPacks < 1 || numPacks > 10);

    return numPacks;
}

/**
 * @brief Initializes a deck of cards with the specified number of packs.
 *
 * The function creates a deck of cards by iterating through packs, suits, and ranks.
 *
 * @param numPacks The number of packs to use for initializing the deck.
 * @return The initialized deck of cards.
 */
DeckOfCards initializeDeck(int numPacks) {
    DeckOfCards deck = { NULL, 0, {0} };
    for (int pack = 0; pack < numPacks; ++pack) {
        for (int suit = Club; suit <= Diamond; ++suit) {
            for (int rank = Two; rank <= Ace; ++rank) {
                addCardToDeck(&deck, (PlayingCard) { suit, rank });
            }
        }
    }
    return deck;
}

/**
 * @brief Shuffles the cards in the deck using the Fisher-Yates algorithm.
 *
 * @param deck Pointer to the deck of cards to be shuffled.
 */
void shuffleDeck(DeckOfCards* deck) {
    for (int i = deck->size - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        PlayingCard temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}

/**
 * @brief Displays the cards in the given deck.
 *
 * @param deck The deck of cards to be displayed.
 */
void displayDeck(DeckOfCards deck) {
    for (int i = 0; i < deck.size; ++i) {
        printf("%s of %s\n", rankToString(deck.cards[i].rank), suitToString(deck.cards[i].suit));
    }
}

/**
 * @brief Converts a Suit enum value to a string.
 *
 * @param suit The Suit enum value to convert.
 * @return A string representing the suit.
 */
const char* suitToString(Suit suit) {
    switch (suit) {
    case Club:
        return "Club";
    case Spade:
        return "Spade";
    case Heart:
        return "Heart";
    case Diamond:
        return "Diamond";
    }
}

/**
 * @brief Converts a Rank enum value to a string.
 *
 * @param rank The Rank enum value to convert.
 * @return A string representing the rank.
 */
const char* rankToString(Rank rank) {
    switch (rank) {
    case Two:
        return "Two";
    case Three:
        return "Three";
    // ... (similar cases for other ranks)
    }
}

/**
 * @brief Sorts the cards in the deck in ascending order of rank.
 *
 * @param deck Pointer to the deck of cards to be sorted.
 */
void customSort(DeckOfCards* deck) {
    for (int i = 0; i < deck->size - 1; ++i) {
        for (int j = 0; j < deck->size - i - 1; ++j) {
            if (deck->cards[j].rank > deck->cards[j + 1].rank) {
                PlayingCard temp = deck->cards[j];
                deck->cards[j] = deck->cards[j + 1];
                deck->cards[j + 1] = temp;
            }
        }
    }
}

/**
 * @brief Adds a card to the deck.
 *
 * @param deck Pointer to the deck of cards.
 * @param card The card to be added to the deck.
 */
void addCardToDeck(DeckOfCards* deck, PlayingCard card) {
    deck->cards = realloc(deck->cards, (deck->size + 1) * sizeof(PlayingCard));
    deck->cards[deck->size++] = card;
}

/**
 * @brief Draws the top card from the deck.
 *
 * @param deck Pointer to the deck of cards.
 * @return The top card drawn from the deck.
 */
PlayingCard drawCard(DeckOfCards* deck) {
    PlayingCard topCard = deck->cards[deck->size - 1];
    deck->size--;
    deck->cards = realloc(deck->cards, deck->size * sizeof(PlayingCard));
    return topCard;
}

/**
 * @brief Checks if a card can be played on the top card of the played deck.
 *
 * A card can be played if it has the same rank or suit as the top card.
 *
 * @param card The card to be checked for playability.
 * @param topCard The top card of the played deck.
 * @return 1 if the card can be played, 0 otherwise.
 */
int canPlayCard(PlayingCard card, PlayingCard topCard) {
    return (card.rank == topCard.rank || card.suit == topCard.suit);
}

/**
 * @brief Performs a turn in the game for the current player.
 *
 * The player attempts to play a card from their deck, and if not possible,
 * draws a card from the hidden deck. The played card is added to the played deck.
 *
 * @param hiddenDeck Pointer to the hidden deck of cards.
 * @param player Pointer to the current player's deck.
 * @param playedDeck Pointer to the played deck of cards.
 * @param currentPlayer The turn of the current player.
 */
void takeTurn(DeckOfCards* hiddenDeck, DeckOfCards* player, DeckOfCards* playedDeck, PlayerTurn currentPlayer) {
    PlayingCard topCard = playedDeck->topCard;

    if (topCard.rank == 0) {
        topCard = drawCard(hiddenDeck);
        printf("\nPlayer %d's turn - Top card: %s of %s\n", currentPlayer + 1, rankToString(topCard.rank), suitToString(topCard.suit));
    } else {
        printf("\nPlayer %d's turn - Top card: %s of %s (last played)\n", currentPlayer + 1, rankToString(topCard.rank), suitToString(topCard.suit));
    }

    int matchIndex = -1;
    for (int i = 0; i < player->size; ++i) {
        if (canPlayCard(player->cards[i], topCard)) {
            matchIndex = i;
            break;
        }
    }

    if (matchIndex != -1) {
        playedDeck->topCard = player->cards[matchIndex];
        addCardToDeck(playedDeck, player->cards[matchIndex]);
        printf("Player %d played card %s of %s\n", currentPlayer + 1, rankToString(player->cards[matchIndex].rank), suitToString(player->cards[matchIndex].suit));

        player->size--;
        for (int i = matchIndex; i < player->size; ++i) {
            player->cards[i] = player->cards[i + 1];
        }
        player->cards = realloc(player->cards, player->size * sizeof(PlayingCard));

        printf("\nPlayer %d's cards:\n", currentPlayer + 1);
        displayDeck(*player);
    } else {
        PlayingCard drawnCard = drawCard(hiddenDeck);
        addCardToDeck(player, drawnCard);  // Add the drawn card to the player's deck
        printf("Player %d picks a card from the hidden deck\n", currentPlayer + 1);

        printf("\nPlayer %d's cards:\n", currentPlayer + 1);
        displayDeck(*player);
    }

    if (hiddenDeck->size == 0) {
        printf("\nReshuffling the deck!\n");
        hiddenDeck->cards = realloc(hiddenDeck->cards, playedDeck->size * sizeof(PlayingCard));
        for (int i = 0; i < playedDeck->size; ++i) {
            hiddenDeck->cards[i] = playedDeck->cards[i];
        }
        hiddenDeck->size = playedDeck->size;

        playedDeck->size = 0;
        playedDeck->topCard.rank = 0; // Reset the top card when reshuffling

        shuffleDeck(hiddenDeck);
    }
}

/**
 * @brief Checks if the game has finished by determining if any player has an empty deck.
 *
 * @param player1 Pointer to the first player's deck.
 * @param player2 Pointer to the second player's deck.
 * @return 1 if the game has finished, 0 otherwise.
 */
int isGameFinished(DeckOfCards* player1, DeckOfCards* player2) {
    return (player1->size == 0 || player2->size == 0);
}

/**
 * @brief Starts the card game between two players.
 *
 * The game proceeds with players taking turns until one of them runs out of cards.
 *
 * @param hiddenDeck Pointer to the hidden deck of cards.
 * @param player1 Pointer to the first player's deck.
 * @param player2 Pointer to the second player's deck.
 * @param playedDeck Pointer to the played deck of cards.
 * @param currentPlayer Pointer to the variable indicating the current player's turn.
 */
void startGame(DeckOfCards* hiddenDeck, DeckOfCards* player1, DeckOfCards* player2, DeckOfCards* playedDeck, PlayerTurn* currentPlayer) {
    printf("\nGame started!\n");

    while (!isGameFinished(player1, player2)) {
        takeTurn(hiddenDeck, (*currentPlayer == PlayerOne) ? player1 : player2, playedDeck, *currentPlayer);
        *currentPlayer = (*currentPlayer == PlayerOne) ? PlayerTwo : PlayerOne;
    }

    printf("\nGame over!\n");
}
