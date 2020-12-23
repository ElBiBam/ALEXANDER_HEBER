#ifndef PIECE_H
#define PIECE_H

class Piece;

#include "mylibrary_global.h"
#include "square.h"

class Piece
{

protected:

    std::string Color{};
    uint16_t ID{};
    int X{64};
    int Y{64};

    bool Captured{false};
    bool Moved{false};

    std::string UrlFigure;

public:
    Piece() = delete;
    Piece(std::string color, int x, int y): Color{color}, X{x}, Y{y} {};
    virtual std::string GetColor() const = 0;
    virtual uint16_t GetID() const = 0;

    virtual uint16_t GetX() const = 0;
    virtual uint16_t GetY() const = 0;
    virtual std::string GetUrlFigure() const = 0;
    virtual bool IsCaptured() const = 0;
    virtual bool IsMoved() const = 0;

    //virtual bool HowMove() const = 0;
    virtual std::vector<Square*> ValidMoves() const = 0;
    virtual std::vector<Square*> AttackSquares() const = 0;
    virtual std::vector<Square*> CaptureFreeMoves() const = 0;

    virtual void SetX(uint16_t x) = 0;
    virtual void SetY(uint16_t y) = 0;

    virtual void SetCaptured(bool captured) = 0;
    virtual void SetMoved(bool moved) = 0;



    virtual ~Piece(){/*std::cout<<"Piece destroyed\n";*/}

};

#endif // PIECE_H
