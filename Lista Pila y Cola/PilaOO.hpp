/*=================================================/
	FILE: PilaOO.hpp               			      /
	CREATED BY: Rene Gomez - 23.430.002 	     /
	ON: 14/04/2018							    /
    Nota: Para esta implementacion de          /
    Pila(Generica) se utilizará el            /
    mecanismo de herencia, donde la clase    / 
    pila será la clase derivada de la       /
    clase base Lista.                      /                
=========================================*/

#ifndef PILAOO_HPP
#define PILAOO_HPP

#include "ListaOO.hpp"

template <class T_Elemento>
class PilaOO : protected ListaOO<T_Elemento>
{

    /*----------Metodos Protegidos----------*/
  protected:
    void minimoPila(T_Elemento *);          /*Devuelve el menor elemento dentro de la pila*/
    void menorPila(PilaOO &, T_Elemento *); /*Devuelve el menor elemento dentro de la pila*/

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
    T_Elemento tope() const { return (this->consultar(1)); } /*Devuelve el tope de la pila*/
    bool esVaciaPila() const { return (this->esVacia()); }   /*Verifica si una pila esta vacia ó no*/
    int longitudPila() const { return (this->longitud()); }  /*Devuelve la cantidad de elementos dentro de la pila*/

    /*----------Metodos Modificadores: Basicos----------*/
    void apilar(const T_Elemento &info) { this->insertar(info, 1); } /*Agrega un elemento a la pila*/
    void desapilar() { this->eliminarPosicion(1); }                  /*Elimina el tope de la pila*/

    /*----------Metodos Modificadores: Personalizados----------*/
    /*recibe un objeto tipo pila por referencia*/
    void ordenaPila(PilaOO &);                 /*Ordena los elementos dentro de la pila*/
    int minimoPila();                          /*Devuelve el menor elemento dentro de la pila*/
    void invertirPila() { this->invertir(); }; /*Invierte los elementos dentro de la pila*/
    void borrarPila() { this->borrarLista(); }

    /*----------Sobrecarga de operadores----------*/
    template <class TElemento> /*Operador de extracion de flujo: Lectura*/
    friend istream &operator>>(istream &, PilaOO<TElemento> &);

    template <class TElemento> /*Operador de insercion de Flujo: Imprimir*/
    friend ostream &operator<<(ostream &, const PilaOO<TElemento> &);

    const PilaOO<T_Elemento> &operator=(const PilaOO<T_Elemento> &); /*Operador de asignacion*/

    /*----------Destructor----------*/

    /*Cuando una variable de este tipo se destruye se 
    llamará primero el destructor de la clase derivada y 
    posteriormente se llama automáticamente el 
    destructor de la clase base.*/
};

/*----------Metodos Protegidos----------*/
template <class T_Elemento>
void PilaOO<T_Elemento>::minimoPila(T_Elemento *min)
{
    T_Elemento aux;

    if (!this->esVacia())
    {
        aux = this->tope();

        if (aux < (*min))
            (*min) = aux;

        this->desapilar();
        this->minimoPila(min);

        if (aux != (*min))
            this->apilar(aux);
    }
}

template <class T_Elemento>
void PilaOO<T_Elemento>::menorPila(PilaOO &p_fuente, T_Elemento *min)
{
    T_Elemento aux;

    aux = p_fuente.tope();
    p_fuente.desapilar();

    if (aux < (*min))
        (*min) = aux;

    if (!p_fuente.esVacia())
        p_fuente.menorPila(p_fuente, min);

    if ((*min) != aux)
        p_fuente.apilar(aux);
}

/*----------Metodos Modificadores: Personalizados----------*/

/*Ordena los elementos dentro de una pila*/
template <class T_Elemento>
void PilaOO<T_Elemento>::ordenaPila(PilaOO &p_fuente)
{
    T_Elemento aux;
    aux = 1000000;

    p_fuente.menorPila(p_fuente, &aux);

    if (!p_fuente.esVacia())
        ordenaPila(p_fuente);

    p_fuente.apilar(aux);
}

/*Devuelve el menor elemento dentro de una pila*/
template <class T_Elemento>
int PilaOO<T_Elemento>::minimoPila()
{
    T_Elemento aux = 1000000;

    this->minimoPila(&aux);
    return (aux);
}

/*----------Sobrecarga de operadores----------*/

/*Operador de extracion de flujo: Lectura*/
template <class T_Elemento>
istream &operator>>(istream &entrada, PilaOO<T_Elemento> &p1)
{
    int tamTemp, i;
    T_Elemento info;
    cout << "Ingrese el tamaño de la Pila a generar: ";
    entrada >> tamTemp;

    for (i = 1; i <= tamTemp; i++)
    {
        cout << "Informacion para el nodo " << i << ": ";
        entrada >> info;
        p1.apilar(info);
    }
    return entrada;
}

/*Operador de insercion de Flujo: Imprimir*/
template <class T_Elemento>
ostream &operator<<(ostream &salida, const PilaOO<T_Elemento> &p1)
{
    int i;
    NodoLista<T_Elemento> *act = p1.getPrimero();
    if (act)
    {
        //cout << "\nSobrecarga del operador de insercion de flujo (Imprimir) '<<'" << endl;
        for (i = 1; i <= p1.longitud(); i++)
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

/*Operador de asignacion el retorno constante evita: ( a1 = a2 ) = a3*/
template <class T_Elemento>
const PilaOO<T_Elemento> &PilaOO<T_Elemento>::operator=(const PilaOO<T_Elemento> &p1)
{
    this->copiaNodos(p1);
    return (*this);
}

/*----------Destructor----------*/

#endif