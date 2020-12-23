#ifndef BOARD_H
#define BOARD_H

class Board;

#include "mylibrary/mylibrary_global.h"
#include "square.h"
#include "mylibrary/share_include.h"
//! [0]
namespace Ui {
class Board;
}

class MYLIBRARYSHARED_EXPORT Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = nullptr);
    ~Board();

    std::vector<std::vector<Square*> > GetSquares() const{ return squares; }

    bool IsChecked();
    bool IsCheckMated(Square *startSquare, Square *square);
    bool ThreatOfCheck(Square *startSquare);
    void OccupySquare(Square *startSquare, Square *endSquare);
    void Eaten(Square *startSquare, Square *endSquare);    
    void Move(Square* startSquare, Square* endSquare);

    enum PieceColor{WHITE = 0, BLACK = 1};
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

    void showEvent(QShowEvent* event) override;

private:
    Ui::Board *ui;

    std::vector<std::vector<Square*> > squares;
    bool Checked{false};
    Piece* KingChecked{nullptr};
    Piece* PieceCheck{nullptr};
    bool CheckMated{false};
    //std::list<Piece*> whitePieces;
    //std::list<Piece*> blackPieces;
    //std::vector<Movement*> moves;
    bool turn{true}; // true es blancas y false es negras
};
//! [0]
#endif // BOARD_H
