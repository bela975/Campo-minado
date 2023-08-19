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

//Reset the cell's mouse state
            get_cell(a, b, cells)->set_mouse_state(0);

            //This is where we draw the effect
            //Get ready to see messy, horrible, unoptimized code
            //I warned you
            //We don't draw the effect if the game is not over or the cell effect timer hasn't yet started.
            if (0 != game_over && EFFECT_DURATION > get_cell(a, b, cells)->get_effect_timer())
            {
                //We calculate the size of the effect
                unsigned char effect_size = static_cast<unsigned char>(2 * round(0.5f * CELL_SIZE * ((EFFECT_DURATION - get_cell(a, b, cells)->get_effect_timer()) / static_cast<float>(EFFECT_DURATION))));

                //The effect timer of each cell will have a random duration
                std::uniform_int_distribution<unsigned short> effect_duration_distribution(1, EFFECT_DURATION - 1);

                //We're gonna use the cell shape to draw effects, because I love recycling!
                cell_shape.setPosition(floor(CELL_SIZE * (0.5f + a) - 0.5f * effect_size), floor(CELL_SIZE * (0.5f + b) - 0.5f * effect_size));
                cell_shape.setSize(sf::Vector2f(effect_size, effect_size));

                //The color of the effect will depend on whether the game is lost or won
                if (-1 == game_over)
                {
                    cell_shape.setFillColor(sf::Color(255, 36, 0));
                }
                else
                {
                    cell_shape.setFillColor(sf::Color(255, 255, 255));
                }

                //We draw the effect
                i_window.draw(cell_shape);

                //We reset the cell shape's size
                cell_shape.setSize(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));

                //If the effect timer is over
                if (1 == get_cell(a, b, cells)->update_effect_timer())
                {
                    //We start each neighboring cell's effect timer
                    if (0 <= a - 1 && EFFECT_DURATION == get_cell(a - 1, b, cells)->get_effect_timer())
                    {
                        get_cell(a - 1, b, cells)->set_effect_timer(static_cast<unsigned char>(effect_duration_distribution(random_engine)));
                    }

                    if (0 <= b - 1 && EFFECT_DURATION == get_cell(a, b - 1, cells)->get_effect_timer())
                    {
                        get_cell(a, b - 1, cells)->set_effect_timer(static_cast<unsigned char>(effect_duration_distribution(random_engine)));
                    }

                    if (COLUMNS > 1 + a && EFFECT_DURATION == get_cell(1 + a, b, cells)->get_effect_timer())
                    {
                        get_cell(1 + a, b, cells)->set_effect_timer(static_cast<unsigned char>(effect_duration_distribution(random_engine)));
                    }

                    if (ROWS > 1 + b && EFFECT_DURATION == get_cell(a, 1 + b, cells)->get_effect_timer())
                    {
                        get_cell(a, 1 + b, cells)->set_effect_timer(static_cast<unsigned char>(effect_duration_distribution(random_engine)));
                    }
                }
            }
        }
    }
}

void Field::flag_cell(unsigned char i_x, unsigned char i_y)
{
    //We don't let the player to flag cells when the game is over
    if (0 == game_over)
    {
        get_cell(i_x, i_y, cells)->flag();
    }
}

void Field::open_cell(unsigned char i_x, unsigned char i_y)
{
    //If this is the first cell we're opening
    if (0 == first_click)
    {
        //We declare coordinate distributions
        std::uniform_int_distribution<unsigned short> x_distribution(0, COLUMNS - 1);
        std::uniform_int_distribution<unsigned short> y_distribution(0, ROWS - 1);

        first_click = 1;

        //Then we generate mines
        for (unsigned short a = 0; a < MINES; a++)
        {
            unsigned char mine_x = static_cast<unsigned char>(x_distribution(random_engine));
            unsigned char mine_y = static_cast<unsigned char>(y_distribution(random_engine));

            //If the chosed cell already has a mine in it or it's a cell that the player wants to open
            if (1 == get_cell(mine_x, mine_y, cells)->get_is_mine() || (i_x == mine_x && i_y == mine_y))
            {
                //We try again
                a--;
            }
            else
            {
                //Otherwise, we set the mine
                get_cell(mine_x, mine_y, cells)->set_mine();
            }
        }

        //After we generate mines, each cell counts how many mines are surrounding it
        for (Cell& cell : cells)
        {
            cell.count_mines_around(cells);
        }
    }

    //We don't open the cell when the game is over or when the cell is flagged
    if (0 == game_over && 0 == get_cell(i_x, i_y, cells)->get_is_flagged())
    {
        if (1 == get_cell(i_x, i_y, cells)->open(cells))
        {
            //When the player opens a cell with a mine, we set the game over to -1
            game_over = -1;
        }
        else
        {
            unsigned short total_closed_cells = 0;

            //We count how many cells are closed
            for (Cell& cell : cells)
            {
                total_closed_cells += 1 - cell.get_is_open();
            }

            //If the number of closed cells equals the total number of mines, we'll consider that the game is won
            if (MINES == total_closed_cells)
            {
                //We set the game over to 1
                game_over = 1;

                //Then we start the effect
                get_cell(i_x, i_y, cells)->set_effect_timer(EFFECT_DURATION - 1);
            }
        }
    }
}

void Field::restart()
{
    //We only restart the game when it's over
    if (0 != game_over)
    {
        first_click = 0;

        game_over = 0;

        for (Cell& cell : cells)
        {
            cell.reset();
        }
    }
}

//Since we can't call the cell's function directly, we must use this function
void Field::set_mouse_state(unsigned char i_mouse_state, unsigned char i_x, unsigned char i_y)
{
    get_cell(i_x, i_y, cells)->set_mouse_state(i_mouse_state);
}


=







