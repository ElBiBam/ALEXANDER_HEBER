#ifndef SQUARE_H
#define SQUARE_H

class Square;

#include "mylibrary/mylibrary_global.h"
#include "mylibrary/Piece.h"

class MYLIBRARYSHARED_EXPORT Square : public QLabel
{
    Q_OBJECT

public:
    explicit Square(QWidget *parent = nullptr);
    ~Square();

    void SetPiece(Piece* piece)
    {
        this->piece = piece;
    }
    /*bool FromSquare(Square* from)
    {
        int stateMoved = Movement::WasMoved(piece, from->GetPiece());
        switch(stateMoved){
        case Movement::NO_MOVED:
            return false;
        case Movement::MOVED:
            from->GetPiece()->SetX(X);
            from->GetPiece()->SetY(Y);
            this->piece = from->GetPiece();
            return true;
        case Movement::CAPTURED:
            Piece* temp = this->piece; // La pieza que va a ser comida
            // Guardando la Posición de la pieza comida
            from->GetPiece()->SetX(X);
            from->GetPiece()->SetY(Y);
            // Le pasamos la pieza
            this->piece = from->GetPiece();
            // Se puede eliminar o enviar a una lista de fichas comidas
            delete temp;
            from->SetPiece(nullptr);
            from->setPixmap(QPixmap::fromImage(QImage(":/images/transparent.svg")));
            return true;
        }
    }*/
    void SetPosition(uint16_t x, uint16_t y){ X = x; Y = y; }
    uint16_t GetX() const { return X; }
    uint16_t GetY() const { return Y; }

    Piece* GetPiece(){ return this->piece; }
private:
    Piece* piece{nullptr};

    uint16_t X;
    uint16_t Y;
};

#endif // SQUARE_H
