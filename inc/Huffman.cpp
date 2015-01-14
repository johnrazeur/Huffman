#include "Huffman.hpp"

Huffman::Huffman()
{
	//Création du tableau de caractères ASCII
	creerTabCarac();

	//Création du tableau de code binaire
	vector<string> _code_binaire(tab.length(), " ");
	code_binaire = _code_binaire;

	//Récupération des fréquences de chaque caractères du corpus
	getFreq();

	//Triage du vector en fonction du poid du caractère
	trier();

	//Création de l'arbre de fréquence
	compression();

	//Création du tableau de Huffman
	creerTab(trie[0], "");
}

Huffman::~Huffman()
{
	for(unsigned int i=0; i < trie.size(); i++)
		trie[i]->destruction(trie[i]);

	arbre->destruction(arbre);
}

//Récupération des fréquences de chaque caractères du corpus
vector<int> Huffman::getFreq()
{
	//Récupération du corpus dans le fichier
	string corp = "";
	ifstream corpus("corpus/autonomy.txt", ios::in);

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

	//Création du tableau de fréquence de caractères
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

//Fonction de comparaison de deux Arbres
bool comparaison(Arbre * i, Arbre * j)
{
	return (i->getValeur() < j->getValeur());
}

//Triage du tableau de fréquence
vector<Arbre*> Huffman::trier()
{
	//Récupération des caractères ayant une fréquence non-nulle
	for(unsigned int i = 0; i < freq.size(); i++)
	{
		if(freq[i] != 0)
		{
			Arbre * nArbre = new Arbre(NULL, freq[i], tab[i]);
			trie.push_back(nArbre);
		}
	}

	//Triage par ordre de poids
	sort(trie.begin(), trie.end(), comparaison);
	return trie;
}

//Création de l'arbre de fréquence
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

//Création du tableau de Huffman
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

//Décompression d'un texte
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

//Création du tableau de caractères ASCII
void Huffman::creerTabCarac()
{
	for(unsigned int i=32; i <= 255; i++)
		tab = tab + (char) i;
}

//Compression d'un fichier
void Huffman::fichierCompresse(string filein, string fileout)
{
	//Récupération du texte à compresser
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

    //Ecriture du texte compressé dans le fichier
	ofstream out(fileout.c_str(), ofstream::binary);
	if(out)
	{
		//Récupération du tableau de caractère
		string sortie = "";
		for(unsigned int i = 0; i < mot.length(); i++)
			sortie = sortie + tabHuffman[mot[i]];

		//Découpage de la suite de bits en octets
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
				//Définition du nombre de bits morts
				mort = 8 - ((i+1)%8);
				for(unsigned int j=0; j < mort; j++)
					octet = octet+ "0";

				carac.push_back((char)bitset<8>(octet).to_ulong());
			}
		}

		//Ajout du nombre de bits mort en début de fichier
		carac.insert(carac.begin(), (char)mort);

		//Ecriture des caractères compressés dans le fichier
		for(unsigned i = 0; i < carac.size(); i++)
			out << carac[i];

		out.close();
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
}

//Décompression d'un fichier
void Huffman::fichierDecompresse(string filein, string fileout)
{
	string result = "";
	int mort = 0;

	//Récupération du fichier compressé
	ifstream in(filein.c_str(), ios::in);
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

    //Suppression des bits morts
    string motcode = "";
    for(unsigned int i=0; i < result.size()-mort; i++)
    {
    	motcode = motcode + result[i];
    }

    //Décompression du texte
	string decomp = decompression(motcode);

	//Ecriture du texte décompressé dans le fichier
	ofstream out(fileout.c_str(), ios::out | ios::trunc);
	if(out)
	{
		out << decomp;
		out.close();
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
}


