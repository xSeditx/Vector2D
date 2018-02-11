//                                                                                                                                                                                                                                                                                                                                       
//                                                                                                                                                                                                                                                                                                                                       
//   Cell class for building and manipulating organisms                                                                                                                                                                                                                                                                                                                        
//                                                                                                                                                                                                                                                                                                                                       
//                                                                                                                                                                                                                                                                                                                                       
//                                                                                                                                                                                                                                                                                                                                       
//                                                                                                                                                                                                                                                                                                                                       
// TODO: Impliment better friction so that cells lose Velocity proportional to their mass and friction Coefficient                                                                                                                                                                                                                                                                                                                                 
//=====================================================================================================================                                                                                                                                                                                                                                                                                                                                      




#include"cell.h"
#include"window.h"
#include"Vertex2D.h"
using namespace std;


int EDGECOUNT= 0,CELLCOUNT=0;
int EDGECOPY = 0, CELLCOPY =0;

Cell::Cell(){ID = rand()%100 + 1000;}
Cell::~Cell(){}
Edge::Edge(){ID = rand()%100 + 1000;}
Edge::~Edge(){}


//==========================================================================================================================================================================
//                                                          CONSTRUCTORS FUNCTIONS                                                                                                                                         
//==========================================================================================================================================================================

Organism::Organism(unsigned char numcells):Number_of_Cells(0)
{
    Position.X = Potential.X = SCREENWIDTH  / 2;   Position.Y = Potential.Y = SCREENHEIGHT / 2;
    Velocity.X = Velocity.Y = 0;
    Number_of_Cells=0;
    
    cells.resize(numcells);

    for(Cell &cell: cells){                                                       // MAKE THE CELLS
            cell  =  MakeCell(*this, numcells - 1 );                              //(PARENT ... Number of Edges)
    }


    FOR_LOOP(cellcount, numcells){                                                // FOR EACH CELL.....
        int e = 0;
        FOR_LOOP(edgecount, numcells){                                            // MAKE EDGES CONNECTING THE OTHER CELLS
              if(edgecount != cellcount){
                       cells[cellcount].edges[e] = MakeEdge(cells[cellcount], cells[edgecount], RANDOM(1));  
                       e++;
              }
        }
    }

}

//==========================================================================================================================================================================
//                                                        CREATION FUNCTIONS                                                                                                                                         
//==========================================================================================================================================================================


//_______________________________________________________________
//||  int ID;
//||  Vector2D Offset, Potential, Velocity, Acceleration, Force;
//||  double   Friction;
//||  unsigned char Number_of_edges;
//||  std::vector<Edge> edges;

Cell MakeCell(Organism &parent, int numedge){
    Cell ret; 
    parent.Number_of_Cells++;
    ret.Number_of_edges = numedge;
    ret.edges.resize(numedge);

    ret.ID = parent.Number_of_Cells;

    ret.Offset.X = ret.Potential.X  = RANDOM(230);
    ret.Offset.Y = ret.Potential.Y  = RANDOM(230);

    ret.Velocity.X = ret.Velocity.Y =0; //RANDOM(1);
    ret.Friction = RANDOM(1);
    ret.Force.X = ret.Force.Y = 0;
    ret.Color = RGB(RANDOM(255),RANDOM(255),RANDOM(255));
    ret.Mass = 10;
    return ret;
}

//_______________________________________________________________
//|    Edge(Cell *parent, Cell *other, double Tension);
//|    Cell *Parent, *second;
//|    float Distance , Tension;

Edge MakeEdge(Cell &parent, Cell &other, unsigned char tension){
    Edge ret;

        ret.ID       =  parent.ID - other.ID;
        ret.second   = &other;
        ret.Distance =  Get_Distance(parent, other); 
        ret.Tension  =  tension;
        ret.Color    =  parent.Color; 

    return ret;
}

//==========================================================================================================================================================================
//                                                      CLASS METHODS                                                                                                                                      
//==========================================================================================================================================================================


void Organism::Draw(){

   for(Cell &Parent:cells){
           for(Edge &Child: Parent.edges){

            float x1 =  Parent.Offset.X + Position.X,
                  y1 =  Parent.Offset.Y + Position.Y,
                  x2 =  Child.second->Offset.X + Position.X,
                  y2 =  Child.second->Offset.Y + Position.Y;
            SET_DRAW_COLOR(Parent.Color);
            LINE(x1,y1,x2,y2);
           }
    }

    for(Cell &cell: cells)
    {
        float x = Position.X+ cell.Offset.X,
              y = Position.Y+ cell.Offset.Y;
      
        SET_PIXEL(x,y,RGB(255,255,255));
       
    }
}




/// Acceleration = change in Velocity / change in time
/// Velocity = Velocity + Acceleration
// Acceleration = Force / Mass


//=====================================================================================================================================================================
//     THIS IS CURRENTLY WHERE i AM PLAYING ALL MY TOY CODE TO ACHIEVE DIFFERENT RESULTS AND TEST VARIOUS THINGS TO DO WITH PHYSICS                                                                                                                                                                        
//_____________________________________________________________________________________________________________________________________________________________________

void Organism::Update()
{
    
      double 
      DELTA_TIME     = 0, 
      DELTA_VELOCITY = 0;
    
      DELTA_TIME = SDL_GetTicks()- SCREEN->TIME;  SCREEN->TIME = SDL_GetTicks();
    
    
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
      for(Cell &Parent:cells){ // Cycle Every Cell
                                                                                              
            Parent.Acceleration = Parent.Force;  
          
            Parent.Velocity += Parent.Acceleration; // Change in Velocity equals Acceleration    
            Parent.Offset   += Parent.Velocity;     // Change in Position over time equals Velocity
            Parent.Velocity /=1.02;                 // APPLY A CRUDE "FRICTION" SO THAT VELOCITY IS LOST OVER TIME
          
            for(Edge &Child: Parent.edges){ // For Every Cell Get and Set Information about all Connecting Cells.
          
                  Child.Angle     = GetAngle     (Parent.Offset,  Child.second->Offset);
                  
                  Child.Distance  = Get_Distance (Parent       , *Child.second);
                  
                  Child.second->Force.X     += (Parent.Force.X * .5);
                  Child.second->Force.Y     += (Parent.Force.Y * .5);
                  
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Parent.Velocity += Parent.Acceleration
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
                  
            }
      }
//_____________________________________________________________________________________________________________________________________________________________________
//=====================================================================================================================================================================
    
}



double Get_Distance(const Cell &parent,const Cell &child){
    double ret =  sqrt(Squared(parent.Offset.X - child.Offset.X)  + Squared(parent.Offset.Y - child.Offset.Y));
    if(ret < 0) ret = 0; // HMMMMMMM
    return ret;
}



// FORCE.X = FORCE_APPLIED * COS(ANGLE)
// FORCE.Y = FORCE_APPLIED * SIN(ANGLE)

// acceleration = netForce / mass


//==========================================================================================================================================================================
//                                                                                                                                                                                    
//==========================================================================================================================================================================






//       Child.Delta_Distance = Child.Distance - Get_Distance(*Child.second, Parent); // Prob does not need to exist but may be useful to calculate yet not store


// (EX:)    tf = 2.47seconds     Acceleration = 46.1(m/s) - 18.5(m/s)  / 2.47(seconds) - 0(seconds) = 11.17(m/s^2)
//           ti = 0                                                                                                                  
//                                                                                                                       
//      Change in Velocity = Final Velocity - Initial Velocity                                                                                                                
//      Change in Time     = Final Time - Initial Time            
//                                                                                                                        
//      Acceleration       = Change in time / Change in Velocity                                                                                                                  
//                                                                                                                        
//                                                                                                                        
//                                                                                                                        
//       1 Newton = 1kg - (m/s^2)                                                                                                                 
//       <-2N-- + --7N-> = --5N->                                                                                                             
//                                                                                                                        
// (EX:) F            = 10N                                                                                                                       
//       mass         = 2kg                                                                                                                 
//       Acceleration = 10N / 2kg = 5(m/s^2)
//                                                                                                                        
//                                                                                                                        
//                                                                                                                        
//                                                                                                                        
