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

string Huffman::decompression(string code)
{
	string caractere;
	string decomp = "";
	for(unsigned int i = 0; i < code.length(); i++)
	{
		caractere += code[i];

		for(unsigned int i = 0; i < code_binaire.size(); i++)
		{
			if(caractere == code_binaire[i])
			{
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

void Huffman::fichierCompresse(string filein, string fileout)
{
	string mot = "";
	ifstream in(filein.c_str(), ios::in);

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

	ofstream out(fileout.c_str(), ofstream::binary);

	if(out)
	{
		string sortie = "";
		for(unsigned int i = 0; i < mot.length(); i++)
			sortie = sortie + tabHuffman[mot[i]];

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
				mort = 8 - ((i+1)%8);
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

void Huffman::fichierDecompresse(string filein, string fileout)
{
	ifstream in(filein.c_str(), ios::in);

	string result = "";
	int mort = 0;

    if(in)
    {
        char contenu;
        in.get(contenu);
        mort = (int) contenu;
        
        while(in.get(contenu))
        	result = result + bitset<8>(contenu).to_string();

        in.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;

    string motcode = "";
    for(unsigned int i=0; i < result.size()-mort; i++)
    {
    	motcode = motcode + result[i];
    }

	string decomp = decompression(motcode);

	ofstream out(fileout.c_str(), ios::out | ios::trunc);

	if(out)
	{
		out << decomp;
		out.close();
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
}


