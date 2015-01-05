#include <iostream>
#include <iomanip>
#include "Arbre.hpp"

using namespace std;

Arbre::Arbre() : parent(NULL), ABR_G(NULL), ABR_D(NULL), valeur(0)
{}

Arbre::Arbre(Arbre* _parent, int _valeur) : parent(_parent),  ABR_G(NULL), ABR_D(NULL), valeur(_valeur)
{}

Arbre* Arbre::getG()
{
  //if(!est_vide())
    return ABR_G;
}

Arbre* Arbre::getD()
{
  //if(!est_vide())
    return ABR_D;
}

void Arbre::setG(Arbre* arbre)
{
  ABR_G = arbre;
  arbre->setParent(this);
}

void Arbre::setD(Arbre* arbre)
{
  ABR_D = arbre;
  arbre->setParent(this);
}

Arbre* Arbre::getParent()
{
  return parent;
}

void Arbre::setParent(Arbre* arbre)
{
  parent = arbre;
}

int Arbre::getValeur()
{
  return valeur;
}

void Arbre::setValeur(int _valeur)
{
  valeur = _valeur;
}

bool Arbre::est_vide()
{
  return valeur == 0;
}

bool Arbre::estRacine()
{
  return parent == NULL;
}

bool Arbre::estExterne()
{
  return (ABR_G == NULL && ABR_D == NULL);
}

bool Arbre::estInterne()
{
  return ((ABR_G != NULL || ABR_D != NULL) && parent != NULL);
}

void Arbre::affiche_croissant()
{
  if(getG() != NULL)
    getG()->affiche_croissant();
  cout << getValeur() << endl;
  if(getD() != NULL)
    getD()->affiche_croissant();
}

Arbre* Arbre::trouve_noeud(int valeur)
{

  if(getValeur() == valeur)
    return this;

  if(valeur >= getValeur())
  {
    if(getD() == NULL)
      return getD()->trouve_noeud(valeur);
  }
  else
  {
    if(getG() == NULL)
      return getG()->trouve_noeud(valeur);
  }
  return NULL;
}

void Arbre::supprime_feuille(int valeur)
{
  Arbre* p_donnee = trouve_noeud(valeur);
  if(p_donnee->estExterne())
  {
    Arbre* p_parent = p_donnee->getParent();
    if(p_donnee->getValeur() > valeur)
      p_parent->setG(NULL);
    else
      p_parent->setD(NULL);
  }
}

void Arbre::supprime_noeud_int(int valeur)
{
  Arbre* fils;
  Arbre* parent;
  Arbre* noeudTrouve = trouve_noeud(valeur);
  if((noeudTrouve->estInterne()) and ((noeudTrouve->getG() == NULL) xor (noeudTrouve->getD() == NULL)))
  {
    if(noeudTrouve->est_vide())
      fils = noeudTrouve->getD();
    else
      fils = noeudTrouve->getG();
    parent = noeudTrouve->getParent();
    if(parent->getValeur() > valeur)
      parent->setG(fils);
    else
      parent->setD(fils);
  }
}

void Arbre::supprime_noeud(int valeur)
{
  Arbre* fils;
  Arbre* noeud = trouve_noeud(valeur);
  supprime_feuille(valeur);
  supprime_noeud_int(valeur);
  if((noeud->getD() != NULL) != (noeud->getD() != NULL))
  {
    fils = noeud->getG();
    while(fils->getD() != NULL)
      fils = fils->getD();
    noeud->setValeur(fils->getValeur());
    if(fils->estInterne())
      noeud->setD(fils->getG());
    fils->getParent()->setD(NULL);
  }
}

void Arbre::insert_feuille(int valeur)
{

    if(valeur >= getValeur())
    {
      if(getD() != NULL)
      {
        getD()->insert_feuille(valeur);
      }
      else
      {
        Arbre* newArbre  = new Arbre(this, valeur);
        setD(newArbre);
      }
    }
    else
    {
      if(getG() != NULL)
      {
        getG()->insert_feuille(valeur);
      }
      else
      {
        Arbre* newArbre = new Arbre(this, valeur);
        setG(newArbre);
      }
    }

}

void Arbre::print(int i)
{
  cout << setw(i);
  cout << getValeur();
  if(getG() != NULL)
    getG()->print(i-5);
  if(getD() != NULL)
    getD()->print(i+5);
}
