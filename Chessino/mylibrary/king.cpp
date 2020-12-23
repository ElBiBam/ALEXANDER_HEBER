#include "king.h"

uint16_t King::Counter{1};

King::King(std::string color, int x, int y)
    : Piece{color, x, y}
{
    ID = King::Counter++;
    if(color.compare(STR_BLACK) == 0)
        UrlFigure = ":/images/b_king.svg";
    else
        UrlFigure = ":/images/w_king.svg";
}

std::string King::GetColor() const
{
    return Color;
}

uint16_t King::GetID() const
{
    return ID;
}

uint16_t King::GetX() const
{
    return X;
}

uint16_t King::GetY() const
{
    return Y;
}

bool King::IsCaptured() const
{
    return Captured;
}

bool King::IsMoved() const
{
    return Moved;
}
void King::SetX(uint16_t x)
{
    X = x;
}
void King::SetY(uint16_t y)
{
    Y = y;
}

void King::SetCaptured(bool captured)
{
    Captured = captured;
}
void King::SetMoved(bool moved)
{
    Moved = moved;
}
std::vector<Square*> King::ValidMoves() const
{
    std::vector<Square*> result;
    if(Captured) return result;

    std::vector<std::vector<Square*> > squares = BOARD.GetSquares();
    int x= X;
    int y= Y;
    if(!Moved){
        qDebug()<<"1"<<Qt::endl;
        result.push_back(squares[x][y+2]);
        result.push_back(squares[x][y-2]);
        qDebug()<<"1"<<Qt::endl;
    }
    Square* square;
    Piece* piece;
    qDebug()<<"1"<<Qt::endl;
    if((x+1)<=7){
        if((y-1)>=0){
            square = squares[x+1][y-1];
            piece = square->GetPiece();
            if(piece && piece->GetColor().compare(Color) != 0)
                result.push_back(square);
            if(!piece) result.push_back(square);
        }
        square = squares[x+1][y];
        piece = square->GetPiece();
        if(piece && piece->GetColor().compare(Color) != 0)
            result.push_back(square);
        if(!piece) result.push_back(square);
        if((y+1)<=7){
            square = squares[x+1][y+1];
            piece = square->GetPiece();
            if(piece && piece->GetColor().compare(Color) != 0)
                result.push_back(square);
            if(!piece) result.push_back(square);
        }
    }
    qDebug()<<"2"<<Qt::endl;
    if((x-1)>=0){
        if((y-1)>=0){
            square = squares[x-1][y-1];
            piece = square->GetPiece();
            if(piece && piece->GetColor().compare(Color) != 0)
                result.push_back(square);
            if(!piece) result.push_back(square);
        }
        square = squares[x-1][y];
        piece = square->GetPiece();
        if(piece && piece->GetColor().compare(Color) != 0)
            result.push_back(square);
        if(!piece) result.push_back(square);
        if((y+1)<=7){
            square = squares[x-1][y+1];
            piece = square->GetPiece();
            if(piece && piece->GetColor().compare(Color) != 0)
                result.push_back(square);
            if(!piece) result.push_back(square);
        }
    }
    qDebug()<<"3"<<Qt::endl;
    if((y-1)>=0){
        square = squares[x][y-1];
        piece = square->GetPiece();
        if(piece && piece->GetColor().compare(Color) != 0)
            result.push_back(square);
        if(!piece) result.push_back(square);
    }
    qDebug()<<"4"<<Qt::endl;
    if((y+1)<=7){
        square = squares[x][y+1];
        piece = square->GetPiece();
        if(piece && piece->GetColor().compare(Color) != 0)
            result.push_back(square);
        if(!piece) result.push_back(square);
    }

    return result;
}
std::vector<Square*> King::AttackSquares() const
{
    std::vector<Square*> result;
    if(Captured) return result;

    std::vector<std::vector<Square*> > squares = BOARD.GetSquares();
    int x= X;
    int y= Y;

    Square* square;
    if((x+1)<=7){
        if((y-1)>=0){
            square = squares[x+1][y-1];
            result.push_back(square);
        }

        square = squares[x+1][y];
        result.push_back(square);

        if((y+1)<=7){
            square = squares[x+1][y+1];
            result.push_back(square);
        }
    }
    if((x-1)>=0){
        if((y-1)>=0){
            square = squares[x-1][y-1];
            result.push_back(square);
        }

        square = squares[x-1][y];
        result.push_back(square);

        if((y+1)<=7){
            square = squares[x-1][y+1];
            result.push_back(square);
        }
    }
    if((y-1)>=0){
        square = squares[x][y-1];
        result.push_back(square);
    }
    if((y+1)<=7){
        square = squares[x][y+1];
        result.push_back(square);
    }

    return result;
}
std::vector<Square*> King::CaptureFreeMoves() const
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

