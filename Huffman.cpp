#include "Huffman.hpp"

Huffman::Huffman(string str)
{
	tab = str;
	vector<string> _code_binaire(tab.length(), " ");
	code_binaire = _code_binaire;
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

Arbre * Huffman::compression()
{
	for(unsigned int i = 0; i < 2; i++)
	{
		if(trie[i]->getValeur() == trie[i+1]->getValeur() || trie[i]->getValeur() < trie[i+1]->getValeur())
		{
			Arbre * abr = new Arbre();
			abr->setValeur(trie[i]->getValeur() + trie[i+1]->getValeur());
			abr->setG(trie[i]);
			abr->setD(trie[i+1]);
			trie.erase(trie.begin()+i);
			trie[i] = abr;
			sort(trie.begin(), trie.end(), comparaison);
			i--;
		}
	}
	arbre = trie[0];
	return trie[0];
}

void Huffman::creerTab(Arbre * abr, string code)
{
	if(abr->estExterne() == false)
	{
		if(abr->getG() != NULL)
		{
			creerTab(abr->getG(), code + "0");
		}

		if(abr->getD() != NULL)
		{
			creerTab(abr->getD(), code + "1");
		}
	}
	else
	{
		for(unsigned int i = 0; i < tab.length(); i++)
		{
			if(tab[i] == abr->getCode())
			{
				tabHuffman[abr->getCode()] = code;
				code_binaire[i] = code;
				break;
			}
		}
	}
}

map<char, string> Huffman::getTabHuffman()
{
	return tabHuffman;
}

//vector<string> Huffman::getCodeBinaire()
//{
//	return code_binaire;
//}

void Huffman::decompression(string code)
{
	string caractere;
	for(unsigned int i = 0; i < code.length(); i++)
	{
		caractere += code[i];
		//cout << caractere;
		for(unsigned int i = 0; i < code_binaire.size(); i++)
		{
			if(caractere == code_binaire[i])
			{
				//cout << "Correspondance : " << caractere << " | Indice : " << i << endl;
				cout << tab[i];
				caractere = "";
				break;
			}
		}
	}
}


