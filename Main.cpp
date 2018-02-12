//                                                                                                                                                                                                                                                                                                            
//                                                                                                                                                                                                                                                                                                            
//        SDL FRAMEWORK FOR GRAPHICS OPERATIONS                                                                                                                                                                                                                                                                                       
//                                                                                                                                                                                                                                                                                                       
//                                                                                                                                                                                                                                                                                                       
//                                                                                                                                                                                                                                                                                                       
//                                                                                                                                                                                                                                                                                                       
// TARGET: WINDOW *SCREEN pointer. This is where all functions read from and draw to.                                                                                                                                                                                                                                                                                                 
//=============================================================================================================                                                                                                                                                                                                                                                                                                              


#include"cell.h"
#include<iostream>
#include "brain.h"



int KEYBOARD_HANDLER(SDL_Keycode sym){
    return 0;
}


#define NUBER_OF_NEURONS    10

void Draw_Edges(int Xx,int Yy, Cell Parent)
{
         for(Edge &Child: Parent.edges){
         
            float 
            X = Parent.Offset.X + Xx,
            Y = Parent.Offset.Y + Yy;

            SET_DRAW_COLOR(Child.Color);                 // SETS DRAW COLOR TO THAT OF THE CELL
            LINE2(X,Y, Child.Angle, Child.Distance *.5); // DRAWS EACH EDGE
           // FILLED_CIRCLE(X,Y,8);                        // DRAWS EACH NODE
     }
}




void main()
{
    srand(1500);
    WINDOW main(0,0,1280,960,"Multicelled automatons");
    SET_ACTIVE_WINDOW(&main);

    Organism Creature(20);

    Cell *Selected = nullptr;

    while(LOOP_GAME()){
       _CLS;

//----------------------------- DRAW EACH CREATURE ------------------------------------------------------------
 
 for(Cell &Parent:Creature.cells){

    // Parent.Force.X = Parent.Force.Y = 0;

     double 
     Old_X = Parent.Offset.X,
     Old_Y = Parent.Offset.Y;
    
     Draw_Edges(Creature.Position.X, Creature.Position.Y , Parent);
 }

//------------------------- CHECK TO SEE IF NODE IS CLICKED ---------------------------------------------------

        if(Selected == nullptr && SCREEN->MOUSE_BUTTON.LEFT == true){
            for(Cell &cell: Creature.cells){

                if(Is_CLICK(cell.Offset.X + Creature.Position.X, cell.Offset.Y + Creature.Position.Y))Selected = &cell;

            }
        }
        

        if (Selected != nullptr){ 
       
            Selected->Offset.X = SCREEN->MOUSE_POSITION.x - Creature.Position.X;
            Selected->Offset.Y = SCREEN->MOUSE_POSITION.y - Creature.Position.Y;
             
            float MASS = 4;

            Selected->Force.X = (MASS * SCREEN->MOUSE_VELOCITY.x) ; // .03, TIME STEP? 
            Selected->Force.Y = (MASS * SCREEN->MOUSE_VELOCITY.y);//(rand()%3-1) * 1;

            SET_DRAW_COLOR(RGB(255,255,255));
            FILLED_CIRCLE(Selected->Offset.X + Creature.Position.X,Selected->Offset.Y + Creature.Position.Y,7);
       }
        if(SCREEN->MOUSE_BUTTON.LEFT == false){Selected = nullptr;}

//-------------------------------------------------------------------------------------------------------------
        double Length = abs(SCREEN->MOUSE_VELOCITY.x) + abs(SCREEN->MOUSE_VELOCITY.y) ;
        if( Length > 400) Length  = 400;                                              // DRAW MOUSE INFORMATION
        LINE2(200,200,SCREEN->MOUSE_ANGLE, Length);
//-------------------------------------------------------------------------------------------------------------

 Print(SCREEN->MOUSE_VELOCITY.x);

        Creature.Update();
       _SYNC;
    }

}




//???   LAST CELL DOES NOT EFFECT ALL OTHER, THE FIRST PROCESSED EFFECTS ALL AND CREATES A HIERACHY









/*
void main(){
    
    vector<Neuron> Brain ;
    
    Brain.resize(NUBER_OF_NEURONS);

    for(Neuron &n: Brain){
        n.Synapses.resize(NUBER_OF_NEURONS);
        n.Voltage = RANDOM(2) - 1;
       Print(n.Voltage);
    }
    Print(Brain.size());

    for(int count = Brain.size(); count > 0;count--)
    {
        Print(Brain[count - 1].Voltage);
    }

   // Print(Brain.back().Voltage);
    system("PAUSE");
}*/
