#ifndef MOVEMENT_H
#define MOVEMENT_H

class Movement;

#include "mylibrary_global.h"
#include "Piece.h"

class Movement
{
public:
    Movement();
    static int WasMoved(Piece* from, Piece* to)
    {
        return 0;
        /*if(from->VerifyMovement(to)){

            return MOVED;
        }else{
            return NO_MOVED;
        }*/
        // Resolver el movimiento

    }
    enum state{NO_MOVED = 0, MOVED, CAPTURED};
};

#endif // MOVEMENT_H
