#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include "Window.h"


#define _CRT_SECURE_NO_WARNINGS
using namespace std;


struct stInfo
{
    int iF = 0;
    int iG = 0;
    int iH = 0;
    int iPosx = -1;
    int iPosy = -1;
    int iFPosx = -1;
    int iFPosy = -1;
};
/***
 * Se obtiene la distancia de manhattan para dos puntos en el tablero
 * @param iPosxFrom
 * @param iPosyFrom
 * @param iPosxTo
 * @param iPosyTo
 * @return
 */
 //ESTA ES LA FUNCION QUE OBTIENE LA DISTANCIA DE MANHATTAN Y AYUDA A QUE EL ALGORITMO ENCUENTRE EL CAMINO
int distanciaManhattan(int iPosxFrom, int iPosyFrom, int iPosxTo, int iPosyTo)
{
    return abs(iPosxFrom - iPosxTo) + abs(iPosyFrom - iPosyTo);
}

/***
 * Construccion de stlnfo
 * @param stTmp
 * @param iPosx
 * @param iPosy
 * @param posBegin
 * @param posEnd
 * @param iFPosx
 * @param iFPosy
 */
 //ESTA FUNCION ES COMO UN TIPO DE CONSTRUCTOR QUE INSTANCIA CADA ATRIBUTO DE lA POSICION Y TAMBIEN
 //CADA SUMA DE G Y H CON LA DISTANCIA DE MANHATTAN
void StInfo(stInfo &stTmp, int iPosx, int iPosy, std::pair<int, int> posBegin, std::pair<int, int> posEnd, int iFPosx = -1, int iFPosy = -1)
{
    stTmp.iPosx = iPosx;
    stTmp.iPosy = iPosy;
    stTmp.iFPosx = iFPosx;
    stTmp.iFPosy = iFPosy;
    stTmp.iG = distanciaManhattan(iPosx, iPosy, posBegin.first, posBegin.second);
    stTmp.iH = distanciaManhattan(iPosx, iPosy, posEnd.first, posEnd.second);
    stTmp.iF = stTmp.iG + stTmp.iH;
}
/***
 * verificación de la ubicación es legal
 * @param pstAr
 * @param iPosx
 * @param iPosy
 * @return
 */
 //ESTA FUNCION DEVUELVE UN VERDADERO O FALSO PARA CONOCER SI LA POSICION DE LA FICHA ES VALIDA O NO
bool PosVal(int **pstAr, int iPosx, int iPosy)
{
    return (iPosx >= 0 && iPosx < 11 && iPosy >= 0 && iPosy < 11) && (pstAr[iPosx][iPosy] != 1);
}
/***
 * comprobación de que un determinado punto no está en la lista abierta
 * @param iPosx
 * @param iPosy
 * @param iF
 * @param mapOpenList
 * @return
 */
 //AQUI SE INSERTAN LOS VALORES QUE NO SE ENCUENTREN EN LA LISTA ABIERTA
bool ListaCerrada(int iPosx, int iPosy, int iF, std::multimap<int, stInfo> &mapOpenList)
{
    int iCount = mapOpenList.count(iF);
    auto it = mapOpenList.find(iF);
    while (it != mapOpenList.end() && iCount)
    {
        if (it->second.iPosx == iPosx && it->second.iPosy == iPosy)
            return false;
        ++it;
        --iCount;
    }
    return true;
}
/***
 * En la lista abierta se insertan informacion  que cumplen los requisitos de una ubicación.
 * @param pstAr
 * @param posNow
 * @param mapOpenList
 * @param mapCloseList
 * @param posBegin
 * @param posEnd
 * @return
 */
bool insertarListaAbierta(int **pstAr, const std::pair<int, int> &posNow, std::multimap<int, stInfo> &mapOpenList, std::map<std::pair<int, int>, stInfo> &mapCloseList,
                           const std::pair<int, int> &posBegin, const std::pair<int, int> &posEnd)
{
    // AQUI SE COMPRUEBA SI LA POSICION DE LA FICHA ESTA BIEN O NO Y SE INSERTA DENTRO DE LA LISTA ABIERTA
    if (PosVal(pstAr, posNow.first - 1, posNow.second) && mapCloseList.find(std::make_pair(posNow.first - 1, posNow.second)) == mapCloseList.end())
    {
        stInfo stTmp;
        StInfo(stTmp, posNow.first-1, posNow.second, posBegin, posEnd, posNow.first, posNow.second);
        if (ListaCerrada(posNow.first - 1, posNow.second, stTmp.iF, mapOpenList))
        {
            mapOpenList.insert(std::make_pair(stTmp.iF, stTmp));
            if (stTmp.iH == 0)
                return true;
        }
    }
    if (PosVal(pstAr, posNow.first, posNow.second-1) && mapCloseList.find(std::make_pair(posNow.first, posNow.second-1)) == mapCloseList.end())
    {
        stInfo stTmp;
        StInfo(stTmp, posNow.first, posNow.second-1, posBegin, posEnd, posNow.first, posNow.second);
        if (ListaCerrada(posNow.first, posNow.second-1, stTmp.iF, mapOpenList))
        {
            mapOpenList.insert(std::make_pair(stTmp.iF, stTmp));
            if (stTmp.iH == 0)
                return true;
        }
    }
    if (PosVal(pstAr, posNow.first + 1, posNow.second) && mapCloseList.find(std::make_pair(posNow.first + 1, posNow.second)) == mapCloseList.end())
    {
        stInfo stTmp;
        StInfo(stTmp, posNow.first+1, posNow.second, posBegin, posEnd, posNow.first, posNow.second);
        if (ListaCerrada(posNow.first+1, posNow.second, stTmp.iF, mapOpenList))
        {
            mapOpenList.insert(std::make_pair(stTmp.iF, stTmp));
            if (stTmp.iH == 0)
                return true;
        }
    }
    if (PosVal(pstAr, posNow.first, posNow.second+1) && mapCloseList.find(std::make_pair(posNow.first, posNow.second+1)) == mapCloseList.end())
    {
        stInfo stTmp;
        StInfo(stTmp, posNow.first, posNow.second+1, posBegin, posEnd, posNow.first, posNow.second);
        if (ListaCerrada(posNow.first, posNow.second+1, stTmp.iF, mapOpenList))
        {
            mapOpenList.insert(std::make_pair(stTmp.iF, stTmp));
            if (stTmp.iH == 0)
                return true;
        }
    }
    return false;
}
/***
 * Una orientacion para el algoritmo
 * @param pstAr
 * @param posBegin
 * @param posEnd
 */
void Window::encontrarCamino(int **pstAr, std::pair<int,int> posBegin, std::pair<int,int> posEnd)
{
    std::multimap<int, stInfo> mapOpenList;
    std::map<std::pair<int, int>, stInfo> mapCloseList;
    std::pair<int, int> posNow = posBegin;

    //Starting point to join Openlist
    stInfo stTmp;
    StInfo(stTmp, posNow.first, posNow.second, posBegin, posEnd);
    mapOpenList.insert(std::make_pair(stTmp.iF, stTmp));
    //AQUI SE HACE EL LLAMADO A LAS FUNCIONES AUXILIARES QUE HACEN EL RESTO DE OPERACIONES PARA
    // EL ALGORITMO Y TAMBIEN SE REVISAN LAS LISTAS, LA ABIERTA Y LA CERRADA
    while (1)
    {
        auto itopen = mapOpenList.begin();
        if (itopen == mapOpenList.end()) //la lista abierta está vacía, sin ruta, Si no está vacía, la primera es el mínimo iF

        {
            cout << "No path" << endl;
            return;
        }

        posNow = std::make_pair(itopen->second.iPosx, itopen->second.iPosy);
        //cout << "====" << posNow.first << "  " << posNow.second << endl;

        stInfo stTmp = itopen->second;
        mapOpenList.erase(itopen);
        mapCloseList.insert(std::make_pair(std::make_pair(stTmp.iPosx, stTmp.iPosy), stTmp));

        if (stTmp.iH == 0)
        {
            cout << "Camino Encontrado" << endl;
            break;
        }

        insertarListaAbierta(pstAr, posNow, mapOpenList, mapCloseList, posBegin, posEnd);
        //if (insertPointToOpenList(pstAr, posNow, mapOpenList, mapCloseList, posBegin, posEnd)) //Add surrounding coordinates
        {
            //	mapCloseList.insert(std::make_pair(std::make_pair(posEnd.first, posEnd.second),stInfo()));
            // cout << "found" << endl;
            //	break;
        }
    }

    posNow = std::make_pair(posEnd.first, posEnd.second);
    while (1)
    {
        auto it = mapCloseList.find(std::make_pair(posNow.first, posNow.second));
        if (it == mapCloseList.end())
            break;
        if (it->first.first == -1 && it->first.second == -1)
            break;
        //cout << it->first.first << " " << it->first.second << " -> ";
        posNow = std::make_pair(it->second.iFPosx, it->second.iFPosy);
        cout<<"\n";
        layout2->addWidget(new QLabel("x"),0+it->first.second,0+it->first.first);

    }

}
/***
 * Funcion que llama al metodo findRoad el cual es un auxiliar que se apoya de otros metodos para mostrar la ruta mas corta
 * @param posx
 * @param posy
 */
void Window::Pathfinding(int posx, int posy)
{
    //AQUI SE CREA EL ARRAY QUE REPRESENTA UNA PARTE DE LA MATRIZ DEL JUEGO CON LOS 1 COMO BLOQUEO
    int **pstAr = new int *[11];
    for (int i = 0; i < 11; ++i)
        pstAr[i] = new int[11];

    for (int i = 0; i < 11; ++i)
        for (int j = 0; j < 11; ++j)
            pstAr[i][j] = 0;

    int i = 0;
    while(i<numJugadoresglobal){
        pstAr[arreglo2[i]][arreglo1[i]]=1;
        pstAr[arreglo4[i]][arreglo3[i]]=1;
        i++;
    }
    //AQUI SE LLAMA LA FUNCION PARA ENCONTRAR EL CAMINO MAS CORTO CON LA POSICION DE LA FICHA ACTUAL
    // Y LA POSICION DONDE SE QUIERE LLEGAR QUE SIEMPRE VA A SER 10,2
    encontrarCamino(pstAr, std::pair<int,int>(0+posx,0+posy), std::pair<int,int>(10,2));

}
