
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <unistd.h>
#include "Window.h"

using namespace std;


struct stInfo
{
    int iF = 0;
    int iG = 0; //To the starting point
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

int distanciaManhattan2(int iPosxFrom, int iPosyFrom, int iPosxTo, int iPosyTo)
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
void StInfo2(stInfo &stTmp, int iPosx, int iPosy, std::pair<int, int> posBegin, std::pair<int, int> posEnd, int iFPosx = -1, int iFPosy = -1)
{
    stTmp.iPosx = iPosx;
    stTmp.iPosy = iPosy;
    stTmp.iFPosx = iFPosx;
    stTmp.iFPosy = iFPosy;
    stTmp.iG = distanciaManhattan2(iPosx, iPosy, posBegin.first, posBegin.second);
    stTmp.iH = distanciaManhattan2(iPosx, iPosy, posEnd.first, posEnd.second);
    stTmp.iF = stTmp.iG + stTmp.iH;
    //cout << "iposx:" << iPosx << " iposy:" << iPosy << " iG:" << stTmp.iG << " iH:" << stTmp.iH << " iF:" << stTmp.iF << endl;
}
/***
 * verificación de la ubicación es legal
 * @param pstAr
 * @param iPosx
 * @param iPosy
 * @return
 */
bool PosVal2(int **pstAr, int iPosx, int iPosy)
{
    //cout << "isLegalPos  " << iPosx << "  " << iPosy << endl;
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
bool ListaCerrada2(int iPosx, int iPosy, int iF, std::multimap<int, stInfo> &mapOpenList)
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
bool insertarListaAbierta2(int **pstAr, const std::pair<int, int> &posNow, std::multimap<int, stInfo> &mapOpenList, std::map<std::pair<int, int>, stInfo> &mapCloseList,
                           const std::pair<int, int> &posBegin, const std::pair<int, int> &posEnd)
{
    if (PosVal2(pstAr, posNow.first - 1, posNow.second) && mapCloseList.find(std::make_pair(posNow.first - 1, posNow.second)) == mapCloseList.end())
    {
        stInfo stTmp;
        StInfo2(stTmp, posNow.first-1, posNow.second, posBegin, posEnd, posNow.first, posNow.second);
        if (ListaCerrada2(posNow.first - 1, posNow.second, stTmp.iF, mapOpenList))
        {
            mapOpenList.insert(std::make_pair(stTmp.iF, stTmp));
            if (stTmp.iH == 0)
                return true;
        }
    }
    if (PosVal2(pstAr, posNow.first, posNow.second-1) && mapCloseList.find(std::make_pair(posNow.first, posNow.second-1)) == mapCloseList.end())
    {
        stInfo stTmp;
        StInfo2(stTmp, posNow.first, posNow.second-1, posBegin, posEnd, posNow.first, posNow.second);
        if (ListaCerrada2(posNow.first, posNow.second-1, stTmp.iF, mapOpenList))
        {
            mapOpenList.insert(std::make_pair(stTmp.iF, stTmp));
            if (stTmp.iH == 0)
                return true;
        }
    }
    if (PosVal2(pstAr, posNow.first + 1, posNow.second) && mapCloseList.find(std::make_pair(posNow.first + 1, posNow.second)) == mapCloseList.end())
    {
        stInfo stTmp;
        StInfo2(stTmp, posNow.first+1, posNow.second, posBegin, posEnd, posNow.first, posNow.second);
        if (ListaCerrada2(posNow.first+1, posNow.second, stTmp.iF, mapOpenList))
        {
            mapOpenList.insert(std::make_pair(stTmp.iF, stTmp));
            if (stTmp.iH == 0)
                return true;
        }
    }
    if (PosVal2(pstAr, posNow.first, posNow.second+1) && mapCloseList.find(std::make_pair(posNow.first, posNow.second+1)) == mapCloseList.end())
    {
        stInfo stTmp;
        StInfo2(stTmp, posNow.first, posNow.second+1, posBegin, posEnd, posNow.first, posNow.second);
        if (ListaCerrada2(posNow.first, posNow.second+1, stTmp.iF, mapOpenList))
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
void Window::encontrarCamino2(int **pstAr, std::pair<int,int> posBegin, std::pair<int,int> posEnd)
{
    std::multimap<int, stInfo> mapOpenList;
    std::map<std::pair<int, int>, stInfo> mapCloseList;
    std::pair<int, int> posNow = posBegin;

    stInfo stTmp;
    StInfo2(stTmp, posNow.first, posNow.second, posBegin, posEnd);
    mapOpenList.insert(std::make_pair(stTmp.iF, stTmp));

    while (1)
    {
        auto itopen = mapOpenList.begin();
        if (itopen == mapOpenList.end()) //openlist is empty, no path If not empty, the first one is the minimum iF
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

        insertarListaAbierta2(pstAr, posNow, mapOpenList, mapCloseList, posBegin, posEnd);

        {

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
        cout << it->first.first << " " << it->first.second << " -> ";
        matrizTablero[it->first.second ][it->first.first]=1;
        posNow = std::make_pair(it->second.iFPosx, it->second.iFPosy);
        cout<<"\n";

    }

}/***
 * Funcion que llama al metodo findRoad2 el cual es un auxiliar que se apoya de otros metodos para mostrar la ruta mas corta
 * @param posx
 * @param posy
 */

void Window::AI(int posx, int posy)
{
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

    encontrarCamino2(pstAr, std::pair<int,int>(0+posx,0+posy), std::pair<int,int>(0,2));

}
void Window::Verificador(){

}