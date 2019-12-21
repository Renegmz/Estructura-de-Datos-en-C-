/*=============================================/
	FILE: PrincipalLista.cpp           		  /
	CREATED BY: Rene Gomez - 23.430.002 	 /
	ON: 13/04/2018							/
==========================================*/

#include "ListaOO.hpp"
using namespace std;

//#include <iostream>
//#include <string>

int main()
{
    ListaOO<int> l1;
    cin >> l1;
    cout << l1;
    
    ListaOO<int> l2;
    cin >> l2;
    cout << l2;

    l1.ordenar();
    l2.ordenar();

    ListaOO<int> l3 = l1;
    cout << l3;
    l3.borrar();
    cout << l3;

    //cout << l2;
    /*for (int i = 1; i <= 10; i++)
        l1.insertarLista(i * 2, l1.longitudLista() + 1);
    l1.insertarOrdenado(4);
    l1.insertarOrdenado(2);
    l1.insertarOrdenado(56);*/
    //l1.imprimirLista();
    /*cout << l1;
    l1.ordenar(3, 6);
    cout << l1;
    cout << "Longitud de l1: " << l1.longitudLista() << endl;
    l2 = l1;
    cout << l2;*/
    //l2.subLista_Lista(l1, 2, 6);
    //l2.imprimirLista();
    //cout << "Longitud de l2: " << l2.longitudLista() << endl;
    /*l3.mergeLista(l1,l2,&l3);
    l3.imprimirLista();*/

    return (0);
}