//
// Created by andres on 16/03/18.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <QKeyEvent>
#include <QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtCore/QCoreApplication>
#include <QtGui/QTextBlock>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QListView>
#include <QPixmap>
#include <QGridLayout>


using namespace std;
/**
 * @brief The Window class : Clase que corresponde a la ventana principal
 */
class Window : public QWidget {
Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);

    //QString getEditorReading();

   // void RefreshRAMBox();
   int arreglo1[4];
   int arreglo2[10];

    int arreglo3[4];
    int arreglo4[10];

    int movCol =5;
    int movRow=2;

    int marcadorGlobal1=1;
    int marcadorGlobal2=1;


    vector<int> RojasFilas = {0,0,0,0};
    vector<int> RojasColumnas = {0,0,0,0};

    vector<int> AzulesFilas = {0,0,0,0};
    vector<int> AzulesColumnas = {0,0,0,0};

    //Representacion matricial del tablero
    vector<string> listaAbierta = {};
    vector<string> listaCerrada = {};

    int matrizTablero[5][11] ={{0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0,0}};


    int movimientosHorizontales=10;
    int movimientosVerticales =10;



    /***
     * Slots para los botones
     */

private slots:

    void StartGame();

    void moverArriba( );

    void moverAbajo( );

    void moverDerecha( );

    void moverIzquierda( );

    void MostrarCamino();


/***
 * Variables privadas para la ventana y la logica
 */
private:
    int numJugadoresglobal =0;

    QLabel *Table;
    QLayout *Hbox;
    QPushButton *start;
    QPushButton *arriba;
    QPushButton *abajo;
    QPushButton *izquierda;
    QPushButton *derecha;
    QPushButton *Pista;
    QLabel *equipo1;
    QLabel *equipo2;
    QGridLayout *layout;
    QGridLayout *layout2;
    QLabel *ficharoja;
    QLabel *fichaazul;
    QLabel *FichaBola;
    QLabel *marcador1;
    QLabel *marcador2;

    QLineEdit *CantidadJugadores;
    QLineEdit *potenciatiro;
    void generarFichas();

    int generarRandom1();
    int generarRandom2();
    int generarRandom3();
    int generarRandom4();
    void Pathfinding(int x, int y);
    void setNumJugadores(QString qString);
    void Movimiento(int x);
    void encontrarCamino(int **pstAr, pair<int, int> posBegin, pair<int, int> posEnd);
    void encontrarCamino2(int **pstAr, pair<int, int> posBegin, pair<int, int> posEnd);


    void AI(int posx, int posy);

    void Verificador();
};

#endif // WINDOW_H
