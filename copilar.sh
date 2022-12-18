#!/bin/bash


g++ "ej${1}.cpp"
./a.out < Entrada/$1a.in > SalidaPrueba/${1}a.out
meld Salida/${1}a.out SalidaPrueba/${1}a.out
