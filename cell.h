#pragma once

#include<vector>
#include<iostream>
#include"window.h"
#include"Vertex2D.h"
 
#define MUTATION_RATE ((rand()%101)-50)

#define MAZE_SIZE          100

#define MAX_AGE            960
#define MAX_HEALTH         2000
#define MAX_CREATURES      1000
#define MAX_CELLS          30

#define WORLD_WIDTH        SCREENWIDTH  
#define WORLD_HEIGHT       SCREENHEIGHT

#define NUM_NEURONS        5
#define NUM_RESPONSES      3

#define NORTHING           0
#define ENEMY              1
#define MATE               2
#define WALL               3
#define FOOD               4
#define NUMBER_OF_NEURONS  2
#define AMOUNT_FOOD        2200

extern int CELLCOUNT,EDGECOUNT;
extern int EDGECOPY, CELLCOPY;

class Organism ; struct Edge; // Forward Declaration

class Cell {
public:
   Cell();~Cell();
   Cell(Organism Parent, int numedges);

    int ID;

    Vector2D Offset,
             Potential,
             Velocity,          // Force = Mass * Acceleration
             Acceleration,
             Force;

    double   Friction;

    double   Angle,
             Speed,
             Mass ;

    unsigned char Number_of_edges;
    unsigned long Color;

    bool     Raised_Up;
    std::vector<Edge> edges;
};

Cell  MakeCell(Organism &parent, int numedge);


struct Edge {
    Edge();~Edge();
    Edge(Cell *parent, Cell *other, double Tension);

    Cell *second;
    int ID;
               
    Vector2D  Displacement,
              RestDistance;

    double          Distance, 
                     Tension,
                       Angle;

    unsigned long Color;
};

Edge MakeEdge(Cell &parent, Cell &other, unsigned char tension);



class Organism {
public:
     Organism(unsigned char numcells);

    unsigned char Number_of_Cells;

    Vector2D Position, 
             Potential, 
             Velocity;
    
    std::vector<Cell> cells;

public:
    
    void  Update();
    void  Draw();
};


extern double Get_Distance(const Cell &parent,const Cell &child);