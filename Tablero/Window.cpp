#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <iostream>
#include "Window.h"
#include <QMessageBox>


/***
 * Creacion de la ventana
 * @param parent
 */
Window::Window(QWidget *parent) :
        QWidget(parent) {
    setFixedSize(950, 500);
    this->setWindowTitle("Futbolito");
    layout = new QGridLayout(this);
    this->setLayout(layout);

    CantidadJugadores = new QLineEdit();
    CantidadJugadores->setPlaceholderText("Cantidad de jugadores");
    CantidadJugadores->setFixedWidth(150);
    CantidadJugadores->setAlignment(Qt::AlignRight);
    QIntValidator* aIntValidator = new QIntValidator;
    aIntValidator->setRange(2, 8);
    CantidadJugadores->setValidator(aIntValidator);

    Table = new QLabel();
    QPixmap px("/home/julio/CLionProjects/window_table/fJCiE5j3n1GkhQGrwkiRjpiG.jpeg");
    Table->setPixmap(px);
    Table->setAlignment(Qt::AlignCenter);
    layout->addWidget(Table,1,1);

    start = new QPushButton("START GAME");
    start->setFixedSize(100,50);
    connect(start,SIGNAL(clicked()),this,SLOT(StartGame()));

    equipo1 = new QLabel();
    equipo2 = new QLabel();
    equipo1->setAlignment(Qt::AlignHCenter);
    equipo2->setAlignment(Qt::AlignHCenter);

    marcador1 = new QLabel();
    marcador2 = new QLabel();

    ficharoja = new QLabel();
    QPixmap px2("/home/julio/CLionProjects/window_table/ficharoja.png");
    ficharoja->setPixmap(px2);

    fichaazul = new QLabel();
    QPixmap px3("/home/julio/CLionProjects/window_table/fichaazul.png");
    fichaazul->setPixmap(px3);
    layout->addWidget(equipo1,0,2);
    layout->addWidget(equipo2,0,0);

    layout->addWidget(marcador1,1,0);
    layout->addWidget(marcador2,1,2);

    //layout->addWidget(CantidadJugadores,0,1);

    QHBoxLayout *box = new QHBoxLayout();
    box->addWidget(start);
    box->addWidget(CantidadJugadores);
    layout->addLayout(box,2,1);

}
/***
 * Ejecucion del juego con la parte grafica y logica
 */
void Window::StartGame() {
    equipo1->setText("EQUIPO AZUL");
    equipo2->setText("EQUIPO ROJO");

    equipo1->setStyleSheet("background-color:#219ac4;");
    equipo2->setStyleSheet("background-color:#ef4341;");

    marcador1->setText("0");
    marcador2->setText("0");
    marcador1->setAlignment(Qt::AlignHCenter);
    marcador2->setAlignment(Qt::AlignHCenter);


    if (CantidadJugadores->text()=="") {
        QMessageBox::information(this, "Futbolito", "Cantidad de jugadores requerida!");
    }else if (CantidadJugadores->text()=="5") {
        QMessageBox::information(this, "Futbolito", "Cantidad maxima: 4 jugadores!");
    }else if (CantidadJugadores->text()=="6") {
        QMessageBox::information(this, "Futbolito", "Cantidad maxima: 4 jugadores!");
    }else if (CantidadJugadores->text()=="7") {
        QMessageBox::information(this, "Futbolito", "Cantidad maxima: 4 jugadores!");
    }else if (CantidadJugadores->text()=="8") {
        QMessageBox::information(this, "Futbolito", "Cantidad maxima: 4 jugadores!");
    }else if (CantidadJugadores->text()=="9") {
        QMessageBox::information(this, "Futbolito", "Cantidad maxima: 4 jugadores!");
    }else{
        start->hide();
        setNumJugadores(CantidadJugadores->text());
        CantidadJugadores->hide();
        generarFichas();
        QHBoxLayout *MovBox = new QHBoxLayout();

        arriba = new QPushButton("↑");
        abajo= new QPushButton("↓");
        izquierda = new QPushButton("←");
        derecha = new QPushButton("→");
        Pista = new QPushButton("Pista");
        potenciatiro = new QLineEdit();
        potenciatiro->setPlaceholderText("Potencia");
        QIntValidator* bIntValidator = new QIntValidator;
        potenciatiro->setValidator(bIntValidator);
        potenciatiro->setFixedSize(80,30);
        arriba->setFixedSize(30,30);
        abajo->setFixedSize(30,30);
        izquierda->setFixedSize(30,30);
        derecha->setFixedSize(30,30);
        Pista->setFixedSize(50,30);

        connect(arriba,SIGNAL(clicked()),this,SLOT(moverArriba()));
        connect(abajo,SIGNAL(clicked()),this,SLOT(moverAbajo()));
        connect(izquierda,SIGNAL(clicked()),this,SLOT(moverIzquierda()));
        connect(derecha,SIGNAL(clicked()),this,SLOT(moverDerecha()));
        connect(Pista,SIGNAL(clicked()),this,SLOT(MostrarCamino()));

        MovBox->addWidget(arriba,0,0);
        MovBox->addWidget(abajo,0,0);
        MovBox->addWidget(izquierda,0,0);
        MovBox->addWidget(derecha,0,0);
        MovBox->addWidget(Pista,0,0);
        MovBox->addWidget(potenciatiro,0,0);
        layout->addLayout(MovBox,0,1);
    }
}
/***
 * Generador de fichas aleatorias en el juego
 */
void Window::generarFichas() {

    layout2 = new QGridLayout(Table);
    layout2->setContentsMargins(65, 0, 0, 0);
    // AGREGAR COLUMNAS Y FILAS AL TABLERO
    int j = 0;
    while (j < 5) {
        QLabel *filas = new QLabel(".");
        layout2->addWidget(filas, 0 + j, 0);
        int i = 1;
        while (i < 11) {
            QLabel *Columnas = new QLabel(".");
            layout2->addWidget(Columnas, 0 + j, 0 + i);
            i++;
        }
        j++;
    }
    generarRandom1();
    srand(time(0));
    generarRandom2();

    generarRandom3();
    srand(time(0));
    generarRandom4();
    //AGREGAR LA FiCHA BOLA EN EL TABLERO
    FichaBola = new QLabel();
    QPixmap px3("/home/julio/CLionProjects/window_table/Bola.png");
    FichaBola->setPixmap(px3);
    layout2->addWidget(FichaBola, 0 + movRow, 0 + movCol);
    for (int i = 0; i < numJugadoresglobal; i++) {
        QLabel *FichaRoja = new QLabel();
        QPixmap px("/home/julio/CLionProjects/window_table/ficharoja.png");
        FichaRoja->setPixmap(px);
        QLabel *FichaAzul = new QLabel();
        QPixmap px2("/home/julio/CLionProjects/window_table/fichaazul.png");
        FichaAzul->setPixmap(px2);

        layout2->addWidget(FichaRoja, 0 + arreglo1[i], 0 + arreglo2[i]);
        layout2->addWidget(FichaAzul, 0 + arreglo3[i], 0 + arreglo4[i]);
    }
    for (int i = 0; i < numJugadoresglobal; i++) {
        RojasFilas[i] = arreglo1[i];
        RojasColumnas[i] = arreglo2[i];
    }
    for (int i = 0; i < numJugadoresglobal; i++) {
        AzulesFilas[i] = arreglo3[i];
        AzulesColumnas[i] = arreglo4[i];
    }
    int i = 0;
}
/***
 * Generador random1
 * @return
 */
int Window::generarRandom1(){
    int aux = 0;
    for(int i = 0; i < numJugadoresglobal; i++){
        aux = (0 + rand() % 5);
        int aux2 = 0;
        while(aux2 < i){
            if(aux != arreglo1[aux2])
                aux2++;
            else{
                aux = (0 + rand() % 5);
                aux2 = 0;
            }
        }
        arreglo1[i] = aux;
    }
    return 0;
}
/***
 * Generador random2
 * @return
 */
int Window::generarRandom2(){
    int aux = 0;
    for(int i = 0; i <numJugadoresglobal; i++){
        aux = (0 + rand() % 5);
        int aux2 = 0;
        while(aux2 < i){
            if(aux != arreglo2[aux2])
                aux2++;
            else{
                aux = (0 + rand() % 5);
                aux2 = 0;
            }
        }
        arreglo2[i] = aux;
    }
    return 0;
}
/***
 * Generador random3
 * @return
 */
int Window::generarRandom3(){
    int aux = 0;
    for(int i = 0; i < numJugadoresglobal; i++){
        aux = (0 + rand() % 4);
        int aux2 = 0;
        while(aux2 < i){
            if(aux != arreglo3[aux2])
                aux2++;
            else{
                aux = (0 + rand() % 4);
                aux2 = 0;
            }
        }
        arreglo3[i] = aux;
    }
    return 0;
}
/***
 * Generador random4
 * @return
 */
int Window::generarRandom4(){
    int aux = 0;
    for(int i = 0; i < numJugadoresglobal; i++){
        aux = 6 + rand() % (10 +1 - 6) ;
        int aux2 = 0;
        while(aux2 < i){
            if(aux != arreglo4[aux2])
                aux2++;
            else{
                aux = 6 + rand() % (10 +1 - 6) ;
                aux2 = 0;
            }
        }
        arreglo4[i] = aux;

    }

    return 0;
}
/***
 * Funcion para obtener el numero de jugadores durante un juego
 * @param qString
 */
void Window::setNumJugadores(QString qString) {
    bool ok;
    int numJugadores = qString.toInt(&ok);
    if (!ok) {
        cout << "Conversion failed. Repeat conversion" <<endl;
    }
    numJugadoresglobal=numJugadores;
}
/***
 * Accion de mover hacia arriba con el boton
 */
void Window::moverArriba( ){
        Movimiento(1);
}
/***
 * Accion de mover hacia abajo con el boton
 */
void Window::moverAbajo( ){
        Movimiento(2);
}
/***
 * Accion de mover hacia la derecha con el boton
 */
void Window::moverDerecha( ){
        Movimiento(3);
}
/***
 * Accion de mover hacia la izquierda con el boton
 */
void Window::moverIzquierda( ){
        Movimiento(4);
}
/***
 * Funcion que muestra el camino mas corto para llegar a la cancha y anotar
 */
void Window::MostrarCamino() {
    Pathfinding(0+movCol,0+movRow);
}
/***
 * Funcion visual y logica para el movimiento de las fichas
 * @param i
 */
void Window::Movimiento(int i){
    bool ok;
    int numpotencia = potenciatiro->text().toInt(&ok);
    if (!ok) {
        QMessageBox::information(this, "Futbolito", "Dale potencia al tiro!");
    }
    if (numpotencia<0) {
        QMessageBox::information(this, "Futbolito", "Numero incorrecto");
    }
    if(i==1){
        if(movRow-numpotencia<0){
            layout2->addWidget(FichaBola,0+movRow,0+movCol);
            movRow=movRow;
        }else{
            for(int i=0;i<numJugadoresglobal;i++){
                if(RojasFilas[i]==movRow-numpotencia  && RojasColumnas[i]==movCol){
                    break;
                }else if(AzulesFilas[i] == movRow - numpotencia && AzulesColumnas[i] == movCol ) {
                    break;
                }else if(i==numJugadoresglobal-1){
                    FichaBola->hide();
                    layout2->addWidget(FichaBola,0+movRow-numpotencia,0+movCol);
                    movRow=movRow-numpotencia;
                    FichaBola->show();
                    AI(0+movCol,0+movRow);
                    Verificador();
                }
            }
        }

    }else if(i==2){
        if(movRow+numpotencia>4){
            layout2->addWidget(FichaBola,0+movRow,0+movCol);
            movRow=movRow;
        }else{
            for(int i=0;i<numJugadoresglobal;i++){
                if(RojasFilas[i]==movRow + numpotencia && RojasColumnas[i]==movCol){
                    break;
                }else if(AzulesFilas[i] == movRow + numpotencia && AzulesColumnas[i] == movCol ){
                    break;
                }else if(i==numJugadoresglobal-1) {
                    FichaBola->hide();
                    layout2->addWidget(FichaBola, 0 + movRow + numpotencia, 0 + movCol);
                    movRow = movRow + numpotencia;
                    FichaBola->show();
                    AI(0+movCol,0+movRow);
                    Verificador();
                }
            }
        }
    }else if(i==3){
        if(movCol+numpotencia>10 && movRow==2){
            FichaBola->hide();
            movRow=2;
            movCol=5;
            layout2->addWidget(FichaBola,0+movRow,0+movCol);
            FichaBola->show();
            QString Qmarcador2 = QString::number(marcadorGlobal2);
            marcador1->setText(Qmarcador2);
            marcadorGlobal2=marcadorGlobal2+1;
            QMessageBox::information(this, "Futbolito", "GOOOOL del equipo rojo!");

        }else{
            if(movCol+numpotencia>10){
                layout2->addWidget(FichaBola,0+movRow,0+movCol);
            }
            else{
                for(int i=0;i<numJugadoresglobal;i++) {
                    if (RojasFilas[i] == movRow && RojasColumnas[i] == movCol + numpotencia) {
                        break;
                    }else if(AzulesFilas[i] == movRow && AzulesColumnas[i] == movCol + numpotencia){
                        break;
                    } else if (i == numJugadoresglobal - 1) {
                        FichaBola->hide();
                        layout2->addWidget(FichaBola, 0 + movRow, 0 + movCol + numpotencia);
                        movCol = movCol + numpotencia;
                        FichaBola->show();
                        AI(0+movCol,0+movRow);
                        Verificador();

                    }
                }
            }

        }
    }else if(i==4){
        if(movCol-numpotencia<0 && movRow==2){
            FichaBola->hide();
            movRow=2;
            movCol=5;
            layout2->addWidget(FichaBola,0+movRow,0+movCol);
            FichaBola->show();
            QString Qmarcador1 = QString::number(marcadorGlobal1);
            marcador2->setText(Qmarcador1);
            marcadorGlobal1=marcadorGlobal1+1;
            QMessageBox::information(this, "Futbolito", "GOOOOL del equipo azul!");
        }else{
            if(movCol+numpotencia>10){
                layout2->addWidget(FichaBola,0+movRow,0+movCol);
            }else{
                for(int i=0;i<numJugadoresglobal;i++) {
                    if (RojasFilas[i] == movRow && RojasColumnas[i] == movCol - numpotencia) {
                        break;
                    }else if(AzulesFilas[i] == movRow && AzulesColumnas[i] == movCol - numpotencia){
                        break;
                    } else if (i == numJugadoresglobal - 1) {
                        FichaBola->hide();
                        layout2->addWidget(FichaBola, 0 + movRow, 0 + movCol - numpotencia);
                        movCol = movCol - numpotencia;
                        FichaBola->show();
                        AI(0+movCol,0+movRow);
                        Verificador();
                    }
                }
            }
        }

    }else{
        cout<<"Error en el movimiento";
    }
}

