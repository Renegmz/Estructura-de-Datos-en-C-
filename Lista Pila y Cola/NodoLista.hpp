/*=============================================/
	FILE: NodoLista(Generico).hpp			          /
	CREATED BY: Rene Gomez - 23.430.002 	     /
	ON: 06/04/2018						  	            /
==========================================*/

/* directivas de preprocesador que
evitan inclusiones múltiples del archivo de encabezado*/
#ifndef NODOLISTA_HPP
#define NODOLISTA_HPP

#ifndef _IOSTREAM_
#include <iostream>
#endif

#ifndef _STDIO_H_
#include <stdio.h>
#endif

#ifndef _STDLIB_H_
#include <stdlib.h>
#endif

#ifndef _STRING_
#include <string>
#endif

#ifndef _CMATH_
#include <cmath>
#endif

template <class TipoElemento>
class NodoLista
{
  /*Atributos*/
private:
  TipoElemento info;
  NodoLista<TipoElemento> *proximo;

  /*Metodos*/
public: /*Interfaz de la Clase*/
  /*Constructores*/
  NodoLista() : info(TipoElemento()), proximo(NULL){};                                                   /* forma para hacer asignaciones dentro de los */
  NodoLista(TipoElemento info_) : info(info_), proximo(NULL){};                                /*parentesis de los parametros lo hace mas rapido*/
  NodoLista(TipoElemento info_, NodoLista<TipoElemento> *prox) : info(info_), proximo(prox){}; /*only constructors take member initializers*/

  /*Metodos de Inspeccion*/
  TipoElemento getInfo() const { return (this->info); };                   /*Devuelve la info del nodo*/
  NodoLista<TipoElemento> *getProximo() const { return (this->proximo); }; /*Devuelve el prox enlace del nodo*/

  /*Metodos de Modificacion*/
  void setInfo(TipoElemento info) { this->info = info; };                 /*Modifica la Info del Nodo*/
  void setProximo(NodoLista<TipoElemento> *sig) { this->proximo = sig; }; /*Modifica el enlace del nodo*/

}; /*Fin de la clase NodoLista*/

#endif