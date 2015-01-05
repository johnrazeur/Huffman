#include "Huffman.hpp"

Huffman::Huffman(string str)
{
	tab = str;
}

void Huffman::setTab(string str)
{
	tab = str;
}

string Huffman::getTab()
{
	return tab;
}

int * Huffman::getFreq(string mot)
{
	for(unsigned int i=0; i < mot.length(); i++)
	{
		for(unsigned int j=0; j < tab.length(); j++)
		{
			if(mot[i] == tab[j])
			{
				cout << mot.length() << " ||| " << tab[j] << endl;
				(freq[j])++;
				break;
			}
		}
		cout << "ok";
	}
	
	return *freq;
}
