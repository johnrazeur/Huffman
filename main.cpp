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
				string tab = "abcdefghijklmnopqrstuvwxyz_";

				Huffman *huff = new Huffman(tab);

				string mot = "";

				ifstream in(argv[2], ios::in);
 
		        if(in)
		        {
		                string contenu;
		                while(getline(in, contenu))
		                {
		                	mot = mot + contenu;
		                }
		 
		                in.close();
		        }
		        else
		                cerr << "Impossible d'ouvrir le fichier !" << endl;

				vector<int> freq = huff->getFreq(mot);

				vector <Arbre*> trie = huff->trier();
				Arbre * comp = huff->compression();
				huff->creerTab(comp, "");
				map<char, string> tabHuffman = huff->getTabHuffman();

				ofstream out(argv[4], ios::out | ios::trunc);

				if(out)
				{
					for(unsigned int i = 0; i < mot.length(); i++)
					{
						out << tabHuffman[mot[i]];
					}

					out.close();
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
		else if(strcmp(argv[1], "-x") == 0)
		{
			if(argc > 2)
			{
				string tab = "abcdefghijklmnopqrstuvwxyz_";

				Huffman *huff = new Huffman(tab);

				string motcode = "";
				
				ifstream in(argv[2], ios::in);
 
		        if(in)
		        {
		                string contenu;
		                while(getline(in, contenu))
		                {
		                	motcode = motcode + contenu;
		                }
		 
		                in.close();
		        }
		        else
		                cerr << "Impossible d'ouvrir le fichier !" << endl;
		            
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
