#ifndef KNIGHT_H
#define KNIGHT_H

#include "mylibrary/mylibrary_global.h"
#include "mylibrary/share_typedef.h"
#include "Piece.h"

class Knight : public Piece
{
public:
    Knight() = delete;
    Knight(std::string color, int x, int y);
    std::string GetColor() const override;
    uint16_t GetID() const override;
    bool IsCaptured() const override;
    bool IsMoved() const override;

    uint16_t GetX() const override;
    uint16_t GetY() const override;
    std::string GetUrlFigure() const override{ return UrlFigure; }

    std::vector<Square*> ValidMoves() const override;
    std::vector<Square*> AttackSquares() const override;
    std::vector<Square*> CaptureFreeMoves() const override;

    void SetX(uint16_t x) override;
    void SetY(uint16_t y) override;

    void SetCaptured(bool captured) override;
    void SetMoved(bool moved) override;

    ~Knight(){ }

private:

    static uint16_t Counter;
};

#endif // KNIGHT_H
