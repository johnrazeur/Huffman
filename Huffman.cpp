#include "Huffman.hpp"

Huffman::Huffman()
{
	creerTabCarac();
	vector<string> _code_binaire(tab.length(), " ");
	code_binaire = _code_binaire;
	getFreq();
	trier();
	compression();
	creerTab(trie[0], "");
}

Huffman::~Huffman()
{
	for(unsigned int i=0; i < trie.size(); i++)
		trie[i]->destruction(trie[i]);

	arbre->destruction(arbre);
}

void Huffman::setTab(string str)
{
	tab = str;
}

string Huffman::getTab()
{
	return tab;
}

vector<int> Huffman::getFreq()
{
	string corp = "";

	ifstream corpus("autonomy.txt", ios::in);

    if(corpus)
    {
            string contenu;
            while(getline(corpus, contenu))
            {
            	corp = corp + contenu;
            }

            corpus.close();
    }
    else
            cerr << "Impossible d'ouvrir le fichier !" << endl;

	vector<int> _freq(tab.length(), 0);
	for(unsigned int i=0; i < corp.length(); i++)
	{
		for(unsigned int j=0; j < tab.length(); j++)
		{
			if(corp[i] == tab[j])
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
	for(unsigned int i = 0; i < trie.size()-1; i++)
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

string Huffman::decompression(string code)
{
	string caractere;
	string decomp = "";
	for(unsigned int i = 0; i < code.length(); i++)
	{
		caractere += code[i];
		//cout << caractere;
		for(unsigned int i = 0; i < code_binaire.size(); i++)
		{
			if(caractere == code_binaire[i])
			{
				//cout << "Correspondance : " << caractere << " | Indice : " << i << endl;
				decomp = decomp + tab[i];
				caractere = "";
				break;
			}
		}
	}

	return decomp;
}

void Huffman::creerTabCarac()
{
	for(unsigned int i=32; i <= 255; i++)
		tab = tab + (char) i;
}


