#include "queen.h"

uint16_t Queen::Counter{1};

Queen::Queen(std::string color, int x, int y)
    : Piece{color, x, y}
{
    ID = Queen::Counter++;
    if(color.compare(STR_BLACK) == 0)
        UrlFigure = ":/images/b_queen.svg";
    else
        UrlFigure = ":/images/w_queen.svg";
}

std::string Queen::GetColor() const
{
    return Color;
}

uint16_t Queen::GetID() const
{
    return ID;
}

uint16_t Queen::GetX() const
{
    return X;
}

uint16_t Queen::GetY() const
{
    return Y;
}

bool Queen::IsCaptured() const
{
    return Captured;
}

bool Queen::IsMoved() const
{
    return Moved;
}
void Queen::SetX(uint16_t x)
{
    X = x;
}
void Queen::SetY(uint16_t y)
{
    Y = y;
}

void Queen::SetCaptured(bool captured)
{
    Captured = captured;
}
void Queen::SetMoved(bool moved)
{
    Moved = moved;
}
std::vector<Square*> Queen::ValidMoves() const
{
    std::vector<Square*> result;
    if(Captured) return result;

    std::vector<std::vector<Square*> > squares = BOARD.GetSquares();
    Square* square;
    Piece* piece = nullptr;
    int x= X;
    int y= Y;
    qDebug()<<"Queen valid moves"<<Qt::endl;
    while(++x<=7 && ++y<=7 && !piece){
        square = squares[x][y];
        piece = square->GetPiece();
        if(piece && piece->GetColor().compare(Color) == 0) break;
        if(piece && piece->GetColor().compare(Color) != 0){ result.push_back(square); break; }
        result.push_back(square);
    }
    piece = nullptr;
    x= X;
    y= Y;
    while(++x<=7 && --y>=0 && !piece){
        square = squares[x][y];
        piece = square->GetPiece();
        if(piece && piece->GetColor().compare(Color) == 0) break;
        if(piece && piece->GetColor().compare(Color) != 0){ result.push_back(square); break; }
        result.push_back(square);
    }
    piece = nullptr;
    x= X;
    y= Y;
    while(--x>=0 && ++y<=7 && !piece){
        square = squares[x][y];
        piece = square->GetPiece();
        if(piece && piece->GetColor().compare(Color) == 0) break;
        if(piece && piece->GetColor().compare(Color) != 0){ result.push_back(square); break; }
        result.push_back(square);
    }
    piece = nullptr;
    x= X;
    y= Y;
    while(--x>=0 && --y>=0 && !piece){
        square = squares[x][y];
        piece = square->GetPiece();
        if(piece && piece->GetColor().compare(Color) == 0) break;
        if(piece && piece->GetColor().compare(Color) != 0){ result.push_back(square); break; }
        result.push_back(square);
    }
    piece = nullptr;
    x= X;
    y= Y;
    while(++x<=7 && !piece){
        square = squares[x][y];
        piece = square->GetPiece();
        if(piece && piece->GetColor().compare(Color) == 0) break;
        if(piece && piece->GetColor().compare(Color) != 0){ result.push_back(square); break; }
        result.push_back(square);
    }
    piece = nullptr;
    x= X;
    y= Y;
    while(--x>=0 && !piece){
        square = squares[x][y];
        piece = square->GetPiece();
        if(piece && piece->GetColor().compare(Color) == 0) break;
        if(piece && piece->GetColor().compare(Color) != 0){ result.push_back(square); break; }
        result.push_back(square);
    }
    piece = nullptr;
    x= X;
    y= Y;
    while(++y<=7 && !piece){
        square = squares[x][y];
        piece = square->GetPiece();
        if(piece && piece->GetColor().compare(Color) == 0) break;
        if(piece && piece->GetColor().compare(Color) != 0){ result.push_back(square); break; }
        result.push_back(square);
    }
    piece = nullptr;
    x= X;
    y= Y;
    while(--y>=0 && !piece){
        square = squares[x][y];
        piece = square->GetPiece();
        if(piece && piece->GetColor().compare(Color) == 0) break;
        if(piece && piece->GetColor().compare(Color) != 0){ result.push_back(square); break; }
        result.push_back(square);
    }

    return result;
}
std::vector<Square*> Queen::AttackSquares() const
{
    std::vector<Square*> result;
    if(Captured) return result;

    std::vector<std::vector<Square*> > squares = BOARD.GetSquares();
    Square* square;
    Piece* piece = nullptr;
    int x= X;
    int y= Y;
    while(++x<=7 && ++y<=7 && !piece){
        square = squares[x][y];
        piece = square->GetPiece();
        if(piece){ result.push_back(square); break; }
        result.push_back(square);
    }
    piece = nullptr;
    x= X;
    y= Y;
    while(++x<=7 && --y>=0 && !piece){
        square = squares[x][y];
        piece = square->GetPiece();
        if(piece){ result.push_back(square); break; }
        result.push_back(square);
    }
    piece = nullptr;
    x= X;
    y= Y;
    while(--x>=0 && ++y<=7 && !piece){
        square = squares[x][y];
        piece = square->GetPiece();
        if(piece){ result.push_back(square); break; }
        result.push_back(square);
    }
    piece = nullptr;
    x= X;
    y= Y;
    while(--x>=0 && --y>=0 && !piece){
        square = squares[x][y];
        piece = square->GetPiece();
        if(piece){ result.push_back(square); break; }
        result.push_back(square);
    }
    piece = nullptr;
    x= X;
    y= Y;
    while(++x<=7 && !piece){
        square = squares[x][y];
        piece = square->GetPiece();
        if(piece){ result.push_back(square); break; }
        result.push_back(square);
    }
    piece = nullptr;
    x= X;
    y= Y;
    while(--x>=0 && !piece){
        square = squares[x][y];
        piece = square->GetPiece();
        if(piece){ result.push_back(square); break; }
        result.push_back(square);
    }
    piece = nullptr;
    x= X;
    y= Y;
    while(++y<=7 && !piece){
        square = squares[x][y];
        piece = square->GetPiece();
        if(piece){ result.push_back(square); break; }
        result.push_back(square);
    }
    piece = nullptr;
    x= X;
    y= Y;
    while(--y>=0 && !piece){
        square = squares[x][y];
        piece = square->GetPiece();
        if(piece){ result.push_back(square); break; }
        result.push_back(square);
    }

    return result;
}
std::vector<Square*> Queen::CaptureFreeMoves() const
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
