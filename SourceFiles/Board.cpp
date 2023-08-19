//
// Created by Isabela Spinelli on 18/08/2023.
//
#include <random>
#include <SFML/Graphics.hpp>

#include "Headers/Square.hpp"
#include "Headers/Board.hpp"
#include "Headers/GetSquare.hpp"
#include "Headers/BaseConfig.hpp"

Board :: board() :

    //starting game
    gameOver(1),
    //calling our random number generator, making it so
    //that this can happen properly in all devices
    randomEngine(randomDevice())
    {
        //making the matrix, aka our game-board
        //adding lines and columns until our board is at desired size
        for(unsigned char a = 0; a < line; a++)
        {
            for(unsigned b = 0; b < col; b++)
            {
                Squares.pushBack(Cell(b,a));
            }
        }

        restart();
}

bool Board::endEffect()
{
    for(Square& square : squares)
    {
        if(0 < cell.getEffectTimer)
        {
            return 0;

        }

    }
    //when all cells are effectless
    return 1;
}

char Board :: detectGameOver()
{
    return gameOver;
}

unsigned short Board :: detectFlags()
{
    unsigned short flagTotal = 0;

    //looking for flags, to then count them
    for(Square& square : squares)
    {
         flagTotal += square.detectFlags();

    }

    return flagTotal;
}

//calling show function to show our items in our board!!!!!!!
void Board::show(sf::RenderWindow& i_windows)
{
    //drawing our cells
    sf::RectangleShape squareShape(sf::Vector2f(pixelBySquare -1, pixelBySquare -1));

    //making another object to be able to create our image
    sf::Sprite iconSprite;
    //creating a texture for it and pulling it from its archive
    sf::Texture iconsTexture;

    iconsTexture.loadFromFile("Resources/Images/Icons" + std::to_string(pixelBySquare) + ".png");

    iconSprite.setTexture(iconsTexture);

    //applying it to every square in our board, using loops
    for (unsigned char a = 0; a < col; a++)
    {
        for (unsigned char b = 0; b < line; b++)
        {
            //positioning our shapes correctly
            squareShape.setPosition(static_cast<float>(CpixelBySquare * a), static_cast<float>(pixelBySquare * b));

            //If the current cell is open
            if (1 == getSquare(a, b, squares)->getOpen())
            {
                //getting number of mines adjacent to it
                unsigned char adjacentMines = getSquare(a, b, squares)->getAdjacentMines();

                squareShape.setFillColor(sf::Color(146, 182, 255));

                //drawing the cell
                i_window.show(squareShape);

                //If the cell has at least one mine around it
                if (0 < adjacentMines)
                {
                    //getting the number corresponding to the icon texture to draw it
                    iconSprite.setPosition(static_cast<float>(pixelBySquare * a), static_cast<float>(pixelBySquare * b));
                    iconSprite.setTextureRect(sf::IntRect(pixelBySquare * adjacentMines, 0, pixelBySquare, pixelBySquare));

                    i_window.show(iconSprite);
                }
            }
            else //If the cell is still closed
            {
                Shape.setFillColor(sf::Color(0, 73, 255));

                //changing square colors to match the event happening in game
                //using the mouse as an input font
                if (0 == gameOver)
                {
                    if (1 == getSquare(a, b, square)->getMouseState())
                    {
                        squareShape.setFillColor(sf::Color(36, 109, 255));
                    }
                    else if (2 == getSquare(a, b, squares)->get_mouse_state())
                    {
                        cell_shape.setFillColor(sf::Color(0, 36, 255));
                    }
                }

                i_window.show(squareShape);

                //If the square is flagged
                if (1 == getSquare(a, b, square)->getFlagged())
                {
                    //drawing/showing image of the square with a flag
                    iconSprite.setPosition(static_cast<float>(pixelBySquare * a), static_cast<float>(pixelBySquare * b));
                    iconSprite.setTextureRect(sf::IntRect(0, 0, pixelBySquare, pixelBySquare));

                    i_window.show(iconSprite);
                }
            }



}







