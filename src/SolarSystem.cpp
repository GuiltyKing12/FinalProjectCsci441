#include "SolarSystem.h"
#include <iostream>
using namespace std;

void SolarSystem::draw() {
    sun.draw();
    for(int i = 0; i < planets.size(); i++) {
        planets[i].draw();
    }
}

void SolarSystem::update() {
    sun.update();
    for(int i = 0; i < planets.size(); i++) {
        planets[i].update();
    }
}

void SolarSystem::create() {
}

bool SolarSystem::readfile(string inputfile) {
    ifstream fin;
    fin.open(inputfile);
    if(!fin) return false;
    
    int number;
    string numb;
    getline(fin, numb);
    number = atoi(numb.c_str());
    
    while(number != 0) {
        string line;
        getline(fin, line);
        vector<string> attr;
        string delim = ",";
        split(line, delim.c_str(), attr);
        
        cout << line << endl;
        
        if(attr[0] == "S") {
            fprintf(stdout, "Sun\n");
            Point sunpos = Point(atoi(attr[2].c_str()),
                                 atoi(attr[3].c_str()),
                                 atoi(attr[4].c_str()));
            
            sun = Sun(atof(attr[1].c_str()),
                      sunpos,
                      atof(attr[5].c_str()));
        }
        else if(attr[0] == "P") {
            fprintf(stdout, "Planet\n");
            Point planpos = Point(atoi(attr[2].c_str()),
                                  atoi(attr[3].c_str()),
                                  atoi(attr[4].c_str()));
            
            planets.push_back(Planet(atof(attr[1].c_str()),
                                     planpos,
                                     Vector(0, 1, 0),
                                     atof(attr[5].c_str())));
        }
        number--;
    }
    return true;
}

void SolarSystem::split(const string &s, const char* delim, vector<string> & v){
    // to avoid modifying original string
    // first duplicate the original string and return a char pointer then free the memory
    char * dup = strdup(s.c_str());
    char * token = strtok(dup, delim);
    while(token != NULL){
        v.push_back(string(token));
        // the call is treated as a subsequent calls to strtok:
        // the function continues from where it left in previous invocation
        token = strtok(NULL, delim);
    }
    free(dup);
}
