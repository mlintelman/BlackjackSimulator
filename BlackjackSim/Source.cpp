/*
* @file Source.cpp
* @brief Main source file for the Blackjack simulation game.
* 
* This file contains the main function, OpenGL initialization, rendering functions,
* and game logic for a simple Blackjack simulation.
* 
* @author Michael Lintelman
* @date 2024-04-01
*/

#include <GL/glut.h>
GLuint textures[66];
#include "SOIL.h"
#include <string>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <cstring>
#include "PlayingCards.h"
#include "Player.h"
#include "Dealer.h"
#include "Sprite.h"

using namespace std;
const int CANVAS_HEIGHT = 600;
const int CANVAS_WIDTH = 800;
bool roundStarted = false;
bool roundOver = false;
bool firstTurn = true;
bool gameOver = false;

//Initialize the deck, player, dealer
Deck deck;
Player player(deck);
Dealer dealer(deck);
//Initialize UI elements. Textures must be set in init() function
Sprite background(0, 600, 800, 600);
Sprite greenCover(300, 390, 300, 275);
Chip half(10, 164);
Chip one(84, 164);
Chip five(158, 164);
Chip twentyfive(10, 82);
Chip onehundred(84, 82);
Chip fivehundred(158, 82);
Button hit(230, 74);
Button stand(368, 74);
Button doubleDown(506, 74);
Button surrender(644, 74);
Sprite endScreen(200, 450, 400, 300);
Sprite rules(10, 590, 200, 300);
Sprite cardBack(0, 0, 110, 155);

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);  // Set display-window color to white.
    glMatrixMode(GL_PROJECTION);       // Set projection parameters.
    gluOrtho2D(0.0, CANVAS_WIDTH, 0.0, CANVAS_HEIGHT);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glFrontFace(GL_CW);
    // H, D, C, S
	textures[0] = SOIL_load_OGL_texture("cards/backs/back_1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   // Aces
    textures[1] = SOIL_load_OGL_texture("cards/hearts/hearts_1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[2] = SOIL_load_OGL_texture("cards/diamonds/diamonds_1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[3] = SOIL_load_OGL_texture("cards/clubs/clubs_1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[4] = SOIL_load_OGL_texture("cards/spades/spades_1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Twos
    textures[5] = SOIL_load_OGL_texture("cards/hearts/hearts_2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[6] = SOIL_load_OGL_texture("cards/diamonds/diamonds_2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[7] = SOIL_load_OGL_texture("cards/clubs/clubs_2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[8] = SOIL_load_OGL_texture("cards/spades/spades_2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Threes
    textures[9] = SOIL_load_OGL_texture("cards/hearts/hearts_3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[10] = SOIL_load_OGL_texture("cards/diamonds/diamonds_3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[11] = SOIL_load_OGL_texture("cards/clubs/clubs_3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[12] = SOIL_load_OGL_texture("cards/spades/spades_3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Fours
    textures[13] = SOIL_load_OGL_texture("cards/hearts/hearts_4.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[14] = SOIL_load_OGL_texture("cards/diamonds/diamonds_4.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[15] = SOIL_load_OGL_texture("cards/clubs/clubs_4.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[16] = SOIL_load_OGL_texture("cards/spades/spades_4.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Fives
    textures[17] = SOIL_load_OGL_texture("cards/hearts/hearts_5.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[18] = SOIL_load_OGL_texture("cards/diamonds/diamonds_5.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[19] = SOIL_load_OGL_texture("cards/clubs/clubs_5.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[20] = SOIL_load_OGL_texture("cards/spades/spades_5.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Sixes
    textures[21] = SOIL_load_OGL_texture("cards/hearts/hearts_6.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[22] = SOIL_load_OGL_texture("cards/diamonds/diamonds_6.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[23] = SOIL_load_OGL_texture("cards/clubs/clubs_6.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[24] = SOIL_load_OGL_texture("cards/spades/spades_6.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Sevens
    textures[25] = SOIL_load_OGL_texture("cards/hearts/hearts_7.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[26] = SOIL_load_OGL_texture("cards/diamonds/diamonds_7.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[27] = SOIL_load_OGL_texture("cards/clubs/clubs_7.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[28] = SOIL_load_OGL_texture("cards/spades/spades_7.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Eights
    textures[29] = SOIL_load_OGL_texture("cards/hearts/hearts_8.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[30] = SOIL_load_OGL_texture("cards/diamonds/diamonds_8.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[31] = SOIL_load_OGL_texture("cards/clubs/clubs_8.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[32] = SOIL_load_OGL_texture("cards/spades/spades_8.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Nines
    textures[33] = SOIL_load_OGL_texture("cards/hearts/hearts_9.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[34] = SOIL_load_OGL_texture("cards/diamonds/diamonds_9.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[35] = SOIL_load_OGL_texture("cards/clubs/clubs_9.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[36] = SOIL_load_OGL_texture("cards/spades/spades_9.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Tens
    textures[37] = SOIL_load_OGL_texture("cards/hearts/hearts_10.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[38] = SOIL_load_OGL_texture("cards/diamonds/diamonds_10.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[39] = SOIL_load_OGL_texture("cards/clubs/clubs_10.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[40] = SOIL_load_OGL_texture("cards/spades/spades_10.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Jacks
    textures[41] = SOIL_load_OGL_texture("cards/hearts/hearts_11.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[42] = SOIL_load_OGL_texture("cards/diamonds/diamonds_11.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[43] = SOIL_load_OGL_texture("cards/clubs/clubs_11.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[44] = SOIL_load_OGL_texture("cards/spades/spades_11.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Queens
    textures[45] = SOIL_load_OGL_texture("cards/hearts/hearts_12.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[46] = SOIL_load_OGL_texture("cards/diamonds/diamonds_12.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[47] = SOIL_load_OGL_texture("cards/clubs/clubs_12.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[48] = SOIL_load_OGL_texture("cards/spades/spades_12.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Kings
    textures[49] = SOIL_load_OGL_texture("cards/hearts/hearts_13.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[50] = SOIL_load_OGL_texture("cards/diamonds/diamonds_13.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[51] = SOIL_load_OGL_texture("cards/clubs/clubs_13.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[52] = SOIL_load_OGL_texture("cards/spades/spades_13.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Card back (red)
    textures[53] = SOIL_load_OGL_texture("cards/backs/back_1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Chips
    textures[54] = SOIL_load_OGL_texture("chips/red.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[55] = SOIL_load_OGL_texture("chips/green.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[56] = SOIL_load_OGL_texture("chips/blue.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[57] = SOIL_load_OGL_texture("chips/yellow.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[58] = SOIL_load_OGL_texture("chips/orange.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[59] = SOIL_load_OGL_texture("chips/purple.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Buttons
    textures[60] = SOIL_load_OGL_texture("buttons/hit.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[61] = SOIL_load_OGL_texture("buttons/stand.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Background and UI
    textures[62] = SOIL_load_OGL_texture("misc/background.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[63] = SOIL_load_OGL_texture("buttons/blank.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[64] = SOIL_load_OGL_texture("buttons/youlose.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    textures[65] = SOIL_load_OGL_texture("misc/rules.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Updated bindings
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    background.setTexture(textures[62]);
    greenCover.setTexture(textures[62]);
    half.setTexture(textures[54]);
    one.setTexture(textures[55]);
    five.setTexture(textures[56]);
    twentyfive.setTexture(textures[57]);
    onehundred.setTexture(textures[58]);
    fivehundred.setTexture(textures[59]);
    hit.setTexture(textures[63]);
    stand.setTexture(textures[63]);
    doubleDown.setTexture(textures[63]);
    surrender.setTexture(textures[63]);
    endScreen.setTexture(textures[64]);
    rules.setTexture(textures[65]);
    cardBack.setTexture(textures[53]);

	// Populate deck now that textures are loaded
    deck.populate();
    // Shuffle
	deck.shuffle();
}

void write(GLfloat x, GLfloat y, const char* message)
{
    glColor3f(0.0, 0.0, 0.0);
    float scale = 0.2;
    float orientation = 0;
    glPushMatrix();
    glTranslatef(x, y, 0); // glTranslatef (dx, dy, dz)
    glScalef(scale, scale, scale); // glScalef (sx, sy, sz)
    glRotatef(orientation, 0, 0, 1); // glRotatef (angle, x, y, z)
    for (int i = 0; i < strlen(message); i++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, message[i]);
    glPopMatrix();
}
void write(GLfloat x, GLfloat y, const char* message, float scale)
{
    glColor3f(0.0, 0.0, 0.0);
    //float scale = 0.2;
    float orientation = 0;
    glPushMatrix();
    glTranslatef(x, y, 0); // glTranslatef (dx, dy, dz)
    glScalef(scale, scale, scale); // glScalef (sx, sy, sz)
    glRotatef(orientation, 0, 0, 1); // glRotatef (angle, x, y, z)
    for (int i = 0; i < strlen(message); i++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, message[i]);
    glPopMatrix();
}

float roundToDecimal(float num, int decimalPlaces) 
{
    float multiplier = std::pow(10.0f, decimalPlaces); // Calculate the multiplier
    return std::round(num * multiplier) / multiplier; // Multiply, round, and divide
}


void writeFloat(int x, int y, float num, int decimalPlaces)
{
    // Round the floating-point number
    float roundedNum = roundToDecimal(num, decimalPlaces);

    // Convert the rounded number to a string with specified decimal places
    stringstream ss;
    ss << fixed << std::setprecision(decimalPlaces) << roundedNum;
    string strNum = ss.str();

    // Convert the string to const char* type to use in write function
    const char* charNum = strNum.c_str();

    // Call the write function to display the rounded number
    write(x, y, charNum);
}

/**********************************************************
* Wincase 1: blackjack
* Wincase 2: normal win
* Wincase 3: loss
* Wincase 4: push
* Wincase 5: error
***********************************************************/
void newRound(int money, int winCase)
{
    player.setBet(0);
    roundStarted = false;
    roundOver = false;
}

void display_func(void)
{
    static int winCase;
    glClear(GL_COLOR_BUFFER_BIT);
    // draw background
    background.draw();
    // display full deck for debugging purposes
    //int y = 600;
    //int x = 0;
    //for (Card c : deck.cards)
    //{
    //    c.display();
    //    c.draw(x, y, textures[c.getTexture()]);
    //    x += c.getWidth() / 2;
    //    if (x > 1100)
    //    {
    //        x = 0;
    //        y -= 50;
    //    }
    //}
    rules.draw();
    if (gameOver)
    {
        endScreen.draw();
    }
    else
    {
        if (player.getTurnOver() && dealer.getTurnOver())
        {
			player.newRound();
			dealer.newRound();
        }
        if (!roundStarted)
        {
            greenCover.draw();
            player.drawHand(textures);
            dealer.drawHand(textures);
            if (player.calculateHandTotal() > 0)
            {
                glDisable(GL_BLEND);
                //Write the player's total
                // Use string so we can concatenate the message with the total variable
                string strTotal = to_string(player.getTotal());
                // Convert the string to const char* type to use in write func
                const char* charMessage = strTotal.c_str();
                write(300, 85, "Total:", .25);
                write(301, 85, "Total:", .25);
                write(380, 85, charMessage, .25);
                write(381, 85, charMessage, .25);

                //Write the dealer's total
                // Use string so we can concatenate the message with the total variable
                strTotal = to_string(dealer.getTotal());
                // Convert the string to const char* type to use in write func
                charMessage = strTotal.c_str();
                write(300, 565, "Total:", .25);
                write(301, 565, "Total:", .25);
                write(380, 565, charMessage, .25);
                write(381, 565, charMessage, .25);
                glEnable(GL_BLEND);
            }
        }
        if (roundStarted)
        {
            // If the deck is at 50%, reset the deck
            if (deck.cards.size() <= 26)
                deck.reset();
            winCase = 0;
            if (player.hand.size() == 0)
            {
                player.hand.push_back(deck.deal());
                dealer.hand.push_back(deck.deal());
                player.hand.push_back(deck.deal());
                dealer.hand.push_back(deck.deal());
                int handTotal = 0;
                std::cout << "Player's hand:" << std::endl;
                for (const Card& c : player.hand)
                {
                    handTotal += c.getValue();
                    c.display();

                }
                std::cout << "Player's total:  " << handTotal << std::endl << std::endl;
            }
            player.drawHand(textures);
            dealer.drawHand(textures);

            hit.draw();
            stand.draw();
            if (player.hand.size() == 2)
            {
                doubleDown.draw();
                surrender.draw();
            }

            glDisable(GL_BLEND);
            // triple bold
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    write(265 + x, 25 - y, "Hit", 0.35);
                    write(375 + x, 25 - y, "Stand", 0.35);
                    if (player.hand.size() == 2)
                    {
                        write(535 + x, 25 - y, "Dbl.", 0.35);
                        write(655 + x, 25 - y, "Surr.", 0.35);
                    }
                }
            }

            //Write the player's total
            // Use string so we can concatenate the message with the total variable
            string strTotal = to_string(player.getTotal());
            // Convert the string to const char* type to use in write func
            const char* charMessage = strTotal.c_str();
            write(300, 85, "Total:", .25);
            write(301, 85, "Total:", .25);
            write(380, 85, charMessage, .25);
            write(381, 85, charMessage, .25);

            //Write the dealer's total
            // Use string so we can concatenate the message with the total variable
            strTotal = to_string(dealer.getTotal());
            // Convert the string to const char* type to use in write func
            charMessage = strTotal.c_str();
            write(300, 565, "Total:", .25);
            write(301, 565, "Total:", .25);
            if (!player.getTurnOver())
            {
                write(380, 565, "...", .25);
                write(381, 565, "...", .25);
            }
            else
            {
                write(380, 565, charMessage, .25);
                write(381, 565, charMessage, .25);
            }

            glEnable(GL_BLEND);
            // Cover the dealer's second card with a card back so it appears face down
            if (!player.getTurnOver())
            {
                cardBack.draw(dealer.getDrawX() + cardBack.getWidth() / 2, dealer.getDrawY());
            }
            else
            {
                // If player didn't  bust, dealer takes turn
                if (!player.getBusted())
                    dealer.takeTurn(deck);
                // If player did bust, dealer turn is over
                else
                {
                    dealer.setTurnOver(true);
                }
                roundOver = true;
                // The dealer's turn should be over by now
                // Calculate and print out both hands
                int playerTotal = player.getTotal();
                int dealerTotal = dealer.getTotal();
                bool dealerBJ = false;
                if (dealerTotal == 21 && dealer.hand.size() == 2)
                    dealerBJ = true;

                //cout << "Your total: " << playerTotal << endl;
                //cout << "Dealer's total: " << dealerTotal << endl << endl;
                // If the round is over, see who wins
                int winnings = 0;
                if (roundOver)
                {
                    // Player wins (player total more than dealer's while not busted, or player doesn't bust and dealer does
                    if ((playerTotal > dealerTotal && !player.getBusted()) || !player.getBusted() && dealer.getBusted())
                    {
                        // Player blackjack
                        if (playerTotal == 21 && player.hand.size() == 2 && !dealerBJ)
                        {
                            cout << "Blackjack! You win big!" << endl;
                            // 3:2 payout
                            winnings = player.getBet() + player.getBet() * 1.5;
                            player.setBal(player.getBal() + winnings);
                            player.displayWinnings(player.getBet() + player.getBet() * 1.5);
                            // Start new round sequence
                            winCase = 1;
                            newRound(winnings, 1);
                        }
                        // Regular win
                        else
                        {
                            cout << "You win!" << endl;
                            // 1:1 payout
                            winnings = player.getBet() * 2;
                            player.setBal(player.getBal() + winnings);
                            player.displayWinnings(player.getBet() * 2);
                            // Start new round sequence
                            winCase = 2;
                            newRound(winnings, 2);
                        }
                    }
                    // Player loses and does not receive their bet back (dealer didn't bust)
                    else if (playerTotal < dealerTotal && !dealer.getBusted() || player.getBusted())
                    {
                        cout << "You lose!" << endl;
                        cout << "Your new balance: " << player.getBal() << endl;
                        if (player.getBal() == 0)
                        {
                            gameOver = true;
                            cout << "gameover";
                        }

                        // Start new round sequence
                        winCase = 3;
                        newRound(winnings, 3);
                    }
                    // Tie, player receives their bet back (as long as no one busted)
                    else if (playerTotal == dealerTotal && !dealer.getBusted() && !player.getBusted())
                    {
                        // If both the dealer and the player got blackjack
                        if ((player.hand.size() == 2 && playerTotal == 21 && dealerBJ) || playerTotal != 21)
                        {
                            cout << "Push!" << endl;
                            player.setBal(player.getBal() + player.getBet());
                            cout << "Your new balance: " << player.getBal() << endl;
                            // Start new round sequence
                            winCase = 4;
                            newRound(winnings, 4);
                        }
                    }
                    //// Start new round sequence (error)
                    //newRound(winnings, 5);
                }
            }
        }
        else
        {
            // NOTE: THIS IS THE DEAL BUTTON NOT HIT
            hit.draw();
            glDisable(GL_BLEND);
            // triple bold
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    write(250 + x, 25 - y, "Deal", 0.35);
                }
            }
            glEnable(GL_BLEND);
        }

        // Draw all of the chips
        half.draw();
        one.draw();
        five.draw();
        twentyfive.draw();
        onehundred.draw();
        fivehundred.draw();

        glDisable(GL_BLEND);

        // Write the values of the chips on top of them
        write(19, 123, "$0.50", 0.14);
        write(20, 123, "$0.50", 0.14);
        write(105, 123, "$1", 0.14);
        write(106, 123, "$1", 0.14);
        write(180, 123, "$5", 0.14);
        write(181, 123, "$5", 0.14);
        write(24, 42, "$25", 0.14);
        write(25, 42, "$25", 0.14);
        write(96, 42, "$100", 0.14);
        write(97, 42, "$100", 0.14);
        write(168, 42, "$500", 0.14);
        write(169, 42, "$500", 0.14);

        // Write the player's bet and balance
        int writeX = 20;
        write(writeX, 250, "Bal:");
        write(writeX + 1, 250, "Bal:");
        write(writeX + 50, 250, "$");
        write(writeX + 51, 250, "$");
        writeFloat(writeX + 67, 250, player.getBal(), 2);
        writeFloat(writeX + 68, 250, player.getBal(), 2);
        write(writeX, 200, "Bet:");
        write(writeX + 1, 200, "Bet:");
        write(writeX + 50, 200, "$");
        write(writeX + 51, 200, "$");
        writeFloat(writeX + 67, 200, player.getBet(), 2);
        writeFloat(writeX + 68, 200, player.getBet(), 2);


        // First, draw end screen
        switch (winCase)
        {
        case 1:
            glEnable(GL_BLEND);
            glDisable(GL_BLEND);
            // triple bold
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    write(325 + x, 320 - y, "Blackjack!", 0.4);
                }
            }
            break;
        case 2:
            writeX = 312;
            glEnable(GL_BLEND);
            glDisable(GL_BLEND);
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    write(writeX + x, 320 - y, "You", 0.35);
                    write(writeX + 90 + x, 320 - y, "won!", 0.35);
                }
            }
            break;
        case 3:
            writeX = 315;
            glEnable(GL_BLEND);
            //endScreen.setVisible(true);
            //endScreen.draw(50, 100, textures[62]);
            glDisable(GL_BLEND);
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    write(writeX + x, 320 - y, "You", 0.35);
                    write(writeX + 90 + x, 320 - y, "lost!", 0.35);
                }
            }
            break;
        case 4:
            writeX = 330;
            glEnable(GL_BLEND);
            //endScreen.setVisible(true);
            //endScreen.draw(50, 100, textures[62]);
            glDisable(GL_BLEND);
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    write(writeX + x, 320 - y, "Push!", 0.4);
                }
            }
            break;
        }

        glEnable(GL_BLEND);

    }

    glFlush();
    glutPostRedisplay();
}

// Exit program using the escape key
void keyboard_func(unsigned char c, int x, int y)
{
    switch (c)
    {
        // Esc: exit
    case 27:
        exit(0);
        break;
    }
}

void mouse_func(int button, int state, int x, int y)
{
    // If right mouse button clicked..
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (gameOver)
        {
            return;
        }
        //if (endScreen.checkClick(x, CANVAS_HEIGHT - y))
            //background.draw()
        // As long as the player's turn isn't over, they should be able to do any of the following:
        if (!player.getTurnOver() && !gameOver)
        {
            // Player may only bet and start the deal if the round hasn't started yet
            if (!roundStarted)
            {
                // If it clicks on a chip, set the bet to the appropriate amount and take away from the balance
                if (half.checkClick(x, CANVAS_HEIGHT - y))
                {
                    // If the player has the money
                    if (player.getBal() >= 0.5)
                    {
                        player.setBet(player.getBet() + 0.5);
                        player.setBal(player.getBal() - 0.5);
                    }
                }
                else if (one.checkClick(x, CANVAS_HEIGHT - y))
                {
                    if (player.getBal() >= 1.0)
                    {
                        player.setBet(player.getBet() + 1.0);
                        player.setBal(player.getBal() - 1.0);
                    }
                }
                else if (five.checkClick(x, CANVAS_HEIGHT - y))
                {
                    if (player.getBal() >= 5.0)
                    {
                        player.setBet(player.getBet() + 5.0);
                        player.setBal(player.getBal() - 5.0);
                    }
                }
                else if (twentyfive.checkClick(x, CANVAS_HEIGHT - y))
                {
                    if (player.getBal() >= 25.0)
                    {
                        player.setBet(player.getBet() + 25.0);
                        player.setBal(player.getBal() - 25.0);
                    }
                }
                else if (onehundred.checkClick(x, CANVAS_HEIGHT - y))
                {
                    if (player.getBal() >= 100.0)
                    {
                        player.setBet(player.getBet() + 100.0);
                        player.setBal(player.getBal() - 100.0);
                    }
                }
                else if (fivehundred.checkClick(x, CANVAS_HEIGHT - y))
                {
                    if (player.getBal() >= 500.0)
                    {
                        player.setBet(player.getBet() + 500.0);
                        player.setBal(player.getBal() - 500.0);
                    }
                }
                // NOTE: this will appeaer as "Deal" button before the round has started
                else if (hit.checkClick(x, CANVAS_HEIGHT - y) && player.getBet() > 0)
                {
					player.resetHand();
                    dealer.resetHand();
                    roundStarted = true;
                }
            }
            // These are actions that can only be taken after the round has started
            else 
            {
                if (hit.checkClick(x, CANVAS_HEIGHT - y))
                {
                    player.takeAction(deck, 1);
                }
                // Stand button
                else if (stand.checkClick(x, CANVAS_HEIGHT - y))
                {
                    player.takeAction(deck, 2);
                }
                // Double down and surrender: have to be at initial deal
                else if (doubleDown.checkClick(x, CANVAS_HEIGHT - y) && player.hand.size() == 2)
                {
                    player.takeAction(deck, 3);
                }
                else if (surrender.checkClick(x, CANVAS_HEIGHT - y) && player.hand.size() == 2)
                {
                    player.takeAction(deck, 4);
                }

            }
        }
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);                        	 // Initialize GLUT.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);     // Set display mode.
    glutInitWindowPosition(0, 0);   		         // Set top-left display-window position.
    glutInitWindowSize(CANVAS_WIDTH, CANVAS_HEIGHT);           	     // Set display-window width and height.
    glutCreateWindow("BlackjackSim"); 	 // Create display window.

    init();                            		        // Execute initialization procedure.
    glutDisplayFunc(display_func);                  // Send graphics to display window.
    glutMouseFunc(mouse_func);
    glutKeyboardFunc(keyboard_func);
    glutMainLoop();                   	            // Display everything and wait.
}