/**
	* \file main.cpp
	* \brief Fichier principal
	* \author Lafont Clément
	* \author Sanigou Alexandre
	* \version 0.1
	*/

#include <iostream>
#include <fstream>
#include <bitset>
#include "inc/Huffman.hpp"

using namespace std;

int main(int argc, char *argv[])
{

	if(argc > 1)
	{
		if(strcmp(argv[1], "--help") == 0)
		{
			cout << "Paramètres :" <<endl;
			cout << "-c [filein] -o [fileout.hff] : Compresse le fichier [filein]" << endl;
			cout << "-x [filein.hff] : Décompresse le fichier [fileing.hff]" << endl;
		}
		else if(strcmp(argv[1], "-c") == 0)
		{
			if(argc > 4)
			{
				Huffman *huff = new Huffman();

				
				string filein = "in/" + string(argv[2]);
				string fileout = "out/" + string(argv[4]);

				huff->fichierCompresse(filein, fileout);
			}
			else
			{
				cout << "Utilisation de -c :" << endl;
				cout << "-c [filein] -o [fileout.hff] : Compresse le fichier [filein]" << endl;
			}
		}
		else if(strcmp(argv[1], "-x") == 0)
		{
			if(argc > 3)
			{
				Huffman *huff = new Huffman();
				
				string filein = "in/" + string(argv[2]);
				string fileout = "out/" + string(argv[3]) + ".txt";
				huff->fichierDecompresse(filein, fileout);
			}
			else
			{
				cout << "Utilisation de -x:" << endl;
				cout << "-x [filein.hff] [fileout] : Décompresse le fichier [fileing.hff] dans le fichier [fileout].txt" << endl;
			}
		}
	}
	else
	{
		cout << "Pas de paramètres" << endl;
		cout << "Faite --help pour de l'aide" << endl;
	}

}
