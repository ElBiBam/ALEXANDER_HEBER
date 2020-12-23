#include "board.h"
#include "ui_board.h"

Board::Board(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Board)
{
    ui->setupUi(this);

    std::vector<Piece*> v;

    v.push_back(new Rook(STR_BLACK, 0, 0));
    v.push_back(new Knight(STR_BLACK, 0, 1));
    v.push_back(new Bishop(STR_BLACK, 0, 2));
    v.push_back(new Queen(STR_BLACK, 0, 3));
    v.push_back(new King(STR_BLACK, 0, 4));
    v.push_back(new Bishop(STR_BLACK, 0, 5));
    v.push_back(new Knight(STR_BLACK, 0, 6));
    v.push_back(new Rook(STR_BLACK, 0, 7));
    for(unsigned i=0; i<8; ++i) v.push_back(new Pawn(STR_BLACK, 1, i));
    for(unsigned i=0; i<32; ++i) v.push_back(nullptr);
    for(unsigned i=0; i<8; ++i) v.push_back(new Pawn(STR_WHITE, 6, i));
    v.push_back(new Rook(STR_WHITE, 7, 0));
    v.push_back(new Knight(STR_WHITE, 7, 1));
    v.push_back(new Bishop(STR_WHITE, 7, 2));
    v.push_back(new Queen(STR_WHITE, 7, 3));
    v.push_back(new King(STR_WHITE, 7, 4));
    v.push_back(new Bishop(STR_WHITE, 7, 5));
    v.push_back(new Knight(STR_WHITE, 7, 6));
    v.push_back(new Rook(STR_WHITE, 7, 7));

    unsigned vi = 0;
    for(int i = 0; i < 8; ++i){
        squares.push_back(std::vector<Square*>());
        for(int j = 0; j < 8; ++j){
            Square* square = new Square;
            square->SetPosition(i, j);
            square->SetPiece(v[vi++]);
            if(square->GetPiece())
                square->setPixmap(QPixmap::fromImage(QImage(square->GetPiece()->GetUrlFigure().c_str())));
            else
                square->setPixmap(QPixmap::fromImage(QImage(":/images/transparent.svg")));
            // .scaled(100,100)
            square->setScaledContents(true);
            square->setStyleSheet("background-color: rgb(255, 255, 127);");
            //square->styleSheet = "background-color: rgb(255, 255, 127);";
            //qDebug()<<square->geometry()<<Qt::endl;
            ui->gridLayout_board->addWidget(square, i, j);
            squares[i].push_back(square);
            square->show();

        }
    }
    qDebug()<<"mousePressEvent"<<Qt::endl;
    std::vector<std::string> styleSheets;
    styleSheets.push_back("background-color: rgb(255, 255, 230);");
    styleSheets.push_back("background-color: rgb(100, 200, 30);");
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            Square* square = static_cast<Square*>(ui->gridLayout_board->itemAtPosition(i, j)->widget());
            square->setStyleSheet(styleSheets[(i+j)%2].c_str());
            //square->styleSheet = styleSheets[(i+j)%2].c_str();
        }
    }

    this->setAcceptDrops(true);
}

Board::~Board()
{
    delete ui;
}
bool Board::IsChecked()
{
    qDebug()<<"IsChecked"<<Qt::endl;
    std::string color;
    if(turn){
        color = STR_BLACK;
    }else{
        color = STR_WHITE;
    }


    std::set<Square*> threatSet;
    std::vector<std::vector<Square*> > squares = BOARD.GetSquares();
    for(unsigned i=0; i<squares.size(); ++i){
        for(unsigned j=0; j<squares[i].size(); ++j){
            Piece* piece = squares[i][j]->GetPiece();

            if(piece && piece->GetColor().compare(color) == 0){
                qDebug()<<"if"<<Qt::endl;
                qDebug()<<i<<j<<Qt::endl;
                std::vector<Square*> attacks = piece->AttackSquares();
                qDebug()<<QString(typeid(*piece).name())<<Qt::endl;
                for(unsigned ii = 0; ii < attacks.size(); ++ii){
                    threatSet.insert(attacks[ii]);
                }
                qDebug()<<QString(typeid(*piece).name())<<Qt::endl;
            }
        }
    }

    qDebug()<<"IsChecked"<<Qt::endl;

    std::set<Square*>::iterator it = threatSet.begin();
    for(; it!=threatSet.end(); ++it){
        Piece* piece = (*it)->GetPiece();
        if(piece && piece->GetColor().compare(color) != 0 && QString(typeid(*piece).name()).compare("class King") == 0){
            Checked = true;
            KingChecked = piece;
            //PieceCheck = square->GetPiece();
            return true;
        }
    }
    qDebug()<<"IsChecked"<<Qt::endl;

    return false;
}
bool Board::IsCheckMated(Square *startSquare, Square *endSquare)
{
    qDebug()<<"IsCheckMated"<<Qt::endl;
    std::string color;
    if(turn){
        color = STR_BLACK;
    }else{
        color = STR_WHITE;
    }

    std::set<Square*> attacksSet;
    std::vector<std::vector<Square*> > squares = BOARD.GetSquares();
    for(unsigned i=0; i<squares.size(); ++i){
        for(unsigned j=0; j<squares[i].size(); ++j){
            Piece* piece = squares[i][j]->GetPiece();

            if(piece && piece->GetColor().compare(color) == 0){
                qDebug()<<"if"<<Qt::endl;
                qDebug()<<i<<j<<Qt::endl;
                std::vector<Square*> attacks = piece->AttackSquares();
                qDebug()<<QString(typeid(*piece).name())<<Qt::endl;
                for(unsigned ii = 0; ii < attacks.size(); ++ii){
                    attacksSet.insert(attacks[ii]);
                    /*Piece* pieceAttacked = attacks[ii]->GetPiece();
                    if(pieceAttacked && pieceAttacked->GetColor().compare(color) != 0
                            && QString(typeid(*pieceAttacked).name()).compare("class King") == 0){
                            //&& QString(typeid(*piece).name()).compare("class Knight") == 0){
                        if(QString(typeid(*piece).name()).compare("class Knight") == 0){

                        }
                    }*/
                }
                qDebug()<<QString(typeid(*piece).name())<<Qt::endl;
            }
        }
    }

    qDebug()<<"IsCheckMated 2"<<Qt::endl;

    std::set<Square*>::iterator it = attacksSet.begin();
    for(; it!=attacksSet.end(); ++it){
        Piece* piece = (*it)->GetPiece();
        if(piece && piece->GetColor().compare(color) != 0 && QString(typeid(*piece).name()).compare("class King") == 0){
            //Checked = true;
            KingChecked = piece;
            break;
            //PieceCheck = square->GetPiece();
            //return true;
        }
    }
    std::vector<Square*> captureFreeMoves;
    if(startSquare->GetPiece() == KingChecked){
        captureFreeMoves = KingChecked->CaptureFreeMoves();
        for(unsigned i = 0; i<captureFreeMoves.size(); ++i){
            if(captureFreeMoves[i] == endSquare){

                Piece* startPiece = startSquare->GetPiece();
                startPiece->SetMoved(true);
                startPiece->SetX(endSquare->GetX());
                startPiece->SetY(endSquare->GetY());
                qDebug()<<startSquare->GetX()<<startSquare->GetY()<<Qt::endl;
                qDebug()<<endSquare->GetX()<<endSquare->GetY()<<Qt::endl;

                //if(startPiece)
                //    qDebug()<<"startPiece exist"<<Qt::endl;
                endSquare->SetPiece(startPiece);
                startSquare->SetPiece(nullptr);
                //if(endSquare->GetPiece())
                //    qDebug()<<"startPiece exist"<<Qt::endl;

                QPixmap pixmap = startSquare->pixmap(Qt::ReturnByValue);
                pixmap = pixmap.scaled(startSquare->size().width(), startSquare->size().height());
                endSquare->setPixmap(pixmap);

                startSquare->setPixmap(QPixmap::fromImage(QImage(":/images/transparent.svg")));
                CheckMated = false;
                Checked = false;
                return CheckMated;
            }
        }
    }
    std::set<Square*> defendersSet;
    //std::vector<std::vector<Square*> > squares = BOARD.GetSquares();
    for(unsigned i=0; i<squares.size(); ++i){
        for(unsigned j=0; j<squares[i].size(); ++j){
            Piece* piece = squares[i][j]->GetPiece();
            qDebug()<<i<<j<<Qt::endl;
            if(piece && piece->GetColor().compare(color) != 0){ // Las piezas amigas
                qDebug()<<QString(typeid(*piece).name())<<Qt::endl;
                qDebug()<<"valid moves"<<Qt::endl;
                std::vector<Square*> validMoves = piece->ValidMoves();
                qDebug()<<"valid moves"<<Qt::endl;
                for(unsigned ii = 0; ii < validMoves.size(); ++ii){
                    defendersSet.insert(validMoves[ii]);
                }
            }
        }
    }
    qDebug()<<"IsCheckMated 3"<<Qt::endl;
    it = attacksSet.begin();
    std::set<Square*>::iterator jt = defendersSet.begin();
    for(; it!=attacksSet.end(); ++it){
        Piece* piece = (*it)->GetPiece();
        if(!piece){
            for(; jt!=defendersSet.end(); ++jt){
                if(*it == *jt){ // Existe movimiento de una pieza amiga en el lugar de los ataques
                    if(*it == startSquare && *jt == endSquare){
                        for(unsigned i = 0; i<captureFreeMoves.size(); ++i){
                            if(captureFreeMoves[i] == endSquare){
                                Piece* startPiece = startSquare->GetPiece();
                                startPiece->SetMoved(true);
                                startPiece->SetX(endSquare->GetX());
                                startPiece->SetY(endSquare->GetY());
                                qDebug()<<startSquare->GetX()<<startSquare->GetY()<<Qt::endl;
                                qDebug()<<endSquare->GetX()<<endSquare->GetY()<<Qt::endl;

                                //if(startPiece)
                                //    qDebug()<<"startPiece exist"<<Qt::endl;
                                endSquare->SetPiece(startPiece);
                                startSquare->SetPiece(nullptr);
                                //if(endSquare->GetPiece())
                                //    qDebug()<<"startPiece exist"<<Qt::endl;

                                QPixmap pixmap = startSquare->pixmap(Qt::ReturnByValue);
                                pixmap = pixmap.scaled(startSquare->size().width(), startSquare->size().height());
                                endSquare->setPixmap(pixmap);

                                startSquare->setPixmap(QPixmap::fromImage(QImage(":/images/transparent.svg")));

                                CheckMated = false;
                                Checked = false;
                                return CheckMated;
                            }
                        }

                    }


                }
            }
        }
    }
    CheckMated = true;
    return CheckMated;
    //return false;
}
bool Board::ThreatOfCheck(Square *square)
{
    return true;
}
void Board::OccupySquare(Square *startSquare, Square *endSquare)
{
    Piece* startPiece = startSquare->GetPiece();
    //Piece* endPiece = nullptr;    

    if(!Checked){
        startPiece->SetMoved(true);
        startPiece->SetX(endSquare->GetX());
        startPiece->SetY(endSquare->GetY());
        qDebug()<<startSquare->GetX()<<startSquare->GetY()<<Qt::endl;
        qDebug()<<endSquare->GetX()<<endSquare->GetY()<<Qt::endl;

        //if(startPiece)
        //    qDebug()<<"startPiece exist"<<Qt::endl;
        endSquare->SetPiece(startPiece);
        startSquare->SetPiece(nullptr);
        //if(endSquare->GetPiece())
        //    qDebug()<<"startPiece exist"<<Qt::endl;

        QPixmap pixmap = startSquare->pixmap(Qt::ReturnByValue);
        pixmap = pixmap.scaled(startSquare->size().width(), startSquare->size().height());
        endSquare->setPixmap(pixmap);

        startSquare->setPixmap(QPixmap::fromImage(QImage(":/images/transparent.svg")));


        if(IsChecked()){
            if(IsCheckMated(startSquare, endSquare)){
                QMessageBox::information(this, "Informacion", "CHECKMATED. ¡Se acabo el juego!", "Continuar");
            }else{
                QMessageBox::information(this, "Informacion", "CHECK", "Continuar");
            }

        }
    }else{
        if(IsCheckMated(startSquare, endSquare)){
            QMessageBox::information(this, "Informacion", "CHECKMATED. ¡Se acabo el juego!", "Continuar");
        }else{
            //QMessageBox::information(this, "Informacion", "CHECK", "Continuar");
        }

    }


    /*if(IsCheckMated(endSquare)){
        QMessageBox::information(this, "Informacion", "IS CHECKMATED", "Continuar") ;
    }*/
    /*if(!Checked){


    }else{
        std::set<Square*> treatSet;
        std::vector<std::vector<Square*> > squares = BOARD.GetSquares();

        std::vector<Square*> captureFreeMoves = startPiece->CaptureFreeMoves();
        if(!CheckMated){
            for(unsigned i=0; i<captureFreeMoves.size(); ++i){
                if(captureFreeMoves[i] == endSquare){
                    startPiece->SetMoved(true);
                    startPiece->SetX(endSquare->GetX());
                    startPiece->SetY(endSquare->GetY());
                    qDebug()<<startSquare->GetX()<<startSquare->GetY()<<Qt::endl;
                    qDebug()<<endSquare->GetX()<<endSquare->GetY()<<Qt::endl;

                    //if(startPiece)
                    //    qDebug()<<"startPiece exist"<<Qt::endl;
                    endSquare->SetPiece(startPiece);
                    startSquare->SetPiece(nullptr);
                    //if(endSquare->GetPiece())
                    //    qDebug()<<"startPiece exist"<<Qt::endl;

                    QPixmap pixmap = startSquare->pixmap(Qt::ReturnByValue);
                    pixmap = pixmap.scaled(startSquare->size().width(), startSquare->size().height());
                    endSquare->setPixmap(pixmap);

                    startSquare->setPixmap(QPixmap::fromImage(QImage(":/images/transparent.svg")));
                    break;
                }
            }
        }

    }*/
}
void Board::Eaten(Square *startSquare, Square *endSquare)
{
    OccupySquare(startSquare, endSquare);
}
void Board::Move(Square *startSquare, Square *endSquare)
{
    /*
    if(CheckMated)
       QMessageBox::information(this, "Informacion", "IS CHECK", "Continuar") ;
    if(CheckMated){
       QMessageBox::information(this, "Informacion", "IS CHECKMATED", "EL juego termino") ;
       return;
    }*/
    Piece* startPiece = startSquare->GetPiece();
    Piece* endPiece = endSquare->GetPiece();

    qDebug()<<"Move"<<Qt::endl;

    qDebug()<<startSquare->GetX()<<startSquare->GetY();
    if(startSquare->GetPiece()){
        qDebug()<<startSquare->GetX()<<startSquare->GetY()<<
                  startSquare->GetPiece()->GetX()<<startSquare->GetPiece()->GetY()
               <<startSquare->GetPiece()->GetColor().c_str()<<turn<<Qt::endl;
    }

    qDebug()<<"Move 2"<<Qt::endl;

    if(startPiece){
        //if(isChecked){
        qDebug()<<"validMoves"<<Qt::endl;
        std::vector<Square*> validMoves = startPiece->ValidMoves();
        bool isValid = false;
        qDebug()<<"for 1"<<Qt::endl;
        for(unsigned i=0; i<validMoves.size(); ++i){
            if(validMoves[i] == endSquare){
                isValid = true; break;
            }
        }
        qDebug()<<"for 1"<<Qt::endl;
        if(isValid){
            if(startSquare->GetPiece()->GetColor().compare(STR_WHITE) == 0 && turn == true){
                turn = false;
            }else{
                if(startSquare->GetPiece()->GetColor().compare(STR_BLACK) == 0 && turn == false){
                    turn = true;
                }else{
                    return;
                }
            }
            if(endPiece){
                //if(ThreadOfCheck(startSquare) == false)
                Eaten(startSquare, endSquare);
            }else{
                OccupySquare(startSquare, endSquare);
            }
            /*std::vector<Square*> attackSquares = startPiece->AttackSquares();
            bool isCaptured = false;
            for(unsigned i=0; i<attackSquares.size(); ++i){
                if(attackSquares[i] == endSquare){
                    isValid = true; break;
                }
            }*/
        }
        //}
    }else{

    }
}
//! [0]

void Board::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void Board::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void Board::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        Square *endSquare = static_cast<Square*>(childAt(event->pos()));

        if (!endSquare  || QString(typeid(*endSquare).name()).compare("class Square") != 0){
            event->ignore();
            return;
        }
        // Recupero la figura y posicion del square de origen
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        uint16_t x;
        uint16_t y;
        dataStream >> x >> y;

        Square* startSquare = static_cast<Square*>(ui->gridLayout_board->itemAtPosition(x, y)->widget());


        //Square* startSquare = static_cast<Square*>(ui->gridLayout_board->itemAtPosition(5, y)->widget());
        // Intentamos pasar la pieza al Square de destino
        Move(startSquare, endSquare);


        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

//! [1]
void Board::mousePressEvent(QMouseEvent *event)
{
    Square *child = static_cast<Square*>(childAt(event->pos()));

    //Square* startSquare_2 = static_cast<Square*>(ui->gridLayout_board->itemAtPosition(5, 4)->widget());
    //qDebug()<<"child xy"<<child->GetX()<<child->GetY()<<Qt::endl;
    //qDebug()<<"child pos"<<event->pos()<<Qt::endl;
    if (!child || QString(typeid(*child).name()).compare("class Square") != 0
            || child->GetPiece() == nullptr)
        return;


    QPixmap pixmap = child->pixmap(Qt::ReturnByValue);

    pixmap = pixmap.scaled(child->size().width(), child->size().height());
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    //dataStream << pixmap << QPoint(event->pos() - child->pos());

    //qDebug()<<child->GetX() << child->GetY();
    dataStream << child->GetX() << child->GetY();

//! [1]

//! [2]
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);
//! [2]

//! [3]
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());
//! [3]

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    //painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));

    painter.end();


    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        //child->close();
    } else {
        //child->setMaximumSize(64, 64);
        //child->show();
        //child->setPixmap(pixmap);
    }
}

void Board::showEvent(QShowEvent* event)
{
    event->accept();

    qDebug()<<ui->gridLayout_board->geometry()<<Qt::endl;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            //Square* square = static_cast<Square*>(ui->gridLayout_board->itemAtPosition(i, j)->widget());
            //qDebug()<<ui->gridLayout_board->itemAtPosition(i, j)->geometry()<<Qt::endl;
            //qDebug()<<ui->gridLayout_board->itemAtPosition(i, j)->widget()->geometry()<<Qt::endl;
            //square->size = QSize(square->geometry().width()+30, square->geometry().height()+30);
            //square->pixmap(Qt::ReturnByValue).scaled(square->size.width()+100, square->size.height()+100);

        }
    }
}
