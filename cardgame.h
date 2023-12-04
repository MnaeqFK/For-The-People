/**
 * @file cardgame.h
 * @brief Header file for a simple card game.
 *
 * This file contains the declarations of functions and data structures for a simple card game.
 * It defines enums for suits and ranks, structures for playing cards and decks of cards,
 * as well as function prototypes for various card game operations.
 *
 * @author Niamh Greally, Lucy Fogarty, Olamide ....
 * @date Last modified: 1-12-2023
 */

#ifndef CARD_GAME_H
#define CARD_GAME_H

/**
 * @enum Suit
 * @brief Enumeration of card suits.
 */
typedef enum {
    Club,    /**< Club suit */
    Spade,   /**< Spade suit */
    Heart,   /**< Heart suit */
    Diamond /**< Diamond suit */
} Suit;

/**
 * @enum Rank
 * @brief Enumeration of card ranks.
 */
typedef enum {
    Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace
} Rank;

/**
 * @struct PlayingCard
 * @brief Structure representing a playing card.
 */
typedef struct {
    Suit suit; /**< The suit of the card */
    Rank rank; /**< The rank of the card */
} PlayingCard;

/**
 * @struct DeckOfCards
 * @brief Structure representing a deck of cards.
 */
typedef struct {
    PlayingCard* cards;  /**< Array of cards in the deck */
    int size;            /**< Number of cards in the deck */
    PlayingCard topCard; /**< The top card of the deck */
} DeckOfCards;

/**
 * @enum PlayerTurn
 * @brief Enumeration of player turns.
 */
typedef enum {
    PlayerOne, /**< Player One's turn */
    PlayerTwo  /**< Player Two's turn */
} PlayerTurn;

/**
 * @brief Initializes a deck of cards with the specified number of packs.
 *
 * The function creates a deck of cards by iterating through packs, suits, and ranks.
 *
 * @param numPacks The number of packs to use for initializing the deck.
 * @return The initialized deck of cards.
 */
DeckOfCards initializeDeck(int numPacks);

/**
 * @brief Shuffles the cards in the deck using the Fisher-Yates algorithm.
 *
 * @param deck Pointer to the deck of cards to be shuffled.
 */
void shuffleDeck(DeckOfCards* deck);

/**
 * @brief Displays the cards in the given deck.
 *
 * @param deck The deck of cards to be displayed.
 */
void displayDeck(DeckOfCards deck);

/**
 * @brief Converts a Suit enum value to a string.
 *
 * @param suit The Suit enum value to convert.
 * @return A string representing the suit.
 */
const char* suitToString(Suit suit);

/**
 * @brief Converts a Rank enum value to a string.
 *
 * @param rank The Rank enum value to convert.
 * @return A string representing the rank.
 */
const char* rankToString(Rank rank);

/**
 * @brief Sorts the cards in the deck in ascending order of rank.
 *
 * @param deck Pointer to the deck of cards to be sorted.
 */
void customSort(DeckOfCards* deck);

/**
 * @brief Adds a card to the deck.
 *
 * @param deck Pointer to the deck of cards.
 * @param card The card to be added to the deck.
 */
void addCardToDeck(DeckOfCards* deck, PlayingCard card);

/**
 * @brief Draws the top card from the deck.
 *
 * @param deck Pointer to the deck of cards.
 * @return The top card drawn from the deck.
 */
PlayingCard drawCard(DeckOfCards* deck);

/**
 * @brief Checks if a card can be played on the top card of the played deck.
 *
 * A card can be played if it has the same rank or suit as the top card.
 *
 * @param card The card to be checked for playability.
 * @param topCard The top card of the played deck.
 * @return 1 if the card can be played, 0 otherwise.
 */
int canPlayCard(PlayingCard card, PlayingCard topCard);

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
void takeTurn(DeckOfCards* hiddenDeck, DeckOfCards* player, DeckOfCards* playedDeck, PlayerTurn currentPlayer);

/**
 * @brief Checks if the game has finished by determining if any player has an empty deck.
 *
 * @param player1 Pointer to the first player's deck.
 * @param player2 Pointer to the second player's deck.
 * @return 1 if the game has finished, 0 otherwise.
 */
int isGameFinished(DeckOfCards* player1, DeckOfCards* player2);

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
void startGame(DeckOfCards* hiddenDeck, DeckOfCards* player1, DeckOfCards* player2, DeckOfCards* playedDeck, PlayerTurn* currentPlayer);

/**
 * @brief Prompts the user to enter the number of packs of cards for the game.
 *
 * The user is prompted until a valid number of packs (between 1 and 10) is entered.
 *
 * @return The number of packs entered by the user.
 */
int getNumPacksFromUser();

#endif /* CARD_GAME_H */
