#include <iostream>
#include <map>
#include <string>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
#include <time.h>
using namespace std;

struct project_data{
  int score, duration, before_day;
  //LLenguatge, Skill_level
  vector<pair<string, int>> skill_level;
};

int NPROJ = 0;
int DEADLINE = 0;
int ACTUAL_DAY = 0;

//LLenguatge,  NOM,  Skill_level
map<string, map<string, int>> M;

//NOM-PERSONA,  LANG,  Skill_level
map<string, map<string, int>> M2;

// NOM-PERSONA, DIA DISPONIBILITAT
map<string, int> D;
// Proj name,  Data
map<string, project_data> PJ;

int score_proj(string s)
{
  auto it = PJ.find(s);
  if (it != PJ.end()) return it->second.score;
  cerr << "Error in score_proj" << endl;
  return -1;
}

int duration_proj(string s)
{
  auto it = PJ.find(s);
  if (it != PJ.end()) return it->second.duration;
  cerr << "Error in duration_proj" << endl;
  return -1;
}

int before_day_proj(string s)
{
  auto it = PJ.find(s);
  if (it != PJ.end()) return it->second.before_day;
  cerr << "Error in before_day_proj" << endl;
  return -1;
}

int level_skill(string c, string s) {
  auto it = M.find(c);
  if (it == M.end()) {
    cerr << "Persona no trobada a level_skill()" << endl;
    return -1;
  }
  auto it2 = it->second.find(s);
  if (it2 == it->second.end()) {
    cerr << "Skill no trobat a level_skill()" << endl;
    return -1;
  }
  return it2->second;
}

void update_level(string c, string s) {
  auto it = M.find(c);
  if (it == M.end()) cerr << "Persona no trobada a update_level()" << endl;
  auto it2 = it->second.find(s);
  if (it2 == it->second.end()) cerr << "Skill no trobat a update_level()" << endl;
  ++it2->second;
}

void lectura_dades()
{
  int n_persones, n_projectes;
  cin >> n_persones >> n_projectes;

  for (int i = 0; i < n_persones; ++i) {
    string persona;
    int num_skills;

    cin >> persona >> num_skills;
    for (int j = 0; j < num_skills; ++j) {
      string skill;
      int level;

      cin >> skill >> level;

      if (M.find(skill) == M.end()) ++NPROJ;

      M[skill][persona] = level;
      M2[persona][skill] = level;
    }
  }

  for (int p = 0; p < n_projectes; ++p){

      project_data pj;
      int roles;
      string name_proj;

      cin >> name_proj >> pj.duration >> pj.score >> pj.before_day >> roles;

      for (int j = 0; j < roles; ++j) {
        string skill;
        int level;
        cin >> skill >> level;
        pj.skill_level.push_back(make_pair(skill, level));
      }
      PJ[name_proj] = pj;
  }
}

void imprimir_dades()
{
  for (auto i : M)
  {
    cout << "Llenguatge: " << i.first << endl;
    for (auto j : i.second)
    {
      cout << j.first << " - " << j.second << endl;
    }
  }
  for (auto i : PJ)
  {
    cout << "Project: " << i.first << endl;
    cout << "---Score: " << i.second.score << endl
    << "---Duration: " << i.second.duration << endl
    << "---BeforeDay: " << i.second.before_day << endl << "---Requirements: " << endl;
    for (auto j : i.second.skill_level)
    {
      cout << "------Llenguatge " << j.first << "; Nivell " << j.second << ';' << endl;
    }
  }
}

void list_by_score(queue<string>& q)
{
  priority_queue<pair<int, string>> p_q;
  for (auto i : PJ) p_q.push(make_pair(i.second.score, i.first));
  queue<string> empty;
  q = empty;
  while (not p_q.empty())
  {
    q.push(p_q.top().second);
    p_q.pop();
  }
}

void initialize_deadline()
{
  for (auto i : PJ) DEADLINE = max(DEADLINE, i.second.score + i.second.before_day);
  //DEADLINE = 3000;
}


void initialize_days() {
  for (auto i : M2) {
    D[i.first] = 0;
  }
}



// PRE: proj és un projecte existent
// POST blah
bool es_possible(string proj, vector<string>& noms){
    noms.clear();
    project_data p = PJ[proj];

    for (auto s : p.skill_level){
        string necessary_skill = s.first;
        int necessary_level = s.second;

        // PER CADA PERSON
        int cool = false;

        for (auto o : M2){
            // 'o' és una persona pk m'he quedat sense noms
            if (o.second.find(necessary_skill) == o.second.end()) continue; // Si la persona no té l'skill demanat
            if (o.second[necessary_skill] < necessary_level) continue; // Si la persona no té el nivell adequat
            if (D[o.first] > ACTUAL_DAY) continue;
            for (string n : noms) if (n == o.first) continue;

            cool = true;

            noms.push_back(o.first);
            D[o.first] = ACTUAL_DAY + duration_proj(proj);
            break;
        }

        if (not cool)
        {
          for (auto n : noms) D[n] = ACTUAL_DAY;
          return false;
        }
    }

    return true;
}

bool puntuacio_positiva(string nomProj) {
    return (score_proj(nomProj) - (ACTUAL_DAY + duration_proj(nomProj) - before_day_proj(nomProj))) > 0;
}

int primer_disponible()
{
  int minim = 2e9; //Oju numero màgic
  for (auto i : D) minim = min(minim, i.second);
  return minim;
}

int main()
{
    lectura_dades();
    initialize_days();
    initialize_deadline();
    //imprimir_dades();

    queue<string> q;
    list_by_score(q);

    vector<pair<string, vector<string>>> vect;

    while (not q.empty() and ACTUAL_DAY < DEADLINE) {
      //Per a tots els projectes
      vector<string> noms;
      int n_elements = q.size();
      cerr << "Nº elements left: " << n_elements << endl;
      cerr << "Actual day: " << ACTUAL_DAY << "   -  DEADLINE: " << DEADLINE << endl;
      bool time_set = false;
      int time = 1;
      while (n_elements--)
      {
        string nom_projecte = q.front();
        q.pop();
        if (not puntuacio_positiva(nom_projecte));
        else if (not es_possible(nom_projecte, noms)) q.push(nom_projecte);
        else {
            vect.push_back(make_pair(nom_projecte, noms));
            if (not time_set) time = duration_proj(nom_projecte);
            else time = min(time, duration_proj(nom_projecte));
        }
      }

      //ACTUAL_DAY = primer_disponible();
      //ACTUAL_DAY += minim_proj();
      ACTUAL_DAY += time;
    }

    //Mostrar resultats
    cout << vect.size() << endl;
    for (auto p : vect){
        cout << p.first << endl;
        for (string x : p.second){
            cout << x << ' ';
        }
        cout << endl;
    }


}
