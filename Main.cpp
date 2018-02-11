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



int KEYBOARD_HANDLER(SDL_Keycode sym){
    return 0;
}

void main()
{
    srand(1500);
    WINDOW main(0,0,1280,960,"Multicelled automatons");
    SET_ACTIVE_WINDOW(&main);
   Cell *Selected;
    Organism Creature(10);
    int h = 0;
            Vector2D OM ,
            NM;
    while(LOOP_GAME()){
       _CLS;

//----------------------------- DRAW EACH CREATURE ------------------------------------------------------------
 
 for(Cell &Parent:Creature.cells){

     Parent.Force.X = Parent.Force.Y = 0;

     double 
     Old_X = Parent.Offset.X,
     Old_Y = Parent.Offset.Y;

     for(Edge &Child: Parent.edges){

            float 
            X = Parent.Offset.X + Creature.Position.X,
            Y = Parent.Offset.Y + Creature.Position.Y;

            SET_DRAW_COLOR(Child.Color);                 // SETS DRAW COLOR TO THAT OF THE CELL
            LINE2(X,Y, Child.Angle, Child.Distance *.5); // DRAWS EACH EDGE
            FILLED_CIRCLE(X,Y,8);                        // DRAWS EACH NODE
     }
 }

//------------------------- CHECK TO SEE IF NODE IS CLICKED ---------------------------------------------------

        if(SCREEN->MOUSE_BUTTON.LEFT == true){
            for(Cell &cell: Creature.cells){

                double
                Old_X = cell.Offset.X,
                Old_Y = cell.Offset.Y;

                if(Is_CLICK(cell.Offset.X + Creature.Position.X, cell.Offset.Y + Creature.Position.Y)) 
                { 
                  //  cell.Acceleration.X = cell.Acceleration.Y = 0;
                    double 
                    ox = cell.Offset.X,
                    oy = cell.Offset.Y;

                    cell.Offset.X = SCREEN->MOUSE_POSITION.x - Creature.Position.X;
                    cell.Offset.Y = SCREEN->MOUSE_POSITION.y - Creature.Position.Y;

                    float MASS = 10;
                    cell.Force.X = (MASS * SCREEN->MOUSE_VELOCITY.x) * .03; // .03, TIME STEP? 
                    cell.Force.Y = (MASS * SCREEN->MOUSE_VELOCITY.y) * .03;//(rand()%3-1) * 1;
                }
 
            }
        }
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