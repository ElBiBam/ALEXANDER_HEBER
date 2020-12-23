#include "bishop.h"

uint16_t Bishop::Counter{1};

Bishop::Bishop(std::string color, int x, int y)
    : Piece{color, x, y}
{
    ID = Bishop::Counter++;
    if(color.compare(STR_BLACK) == 0)
        UrlFigure = ":/images/b_bishop.svg";
    else
        UrlFigure = ":/images/w_bishop.svg";
}

std::string Bishop::GetColor() const
{
    return Color;
}

uint16_t Bishop::GetID() const
{
    return ID;
}

uint16_t Bishop::GetX() const
{
    return X;
}

uint16_t Bishop::GetY() const
{
    return Y;
}

bool Bishop::IsCaptured() const
{
    return Captured;
}

bool Bishop::IsMoved() const
{
    return Moved;
}
void Bishop::SetX(uint16_t x)
{
    X = x;
}
void Bishop::SetY(uint16_t y)
{
    Y = y;
}

void Bishop::SetCaptured(bool captured)
{
    Captured = captured;
}
void Bishop::SetMoved(bool moved)
{
    Moved = moved;
}

std::vector<Square*> Bishop::ValidMoves() const
{
    std::vector<Square*> result;
    if(Captured) return result;

    std::vector<std::vector<Square*> > squares = BOARD.GetSquares();
    Square* square;
    Piece* piece = nullptr;
    int x= X;
    int y= Y;
    qDebug()<<"Bishop valid moves"<<Qt::endl;
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
    return result;
}
std::vector<Square*> Bishop::AttackSquares() const
{
    std::vector<Square*> result;
    if(Captured) return result;

    std::vector<std::vector<Square*> > squares = BOARD.GetSquares();
    Square* square = squares[X][Y];
    Piece* piece = nullptr;
    int x= X;
    int y= Y;
    while(++x<=7 && ++y<=7){
        square = squares[x][y];
        piece = square->GetPiece();
        if(piece){ result.push_back(square); break; }
        result.push_back(square);
    }
    piece = nullptr;
    x= X;
    y= Y;
    while(++x<=7 && --y>=0){
        square = squares[x][y];
        piece = square->GetPiece();
        if(piece){ result.push_back(square); break; }
        result.push_back(square);
    }
    piece = nullptr;
    x= X;
    y= Y;
    while(--x>=0 && ++y<=7){
        square = squares[x][y];
        piece = square->GetPiece();
        if(piece){ result.push_back(square); break; }
        result.push_back(square);
    }
    piece = nullptr;
    x= X;
    y= Y;
    while(--x>=0 && --y>=0){
        square = squares[x][y];
        piece = square->GetPiece();
        if(piece){ result.push_back(square); break; }
        result.push_back(square);
    }
    return result;
}
std::vector<Square*> Bishop::CaptureFreeMoves() const
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
