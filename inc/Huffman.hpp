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
#include <bitset>
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
			*/
		Huffman();
			/**
			* \brief Destructeur
			*/
		~Huffman();
		/**
			* \brief Getter de la fréquence du mot donné
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
			* \brief Décompresse la chaine de caractère
			* \param code : La chaine de caractère à décompresser
			*/
		string decompression(string code);
		/**
			* \brief Créer la table des caratères ASCII
			*/
		void creerTabCarac();
		/**
			* \brief Lit un fichier et compresse son contenu dans un autre fichier
			* \param string : Le nom du fichier d'entrée
			* \param string : Le nom du fichier de sortie
			*/
		void fichierCompresse(string, string);
		/**
			* \brief Décopresse un fichier et renvoi le résultat dans un autre fichier
			* \param string : Le nom du fichier d'entrée
			* \param string : Le nom du fichier de sortie
			*/
		void fichierDecompresse(string, string);

	private:
		string tab;
		vector<int> freq;
		vector<Arbre*> trie;
		map<char, string> tabHuffman;
		vector<string> code_binaire;

		Arbre * arbre;

};
