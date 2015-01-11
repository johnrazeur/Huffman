/**
	* \file main.cpp
	* \brief Fichier principal
	* \author Lafont Clément
	* \author Sanigou Alexandre
	* \version 0.1
	*/

#include <iostream>
#include "Huffman.hpp"

using namespace std;

int main()
{
	/*Arbre *arbre = new Arbre(NULL, 14);
	Arbre *arbreg = new Arbre(arbre, 6);
	Arbre *arbred = new Arbre(arbre, 17);
	arbre->setD(arbred);
	arbre->setG(arbreg);
	arbre->insert_feuille(7);*/
	//arbre->affiche_croissant();
	//arbre->print(20);

	string tab = "abcdefghijklmnopqrstuvwxyz_";

	Huffman *huff = new Huffman(tab);
	
	string mot = "anticonstitutionnellement";

	vector<int> freq = huff->getFreq(mot);

	//cout << freq[13];
 	vector <Arbre*> trie = huff->trier();
 	Arbre * comp = huff->compression();
 	huff->creerTab(comp, "");
	 

 	map<char, string> tabHuffman = huff->getTabHuffman();
 	/*for(unsigned int i = 0; i < mot.length(); i++)
	{
		cout << tabHuffman[mot[i]];
	}*/
	
	string motcode = "110000001101110011110001111110110101111100110111100000100110111011001111101000001";
	
	huff->decompression(motcode);

}
