#ifndef PAWN_H
#define PAWN_H

class Pawn;

#include "mylibrary/mylibrary_global.h"
#include "mylibrary/share_typedef.h"
#include "Piece.h"

class Pawn : public Piece
{
public:
    Pawn() = delete;
    Pawn(std::string color, int x, int y);
    std::string GetColor() const override;
    uint16_t GetID() const override;
    bool IsCaptured() const override;
    bool IsMoved() const override;

    uint16_t GetX() const override;
    uint16_t GetY() const override;
    std::string GetUrlFigure() const override{ return UrlFigure; }

    //bool HowMove() const override;
    std::vector<Square*> ValidMoves() const override;
    std::vector<Square*> AttackSquares() const override;
    std::vector<Square*> CaptureFreeMoves() const override;

    void SetX(uint16_t x) override;
    void SetY(uint16_t y) override;

    void SetCaptured(bool captured) override;
    void SetMoved(bool moved) override;



    ~Pawn(){ }

private:
    static uint16_t Counter;

    static uint16_t Max(int a, int b )
    {
        return ( a > b ) ? a : b;
    };

};

#endif // PAWN_H
