#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

struct Street{
    pair<int,int> intersect;
    string name;
    int time;
};

struct Car{
    vector<string> route;
    vector<int> intersections;
    int position = 0; //comença al principi
};

struct Intersection{
    vector<string> entrades;
    vector<string> sortides;
    int ID;
};

vector<int> mostTraffic(const vector<Car>& cars, Intersection inter){
	int n = inter.entrades.size();
	vector<int> res(n, 0);
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < cars.size(); ++j){
			for (int k = 0; k < cars[j].route.size(); ++k){
				if (cars[j].route[k] == inter.entrades[i]) ++res[i];
			}
		}
	}
	return res;
}

void calcular(const vector<Car>& cars, const vector<Intersection>& intersections) {
  
	int size = intersections.size();
  	cout << size << endl;
	for(int i = 0; i < size; ++i) {
      
		int n_entrades = intersections[i].entrades.size();
		int n_sortides = intersections[i].sortides.size();

		if(n_entrades == 1){
			cout << intersections[i].ID << endl << "1" << endl;
			cout << intersections[i].entrades[0] << " 1" << endl;
		}
		else {
			vector<int> vegades = mostTraffic(cars, intersections[i]);
			int den = 0;
			for (int i = 0; i < vegades.size(); ++i) den += vegades[i];
            vector<double> proporcions(size);
            for (int i = 0; i < size; ++i) proporcions[i] = vegades[i] / den;
            double least = 100000.0;
            for (int i = 0; i < proporcions.size(); ++i){
            	if (proporcions[i] < least) least = proporcions[i];
            }
            vector<int> cicles(size);
          	for (int i = 0; i < size; ++i) cicles[i] = int(ceil(proporcions[i] / least));
              
            // OUTPUT
            cout << intersections[i].ID << endl << proporcions.size() << endl;
			for (int i = 0; i < intersections[i].entrades.size(); ++i){
            	cout << intersections[i].entrades[i] << " " << cicles[i] << endl;
            }
		}
	}
}

//Retorna true si l'string forma part de la llista
bool inclos(const vector<string>& llista, string s) {
	for(int i = 0; i < llista.size(); ++i) if(llista[i] == s) return true;
  	return false;
}

//Pre:donat una interseccio i un carrer 
//Pos:si el carrer o hi és, l'inclou a la llista d'entrades
void incloure_entrada(Intersection& inter, string s) {
	if(not inclos(inter.entrades, s)) inter.entrades.push_back(s);
}
//El mateix que l'anterior però per les sortides
void incloure_sortida(Intersection& inter, string s) {
	if(not inclos(inter.sortides, s)) inter.sortides.push_back(s);
}


//donat un carrer retorna les interseccions
pair<int, int> inter_num(string a, const vector<Street>& streets){

    int i = 0;
    
    while (i < streets.size()) {
        
        if (a == streets[i].name) {
            
            return streets[i].intersect;
            
        }
        ++i;
    }
    pair<int, int> p;
    p.first = -1;
    p.second = -1;
    return p;
}

//donada la ruta d'un cotxe i els carrers retorna les interseccions per les que passa
vector<int> intersecciones(const vector<string>& route, const vector<Street>& streets) {
    
    int size = route.size();
    
    vector<int> inter(size + 1);
    
    for (int i = 0; i < size; ++i) {
        
        pair<int,int> num = inter_num(route[i], streets);
        inter[i] = num.first;
        
        if (i < size) {
            inter[i + 1] = num.second;
        }
    }
    return inter;
    
}

int main() {
    
    //Obtain Data
    int duration, n_intersections, n_streets, n_cars, bonus;
    cin >> duration >> n_intersections >> n_streets >> n_cars >> bonus;
    
  	  //Creem un vector d'interseccions i assignem un ID a cadascun
    vector<Intersection> interseccions(n_intersections);
    for (int i = 0; i < n_intersections; ++i) 
    {
        interseccions[i].ID = i;
    }
  
    vector<Street> streets(n_streets);
    
    for (int i = 0; i < n_streets; ++i)
    {    
        cin >> streets[i].intersect.first >> streets[i].intersect.second 
        >> streets[i].name >> streets[i].time;
      	//Incloem entrades i sortides a una llista per cada interseccio
      	incloure_entrada(interseccions[streets[i].intersect.second], streets[i].name);
      	incloure_sortida(interseccions[streets[i].intersect.first], streets[i].name);   /// AQUIIIIIIIIIIII
    }
    
    vector<Car> cars(n_cars);
    
    for (int i = 0; i < n_cars; ++i) {
        
        int m_streets;
        cin >> m_streets;
        cars[i].route.resize(m_streets);
        
        for (int j = 0; j < m_streets; ++j) {
            cin >> cars[i].route[j];
        }
        cars[i].intersections = intersecciones(cars[i].route, streets);
    }
  	
  	//Mostrar resultat
  	cout << n_intersections << endl;
  
  	//AQUÍ VA LA FUNCIO PER MOSTRAR ELS CARRERS I ELS TEMPS
  	calcular(cars, interseccions);
    
}
