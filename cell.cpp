//
// Created by Isabela Spinelli on 16/08/2023.
//
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public struct Cell
{
    //creating data type to specify the state of each cell
public enum Type
    {
        //determinating enumerators
        Empty,
        Mine,
        Number,
    }
    //creating tridimensional vector for cell position
public Vector3Int position;
    //creating a variable on which cell states can be applied to
public Type type;
public int number;
public bool revealed;
public bool flagged;
public bool exploded;
}
