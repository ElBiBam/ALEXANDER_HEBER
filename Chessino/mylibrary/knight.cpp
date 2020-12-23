#include "knight.h"

uint16_t Knight::Counter{1};

Knight::Knight(std::string color, int x, int y)
    : Piece{color, x, y}
{
    ID = Knight::Counter++;
    if(color.compare(STR_BLACK) == 0)
        UrlFigure = ":/images/b_knight.svg";
    else
        UrlFigure = ":/images/w_knight.svg";
}

std::string Knight::GetColor() const
{
    return Color;
}

uint16_t Knight::GetID() const
{
    return ID;
}

uint16_t Knight::GetX() const
{
    return X;
}

uint16_t Knight::GetY() const
{
    return Y;
}

bool Knight::IsCaptured() const
{
    return Captured;
}

bool Knight::IsMoved() const
{
    return Moved;
}
void Knight::SetX(uint16_t x)
{
    X = x;
}
void Knight::SetY(uint16_t y)
{
    Y = y;
}

void Knight::SetCaptured(bool captured)
{
    Captured = captured;
}
void Knight::SetMoved(bool moved)
{
    Moved = moved;
}
std::vector<Square*> Knight::ValidMoves() const
{
    std::vector<Square*> result;
    if(Captured) return result;

    std::vector<std::vector<Square*> > squares = BOARD.GetSquares();
    int x= X;
    int y= Y;
    qDebug()<<"Knight valid moves"<<Qt::endl;

    Square* square;
    Piece* piece;
    if((x+1)<=7 && (y+2)<=7){
        square = squares[x+1][y+2];
        piece = square->GetPiece();
        if(piece && piece->GetColor().compare(Color) != 0) result.push_back(square);
        if(!piece) result.push_back(square);
    }
    if((x+1)<=7 && (y-2)>=0){
        square = squares[x+1][y-2];
        piece = square->GetPiece();
        if(piece && piece->GetColor().compare(Color) != 0) result.push_back(square);
        if(!piece) result.push_back(square);
    }
    if((x-1)>=0 && (y+2)<=7){
        square = squares[x-1][y+2];
        piece = square->GetPiece();
        if(piece && piece->GetColor().compare(Color) != 0) result.push_back(square);
        if(!piece) result.push_back(square);
    }
    if((x-1)>=0 && (y-2)>=0){
        square = squares[x-1][y-2];
        piece = square->GetPiece();
        if(piece && piece->GetColor().compare(Color) != 0) result.push_back(square);
        if(!piece) result.push_back(square);
    }
    if((x+2)<=7 && (y+1)<=7){
        square = squares[x+2][y+1];
        piece = square->GetPiece();
        if(piece && piece->GetColor().compare(Color) != 0) result.push_back(square);
        if(!piece) result.push_back(square);
    }
    if((x+2)<=7 && (y-1)>=0){
        square = squares[x+2][y-1];
        piece = square->GetPiece();
        if(piece && piece->GetColor().compare(Color) != 0) result.push_back(square);
        if(!piece) result.push_back(square);
    }
    if((x-2)>=0 && (y+1)<=7){
        square = squares[x-2][y+1];
        piece = square->GetPiece();
        if(piece && piece->GetColor().compare(Color) != 0) result.push_back(square);
        if(!piece) result.push_back(square);
    }
    if((x-2)>=0 && (y-1)>=0){
        square = squares[x-2][y-1];
        piece = square->GetPiece();
        if(piece && piece->GetColor().compare(Color) != 0) result.push_back(square);
        if(!piece) result.push_back(square);
    }

    return result;
}
std::vector<Square*> Knight::AttackSquares() const
{
    std::vector<Square*> result;
    if(Captured) return result;

    std::vector<std::vector<Square*> > squares = BOARD.GetSquares();
    int x= X;
    int y= Y;
    Square* square;
    if((x+1)<=7 && (y+2)<=7){
        square = squares[x+1][y+2];
        result.push_back(square);
    }
    if((x+1)<=7 && (y-2)>=0){
        square = squares[x+1][y-2];
        result.push_back(square);
    }
    if((x-1)>=0 && (y+2)<=7){
        square = squares[x-1][y+2];
        result.push_back(square);
    }
    if((x-1)>=0 && (y-2)>=0){
        square = squares[x-1][y-2];
        result.push_back(square);
    }
    if((x+2)<=7 && (y+1)<=7){
        square = squares[x+2][y+1];
        result.push_back(square);
    }
    if((x+2)<=7 && (y-1)>=0){
        square = squares[x+2][y-1];
        result.push_back(square);
    }
    if((x-2)>=0 && (y+1)<=7){
        square = squares[x-2][y+1];
        result.push_back(square);
    }
    if((x-2)>=0 && (y-1)>=0){
        square = squares[x-2][y-1];
        result.push_back(square);
    }

    return result;
}
std::vector<Square*> Knight::CaptureFreeMoves() const
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
