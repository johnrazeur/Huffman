/**
	* \file Arbre.cpp
	* \brief Défénition de la classe arbre
	* \author Lafont Clément
	* \author Sanigou Alexandre
	* \version 0.1
	*/

/**
	* \class Arbre
	* \brief Classe représentant un arbre
	*/
class Arbre
{
	public:
			/**
			* \brief Constructeur
			*/
		Arbre();
			/**
			* \brief Constructeur
			* \param _parent : adresse de l'abre parent
			* \param _valeur : valeur de l'abre
			* \param _code : code de l'arbre
			*/
		Arbre(Arbre* _parent, int _valeur, char _code);
			/**
			* \brief Getter de l'arbre gauche
			* \return Adresse de l'arbre gauche si il existe, null sinon
			*/
		Arbre* getG();
			/**
			* \brief Getter de l'arbre droite
			* \return Adresse de l'arbre droite si il existe, null sinon
			*/
		Arbre* getD();
			/**
			* \brief Définit de l'arbre gauche
			*	\param arbre : Arbre à définir en tant qu'arbre gauche
			*/
		void setG(Arbre* arbre);
			/**
			* \brief Définit de l'arbre droit
			*	\param arbre : Arbre à définir en tant qu'arbre droit
			*/
		void setD(Arbre*);
			/**
			* \brief Getter de l'arbre parent
			* \return Adresse de l'arbre parent
			*/
		Arbre* getParent();
			/**
			* \brief Définit l'arbre parent
			* \param arbre : Arbre à définir en tant que parent
			*/
		void setParent(Arbre* arbre);
			/**
			* \brief Getter de la valeur
			* \return Valeur de l'arbre
			*/
		int getValeur();
			/**
			* \brief Définit la valeur
			* \param valeur : valeur à définir
			*/
		void setValeur(int valeur);
			/**
			* \brief Getter du code
			* \return Le code de l'arbre
			*/
		char getCode();
			/**
			* \brief Définit le code de l'arbre
			* \param _code : Le code de l'arbre
			*/
		void setCode(char _code);
			/**
			* \brief Vérifie si l'arbre est vide
			* \return true si l'arbre est vide, false sinon
			*/
		bool est_vide();
			/**
			* \brief Vérifie si l'arbre est racine
			* \return true si l'arbre est racine, false sinon
			*/
		bool estRacine();
			/**
			* \brief Vérifie si l'arbre est externe
			* \return true si l'arbre est externe, false sinon
			*/
		bool estExterne();
			/**
			* \brief Vérifie si l'arbre est interne
			* \return true si l'arbre est interne, false sinon
			*/
		bool estInterne();
			/**
			* \brief Affiche l'arbre croissant
			*/
		void affiche_croissant();
			/**
			* \brief Trouve une valeur donnée
			* \param valeur : la valeur à chercher
			* \return L'adresse de l'arbre trouvé
			*/
		Arbre* trouve_noeud(int valeur);
			/**
			* \brief Supprime les feuilles ayant une valeur donnée
			* \param valeur : la valeur des feuilles à supprimer
			*/
		void supprime_feuille(int valeur);
			/**
			* \brief Supprime les noeuds internes ayant une valeur donnée
			* \param valeur : la valeur des noeuds internes à supprimer
			*/
		void supprime_noeud_int(int valeur);
			/**
			* \brief Supprime les noeuds ayant une valeur donnée
			* \param valeur : la valeur des noeuds à supprimer
			*/
		void supprime_noeud(int valeur);
			/**
			* \brief Insert une feuille dans l'arbre
			* \param valeur : Valeur à insérer
			*/
		void insert_feuille(int valeur);
			/**
			* \brief Affiche l'arbre
			*/
		void print(int);

		void destruction(Arbre *);

	private:
		Arbre* parent;
		Arbre* ABR_G;
		Arbre* ABR_D;
		int valeur;
		char code;

};
