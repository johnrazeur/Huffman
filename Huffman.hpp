/**
	* \file Huffman.cpp
	* \brief Définition de la classe Huffman
	* \author Lafont Clément
	* \author Sanigou Alexandre
	* \version 0.1
	*/

#include <cstring>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "Arbre.hpp"

using namespace std;


/**
	* \class Huffman
	* \brief Classe représentant un Huffman
	*/
class Huffman
{
	public:
		/**
			* \brief Constructeur
			* \param string : Le tableau de caractère
			*/
		Huffman(string);
		/**
			* \brief Définit le tableau de caractère
			* \param string : Le tableau de caractère
			*/
		void setTab(string);
		/**
			* \brief Getter du tableau de caractère
			* \return Le tableau de caractère
			*/
		string getTab();
		/**
			* \brief Getter de la fréquence du mot donné
			* \param string : Le mot à obtenir la fréquence
			* \return Le vecteur des fréquences
			*/
		vector<int> getFreq(string);

		vector<Arbre*> trier();

		Arbre * compression();

		void creerTab(Arbre *, string);

		map<char, string> getTabHuffman();
		
		void decompression(string code);
		
		//vector<string> getCodeBinaire();

	private:
		string tab;
		vector<int> freq;
		vector<Arbre*> trie;
		map<char, string> tabHuffman;
		vector<string> code_binaire;
		
		Arbre * arbre;

};
