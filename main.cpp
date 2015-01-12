/**
	* \file main.cpp
	* \brief Fichier principal
	* \author Lafont Clément
	* \author Sanigou Alexandre
	* \version 0.1
	*/

#include <iostream>
#include <fstream>
#include "Huffman.hpp"

using namespace std;

int main(int argc, char *argv[])
{

	if(argc > 1)
	{
		if(argv[1] == "--help")
		{
			cout << "Paramètres :" <<endl;
			cout << "-c [filein] -o [fileout.hff] : Compresse le fichier [filein]" << endl;
			cout << "-x [filein.hff] : Décompresse le fichier [fileing.hff]" << endl;
		}
		else if(argv[1] == "-c")
		{
			if(argc > 4)
			{
				string tab = "abcdefghijklmnopqrstuvwxyz_";

				Huffman *huff = new Huffman(tab);

				string mot = "anticonstitutionnellement";

				vector<int> freq = huff->getFreq(mot);

				vector <Arbre*> trie = huff->trier();
				Arbre * comp = huff->compression();
				huff->creerTab(comp, "");
				map<char, string> tabHuffman = huff->getTabHuffman();

				ofstream fichier($argv[4], ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert

				if(fichier)
				{
					for(unsigned int i = 0; i < mot.length(); i++)
					{
						fichier << tabHuffman[mot[i]];
					}

					fichier.clcoose();
				}
				else
					cerr << "Impossible d'ouvrir le fichier !" << endl;

			}
			else
			{
				cout << "Utilisation de -c :" << endl;
				cout << "-c [filein] -o [fileout.hff] : Compresse le fichier [filein]" << endl;
			}
		}
		else if(argv[1] == "-x")
		{
			if(argc > 2)
			{
				string motcode = "110000001101110011110001111110110101111100110111100000100110111011001111101000001";
				huff->decompression(motcode);
			}
			else
			{
				cout << "Utilisation de -x:" << endl;
				cout << "-x [filein.hff] : Décompresse le fichier [fileing.hff]" << endl;
			}
		}
	}
	else
	{
		cout << "Pas de paramètres" << endl;
		cout << "Faite --help pour de l'aide" << endl;
	}








}
