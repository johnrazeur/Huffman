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
#include <fstream>
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
		Huffman();
			/**
			* \brief Destructeur
			*/
		~Huffman();
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
		vector<int> getFreq();
		/**
			* \brief Trie le tableau d'arbre
			* \return Le vector d'arbre trié
			*/
		vector<Arbre*> trier();
		/**
			* \brief Génère l'arbre trié
			* \return L'arbre trié
			*/
		Arbre * compression();
		/**
			* \brief Créer la table de Huffmane
			* \param Arbre * : L'arbre pour générer le tableau d'huffman
			* \param string : Le mot à compresser
			*/
		void creerTab(Arbre *, string);
		/**
			* \brief Getter de tabHuffman
			* \return La map "map<char, string>" de tabHuffman
			*/
		map<char, string> getTabHuffman();
		/**
			* \brief Décompresse la chaine de caractère
			* \param code : La chaine de caractère à décompresser
			*/
		string decompression(string code);

		void creerTabCarac();

	private:
		string tab;
		vector<int> freq;
		vector<Arbre*> trie;
		map<char, string> tabHuffman;
		vector<string> code_binaire;

		Arbre * arbre;

};
