#include <iostream>
#include <string>
#include <vector>
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
    vector<int> temps; //Vector amb el temps de cada semafor d'entra
    int ID;
};

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
vector<int> interseccions(const vector<string>& route, const vector<Street>& streets) {
    
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

void primer_obert(const vector<Intersection>& inters) {
    int n_interseccions = inters.size();
    cout << n_interseccions << endl;
    for(int i = 0; i < n_interseccions; ++i) 
    {
        cout << i << endl << "1" << endl;
        cout << inters[i].entrades[0] << " 1" << endl;
    }
}

//Deixem cada semafor 1 segon a veure que passa
void una_mica_de_tot(const vector<Intersection>& inters) { 
    int n_interseccions = inters.size();
    cout << n_interseccions << endl;
    for(int i = 0; i < n_interseccions; ++i) 
    {
        int n_entrades = inters[i].entrades.size();
        cout << i << endl << n_entrades << endl;
        for(int j = 0; j < n_entrades; ++j) {
            cout << inters[i].entrades[j] << " 1" << endl;
        }
    }
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

    una_mica_de_tot(interseccions);
    
}
/*
// Donada una interseccio retorna quants cotxes hi entraran per cada carrer (amb el mateix ordre que inter.entrades)
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

// Donades les rutes dels cotxes i les interseccions ens fa l'output
void calcular(const vector<Car>& cars, const vector<Intersection>& intersections) {
  
    int size = intersections.size();
    cout << size << endl;
    for(int i = 0; i < size; ++i) {
      
        int n_entrades = v[i].entrades.size();
        int n_sortides = v[i].sortides.size();

        if(n_entrades == 1){
            cout << intersections[i].ID << endl << "1" << endl;
            cout << intersections[i].entrades[0] << " 1" << endl;
        }
        else {
            vector<int> proporcions = mostTraffic(cars, intersections[i]);
        }
    }
}
*/


//funcio una mica random xddd

