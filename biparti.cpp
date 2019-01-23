#include <iostream>                                                    
#include <vector>
#include <algorithm>
#include <iterator>
#include <queue>
#include <time.h>
using namespace std;


/**
	g++ -std=c++11 biparti.cpp

	graphe : num du noeud puis sa liste d adjacence
	Exemple :
	0 1 3
	1 2 0
	2 1
	3 0


	Soit F une file vide
	Colorier s en rouge et l’enfiler dans F
	Tant que la file F n’est pas vide

		Défiler F dans x
		Si x est rouge alors pour tout sommet a adjacent à x
			Si a est rouge alors renvoyer faux
			sinon, si a n’est pas colorié, alors le colorier en vert et l’enfiler dans F
		
		Si x est vert alors pour tout sommet a adjacent à x
			Si a est vert alors renvoyer faux
			sinon, si a n’est pas colorié, alors le colorier en rouge et l’enfiler dans F
*/

typedef vector<vector<int> > graphe;

bool rep(vector<int> l,int _ran) { //verifie si il y a un doublon dans la liste d adjacence
	for(int i=0;i<l.size();i++) {
		if(l[i] == _ran) {
			return true;
		}
	}
	return false;
}

bool rep2(vector<int> l,int _ran) { //verifie si il y a un doublon dans la liste d adjacence
	for(int i=1;i<l.size();i++) {
		if(l[i] == _ran) {
			return true;
		}
	}
	return false;
}



graphe genererG(int nb_l) {
	graphe g;
	int _ran(0);
	g.resize(nb_l);
	//vector<int> v;//vector pour que le graphe soit non oriente
	for(int i=0;i<nb_l;i++) {
		//g[i].resize(rand()%5+2);
		g[i].push_back(i);
	}

	for(int i=0;i<nb_l;i++) {
		int nb_aretes = rand()%5+2;
		for(int j=g[i].size();j<nb_aretes;j++) {
			do {
				_ran = rand()%nb_l;
			}while(rep(g[i],_ran)); //pour pas de repetitions
		
			g[i].push_back(_ran);
			if(!rep2(g[_ran],g[i][0]))//pour que le graphe soit non oriente
				g[_ran].push_back(g[i][0]);
		}
	}
	return g;
}

void afficher_v(const vector<int>& v) {
	for(int i=0;i<v.size();i++)
		cout << v[i] << endl;
}

void afficher_g(const graphe& g) {
	int nb_l = g.size();
	for(int i=0;i<nb_l;i++) {
		for(int j=0;j<g[i].size();j++)
			cout << g[i][j] << ' ';
		cout << endl;
	}
}


//-1 pas colorié, 0 rouge, 1 vert
bool isBIP(const graphe& g) {
	int nb_l, nb_c;
	nb_l = g.size();
	queue<int> F;
	vector<int> bicolor(nb_l,-1);
	bicolor[0] = 0; //colorie en rouge
	F.push(0);
	while(!F.empty()) {
		int x = F.front();
		F.pop();
		///cout << "TOT : " << bicolor[x] << endl;
		///cout << x << " : ";
		if(bicolor[x] == 0) { //rouge
			for(int i=1; i<g[x].size();i++) {
				
				///cout << g[x][i] << " ";
				//cout << bicolor[g[x][i]] << endl;
				if(bicolor[g[x][i]] == 0) {
					return false;
				}

				else if(bicolor[g[x][i]] == -1) {
					///cout << "JE SSUIS : " << bicolor[x] << endl;
					///cout << "gxi : " << g[x][i] << endl;
					///cout << "bicxi : " << bicolor[g[x][i]] << endl;
					bicolor[g[x][i]] = 1;
					///cout << "bicxi : " << bicolor[g[x][i]] << endl;
					F.push(g[x][i]);
				}

			}
		}
		else if(bicolor[x] == 1) { //vert
			///cout << "TOOTTOTO";
			for(int i=1; i<g[x].size();i++) {
				///cout << g[x][i] << " ";
				//cout << bicolor[g[x][i]] << endl;
				if(bicolor[g[x][i]] == 1) {
					return false;
				}
				else if(bicolor[g[x][i]] == -1) {
					bicolor[g[x][i]] = 0;
					F.push(g[x][i]);
				}

			}
		}
		///cout << endl;
	}
	cout << "Premier ensemble :" << endl;
	for(int k=0;k<bicolor.size();k++) {
		if(bicolor[k] == 0) {
			cout << g[k][0] << " :";
			for(int l = 1; l < g[k].size();l++)
				cout << g[k][l] << " ";
			cout << endl;
		}
	}
	cout << endl << "Deuxième ensemble :" << endl;
	for(int k=0;k<bicolor.size();k++) {
		if(bicolor[k] == 1) {
			cout << g[k][0] << " :";
			for(int l = 1; l < g[k].size();l++)
				cout << g[k][l] << " ";
			cout << endl;
		}
	}
	cout << endl;
	//afficher_v(bicolor);
	return true;
}



int main() {
	srand(time(NULL));
	graphe gg = genererG(10);
	cout << "graphe aléatoire :" << endl;
	afficher_g(gg);

	cout << "------------" << endl;


	graphe g;// GRAPHE BIPARTI
	g.resize(7);
	g[0].push_back(0);
	g[0].push_back(4);
	g[0].push_back(5);
	g[1].push_back(1);
	g[1].push_back(5);
	g[2].push_back(2);
	g[2].push_back(6);
	g[3].push_back(3);
	g[3].push_back(5);
	g[3].push_back(6);
	g[4].push_back(4);
	g[4].push_back(0);
	g[5].push_back(5);
	g[5].push_back(0);
	g[5].push_back(1);
	g[5].push_back(3);
	g[6].push_back(6);
	g[6].push_back(2);
	g[6].push_back(3);
	cout << "graphe biparti créé manuellement :" << endl;
	afficher_g(g);
	cout << "------------" << endl;

	cout << "------------" << endl;
	cout << "le graphe aléatoire est-il biparti ? " << isBIP(gg) << endl << endl;
	cout << "------------ Second graphe ------------" << endl << endl;
	cout << "le graphe manuel est-il biparti ? " << isBIP(g) << endl;
	
	return 0;
}
