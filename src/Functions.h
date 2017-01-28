/*************************************************************************************\
*	Elaborato_ASD 
*
*	Programmers ---> Eugenio - Mauro - Ludovico
*
*	Functions.h
\*************************************************************************************/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

													/* PROTOPI FUNZIONI */

bool read_file(string& input_string, string input_file); // Apertura e lettura del file di input, la funzione ha 2 parametri ---> 1. la stinga in cui si vuole memorizzare il contenuto del file in input 2. il nome/percorso del file
bool write_file(string output_string, string output_file); // Creazione e scrittura del file di output, la funzione ha 2 parametri ---> 1. la stinga contenente l'output da salvare sul file  2. il nome del file da creare (percorso compreso)
void getNumber(int* choice); // Si occupa di prendere un numero da tastiera, contolla la validità del numero inserito e lo attribuisce al parametro choice
size_t find_comma(string input_string); // Trova la posizione della virgola tra 2 operandi ---> la funzione prende in input la stringa da elaborare -- la funzione restituisce la posizione della virgola cercata, e 0 se non sono presenti virgole tra gli operandi
bool derivative(string input_string, string& output_string); // Calcolo della derivata, la funzione ha 2 parametri ---> 1. la stringa di testo da elaborare  2. la stringa contenente il risultato della derivazione -- restituisce 1 in caso di errore e 0 se il calcolo della derivata ha avuto successo