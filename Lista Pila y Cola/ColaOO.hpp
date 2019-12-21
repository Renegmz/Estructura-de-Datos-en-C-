/*=================================================/
	FILE: ColaOO.hpp               			      /
	CREATED BY: Rene Gomez - 23.430.002 	     /
	ON: 22/04/2018							    /
    Nota: Para esta implementacion de          /
    Cola(Generica) se utilizará el            /
    mecanismo de herencia, donde la clase    / 
    cola será la clase derivada de la       /
    clase base Lista.                      /                
=========================================*/

#ifndef COLAOO_HPP
#define COLAOO_HPP

#include "ListaOO.hpp"

template <class T_Elemento>
class ColaOO : protected ListaOO<T_Elemento>
{
    /*Metodos*/
  public: /*Interfaz de la clase*/
    /*----------Constructor----------*/

    /*Se llama constructor por defecto a un constructor que 
    no necesita que se le pasen parámetros o argumentos para
    inicializar las variables miembro de la clase. 
    Un constructor por defecto es pues un constructor que 
    no tiene argumentos o que, si los tiene, todos sus 
    argumentos tienen asignados un valor por defecto en la 
    declaración del constructor. En cualquier caso, puede 
    ser llamado sin tenerle que pasar ningún argumento.*/

    /*El inicializador base puede ser omitido en el caso de 
    que la clase base tenga un constructor por defecto. 
    En el caso de que el constructor de la clase base exista,
    al declarar un objeto de la clase derivada se ejecuta 
    primero el constructor de la clase base.*/

    /*----------Metodos Observadores----------*/
    T_Elemento frente() const { return (this->consultar(1)); } /*Obtener/Devuelve el frente de la cola*/
    bool esVaciaCola() const { return (this->esVacia()); }     /*Saber si una cola esta vacia o NO*/
    int longitudCola() const { return (this->longitud()); }    /*Devuelve la longitud de la cola*/

    /*----------Metodos modificadores: Basicos----------*/
    void encolar(const T_Elemento info) { this->insertar(info, this->longitud() + 1); } /*Agrega un elemento a la cola*/
    void desencolar() { this->eliminarPosicion(1); }                                    /*Elimina el primer elemento de la cola*/

    /*----------Metodos Modificadores: Personalizados----------*/
    void invertirCola() { this->invertir(); }
    void borrarCola() { this->borrarLista(); }

    /*----------Sobrecarga de operadores----------*/
    template <class TElemento>
    friend istream &operator>>(istream &, ColaOO<TElemento> &); /*Operador de extracion de flujo: Lectura*/

    template <class TElemento>
    friend ostream &operator<<(ostream &, const ColaOO<TElemento> &); /*Operador de insercion de Flujo: Imprimir*/

    const ColaOO<T_Elemento> &operator=(const ColaOO<T_Elemento> &); /*Operador de asignacion*/

    /*----------Destructor----------*/

    /*Cuando una variable de este tipo se destruye se 
    llamará primero el destructor de la clase derivada y 
    posteriormente se llama automáticamente el 
    destructor de la clase base.*/
};

/*----------Sobrecarga de operadores----------*/

/*Operador de extracion de flujo: Lectura*/
template <class T_Elemento>
istream &operator>>(istream &entrada, ColaOO<T_Elemento> &c1)
{
    int tamTemp, i;
    T_Elemento info;
    cout << "Ingrese el tamaño de la Cola a generar: ";
    entrada >> tamTemp;

    for (i = 1; i <= tamTemp; i++)
    {
        cout << "Informacion para el nodo " << i << ": ";
        entrada >> info;
        c1.encolar(info);
    }
    return entrada;
}

/*Operador de insercion de Flujo: Imprimir*/
template <class T_Elemento>
ostream &operator<<(ostream &salida, const ColaOO<T_Elemento> &c1)
{
    int i;
    NodoLista<T_Elemento> *act = c1.getPrimero();
    if (act)
    {
        //cout << "\nSobrecarga del operador de insercion de flujo (Imprimir) '<<'" << endl;
        for (i = 1; i <= c1.longitud(); i++)
        {
            if (act->getProximo() != NULL)
                salida << act->getInfo() << "->";
            else
                salida << act->getInfo();
            act = act->getProximo();
        }
        salida << "-> NULL";
        salida << endl;
    }
    else
        salida << "NULL" << endl;
    return salida;
}

/*Operador de asignacion: el retorno constante evita: ( a1 = a2 ) = a3*/
template <class T_Elemento>
const ColaOO<T_Elemento> &ColaOO<T_Elemento>::operator=(const ColaOO<T_Elemento> &c1)
{
    this->copiaNodos(c1);
    return (*this);
}

/*----------Destructor----------*/

#endif