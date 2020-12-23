#include "pawn.h"

uint16_t Pawn::Counter{1};

Pawn::Pawn(std::string color, int x, int y)
    : Piece{color, x, y}
{
    ID = Pawn::Counter++;
    if(color.compare(STR_BLACK) == 0)
        UrlFigure = ":/images/b_pawn.svg";
    else
        UrlFigure = ":/images/w_pawn.svg";
}

std::string Pawn::GetColor() const
{
    return Color;
}

uint16_t Pawn::GetID() const
{
    return ID;
}

uint16_t Pawn::GetX() const
{
    return X;
}

uint16_t Pawn::GetY() const
{
    return Y;
}

bool Pawn::IsCaptured() const
{
    return Captured;
}

bool Pawn::IsMoved() const
{
    return Moved;
}
void Pawn::SetX(uint16_t x)
{
    X = x;
}
void Pawn::SetY(uint16_t y)
{
    Y = y;
}

void Pawn::SetCaptured(bool captured)
{
    Captured = captured;
}
void Pawn::SetMoved(bool moved)
{
    Moved = moved;
}
/*bool Pawn::HowMove() const
{
    if(Moved){
        if(GetColor().compare(STR_WHITE) == 0){

        }else{

        }
    }else{

    }
    return true;
}*/
std::vector<Square*> Pawn::ValidMoves() const
{
    std::vector<Square*> result;
    if(Captured) return result;

    std::vector<std::vector<Square*> > squares = BOARD.GetSquares();
    int x= X;
    int y= Y;
    if(!Moved){
        if(Color.compare(STR_WHITE) == 0)
            result.push_back(squares[x-2][y]);
        else
            result.push_back(squares[x+2][y]);        
    }
    qDebug()<<"Pawn valid moves"<<Qt::endl;
    if(Color.compare(STR_WHITE) == 0){
        result.push_back(squares[x-1][y]);

        if((y-1)>=0){
            Square* square = squares[x-1][y-1];
            Piece* piece = square->GetPiece();
            if(piece && piece->GetColor().compare(Color) != 0)
                result.push_back(square);
        }
        if((y+1)<=7){
            Square* square = squares[x-1][y+1];
            Piece* piece = square->GetPiece();
            if(piece && piece->GetColor().compare(Color) != 0)
                result.push_back(square);
        }
    }else{
        result.push_back(squares[x+1][y]);

        if((y-1)>=0){
            Square* square = squares[x+1][y-1];
            Piece* piece = square->GetPiece();
            if(piece && piece->GetColor().compare(Color) != 0)
                result.push_back(square);
        }
        if((y+1)<=7){
            Square* square = squares[x+1][y+1];
            Piece* piece = square->GetPiece();
            if(piece && piece->GetColor().compare(Color) != 0)
                result.push_back(square);
        }
    }



    return result;
}
std::vector<Square*> Pawn::AttackSquares() const
{
    std::vector<Square*> result;
    if(Captured) return result;

    std::vector<std::vector<Square*> > squares = BOARD.GetSquares();
    int x= X;
    int y= Y;

    if(Color.compare(STR_WHITE) == 0){
        if((y-1)>=0){
            Square* square = squares[x-1][y-1];
            result.push_back(square);
        }
        if((y+1)<=7){
            Square* square = squares[x-1][y+1];
            result.push_back(square);
        }
    }else{
        if((y-1)>=0){
            Square* square = squares[x+1][y-1];
            result.push_back(square);
        }
        if((y+1)<=7){
            Square* square = squares[x+1][y+1];
            result.push_back(square);
        }
    }

    return result;
}
std::vector<Square*> Pawn::CaptureFreeMoves() const
{
    std::vector<Square*> result;
    if(Captured) return result;

    std::set<Square*> threatSet;
    std::vector<std::vector<Square*> > squares = BOARD.GetSquares();
    for(unsigned i=0; i<squares.size(); ++i){
        for(unsigned j=0; j<squares[i].size(); ++j){
            Piece* piece = squares[i][j]->GetPiece();

            if(piece && piece->GetColor().compare(Color) != 0){
                std::vector<Square*> attacks = piece->AttackSquares();
                for(unsigned ii = 0; ii < attacks.size(); ++ii){
                    threatSet.insert(attacks[ii]);
                }
            }
        }
    }
    result = ValidMoves();
    std::set<Square*>::iterator it = threatSet.begin();
    for(; it!=threatSet.end(); ++it){
        result.erase(std::find(result.begin(), result.end(), *it));
    }
    return result;
}
