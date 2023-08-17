//
// Created by Isabela Spinelli on 16/08/2023.
//
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;

public class Board : MonoBehaviour
{
    //reference our tilemap to be able to apply our tiles
    //setting it to public getter, but private setter so that our game script
    //can only access, not alter the tilemap
public Tilemap tilemap {get; private set;}

public Tile unknownTile;
public Tile emptyTile;
public Tile mineTile;
public Tile explodedTile;
public Tile flagTile;
public Tile num1Tile;
public Tile num2Tile;
public Tile num3Tile;
public Tile num4Tile;
public Tile num5Tile;
public Tile num6Tile;
public Tile num7Tile;
public Tile num8Tile;

private void Awake()
    {
        tilemap = GetComponent<Tilemap>();

    }

    // function to create game board,
    //public so it can be accessed by our game script
public void Create(Cell[,] state)
    {
        //establishing that it is bidimensional
        int width = state.GetLength(0);
        int height = state.GetLength(1);

        //creating the gameboard with 2 for loops
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                //referencing especific cell based on its coordinates,
                // to then be able to access its data
                Cell cell = state[x,y];
                tilemap.SetTile(cell.position, GetTile(cell));
            }
        }
    }
    //function to render an specific tile, and get its respective data
private Tile GetTile(Cell cell)
    {
        if (cell.revealed)
        {
            return GetRevealedTile(cell);
        } else if(cell.flagged)
        {
            return flagTile;
        } else
        {
            return unknownTile;
        }
    }


private Tile GetRevealedTile(Cell cell)
    {
        switch(cell.type)
        {
            case Cell.Type.Empty: return emptyTile;
            case Cell.Type.Mine: return mineTile;
            case Cell.Type.Number: return GetNumberTile(cell);
            default: return null;
        }
    }

private Tile GetNumberTile(Cell cell)
    {
        switch (cell.number)
        {
            case 1: return num1Tile;
            case 2: return num2Tile;
            case 3: return num3Tile;
            case 4: return num4Tile;
            case 5: return num5Tile;
            case 6: return num6Tile;
            case 7: return num7Tile;
            case 8: return num8Tile;
            default: return null;
        }
    }
}

