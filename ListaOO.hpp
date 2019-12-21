/*=============================================/
	FILE: ListaOO.hpp           			  /
	CREATED BY: Rene Gomez - 23.430.002 	 /
	ON: 13/04/2018							/
==========================================*/

#ifndef LISTAOO_HPP
#define LISTAOO_HPP

#include "NodoLista.hpp"
using namespace std;
template <class TipoElemento>
class ListaOO
{
    /*Atributos*/
  private:
    int tamanho;
    NodoLista<TipoElemento> *primero; /*objeto NodoLista compuesto*/
    NodoLista<TipoElemento> *ultimo;  /*objeto NodoLista compuesto*/
    void copiaNodos(const ListaOO<TipoElemento> &);

    /*Metodos*/
  protected:
    /*Obtiene el enlace del apuntador primero*/
    NodoLista<TipoElemento> *getPrimero() const { return (this->primero ? this->primero : NULL); } 
    void setPrimero(NodoLista<TipoElemento> *sig) { this->primero = sig; }

  public: /*Interfaz de la Clase*/
    /*----------Constructor----------*/
    ListaOO() : tamanho(0), primero(NULL), ultimo(NULL){};
    /*----------Constructor copia----------*/
    ListaOO(const ListaOO &);

    /*----------Metodos Observadores----------*/
    bool esVacia() const { return (this->primero == NULL); } /*Verifica si la lista esta vacia o no*/
    int longitud() const { return (this->tamanho); }         /*Devuelve la tamanho de la lista*/
    TipoElemento consultar(int) const;                       /*Consulta una posicion dentro de la lista*/
    int posicion(const TipoElemento) const;                  /*Devuelve la posicion de un elemento en la lista*/ 
    bool estaElemento(TipoElemento) const;                   /*Consulta si un elemento esta dentro de la lista ó no*/
    void imprimir() const;                                   /*Muestra la lista por Pantalla*/
    bool sonIguales(const ListaOO &) const;                  /*Verifica si dos listas son iguales o no*/

    /*----------Metodos Modificadores: Basicos----------*/
    void insertar(TipoElemento, int);     /*Inserta un elemento dentro de la Lista*/
    void eliminarElementos(TipoElemento); /*elimina todos los elementos iguales a: e*/
    void borrar(int);           /*elimina una Posicion dentro de la lista*/
    void borrar();                   /*Borra todos los elementos dentro de la lista*/

    /*----------Metodos Modicadores: Personalizados----------*/
    void modificar(const TipoElemento, const int);                          /*Modifica(actualiza la posicion: p, con el elemento: e)*/
    void insertar(TipoElemento);                                            /*Insertar Ordenado, los elementos en la lista de menor a mayor*/
    void subLista(const ListaOO &, int, int);                               /*Sub_lista de un rango [a,b]*/
    int subLista(const ListaOO &);                                          /*Determina cuantas veces una lista es sublista de otra*/
    void invertir();                                                        /*Invierte el orden de los elementos dentro de la lista*/
    void invertir(TipoElemento, TipoElemento);                              /*Invierte el orden de los elementos dentro de una sublista*/
    void invertirSubLista(int, int);                                        /*Invierte el orden de los elementos dentro de una sublista*/
    void ordenar();                                                         /*Ordena La Lista*/
    void ordenar(const int, const int);                                     /*Ordena Una SubLista De La Lista*/
    ListaOO<TipoElemento> mergeLista(ListaOO &);                            /*Mezcla dos Listas*/
    void interseccionOrdenada(const ListaOO &, const ListaOO &, ListaOO *); /*Apartir de 2 listas ordenadas ascendentemente crea 
    la insterseccion entre las listas*/

    /*----------Sobrecarga de Operadores----------*/

    /*1: Operador de insercion de Flujo: Imprimir*/
    /*Nota: plantillas de funciones para generar funciones sobrecargadas que reali-
    zan tareas idénticas sobre tipos de datos diferentes.*/
    template <class T_Elemento>
    friend ostream &operator<<(ostream &, const ListaOO<T_Elemento> &);
    /*Nota: Dentro de una plantilla de clase correspondiente a la clase X que se declaró como:
    template< class T > class X
    una declaración de amistad de la forma:
    friend void f2( X< T > & );
    para un tipo particular T tal como float, hace de la función f2( X< float>& ) una amiga sólo de X<
    float >.*/

    /*2:Operador de extracion de flujo: Lectura*/
    template <class T_Elemento>                                   /*Plantilla de funcion*/
    friend istream &operator>>(istream &, ListaOO<T_Elemento> &); /*Funcion amiga dentro de una plantilla*/
    /*Nota: Si el operando izquierdo debe ser un objeto de una clase diferente o un tipo integrado,
    esta función operador debe implementarse como una función no miembro. Una función operador
    no miembro necesita ser amiga, si esa función debe acceder directamente a miembros
    privados o protegidos de esa clase.*/

    /*3: Operador de asignacion*/
    const ListaOO<TipoElemento> &operator=(const ListaOO<TipoElemento> &);
    /*Nota: Cuando una función operador se implementa como una función miembro, el operando más hacia la 
    izquierda (o el único operando) debe ser un objeto de clase (o una referencia a un objeto de clase) 
    correspondiente a la clase del operador.*/

    /*----------Destructor----------*/
    ~ListaOO();
}; /*Fin de la clase ListaOO*/

template <class TipoElemento>
void ListaOO<TipoElemento>::copiaNodos(const ListaOO<TipoElemento> &l_spe)
{
    NodoLista<TipoElemento> *act = NULL;
    
    /*Copiando las listas*/
    if (l_spe.primero && this != &l_spe)
    {    
        this->borrar(); //Se destruye la LISTA instancia
        act = l_spe.primero;
        while (act)
        {
            this->insertar(act->getInfo(), this->tamanho + 1);
            act = act->getProximo();
        }
    }
}

/*----------Constructor Copia----------*/
template <class TipoElemento>
ListaOO<TipoElemento>::ListaOO(const ListaOO &ObjetoACopiar)
{
   /*Copiando las listas*/
    if (ObjetoACopiar.primero)
    {
        this->primero = this->ultimo = NULL;
        this->tamanho = 0;
        this->copiaNodos(ObjetoACopiar);
    } 
}
/*----------FIN DE LOS CONSTRUCTORES----------*/

/*----------Metodos Observadores----------*/

/*Consulta una posicion dentro de la lista*/
template <class TipoElemento>
TipoElemento ListaOO<TipoElemento>::consultar(int pos) const
{
    NodoLista<TipoElemento> *act = this->primero;
    bool consulta = false;

    /*Validando que la posicion a consultar sea valida*/
    if (this->primero && pos >= 1 && pos <= this->tamanho)
    {
        for (int i = 1; i < pos; i++)
            act = act->getProximo();
        consulta = true;
    }
    return (consulta ? act->getInfo() : TipoElemento());
}

/*Devuelve la posicion de un elmento dentro de la lista y 
devuelve 0 si no lo encuentra*/
template <class TipoElemento>
int ListaOO<TipoElemento>::posicion(const TipoElemento e) const
{
    NodoLista<TipoElemento> *act = this->primero;
    bool encontrado = false;
    int i = 1;

    if (this->primero)
    {
        while (act && !encontrado)
        {
            if (act->getInfo() == e)
                encontrado = true;
            act = act->getProximo();
            i++;
        }
    }
    return (encontrado ? i-1 : int());
}

/*Consulta si un elemento está dentro de la lista ó no*/
template <class TipoElemento>
bool ListaOO<TipoElemento>::estaElemento(TipoElemento elm_) const
{
    bool encontrado = false;
    NodoLista<TipoElemento> *act = this->primero;

    while (act && !encontrado)
    {
        if (act->getInfo() == elm_)
            encontrado = true;
        act = act->getProximo();
    }
    return (encontrado);
}

/*Muestra los elementos de la lista por pantalla*/
template <class TipoElemento>
void ListaOO<TipoElemento>::imprimir() const
{
    int i;
    NodoLista<TipoElemento> *act = this->primero;
    if (this->primero)
    {
        for (i = 1; i <= this->tamanho; i++)
        {
            if (act->getProximo())
                cout << "" << act->getInfo() << "->";
            else
                cout << "" << act->getInfo();
            act = act->getProximo();

            /*if (act->getProximo())
            {
                if (act->getInfo() != "\0")
                    cout << act->getInfo() << "->";
                else
                    cout << "' '" << " ";
            }
            else
                cout << act->getInfo() << " ";
            act = act->getProximo();*/
        }
        cout << "-> NULL" << endl;
    }
    else
        cout << "NULL. Lista Vacia" << endl;
}

/*Verifica si dos listas son iguales ó no*/
template <class TipoElemento>
bool ListaOO<TipoElemento>::sonIguales(const ListaOO &l_spe) const
{
    NodoLista<TipoElemento> *tmp1 = NULL, *tmp2 = NULL;
    bool iguales = true;

    tmp1 = this->primero;
    tmp2 = l_spe.primero;

    if (this->tamanho == l_spe.tamanho)
    {
        int i = 1;
        while (i <= this->tamanho && iguales)
        {
            if (tmp1->getInfo() != tmp2->getInfo())
                iguales = false;
                
            tmp1 = tmp1->getProximo();
            tmp2 = tmp2->getProximo();
            i++;
        }
    }
    else
        iguales = false;
    return (iguales);
}
/*----------FIN DE METODOS OBSERVADORES----------*/

/*----------Metodos Modificadores: Basicos----------*/

/*Inserta un elemento dentro de la lista en la posicion: pos*/
template <class TipoElemento>
void ListaOO<TipoElemento>::insertar(TipoElemento info_, int pos)
{
    int i;
    NodoLista<TipoElemento> *ant = NULL, *sig = NULL, *nuevo = NULL;

    if (pos > 0 && pos <= this->tamanho + 1)
    {
        nuevo = new NodoLista<TipoElemento>(info_);
        if (pos == 1) /*Insertando en la primera pos*/
        {
            nuevo->setProximo(this->primero);
            this->primero = nuevo;
        }
        else
        {
            /*Insertando en el medio o al final de la lista*/
            ant = this->primero;
            sig = ant->getProximo();
            for (i = 2; i < pos; i++)
            {
                ant = sig;
                sig = sig->getProximo();
            }
            ant->setProximo(nuevo);
            nuevo->setProximo(sig);
        }
        if (pos == this->tamanho + 1)
        {
            nuevo->setProximo(NULL);
            this->ultimo = nuevo;
        }

        this->tamanho++;
        //nuevo = NULL;
        //delete nuevo; // recaptura memoria

        /*Buena práctica de programación :Después de eliminar memoria asignada de 
        manera dinámica, establezca en 0 al apuntador que hace referencia a dicha 
        memoria. Esto desconecta al apuntador del espacio asignado previamente en el }
        espacio libre.*/
    }
    else
        cout << "Error INSERTAR. Posición Invalida" << endl;
}

/*Elimina una posicion dentro de la lista*/
template <class TipoElemento>
void ListaOO<TipoElemento>::borrar(int pos)
{
    int i;
    NodoLista<TipoElemento> *ant = NULL, *act = NULL, *sig = NULL;

    if (this->primero && (pos >= 1 && pos <= this->tamanho))
    {
        if (pos == 1)
        {
            /*Eliminando la primera pos*/
            act = this->primero;
            this->primero = act->getProximo();
            if (this->primero == NULL)
                this->ultimo = NULL;
        }
        else
        {
            ant = this->primero;
            act = ant->getProximo();
            sig = act->getProximo();
            for (i = 2; i < pos; i++)
            {
                ant = act;
                act = sig;
                sig = sig->getProximo();
            }
            ant->setProximo(sig);
            if (sig == NULL)
                this->ultimo = ant;
        }
        delete act;
        this->tamanho--;
    }
}

/*Elimina todos los elementos iguales a: 'elem' dentro de la lista*/
template <class TipoElemento>
void ListaOO<TipoElemento>::eliminarElementos(TipoElemento elem)
{
    NodoLista<TipoElemento> *act = NULL, *prox = NULL, *ant = NULL;

    /*Inicializando apuntadores*/
    act = this->primero;
    prox = act->getProximo();

    /*Recorriendo los elementos internos de la lista*/
    while (act && act->getProximo())
    {
        /*Buscando al elemento dentro de la lista*/
        while (prox && act->getInfo() != elem)
        {
            ant = act;
            act = prox;
            prox = prox->getProximo();
        }
        if (act->getInfo() == elem)
        {
            /*Eliminando al elemento*/
            if (act == this->primero)
            {
                this->primero = prox;
                delete act;
                act = NULL;
                act = prox;
                prox = prox->getProximo();
            }
            else
            {
                if (act == this->ultimo)
                {
                    this->ultimo = ant;
                    ant->setProximo(prox);
                    delete act;
                    act = NULL;
                }
                else
                {
                    ant->setProximo(prox);
                    delete act;
                    act = NULL;
                    if (prox)
                    {
                        act = prox;
                        prox = prox->getProximo();
                    }
                }
            }
            this->tamanho--;
        }
    }
    /*Ultima posicion de la lista*/
    if (act && act->getInfo() == elem)
    {
        if (this->primero == this->ultimo)
        {
            this->primero = NULL;
            this->ultimo = NULL;
        }
        else
        {
            ant->setProximo(NULL);
            this->ultimo = ant;
        }
        this->tamanho--;
    }
}

/*----------Metodos Modicadores: Personalizados----------*/

/*Modifica(actualiza la posicion: p, con el elemento: e)*/
template <class TipoElemento>
void ListaOO<TipoElemento>::modificar(const TipoElemento e, const int pos)
{
    NodoLista<TipoElemento> *act = NULL;
    int i;

    /*Ubicando el nodo a actualizar el campo: info*/
    if (this->primero && (pos > 0 && pos <= this->tamanho))
    {
        act = this->primero;
        for (i = 2; i <= pos; i++)
            act = act->getProximo();

        /*Actualizando el nodo*/
        if (act)
            act->setInfo(e);
    }
    else
        cout << "Error Modifica: Posicion a moficar es incorrecta" << endl;
}

/*Insertar Ordenado, los elementos en la lista de menor a mayor*/
template <class TipoElemento>
void ListaOO<TipoElemento>::insertar(TipoElemento elem)
{
    NodoLista<TipoElemento> *nuevo = NULL;
    nuevo = new NodoLista<TipoElemento>(elem);

    if (this->longitud == 0)
    {
        this->primero = nuevo;
        this->ultimo = nuevo;
    }
    else
    {
        if (elem < primero->getInfo())
        {
            nuevo->setProximo(this->primero);
            this->primero = nuevo;
        }
        else
        {
            NodoLista<TipoElemento> *ant = NULL, *p = NULL;
            ant = p = this->primero;
            while (p->getProximo() != NULL && elem > p->getInfo())
            {
                ant = p;
                p = p->getProximo();
            }
            if (elem > p->getInfo())
            {
                ant = p;
                nuevo->setProximo(ant->getProximo());
                ant->setProximo(nuevo);
                this->ultimo = nuevo;
            }
            else
            {
                nuevo->setProximo(p);
                ant->setProximo(nuevo);
            }
        }
    }
    this->tamanho++;
    //delete nuevo;
}

/*Genera una Sub_lista de un rango [a,b]*/
template <class TipoElemento>
void ListaOO<TipoElemento>::subLista(const ListaOO &l_fuente, int a, int b)
{
    NodoLista<TipoElemento> *act = NULL, *nuevo = NULL, *act2 = NULL;
    int inicio, fin, i;
    inicio = fin = 0;

    if (a < b)
    {
        inicio = a;
        fin = b;
    }
    else
    {
        inicio = b;
        fin = a;
    }

    if (l_fuente.tamanho > 0 && fin <= l_fuente.tamanho)
    {
        act = l_fuente.primero;
        for (i = 1; i <= fin; i++)
        {
            if (i == inicio)
            {
                if (this->tamanho == 0) //this->tamanho == 0
                {
                    nuevo = new NodoLista<TipoElemento>(act->getInfo());
                    this->primero = nuevo;
                    act2 = this->primero;
                    this->ultimo = nuevo;
                    this->tamanho++;
                }
            }
            else
            {
                if (this->tamanho > 0) // this->tamanho > 0
                {
                    nuevo = new NodoLista<TipoElemento>(act->getInfo());
                    act2->setProximo(nuevo);
                    act2 = act2->getProximo();
                    this->ultimo = act2;
                    this->tamanho++;
                }
            }
            act = act->getProximo();
        }
    }
    else
        cout << "SubLista: Error en los parametros" << endl;
}

/*Determina cuantas veces una lista es sublista de otra*/
template <class TipoElemento>
int ListaOO<TipoElemento>::subLista(const ListaOO &lista_B)
{
    int contador;
    NodoLista<TipoElemento> *act, *auxA, *auxB;

    /*Inicializando variables*/
    contador = 0;
    act = auxA = auxB = NULL;

    /*Validando que se puedan buscar sublistas*/
    if (this->tamanho <= lista_B.tamanho)
    {
        /*Pto. de partida para la busqueda*/
        auxA = this->primero;  //auxA->setProximo(this->primero);
        act = lista_B.primero; //act->setProximo(lista_B.primero);
        auxB = act;            //auxB->setProximo(act);

        /*La busqueda termina cuando se llegue al final de la lista_B*/
        /*act == NULL */
        while (act->getProximo())
        {
            /*Pto. de partida de la sublista*/
            if (auxA->getInfo() == auxB->getInfo())
            {
                /*Buscando Sublista*/
                while (auxA->getInfo() == auxB->getInfo() && auxA->getProximo() && auxB->getProximo())
                {
                    auxA = auxA->getProximo(); //auxA->setProximo(auxA->getProximo());
                    auxB = auxB->getProximo(); //auxB->setProximo(auxB->getProximo());
                }
                /*¿Se encontro una sublista?*/
                if (auxA->getProximo() == NULL && auxA->getInfo() == auxB->getInfo())
                    contador++; /*auxA == NULL: Se encontro una sublista*/

                /*Reinicializando los apuntadores para la busqueda*/
                auxA = this->primero;    //auxA->setProximo(this->primero);
                act = act->getProximo(); //act->setProximo(act->getProximo());
                auxB = act;              //auxB->setProximo(act);
            }
            else
            {
                /*Actualizando el pto. de partida de la sublista*/
                act = act->getProximo(); //act->setProximo(act->getProximo());
                auxB = act;              //auxB->setProximo(act);
            }
        }
        /*¿Se encontro una sublista? Al llegar al final de la lista_B
        se compara ese elemento con el ultimo de la lista_A*/
        if (auxA->getProximo() == NULL && auxA->getInfo() == auxB->getInfo())
            contador++; /*auxA == NULL: Se encontro una sublista*/
    }
    return (contador);
}

/*Invierte el orden de todos los elementos dentro de una lista*/
template <class TipoElemento>
void ListaOO<TipoElemento>::invertir()
{
    NodoLista<TipoElemento> *ant = NULL, *act = NULL, *sig = NULL;
    this->ultimo = this->primero;
    act = this->primero;

    /*Validando que se pueda invertir la lista*/
    if (this->tamanho > 0)
    {
        while (act)
        {
            sig = act->getProximo();
            act->setProximo(ant);
            ant = act;
            act = sig;
        }
        this->primero = ant;
    }
    else
        cout << "Invertir Error... Lista vacia" << endl;
}

/*Invierte el orden de los elementos dentro de una sublista*/
/*Desde el elemento "a" hasta el elemento "b"*/
template <class TipoElemento>
void ListaOO<TipoElemento>::invertir(TipoElemento a, TipoElemento b)
{
    bool encontradoIni, encontradoFin;
    NodoLista<TipoElemento> *act = NULL, *ini = NULL, *ant = NULL, *sig = NULL, *fin = NULL;

    encontradoIni = false;
    encontradoFin = false;
    act = this->primero;
    /*Validando que los elementos esten el la lista*/
    while (act && (!encontradoIni || !encontradoFin))
    {
        
        /*Buscando el Inicio y Fin de la Sublista*/
        if (!encontradoIni && (act->getInfo() == a || act->getInfo() == b))
        {
            ini = act;
            encontradoIni = true;
        }
        else
        {
            if (encontradoIni && (act->getInfo() == a || act->getInfo() == b))
            {
                fin = act;
                encontradoFin = true;
            }
        }
        
        if (!encontradoIni)
            ant = act;

        act = act->getProximo();
    }

    if (encontradoIni && encontradoFin && ini != fin)
    {
        /*Invirtiendo la sublista*/
        act = ini;
        while (act != fin)
        {
            sig = act->getProximo();
            act->setProximo(ant);
            ant = act;
            act = sig;
        }
        sig = act->getProximo();
        act->setProximo(ant);

        /*Caso_1: El rango de la sublista a invertir es igual
        al la longitud de la lista original*/
        if(ini == this->primero && fin == this->ultimo)
        {
            this->ultimo = this->primero;
            this->primero = fin;
        }
        else
        {
            /*Caso_2: El primer nodo de la lista original es
            modificado, hay que actualizar this->primero*/
            if(!this->primero->getProximo())
            {
                ini->setProximo(sig);
                this->primero = fin;
            }
            else
            {
                /*Caso_3: El ultimo nodo de la lista original es
                modificado, hay que actualizar this->ultimo*/
                if(this->ultimo->getProximo())
                {
                    act = ini->getProximo();
                    act->setProximo(fin);
                    ini->setProximo(sig);
                    this->ultimo = ini;
                }
                else
                {
                    /*Caso_4: Se invierten las posiciones 
                    intermedias en la lista*/
                    act = ini->getProximo();
                    act->setProximo(fin);
                    ini->setProximo(sig);
                }
            }
        }
    }
    else
        cout << "Error... Los elementos: " << a << " y: " << b << " No estan en la lista" << endl;
}

/*Invierte el orden de los elementos dentro de una sublista*/
/*Desde la pos "pos1" hasta la pos "pos2"*/
template <class TipoElemento>
void ListaOO<TipoElemento>::invertirSubLista(int pos1, int pos2)
{
    int inicio, fin;
    NodoLista<TipoElemento> *aux = NULL, *act = NULL, *ant = NULL, *sig = NULL;

    /*Validando que la lista no este vacia*/
    if (this->tamanho > 0)
    {
        /*Buscando el inicio y fin de la sublista*/
        if (pos1 < pos2)
        {
            inicio = pos1;
            fin = pos2;
        }
        else
        {
            inicio = pos2;
            fin = pos1;
        }
        /*Ubicando los apuntadores en la sublista*/
        if (fin <= this->tamanho && inicio != fin)
        {
            act = this->primero;
            /*Ubicando la primera posicion 'inicio' desde donde se
            comenzara a invertir la sublista*/
            for (int i = 1; i < inicio; i++)
            {
                aux = act;
                act = act->getProximo();
            }
            
            /*Invirtiendo la sublista*/
            for (int j = inicio; j <= fin; j++)
            {
                sig = act->getProximo();
                act->setProximo(ant);
                ant = act;
                act = sig;
            }

            /*Caso_1: La longitud de la sublista a invertir es igual
            al la longitud de la lista original*/
            if(inicio == 1 && fin == this->tamanho)
            {
                this->ultimo = this->primero;
                this->primero = ant;
            }
            else
            {
                /*Caso_2: El primer nodo de la lista original es
                modificado, hay que actualizar this->primero*/
                if(!this->primero->getProximo())
                {
                    act = this->primero;
                    act->setProximo(sig);
                    this->primero = ant;
                }
                else
                {
                    /*Caso_3: El ultimo nodo de la lista original es
                    modificado, hay que actualizar this->ultimo*/
                    if(this->ultimo->getProximo())
                    {
                        this->ultimo = aux->getProximo();
                        aux->setProximo(ant);
                    }
                    else
                    {
                        /*Caso_4: Se invierten las posiciones 
                        intermedias en la lista*/
                        act = aux->getProximo();
                        act->setProximo(sig);
                        aux->setProximo(ant);
                    }
                }
            }
        }
    }
}

/*Ordena todos los elementos de la lista de menor a mayor*/
template <class TipoElemento>
void ListaOO<TipoElemento>::ordenar()
{
    NodoLista<TipoElemento> *ant, *act;
    int i, j;
    TipoElemento aux;

    if (this->tamanho > 1)
    {
        ant = this->primero;
        act = ant->getProximo();

        for (i = 1; i < this->tamanho; i++)
        {
            for (j = 0; j < (this->tamanho - i); j++)
            {
                if (ant->getInfo() > act->getInfo())
                {
                    aux = ant->getInfo();
                    ant->setInfo(act->getInfo());
                    act->setInfo(aux);
                }
                ant = act;
                act = act->getProximo();
            }
            ant = this->primero;
            act = ant->getProximo();
        }
    }
}

/*Ordena una SubLista Por El Método de Burbuja*/
template <class TipoElemento>
void ListaOO<TipoElemento>::ordenar(const int ini, const int fin)
{
    NodoLista<TipoElemento> *prim, *ant, *act;
    int i, j;
    TipoElemento aux;

    if ((ini > 0) && (ini < fin) && (fin <= this->tamanho))
    {
        if (this->tamanho > 2)
        {
            ant = this->primero;
            act = ant->getProximo();

            for (i = 1; i < fin; i++)
            {
                if (i >= ini)
                {
                    prim = ant;

                    for (j = 0; j < (fin - i); j++)
                    {
                        if (ant->getInfo() > act->getInfo())
                        {
                            aux = ant->getInfo();
                            ant->setInfo(act->getInfo());
                            act->setInfo(aux);
                        }

                        ant = act;
                        act = act->getProximo();
                    }

                    ant = prim;
                    act = ant->getProximo();
                }
                else
                {
                    ant = act;
                    act = act->getProximo();
                }
            }
        }
        else
            cerr << endl
                 << "Si Desea Ordenar La Lista Completa, Usar Ordenar Lista" << endl;
    }
}

/*Mezcla los elementos de 2 listas(estas deben estas ordenadas ascendentemente)*/
template <class TipoElemento>
ListaOO<TipoElemento> ListaOO<TipoElemento>::mergeLista(ListaOO &l_fuente2)
{
    ListaOO<TipoElemento> l3;

    /*Termina cuando: Las dos listas a mezclar esten vacias*/
    while (this->tamanho > 0 && l_fuente2.tamanho > 0)
    {
        /*Buscando el Pto. de partida para el merge*/
        if (this->consultar(1) < l_fuente2.consultar(1))
        {
            /*Mezclando las listas*/
            while (this->tamanho > 0 && this->consultar(1) <= l_fuente2.consultar(1))
            {
                l3.insertar(this->consultar(1), l3.tamanho + 1);
                this->borrar(1);
            }
        }
        else
        {
            while (!l_fuente2.esVacia() && l_fuente2.consultar(1) <= this->consultar(1))
            {
                l3.insertar(l_fuente2.consultar(1), l3.tamanho + 1);
                l_fuente2.borrar(1);
            }
        }
        /*Una de las listas ya esta vacia*/
        if (this->tamanho == 0)
        {
            while (!l_fuente2.esVacia())
            {
                l3.insertar(l_fuente2.consultar(1), l3.tamanho + 1);
                l_fuente2.borrar(1);
            }
        }
        else
        {
            if (l_fuente2.tamanho == 0)
            {
                while (this->tamanho > 0)
                {
                    l3.insertar(this->consultar(1), l3.tamanho + 1);
                    this->borrar(1);
                }
            }
        }
    }
    return (l3);
}

/*Borra todos los elemetos dentro de la lista*/
template <class TipoElemento>
void ListaOO<TipoElemento>::borrar()
{
    NodoLista<TipoElemento> *act = this->primero;

    if (this->tamanho > 0)
    {
        while (act)
        {
            this->primero = this->primero->getProximo();
            delete act;
            act = this->primero;
        }
        this->tamanho = 0;
        this->ultimo = NULL;
        delete ultimo;
    }
}

/*Apartir de 2 listas ordenadas ascendentemente crea la insterseccion entre las listas*/
template <class TipoElemento>
void ListaOO<TipoElemento>::interseccionOrdenada(const ListaOO &l_spe1, const ListaOO &l_spe2, ListaOO *l_spe3)
{
    int pos = 1;
    bool finl1 = false;
    NodoLista<TipoElemento> *actl1 = NULL, *actl2 = NULL;

    if (l_spe1.tamanho > 0 && l_spe2.tamanho > 0)
    {
        /*Asignado actl1 a la lista mas larga*/
        if (l_spe1.tamanho >= l_spe2.tamanho)
        {
            actl1 = l_spe1.primero;
            actl2 = l_spe2.primero;
        }
        else
        {
            actl1 = l_spe2.primero;
            actl2 = l_spe1.primero;
        }
        while (actl2 != NULL && !finl1)
        {
            if (actl1 == NULL)
                finl1 = true;
            else
            {
                if (actl1->getInfo() == actl2->getInfo())
                {
                    if (this->tamanho == 0)
                    {
                        l_spe3->insertar(actl1->getInfo(), pos);
                        actl1 = actl1->getProximo();
                        actl2 = actl2->getProximo();
                        pos++;
                    }
                    else
                    {
                        if (!(l_spe3->estaElemento(actl1->getInfo())))
                        {
                            l_spe3->insertar(actl1->getInfo(), pos);
                            pos++;
                        }
                        actl1 = actl1->getProximo();
                        actl2 = actl2->getProximo();
                    }
                }
                else
                {
                    if (actl2->getInfo() > actl1->getInfo())
                        actl1 = actl1->getProximo();
                    else
                        actl2 = actl2->getProximo();
                }
            }
        }
    }
}

/*----------Sobrecarga de Operadores----------*/

/*Inserción de Flujo: Imprimir*/
template <class TipoElemento>
ostream &operator<<(ostream &salida, const ListaOO<TipoElemento> &l_spe)
{
    l_spe.imprimir();
    return salida;
}

/*Operador de extracion de flujo: Lectura*/
template <class TipoElemento>
istream &operator>>(istream &entrada, ListaOO<TipoElemento> &l_spe)
{
    int i, tamTemp;
    NodoLista<TipoElemento> *ant = NULL, *nuevo = NULL;
    TipoElemento info_;

    /*cout << "Creando una lista con el operador '>>' Sobrecargado\n";*/
    cout << "Ingrese el tamaño de la lista a generar: ";
    entrada >> tamTemp;
    l_spe.tamanho = tamTemp;
    for (i = 1; i <= tamTemp; i++)
    {
        cout << "Informacion para el nodo " << i << ": ";
        entrada >> info_;
        /*entrada.ignore();
            getline(entrada,info_,'\n');
            cout << endl;*/
        nuevo = new NodoLista<TipoElemento>(info_);
        if (l_spe.primero != NULL)
        {
            ant->setProximo(nuevo);
            ant = nuevo;
        }
        else
        {
            nuevo->setProximo(l_spe.primero);
            l_spe.primero = nuevo;
            ant = l_spe.primero;
        }
        nuevo = NULL;
    }
    l_spe.ultimo = ant;

    //nuevo = NULL;
    //delete nuevo;
    return entrada;
}

/*Operador de asignacion: el retorno constante evita: ( a1 = a2 ) = a3*/
template <class TipoElemento>
const ListaOO<TipoElemento> &ListaOO<TipoElemento>::operator=(const ListaOO<TipoElemento> &l_spe)
{
    this->copiaNodos(l_spe);
    return (*this);
}

/*----------Destructor----------*/

template <class TipoElemento>
ListaOO<TipoElemento>::~ListaOO()
{
    this->borrar();
}

#endif
