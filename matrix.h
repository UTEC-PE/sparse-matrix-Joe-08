#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "node.h"

using namespace std;

template <typename T>
class Matrix {
    private:
        Node<T>* hRows;
        Node<T>* hColumns;
        int columns;
        int rows;

    public:
        Matrix(){
            hRows = NULL;
            hColumns = NULL;
            columns = 0;
            rows = 0;
        }
        
        Matrix(int sizeX, int sizeY){
            columns = sizeX;
            rows = sizeY;
            hRows = new Node<T>{-1,0,0,NULL,NULL};
            hColumns = new Node<T>{0,-1,0,NULL,NULL}; 
            Node<T> *tempR = hRows;
            Node<T> *tempC = hColumns;
            for (int i = 0; i < columns; i++){
                Node<T> *nodo = new Node<T>{i+1,-1,i+1,NULL,NULL};
                tempC->next = nodo;
                tempC = nodo;
            }

            for (int i = 0; i < rows; i++){
                Node<T> *nodo = new Node<T>{-1,i+1,i+1,NULL,NULL};
                tempR->down = nodo;
                tempR = nodo;
            }
        }

        void set(int x, int y, T data){
            Node<T> *tempc = hColumns;
            Node<T> *tempr = hRows;

            if (x > columns || y > rows)
                throw out_of_range("Fuera de rango");

            while (tempc->data != x){tempc = tempc->next;}
            while (tempr->data != y){tempr = tempr->down;}

            Node<T> *colY = tempc, *prevY;

            if (tempr->next == NULL){
                if (data == 0){
                    return;
                }
                if (tempc->down == NULL){
                    Node<T> *temp = new Node<T>{x,y,data,NULL,NULL};
                    tempr->next = temp;
                    tempc->down = temp;
                    return; 
                }
                while (colY->down != NULL){
                    prevY = colY;
                    colY = colY->down;
                    if (colY->y > y){
                        Node<T> *nodo = new Node<T>{x,y,data,NULL,colY};
                        prevY->down = nodo;
                        tempr->next = nodo;
                        return;
                    }
                }
                Node<T> *nodo = new Node<T>{x,y,data,NULL,NULL};
                colY->down = nodo;
                tempr->next = nodo;
                return;
            }

            Node<T> *rowX = tempr, *prevX;

            while (rowX->next != NULL){
                prevX = rowX;
                rowX = rowX->next;
                if (rowX->x == x){
                    if (data == 0){
                        while (colY->down != NULL){
                            prevY = colY;
                            colY = colY->down;
                            if (colY->y == y){
                                break;
                            }
                        }
                        prevY->down = colY->down;
                        prevX->next = rowX->next;
                        delete rowX;
                        return;
                    }
                    rowX->data = data;
                    return;
                }
                if (rowX->x > x){
                    if (data == 0){
                        return;
                    }
                    Node<T> *nodo = new Node<T>{x,y,data,rowX,NULL};
                    prevX->next = nodo;
                    if (tempc->down == NULL){
                        tempc->down = nodo;
                        return;
                    }
                    while (colY->down != NULL){
                        prevY = colY;
                        colY = colY->down;
                        if (colY->x > x){
                            prevY->down = nodo;
                            nodo->down = colY;
                            return;
                        }
                    }
                    colY->down = nodo;
                    return;
                }
            }

            if (data == 0){
                return;
            }
            Node<T> *nodo = new Node<T>{x,y,data,NULL,NULL};
            rowX->next = nodo;
            if (tempc->down == NULL){
                tempc->down = nodo;
                return;
            }
            while (colY->down != NULL){
                prevY = colY;
                colY = colY->down;
                if (colY->y > y){
                    prevY->down = nodo;
                    nodo->down = colY;
                    return;
                }
            }
            colY->down = nodo;
            return;
        }

        T operator()(int x, int y){
            if (x>columns || y>rows){
                throw out_of_range("Fuera de rango");
            }

            Node<T> *r = hRows;
            while (r->data != y){
                r = r->down;
            }

            Node<T> *temp = r;
            while (temp->next != NULL){
                temp = temp->next;
                if (temp->x == x){
                    return temp->data;
                }else if (temp->x > x){
                    return 0;
                }
            }
            return 0;
        }

        /*void printRow(){
            Node<T>* aux=hRows;
            while (aux->down != NULL){
                Node<T> *aux2 = aux;
                cout<<aux->data<<"| ";
                while (aux2->next != NULL){
                    aux2 = aux2->next;
                    cout<<aux2->data<<" ";
                }
                cout<<endl;
                aux = aux->down;
            }
        }*/

        void print(){
            for (int i = 0; i < rows; ++i){
                for (int j = 0; j < columns; ++j){
                    cout<<(*this)(j,i)<<" ";
                }
                cout<<endl;
            }
        }
        
        Matrix<T> operator*(Matrix<T> other){
            if (columns != other.rows){
                throw out_of_range("Columnas de la matriz 1 es diferente de las filas de la matriz 2");
            }

            Matrix<T> resultado(rows,other.columns);

            for (int i = 0; i < other.columns; ++i){
                for (int j = 0; j < rows; ++j){
                    T tot = 0;
                    for (int k = 0; k < columns; ++k){
                        tot += ((*this)(k,i)*(other(j,k)));
                    }
                    resultado.set(j,i,tot);
                }
            }

            return resultado;
        }
        
        Matrix<T> operator*(T scalar){
            Matrix<T> resultado(columns,rows);
            Node<T> *tempR = hRows, *temp;

            for (int i = 0; i < rows; ++i){
                temp = tempR->next;
                while (temp != NULL){
                    resultado.set(temp->x,temp->y,temp->data * scalar);
                    temp = temp->next;
                }
                tempR = tempR->down;
            }

            return resultado; 
        }
        
        Matrix<T> operator+(Matrix<T> other){
            if (rows != other.rows || columns != other.columns){
                throw out_of_range("Matrices de diferentes dimensiones");
            }

            Matrix<T> resultado = (*this)*1;
            Node<T> *tempR = other.hRows;

            while (tempR->down != NULL){
                Node<T> *temp = tempR;
                while (temp->next != NULL){
                    temp = temp->next;
                    resultado.set(temp->x,temp->y, resultado(temp->x,temp->y)+ temp->data);
                }
                tempR = tempR->down;
            }

            return resultado;
        }
        
        Matrix<T> operator-(Matrix<T> other){
            if (rows != other.rows || columns != other.columns){
                throw out_of_range("Matrices de diferentes dimensiones");
            }

            Matrix<T> resultado = (*this)*1;
            Node<T> *tempR = other.hRows;

            while (tempR->down != NULL){
                Node<T> *temp = tempR;
                while (temp->next != NULL){
                    temp = temp->next;
                    resultado.set(temp->x,temp->y, resultado(temp->x,temp->y)- temp->data);
                }
                tempR = tempR->down;
            }

            return resultado;
        }
        
        Matrix<T> transposed(){
            Matrix resultado(rows,columns);
            Node<T> *tempR = hRows;

            while (tempR->down != NULL){
                Node<T> *temp = tempR;
                while (temp->next != NULL){
                    temp = temp->next;
                    resultado.set(temp->y,temp->x,temp->data);
                }
                tempR = tempR->down;
            }

            return resultado;
        }

        Matrix<T> operator=(Matrix<T> other){
            Matrix<T> resultado = (*this)*1;
            return resultado;
        }

        ~Matrix(){
            //
        }
};

#endif