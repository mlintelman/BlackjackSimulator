/*
* @file Dealer.h
* @brief Dealer class header file
*
* This file defines the Dealer class, which represents the dealer in a Blackjack game.
* The dealer manages their hand, calculates totals, and handles game actions such as hitting and standing.
* It also includes methods for drawing the dealer's hand and managing the dealer's turn.
*
* @author Michael Lintelman
* @date 2024-04-01
*/

#pragma once
#include <vector>
class Dealer
{
private:
	int handTotal = 0;
	bool turnOver = false;
	bool busted = false;
	int drawX = 300;
	int drawY = 550;

public:
	std::vector<Card> hand;
	std::vector<Card> handCopy;

	bool getBusted() const { return busted; }
	int getDrawX() const { return drawX; }
	int getDrawY() const { return drawY; }
	bool getTurnOver() const { return turnOver; }

	void setDrawX(int x) { drawX = x; }
	void setDrawY(int y) { drawY = y; }
	void setTurnOver(bool value) { turnOver = value; }

	Dealer(Deck d)
	{

	}

	void newRound()
	{
		turnOver = false;
		busted = false;
		//handCopy = hand;
		// Pop each card from hand
		//hand.clear();
	}

	void resetHand()
	{
		handCopy = hand;
		hand.clear();
	}

	// Start the dealer's hand
	void startHand(Deck& d)
	{
		// Give the player their first two cards
		hand.push_back(d.deal());
		hand.push_back(d.deal());
	}

	int getTotal() const {
		int total = 0;
		bool firstAceEncountered = false;

		for (const Card& c : hand) {
			total += c.getValue();
			if (c.getRank() == Rank::Ace && !firstAceEncountered) {
				// First Ace encountered, count as 11
				total += 10;
				firstAceEncountered = true;
			}
		}

		// If the total exceeds 21 and the first Ace was counted as 11, 
		// deduct 10 to make it count as 1
		if (total > 21 && firstAceEncountered) {
			total -= 10;
		}

		return total;
	}

	int getTotalCopy() const {
		int total = 0;
		bool firstAceEncountered = false;

		for (const Card& c : handCopy) {
			total += c.getValue();
			if (c.getRank() == Rank::Ace && !firstAceEncountered) {
				// First Ace encountered, count as 11
				total += 10;
				firstAceEncountered = true;
			}
		}

		// If the total exceeds 21 and the first Ace was counted as 11, 
		// deduct 10 to make it count as 1
		if (total > 21 && firstAceEncountered) {
			total -= 10;
		}

		return total;
	}

	// Calc the hand total
	int calculateHandTotal(void)
	{
		int total = 0;
		for (const Card& c : hand)
		{
			total += c.getValue();
		}
		return total;
	}
	// Calc the hand total
	int calculateHandCopyTotal(void)
	{
		int total = 0;
		for (const Card& c : handCopy)
		{
			total += c.getValue();
		}
		return total;
	}

	void drawHand(GLuint texture[])
	{
		int x = drawX;
		for (const Card& c : hand)
		{
			//c.draw(x, drawY, texture[c.getTexture()]);
			c.draw(x, drawY);
			x += c.getWidth() / 2;
		}
	}

	void drawHandCopy(GLuint texture[])
	{
		int x = drawX;
		for (const Card& c: handCopy)
		{
			//c.draw(x, drawY, texture[c.getTexture()]);
			c.draw(x, drawY);
			x += c.getWidth() / 2;
		}
	}

	// Display the dealer's initial hand
	void displayInitHand()
	{
		std::cout << "Dealer's hand: " << std::endl;
		hand.front().display();
		std::cout << "??? of ???" << std::endl << std::endl;
	}

	/*******************************************************************************************
	* Hit: the player receives another card
	********************************************************************************************/
	void hit(Deck& d)
	{
		hand.push_back(d.deal());
		std::cout << "The dealer hit and received a ";
		hand.back().display();
		std::cout << std::endl;
		handTotal += hand.back().getValue();
	}

	/*******************************************************************************************
	* Stand: the player does not receive another card
	********************************************************************************************/
	void stand(void)
	{
		std::cout << "The dealer stood!" << std::endl << std::endl;
		turnOver = true;
	}

	/*******************************************************************************************
	* Bust: the player went over 21 and they lose
	********************************************************************************************/
	void bust(void)
	{
		std::cout << "The dealer busted and lost!" << std::endl << std::endl;
		turnOver = true;
		busted = true;
	}

	void takeTurn(Deck& d);
};

// Dealer's turn
void Dealer::takeTurn(Deck& d)
{
	while (!turnOver)
	{
		std::cout << "Dealer's hand:" << std::endl;
		for (const Card& c : hand)
		{
			handTotal += c.getValue();
			c.display();
		}
		std::cout << "Dealer's total:  " << handTotal << std::endl << std::endl;

		// If the hand total is 21 off the first two cards, it is a blackjack
		if (handTotal == 21 && hand.size() == 2)
		{
			// The turn is over, and return the whole function
			std::cout << "The dealer got a Blackjack!" << std::endl << std::endl;
			turnOver = true;
			return;
		}

		// While the total is 16 or lower, the dealer hits
		if (handTotal <= 16)
		{
			hit(d);
			drawHand(texture);
			//std::this_thread::sleep_for(std::chrono::seconds(2));
		}
		else
			stand();
		// If dealer's hand total is over 21, they bust and the turn is over.
		if (handTotal > 21)
			bust();
		handTotal = 0;
	}
}