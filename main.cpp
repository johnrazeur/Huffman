/**
	* \file main.cpp
	* \brief Fichier principal
	* \author Lafont Clément
	* \author Sanigou Alexandre
	* \version 0.1
	*/

#include <iostream>
#include "Arbre.hpp"

using namespace std;

int main()
{
	Arbre *arbre = new Arbre(NULL, 14);
	Arbre *arbreg = new Arbre(arbre, 6);
	Arbre *arbred = new Arbre(arbre, 17);
	arbre->setD(arbred);
	arbre->setG(arbreg);
	arbre->insert_feuille(7);
	//arbre->affiche_croissant();
	arbre->print(20);

}
