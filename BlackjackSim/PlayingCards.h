/*
* @file PlayingCards.h
* @brief Header file for playing cards and deck management in a Blackjack simulation.
* 
* This file defines the `Card` class representing a playing card with its rank, suit, and texture,
* and the `Deck` class which manages a collection of cards, allowing for shuffling and dealing.
* It includes methods for displaying cards, drawing them on the screen, and managing the deck's state.
* It also provides an enumeration for `Suit` and `Rank` to categorize the cards.
* 
* @author Michael Lintelman
* @date 2024-04-01
*/

#pragma once
#include <vector>
#include <algorithm> // For std::shuffle
#include <random>    // For std::default_random_engine and std::random_device

enum class Suit
{
	Hearts, Diamonds, Clubs, Spades
};

enum class Rank
{
    Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King
};

class Card 
{
private:
    Rank rank = Rank::Ace;
    Suit suit = Suit::Hearts;
    int value = 0;
    int width = 110;
    int height = 155;
	GLuint texture = 0;
	//bool isFaceUp = true; // Default to face up
public:
    // Full constructor with rank, suit, and texture
    Card(Rank r, Suit s, GLuint tex)
        : rank(r), suit(s), texture(tex)
    {
        switch (rank) {
        case Rank::Ace: value = 1; break;
        case Rank::Two: value = 2; break;
        case Rank::Three: value = 3; break;
        case Rank::Four: value = 4; break;
        case Rank::Five: value = 5; break;
        case Rank::Six: value = 6; break;
        case Rank::Seven: value = 7; break;
        case Rank::Eight: value = 8; break;
        case Rank::Nine: value = 9; break;
        case Rank::Ten:
        case Rank::Jack:
        case Rank::Queen:
        case Rank::King:
            value = 10; break;
        }
    }

    void setTexture(GLuint tex) {
        texture = tex;
	}

	// Getters for card properties
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getValue() const { return value; }
    Rank getRank() const { return rank; }
    Suit getSuit() const { return suit; }
    GLuint getTexture() const { return texture; }

    void display() const {
        std::cout << "Card: ";
        switch (rank) {
        case Rank::Ace: std::cout << "Ace"; break;
        case Rank::Two: std::cout << "Two"; break;
        case Rank::Three: std::cout << "Three"; break;
        case Rank::Four: std::cout << "Four"; break;
        case Rank::Five: std::cout << "Five"; break;
        case Rank::Six: std::cout << "Six"; break;
        case Rank::Seven: std::cout << "Seven"; break;
        case Rank::Eight: std::cout << "Eight"; break;
        case Rank::Nine: std::cout << "Nine"; break;
        case Rank::Ten: std::cout << "Ten"; break;
        case Rank::Jack: std::cout << "Jack"; break;
        case Rank::Queen: std::cout << "Queen"; break;
        case Rank::King: std::cout << "King"; break;
        }
        std::cout << " of ";
        switch (suit) {
        case Suit::Hearts: std::cout << "Hearts"; break;
        case Suit::Diamonds: std::cout << "Diamonds"; break;
        case Suit::Clubs: std::cout << "Clubs"; break;
        case Suit::Spades: std::cout << "Spades"; break;
        }
        std::cout << " (" << texture << ")" << std::endl;
    }

    // Draw the card at a position using its own texture
    void draw(int x, int y) const {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glColor3f(1.0f, 1.0f, 1.0f);

        glBegin(GL_QUADS);
        glTexCoord2i(0, 1); glVertex2i(x, y);                 // top-left
        glTexCoord2i(1, 1); glVertex2i(x + width, y);         // top-right
        glTexCoord2i(1, 0); glVertex2i(x + width, y - height);// bottom-right
        glTexCoord2i(0, 0); glVertex2i(x, y - height);        // bottom-left
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }
};


class Deck
{
private:
    
    int length = 0;
public:
    // 
    std::vector<Card> cards;
    Deck()
    {
        GLuint texture = 0;
        // Populate the deck with aces and number cards
        for (int rank = 0; rank < 13; ++rank)
        {
            for (int suit = 0; suit < 4; ++suit)
            {
                //GLuint textureId = loadTextureForCard(rank, suit);
                cards.push_back(Card(static_cast<Rank>(rank), static_cast<Suit>(suit), texture));
                texture++;
                length++;
            }
        }
        // Shuffle the deck once the deck is made
        shuffle();
        // Push an an ace and some 10s to check blackjack
        //cards.push_back(Card(static_cast<Rank>(11), static_cast<Suit>(1), texture));
        //cards.push_back(Card(static_cast<Rank>(12), static_cast<Suit>(3), texture));
        //cards.push_back(Card(static_cast<Rank>(0), static_cast<Suit>(0), texture));
    }

    int getLength() const { return length; }

    void display() const 
    {
        for (const auto& card : cards) {
            card.display();
        }
    }

    // Shuffle the deck of cards randomly
    void shuffle()
    {
        std::random_device rd;
        std::default_random_engine rng(rd());
        std::shuffle(cards.begin(), cards.end(), rng);
    }
    // Pop the last card in the deck and return it
    Card deal()
    {
        Card retCard = cards.back();
        cards.pop_back();
        length--;
        return retCard;
    }
    void reset()
    {
        cards.clear();
        GLuint texture = 0;
        // Populate the deck with aces and number cards
        for (int rank = 0; rank < 13; ++rank)
        {
            for (int suit = 0; suit < 4; ++suit)
            {
                //GLuint textureId = loadTextureForCard(rank, suit);
                cards.push_back(Card(static_cast<Rank>(rank), static_cast<Suit>(suit), texture));
                texture++;
                length++;
            }
        }
        // Shuffle the deck once the deck is made
        shuffle();
    }
};