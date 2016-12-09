#include "SolarSystem.h"
#include <iostream>

using namespace std;

void SolarSystem::draw() {
    glUseProgram(sunshaderhandle);
    float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    float dis = rand()%100+1;
    glUniform1f(uniformTimeLoc, time);
    if(dis) glUniform1i(uniformDistortLoc, 1);
    else glUniform1i(uniformDistortLoc, 0);
    sun.draw();
    glUseProgram(0);
    for(int i = 0; i < planets.size(); i++) {
        planets[i].draw();
    }
}

void SolarSystem::update(Ship &ship) {
    sun.update();
    double distance = (ship.getPosition() - sun.getPosition()).mag() - sun.getRadius();
    
    if(distance <= sun.getRadius() * 2) {
        // do some death animation
        double ratio = distance / (sun.getRadius() * 2);
        ship.nearSun(true, ratio);
        
        if(ratio < .1) {
            ship.exploded = true;
        }
    }
    else ship.nearSun(false, 0.0);
    for(int i = 0; i < planets.size(); i++) {
        planets[i].update();
        distance = (planets[i].getPosition() - ship.getPosition()).mag() - planets[i].getRadius();
        if(distance <= planets[i].getRadius()+ship.bodySize*5) {
           double ratio = distance / (planets[i].getRadius()+ship.bodySize*5);
            if(ratio < .1) ship.exploded = true;
        }
    }
}

void SolarSystem::setSunShader(GLuint handle) {
    sunshaderhandle = handle;
    uniformTimeLoc = glGetUniformLocation(sunshaderhandle, "time");
    uniformDistortLoc = glGetUniformLocation(sunshaderhandle, "distort");
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
            
            GLuint texHandle = SOIL_load_OGL_texture(
                                                     "textures/planets/sunmap.jpg",
                                                     SOIL_LOAD_AUTO,
                                                     SOIL_CREATE_NEW_ID,
                                                     SOIL_FLAG_MIPMAPS
                                                     | SOIL_FLAG_INVERT_Y
                                                     | SOIL_FLAG_COMPRESS_TO_DXT
                                                     );
            
            sun = Sun(atof(attr[1].c_str()),
                      sunpos,
                      atof(attr[5].c_str()),
                      texHandle);
        }
        else if(attr[0] == "P") {
            fprintf(stdout, "Planet\n");
            Point planpos = Point(atoi(attr[2].c_str()),
                                  atoi(attr[3].c_str()),
                                  atoi(attr[4].c_str()));
            
            string image = "textures/planets/" + attr[6].substr(1);
            //string test = "textures/planets/jupitermap.jpg";
            GLuint texHandle = SOIL_load_OGL_texture(
                                                     image.c_str(),
                                                     SOIL_LOAD_AUTO,
                                                     SOIL_CREATE_NEW_ID,
                                                     SOIL_FLAG_MIPMAPS
                                                     | SOIL_FLAG_INVERT_Y
                                                     | SOIL_FLAG_COMPRESS_TO_DXT
                                                     );
            
            cout << image << endl;
            cout << texHandle << endl;
			
			vector<Point> orbitalPath;
					
            if(atoi(attr[7].c_str()) == 1) {
                image = "textures/planets/" + attr[8].substr(1);
                GLuint texHandle2 = SOIL_load_OGL_texture(
                                                         image.c_str(),
                                                         SOIL_LOAD_AUTO,
                                                         SOIL_CREATE_NEW_ID,
                                                         SOIL_FLAG_MIPMAPS
                                                         | SOIL_FLAG_INVERT_Y
                                                         | SOIL_FLAG_COMPRESS_TO_DXT
                                                         );
                cout << image << endl;
                cout << texHandle2 << endl;
				
				if( !bezierPoints(attr[10].substr(1), orbitalPath) ) return false;
				
                planets.push_back(Planet(atof(attr[1].c_str()),
                                         planpos,
                                         Vector(0, 1, 0),
                                         atof(attr[5].c_str()),
                                         texHandle,
                                         texHandle2,
                                         atof(attr[9].c_str()),
										 orbitalPath));
            }
            else {
				if( !bezierPoints(attr[8].substr(1), orbitalPath) ) return false;
				
				planets.push_back(Planet(atof(attr[1].c_str()),
										 planpos,
										 Vector(0, 1, 0),
										 atof(attr[5].c_str()),
										 texHandle,
										 orbitalPath));
            }
        }
        number--;
    }
    fin.close();
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

bool SolarSystem::bezierPoints(string bezFile, vector<Point> &p) {
	// Return false if the file cannot be opened
	string file = "beziers/" + bezFile;
	cout << file << endl;
    ifstream fin;
    fin.open(file.c_str());
    if(!fin) return false;
    
    // Reads how many points are contained in the file
    string num;
    getline(fin, num);
	int numPoints = atoi(num.c_str());
    fprintf(stdout, "Number of Points: %d\n", numPoints);

    // Reads in the points
	for(int i = 0; i < numPoints; i++) {
        string line;
        getline(fin, line);
        vector<string> coords;
        string delim = ",";

        split(line, delim.c_str(), coords);

        // Uses the values in the coords array to create a new point and then stores it into the controlPoints vector
        Point point(atof(coords[0].c_str()), atof(coords[1].c_str()), atof(coords[2].c_str()));
        p.push_back(point);
        fprintf(stdout, "Point( %f, %f, %f)\n", atof(coords[0].c_str()), atof(coords[1].c_str()), atof(coords[2].c_str()));
    }

    fin.close();
    return true;
}
