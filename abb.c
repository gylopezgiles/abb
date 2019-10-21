#include "abb.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct nodo_abb{
    struct nodo_abb_t* izq;
    struct nodo_abb_t* der;
    struct nodo_abb_t* padre;
    char* clave;
    void* dato;
} nodo_abb_t;

struct abb{
    struct nodo_t* raiz;
    size_t cantidad;
    abb_destruir_dato_t destruir_dato;
    abb_comparar_clave_t comparar_clave;
};

struct abb_iter {
    const abb_t* abb;
};

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t* abb = malloc(sizeof(abb_t));
    if(abb == NULL){
        return NULL;
    }
    abb->raiz = NULL;
    abb->cantidad = 0;
    abb->destruir_dato = destruir_dato;
    abb->comparar_clave = cmp;
    return abb;
}

nodo_abb_t* nodo_crear(const char* clave, void* valor){
    nodo_abb_t* nodo = malloc(sizeof(nodo_abb_t));
    if(nodo == NULL){
        return NULL;
    }
    nodo->clave = strdup(clave);
    nodo->dato = valor;
    nodo->izq = NULL;
    nodo->der = NULL;
    nodo->padre = NULL;
    return nodo;
}

nodo_abb_t* obtener_nodo_padre(nodo_abb_t* abb, const char* clave){

}

bool abb_guardar(abb_t* arbol, const char* clave, void* dato){
    if(abb_pertenece(arbol, clave)){
        nodo_abb_t* nodo = _abb_obtener_nodo(arbol->raiz, clave);
        if(arbol->destruir_dato != NULL){
            arbol->destruir_dato(nodo->dato);
        }
        nodo->dato = dato;
        return true;
    }
    nodo_abb_t* nodo = nodo_crear(clave, dato);
    if(nodo == NULL){
        return false;
    }
    if(arbol->raiz == NULL){
        arbol->raiz = nodo;
        return true;
    }
    nodo_abb_t* padre = obtener_nodo_padre(arbol->raiz, clave);
    if(strcmp(padre->clave, clave) > 0){
        padre->izq = nodo;
        nodo->padre = padre;
    } else {
        padre->der = nodo;
        nodo->padre = padre;
    } 
    return true;
}

nodo_abb_t* _abb_obtener_nodo(const nodo_abb_t* abb, const char* clave){
    if(abb == NULL){
        return NULL;
    }
    if(strcmp(abb->clave, clave) == 0){
        return abb;
    }
    if(strcmp(abb->clave, clave) > 0){
        return _abb_obtener(abb->izq, clave);
    }
    return _abb_obtener(abb->der, clave);
}

void* abb_borrar(abb_t* arbol, const char* clave){
    if(!abb_pertenece(arbol, clave)){
        return NULL;
    }
    nodo_abb_t* nodo = _abb_obtener_nodo(arbol->raiz, clave);
    return NULL;
}

void* abb_obtener(const abb_t* arbol, const char* clave){
    if(!abb_pertenece(arbol, clave)){
        return NULL;
    }
    nodo_abb_t* nodo = _abb_obtener_nodo(arbol->raiz, clave);
    return nodo->dato;
}

bool abb_pertenece(const abb_t* arbol, const char* clave){
    if(arbol->cantidad == 0){
        return false;
    }
    nodo_abb_t* nodo = _abb_obtener_nodo(arbol, clave);
    if(nodo == NULL){
        return false;
    }
    return true;
}

size_t abb_cantidad(abb_t* arbol){
    return arbol->cantidad;
}

void _abb_destruir(nodo_abb_t* abb, abb_destruir_dato_t* destruir_dato(void* dato)){
    if(abb == NULL){
        return;
    }
    _abb_destruir(abb->izq, destruir_dato);
    _abb_destruir(abb->der, destruir_dato);
    if(destruir_dato != NULL){
        destruir_dato(abb->dato);
    }
    free(abb->clave);
    free(abb);
}

void abb_destruir(abb_t* arbol){
    _abb_destruir(arbol->raiz, arbol->destruir_dato);
    free(arbol);
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
    _abb_in_order(arbol->raiz, visitar, extra);
}

void _abb_in_order(nodo_abb_t* abb, bool visitar(const char*, void*, void*), void* extra){
    if(abb == NULL){
        return;
    }
    _abb_in_order(abb->izq, visitar, extra);
    visitar(abb->clave, abb->dato, extra);
    _abb_in_order(abb->der, visitar, extra);
}

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
    abb_iter_t* iter = malloc(sizeof(abb_iter_t));
    if(iter == NULL){
        return NULL;
    }
    iter->abb = arbol;
    return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
    return true;
}

const char* abb_iter_in_ver_actual(const abb_iter_t *iter){
    return NULL;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
    return true;
}

void abb_iter_in_destruir(abb_iter_t* iter){

}
