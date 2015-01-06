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

vector<int> Huffman::getFreq(string mot)
{
	vector<int> _freq(tab.length(), 0);
	for(unsigned int i=0; i < mot.length(); i++)
	{
		for(unsigned int j=0; j < tab.length(); j++)
		{
			if(mot[i] == tab[j])
			{
				//cout << mot.length() << " ||| " << tab[j] << endl;
				_freq[j]++;
				break;
			}
		}
	}
	freq = _freq;
	return freq;
}

bool comparaison(Arbre * i, Arbre * j)
{
	return (i->getValeur() < j->getValeur());
}

vector<Arbre*> Huffman::trier()
{
	for(unsigned int i = 0; i < freq.size(); i++)
	{
		if(freq[i] != 0)
		{
			Arbre * nArbre = new Arbre(NULL, freq[i], tab[i]);
			trie.push_back(nArbre);
		}
	}
	sort(trie.begin(), trie.end(), comparaison);
	return trie;
}

vector<Arbre*> Huffman::compression()
{
	for(unsigned int i = 0; i < trie.size()-1; i++)
	{
		if(trie[i]->getValeur() == trie[i+1]->getValeur())
		{
			Arbre * abr = new Arbre();
			abr->setValeur(trie[i+1]->getValeur() + trie[i+1]->getValeur());
			abr->setG(trie[i]);
			abr->setD(trie[i+1]);
			trie.erase(trie.begin()+i);
			trie[i] = abr;
		}
	}

	return trie;
}


