/*
* @file Player.h
* @brief Player class for a Blackjack game simulation
*
* This class manages the player's hand, actions, and state during the game.
* It includes methods for starting a hand, calculating totals, drawing cards,
* and handling player actions such as hitting, standing, doubling down, and surrendering.
* It also tracks the player's balance and bet amount.
*
* @author Michael Lintelman
* @date 2024-04-01
*/

#pragma once
class Player
{
private:
    bool hasAce = false;
    bool canHit = true;
    bool canStand = true;
    bool canSurrender = true;
    bool canDouble = true;
    bool canSplit = false;
    bool turnOver = false;
    bool busted = false;
    float bal = 50;
    float bet = 0;
    int handTotal = 0;
    int drawX = 300;
    int drawY = 270;

public:
    std::vector<Card> hand;
    std::vector<Card> handCopy;
    Player(Deck d)
    {
        canHit = true;
        canStand = true;
        canSurrender = true;
        canDouble = true;
        canSplit = false;
        bal = 50;
    }
    // Getters
    bool getCanHit() const { return canHit; }
    bool getCanStand() const { return canStand; }
    bool getCanSurrender() const { return canSurrender; }
    bool getCanDouble() const { return canDouble; }
    bool getCanSplit() const { return canSplit; }
    bool getTurnOver() const { return turnOver; }
    bool getBusted() const { return busted; }
    float getBal() const { return bal; }
    float getBet() const { return bet; }
    const std::vector<Card>& getHand() const { return hand; }
    int getDrawX() const { return drawX; }
    int getDrawY() const { return drawY; }
    bool getHasAce() const { return hasAce; }

    // Setters
    void setCanHit(bool value) { canHit = value; }
    void setCanStand(bool value) { canStand = value; }
    void setCanSurrender(bool value) { canSurrender = value; }
    void setCanDouble(bool value) { canDouble = value; }
    void setCanSplit(bool value) { canSplit = value; }
    void setBal(float value) { bal = value; }
    void setBet(float value) { bet = value; }
    void setDrawX(int x) { drawX = x; }
    void setDrawY(int y) { drawY = y; }
    void setHasAce(bool value) { hasAce = value; }

    void startHand(Deck& d)
    {
        // Give the player their first two cards
        hand.push_back(d.deal());
        hand.push_back(d.deal());
    }

    // Calculate the total value of the hand
    int getTotal() const
    {
        int total = 0;
        int numAces = 0;

        for (const Card& c : hand) {
            total += c.getValue();
            if (c.getRank() == Rank::Ace) {
                numAces++;
            }
        }

        // Add 10 for each Ace if it doesn't bust
        while (numAces > 0 && total + 10 <= 21) {
            total += 10;
            numAces--;
        }

        return total;
    }
    int getTotalCopy() const
    {
        int total = 0;
        int numAces = 0;

        for (const Card& c : handCopy) {
            total += c.getValue();
            if (c.getRank() == Rank::Ace) {
                numAces++;
            }
        }

        // Add 10 for each Ace if it doesn't bust
        while (numAces > 0 && total + 10 <= 21) {
            total += 10;
            numAces--;
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
        for (const Card& c : handCopy)
        {
            //c.draw(x, drawY, texture[c.getTexture()]);
			c.draw(x, drawY);
            x += c.getWidth() / 2;
        }
    }

    //void placeBet();

    bool takeTurn(Deck& d);
    bool takeAction(Deck& d, int action);

    /*******************************************************************************************
    * Surrender: the player gets half their bet back after the initial deal
    ********************************************************************************************/
    void surrender(void)
    {
        bal += .5 * bet;
        turnOver = true;
    }

    /*******************************************************************************************
    * Double down: the player doubles their bet after the initial deal, receives an extra card,
    * and ends their turn
    ********************************************************************************************/
    void doubleDown(Deck& d)
    {
        bet *= 2;
        d.deal();
        hand.push_back(d.deal());
        handTotal += hand.back().getValue();
        turnOver = true;
    }

    /*******************************************************************************************
    * Hit: the player receives another card
    ********************************************************************************************/
    void hit(Deck& d)
    {
        if (calculateHandTotal() >= 21)
        {
            std::cout << "You can't hit right now!" << std::endl;
            return;
        }
        hand.push_back(d.deal());
        std::cout << "You hit and received a ";
        hand.back().display();
        if (hand.back().getValue() == 1)
            hasAce = true;
        std::cout << std::endl;
        handTotal += hand.back().getValue();
    }

    /*******************************************************************************************
    * Stand: the player does not receive another card
    ********************************************************************************************/
    void stand(void)
    {
        if (!canStand)
        {
            std::cout << "You can't stand right now!" << std::endl;
            return;
        }
        std::cout << "You stood!" << std::endl << std::endl;
        turnOver = true;
    }

    /*******************************************************************************************
    * Bust: the player went over 21 and they lose
    ********************************************************************************************/
    void bust(void)
    {
        std::cout << "You busted and lost!" << std::endl << std::endl;
        busted = true;
        turnOver = true;
    }

    /*******************************************************************************************
    * Bust: the player went over 21 and they lose
    ********************************************************************************************/
    void displayWinnings(float winnings)
    {
        std::cout << "You won: " << winnings << std::endl;
        std::cout << "Your new balance: " << bal << std::endl << std::endl;
    }

    void newRound()
    {
        turnOver = false;
        busted = false;
        //handCopy = hand;
        //hand.clear();
        bet = 0;
    }

    void resetHand()
    {
        handCopy = hand;
		hand.clear();
    }

};
bool Player::takeAction(Deck& d, int action)
{
    switch (action)
    {
        // if a 1 is passed in, it means hit
    case 1:
        hit(d);
        drawHand(textures);
        break;
        // 2 means stand
    case 2:
        stand();
        break;
    case 3:
        doubleDown(d);
        drawHand(textures);
        break;
    case 4:
        surrender();
        break;
    }


    // If player's hand total is over 21, they bust and the turn is over.
    if (calculateHandTotal() > 21)
    {
        bust();
        return 0;
    }
    else {
        return 1;
    }
}