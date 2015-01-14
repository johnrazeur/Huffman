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
				Huffman *huff = new Huffman();

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

				map<char, string> tabHuffman = huff->getTabHuffman();

				ofstream out(argv[4], ofstream::binary);

				if(out)
				{
					string sortie = "";
					for(unsigned int i = 0; i < mot.length(); i++)
						sortie = sortie + tabHuffman[mot[i]];

					//unsigned char temp[8];

					string octet;
					vector<char> carac;
					unsigned int mort = 0;
					for(unsigned int i=0; i < sortie.length(); i++)
					{
						octet = octet + sortie[i];
						if((i+1)%8 == 0)
						{
							carac.push_back((char)bitset<8>(octet).to_ulong());
							octet = "";
						}
						else if(i == sortie.length()-1)
						{
							mort = (i+1)%8;
							for(unsigned int j=0; j < mort; j++)
								octet = octet+ "0";
							carac.push_back((char)bitset<8>(octet).to_ulong());
							octet = "";
						}
					}

					carac.insert(carac.begin(), (char)mort);

					for(unsigned i = 0; i < carac.size(); i++)
						out << carac[i];

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
				Huffman *huff = new Huffman();

				ifstream in(argv[2], ios::in);

				string result = "";
				int mort;
 
		        if(in)
		        {
	                char contenu;

	                in.get(contenu);

	                mort = (int) contenu;

	                
	                while(in.get(contenu))
	                	result = result + bitset<8>(contenu).to_string();
		        }
		        else
		            cerr << "Impossible d'ouvrir le fichier !" << endl;

		        string motcode = "";
		        for(unsigned int i=0; i < result.size()-mort-1; i++)
		        {
		        	motcode = motcode + result[i];
		        }

		        in.close();

				string decomp = huff->decompression(motcode);

				string nomfichier = argv[2];
				string fichier = "";

				for(unsigned int i=0; i < nomfichier.length(); i++)
				{
					if(nomfichier[i] == '.')
					{
						for(unsigned int j=0; j < i; j++)
							fichier = fichier + nomfichier[j];
						break;
					}
				}

				fichier = fichier + ".txt";

				ofstream out(fichier.c_str(), ios::out | ios::trunc);

				if(out)
				{
					out << decomp;
				}
				else
					cerr << "Impossible d'ouvrir le fichier !" << endl;
				out.close();
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
