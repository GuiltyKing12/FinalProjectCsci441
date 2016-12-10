#include "Track.h"

Track::Track() {
	load_points("beziers/default.csv");
	calculate_lookup();
	res = 1000;
	step = 5;
}

Track::Track(std::string fn, float speed) {
	orbitSpeed = speed;
	load_points(fn);
	calculate_lookup();
	res = 1000;
	step = segments;
}

void Track::draw() {
  glPushMatrix();
    glColor3f(1, 1, 0);
    glBegin(GL_LINES);
      for (int t = 0; t < segments * res; t += 1) {
        vertex(get_point((float)t / res));
        vertex(get_point((float)(t + 1) / res));
      }
    glEnd();
  glPopMatrix();
}

void Track::load_points(std::string fn) {
  std::string file = "beziers/" + fn;
  std::ifstream infile(file.c_str());
  std::string line;

  getline(infile, line);
  segments = atoi(line.c_str());
  //cout << segments << endl;

  control_points = new Point*[segments];
  for (int i = 0; i < segments; i++) {
    control_points[i] = new Point[4];
  }

  for (int i = 0; i < segments * 4; i++) {
    if (!getline(infile, line)) {
      break;
    }

    float x = atof(line.substr(0, line.find_first_of(',')).c_str());
    float y = atof(line.substr(line.find_first_of(',') + 1, line.find_last_of(',') - line.find_first_of(',') - 1).c_str());
    float z = atof(line.substr(line.find_last_of(',') + 1).c_str());

    Point p(x, y, z);
    int inner_index = i % 4;
    int outer_index = i / 4;
    control_points[outer_index][inner_index] = p;
	//cout << p.toString() << endl;
  }

  infile.close(); 
}

void Track::vertex(Point p) {
  glVertex3f(p.getX(), p.getY(), p.getZ());
}

Point Track::get_point(float t) {
  int o = 0;
  while (t > 1.0) {
    o += 1;
    t -= 1.0;
  }

  return bez_curve(t, 
    control_points[o][0], control_points[o][1],
    control_points[o][2], control_points[o][3]);
}

Point Track::bez_curve(float t, Point p0, Point p1, Point p2, Point p3) {
  float t2 = t * t;
  float t3 = t2 * t;
  float mt = 1.0 - t;
  float mt2 = mt * mt;
  float mt3 = mt2 * mt;

  return p0 * mt3 + p1 * (3.0 * mt2 * t) + p2 * (3.0 * mt * t2) + p3 * t3;
}

Point Track::arc_pos() {
    int a = 0;
    int b = 1;
    for (int i = 0; i < segments * 100; i += 1) {
      if (lookup_table[i] > arc_t) {
        a = i - 1;
        b = i;
        break;
      }
    }

    float offset = (arc_t - lookup_table[a]) / (lookup_table[b] - lookup_table[a]);
    float t = (1 - offset) * ((float)a / 100) + offset * ((float)b / 100);

    arc_t += (max_dist / orbitSpeed);
    if (arc_t >= max_dist) {
      arc_t -= max_dist;
    }
    return get_point(t);
}

Vector Track::arc_dir() {
    int a = 0;
    int b = 1;
    for (int i = 0; i < segments * 100; i += 1) {
      if (lookup_table[i] > arc_t) {
        a = i - 1;
        b = i;
        break;
      }
    }

    float offset = (arc_t - lookup_table[a]) / (lookup_table[b] - lookup_table[a]);
    float t = (1 - offset) * ((float)a / 100) + offset * ((float)b / 100);
    float nt = t + 0.05;
    if (nt >= segments) {
      nt -= segments;
    }

    return get_point(nt) - get_point(t);
}

void Track::calculate_lookup() {
    lookup_table[0] = 0;
    for (int t = 1; t < segments * 100; t += 1) {
      float dist = (get_point((float)t / 100) - get_point((float)(t - 1) / 100)).mag();
      lookup_table[t] = lookup_table[t - 1] + dist;
    }
    max_dist = lookup_table[segments * 100 - 1];
}
