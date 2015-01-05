/**
	* \file Huffman.cpp
	* \brief Définition de la classe Huffman
	* \author Lafont Clément
	* \author Sanigou Alexandre
	* \version 0.1
	*/
	
#include <cstring>
#include <iostream>

using namespace std;


/**
	* \class Huffman
	* \brief Classe représentant un Huffman
	*/
class Huffman
{
	public:
		Huffman(string);
		void setTab(string);
		string getTab();
		int * getFreq(string);
		
	
	
	private:
		string tab;
		int *freq[];
	
};
