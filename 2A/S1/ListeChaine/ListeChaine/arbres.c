#pragma once
#include "arbres.h"
#include "affichage.h"
#include <stdio.h>
#include <stdlib.h>
//0 - char-!avl   1 - int-avl
treeNode * creerNoeudArbre(void* p_value, char type, char avl) {
	
	treeNode* noeud = (treeNode*)calloc(1, sizeof(*noeud));

	if (!noeud) {
		printf("Erreur lors de l'allocation de list ou node.\n");
		return NULL;
	}
	if (type != 0 && type != 1) {
		print("Veuillez sp�cifier le type correctement :\n- 0 : char\n- 1 : int\n");
		return NULL;
	}
	noeud->avl = avl;
	noeud->type = type;	
	noeud->m_data = p_value;	
	noeud->m_left = NULL;
	noeud->m_right = NULL;

	return noeud;
}

void libererArbre(treeNode ** p_ppRoot) {

	if (!(*p_ppRoot)) {
		return;
	}
	libererArbre(&((*p_ppRoot)->m_left));
	libererArbre(&((*p_ppRoot)->m_right));	
	free(*p_ppRoot);
	*p_ppRoot = NULL;
	return;
}

void ajoutGauche(treeNode * p_pRoot, void* p_value, char type) {

	if (!p_pRoot) {
		print("Le noeud n'�xiste pas\n");
		return;
	}
	if (p_pRoot->m_left) {
		ajoutGauche(p_pRoot->m_left, p_value, type);
		return;
	}
	p_pRoot->m_left = creerNoeudArbre(p_value, type, p_pRoot->avl);

}

void ajoutDroite(treeNode * p_pRoot, void* p_value, char type) {

	if (!p_pRoot) {
		print("Le noeud n'�xiste pas\n");
		return;
	}
	if (p_pRoot->m_right) {
		ajoutDroite(p_pRoot->m_right, p_value, type);
		return;
	}
	p_pRoot->m_right = creerNoeudArbre(p_value, type, p_pRoot->avl);	
}

int hauteur(treeNode * p_pRoot) {

	if (!p_pRoot || (!p_pRoot->m_left) && (!p_pRoot->m_right)) {
		return 0;
	}
	int a = hauteur(p_pRoot->m_left);
	int b = hauteur(p_pRoot->m_right);
	
	return (a > b) ? a + 1: b + 1;
}

int taille(treeNode * p_pRoot) {

	if (!p_pRoot) {
		return 0;		
	}
	return taille(p_pRoot->m_left) + 1 + taille(p_pRoot->m_right);
}

int nbFeuilles(treeNode * p_pRoot) { 
	
	if (!p_pRoot) {
		return 0;
	}
	int a = 0, b = 0;
	if (!p_pRoot->m_left && !p_pRoot->m_right) {
		return 1;
	}
	a = nbFeuilles(p_pRoot->m_left);
	b = nbFeuilles(p_pRoot->m_right);
	return a + b;
}

void supprSousArbre(treeNode ** p_ppRoot, int p_value) { 

	if (!(*p_ppRoot) ) {
		return;
	}
	if ((int)((*p_ppRoot)->m_data) == p_value) {
		libererArbre(&(*p_ppRoot));
		return;
	}
	supprSousArbre(&(*p_ppRoot)->m_left, p_value);
	supprSousArbre(&(*p_ppRoot)->m_right, p_value);
}
void afficher_noeud(treeNode * p_pRoot) {
	if (!p_pRoot) {
		return;
	}
	if (p_pRoot->type == 1) {
		printf("[%d]", (int)p_pRoot->m_data);
	}
	else {
		printf("\"%c\"", (char)p_pRoot->m_data);
	}
}

void parcoursPrefixe(treeNode * p_pRoot) {

	if (p_pRoot) {	
		afficher_noeud(p_pRoot);
		if (p_pRoot->m_left) {
			parcoursPrefixe(p_pRoot->m_left);
		}
		if (p_pRoot->m_right) {
			parcoursPrefixe(p_pRoot->m_right);
		}
	}
}

void parcoursInfixe(treeNode * p_pRoot) {

	if ((!p_pRoot->m_left) && (!p_pRoot->m_right)) {
		afficher_noeud(p_pRoot);
		return;
	}
	if (p_pRoot->m_left) {
		parcoursInfixe(p_pRoot->m_left);
	}
	afficher_noeud(p_pRoot);
	if (p_pRoot->m_right) {
		parcoursInfixe(p_pRoot->m_right);
	}
}

void parcoursPostfixe(treeNode * p_pRoot) {

	if ((!p_pRoot->m_left) && (!p_pRoot->m_right)) {
		afficher_noeud(p_pRoot);
		return;
	}
	if (p_pRoot->m_left) {
		parcoursPostfixe(p_pRoot->m_left);
	}	
	if (p_pRoot->m_right) {
		parcoursPostfixe(p_pRoot->m_right);		
	}
	afficher_noeud(p_pRoot);
}

void afficher_Arbre(treeNode * p_pRoot, int profondeur) {
	if (!p_pRoot) {			
		return;
	}
	int i = 0;
	afficher_Arbre(p_pRoot->m_right, profondeur + 1);
	for (i = 0; i < profondeur; i++) {
		printf("    ");
	}
	afficher_noeud(p_pRoot);
	printf("\n");
	afficher_Arbre(p_pRoot->m_left, profondeur + 1);	
}

void affichage_propre(char* message, treeNode * p_pRoot) {
	int i, profondeur = hauteur(p_pRoot);
	print(message);	
	
	for (i = 0; i < 4 * (profondeur + 1); i++) {
		printf("-");
	}
	printf("\n");
	afficher_Arbre(p_pRoot, 0);
	for (i = 0; i < 4 * (profondeur + 1); i++) {
		printf("-");
	}
	printf("\n");
}
void test_Arbre() {

	treeNode * arbre = creerNoeudArbre((void *)1, 1, 0);
	ajoutGauche(arbre, 2, 1);
	ajoutGauche(arbre, 3, 1);
	ajoutDroite(arbre->m_left, 4, 1);

	ajoutDroite(arbre, '5', 0);
	ajoutDroite(arbre, 7, 1);
	ajoutGauche(arbre->m_right, 6, 1);
	affichage_propre("arbre\n", arbre);
	printf("L'arbre est de hauteur : %d\n", hauteur(arbre));
	printf("L'arbre est de taille : %d\n", taille(arbre));
	printf("L'arbre a %d feuilles\n", nbFeuilles(arbre));

	supprSousArbre(&arbre, 1);
	affichage_propre("arbre apr�s supression\n", arbre);

	libererArbre(&arbre);	
	return;
}