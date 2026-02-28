#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>

using namespace std;

struct Student {
    int carnet;
    string nombre;
    string apellido;
    string carrera;
    int semestre;
};

struct Course {
    int codigo;
    string nombre;
    int creditos;
    int semestre;
    string carrera;
};

struct Grade {
    int carnet;
    int codigo_curso;
    double nota;
    string ciclo;
    int anio;
};

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

bool loadStudents(const string &path, vector<Student> &students) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Error: no se puede abrir el archivo de estudiantes " << path << "\n";
        return false;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        auto parts = split(line, ',');
        if (parts.size() < 5) continue;
        Student s;
        s.carnet = stoi(parts[0]);
        s.nombre = parts[1];
        s.apellido = parts[2];
        s.carrera = parts[3];
        s.semestre = stoi(parts[4]);
        students.push_back(s);
    }
    return true;
}

bool loadCourses(const string &path, vector<Course> &courses) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Error: no se puede abrir el archivo de cursos " << path << "\n";
        return false;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        auto parts = split(line, ',');
        if (parts.size() < 5) continue;
        Course c;
        c.codigo = stoi(parts[0]);
        c.nombre = parts[1];
        c.creditos = stoi(parts[2]);
        c.semestre = stoi(parts[3]);
        c.carrera = parts[4];
        courses.push_back(c);
    }
    return true;
}

bool loadGrades(const string &path, vector<Grade> &grades) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Error: no se puede abrir el archivo de notas " << path << "\n";
        return false;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        auto parts = split(line, ',');
        if (parts.size() < 5) continue;
        Grade g;
        g.carnet = stoi(parts[0]);
        g.codigo_curso = stoi(parts[1]);
        g.nota = stod(parts[2]);
        g.ciclo = parts[3];
        g.anio = stoi(parts[4]);
        grades.push_back(g);
    }
    return true;
}

// statistical helpers

double average(const vector<double> &vals) {
    if (vals.empty()) return 0.0;
    double sum = 0;
    for (auto v : vals) sum += v;
    return sum / vals.size();
}

double variance(const vector<double> &vals) {
    double avg = average(vals);
    double var = 0;
    for (auto v : vals) var += (v - avg) * (v - avg);
    return vals.empty() ? 0 : var / vals.size();
}

double stddev(const vector<double> &vals) {
    return sqrt(variance(vals));
}

double median(vector<double> vals) {
    if (vals.empty()) return 0;
    sort(vals.begin(), vals.end());
    size_t n = vals.size();
    if (n % 2 == 1) return vals[n/2];
    return (vals[n/2 -1] + vals[n/2]) / 2.0;
}


void reportStatsByCourse(const vector<Student>& students, const vector<Course>& courses, const vector<Grade>& grades) {
    string filename = "reporte_curso.html";
    ofstream out(filename);
    out << "<html><head><meta charset=\"utf-8\"><title>Estadísticas por Curso</title></head><body>";
    out << "<h1>Estadísticas Generales por Curso</h1>";
    out << "<table border=\"1\"><tr><th>Curso</th><th>Estudiantes</th><th>Promedio</th><th>Max</th><th>Min</th><th>Desviación</th><th>Mediana</th></tr>";
    for (const auto &c : courses) {
        vector<double> notas;
        for (const auto &g : grades) {
            if (g.codigo_curso == c.codigo) {
                notas.push_back(g.nota);
            }
        }
        if (notas.empty()) continue;
        double avg = average(notas);
        double mx = *max_element(notas.begin(), notas.end());
        double mn = *min_element(notas.begin(), notas.end());
        double sd = stddev(notas);
        double med = median(notas);
        out << "<tr><td>" << c.nombre << "</td><td>" << notas.size() << "</td><td>" << avg << "</td><td>" << mx << "</td><td>" << mn << "</td><td>" << sd << "</td><td>" << med << "</td></tr>";
    }
    out << "</table></body></html>";
    cout << "Reporte generado: " << filename << "\n";
}

void reportPerformanceByStudent(const vector<Student>& students, const vector<Course>& courses, const vector<Grade>& grades) {
    string filename = "reporte_estudiante.html";
    ofstream out(filename);
    out << "<html><head><meta charset=\"utf-8\"><title>Rendimiento por Estudiante</title></head><body>";
    out << "<h1>Rendimiento por Estudiante</h1>";
    out << "<table border=\"1\"><tr><th>Carnet</th><th>Nombre</th><th>Carrera</th><th>Semestre</th><th>Promedio</th><th>APROBADOS</th><th>REPROBADOS</th><th>Créditos</th></tr>";
    map<int,int> credits;
    for (auto &c : courses) credits[c.codigo] = c.creditos;
    for (const auto &s : students) {
        vector<double> notas;
        int aprob = 0, repro = 0;
        int creditos = 0;
        for (auto &g : grades) {
            if (g.carnet == s.carnet) {
                notas.push_back(g.nota);
                if (g.nota >= 61) {
                    aprob++;
                    creditos += credits[g.codigo_curso];
                } else repro++;
            }
        }
        if (notas.empty()) continue;
        double avg = average(notas);
        out << "<tr><td>"<< s.carnet <<"</td><td>"<< s.nombre <<" "<< s.apellido <<"</td><td>"<< s.carrera <<"</td><td>"<< s.semestre <<"</td><td>"<< avg <<"</td><td>"<< aprob <<"</td><td>"<< repro <<"</td><td>"<< creditos <<"</td></tr>";
    }
    out << "</table></body></html>";
    cout << "Reporte generado: " << filename << "\n";
}

void reportTop10(const vector<Student>& students, const vector<Course>& courses, const vector<Grade>& grades) {
    vector<pair<double,int>> avgCarnet;
    map<int,double> credits;
    for (auto &s : students) {
        vector<double> notas;
        for (auto &g: grades) if (g.carnet == s.carnet) notas.push_back(g.nota);
        if (!notas.empty()) {
            avgCarnet.push_back({average(notas), s.carnet});
        }
    }
    sort(avgCarnet.begin(), avgCarnet.end(), greater<>());
    string filename = "reporte_top10.html";
    ofstream out(filename);
    out << "<html><head><meta charset=\"utf-8\"><title>Top 10</title></head><body>";
    out << "<h1>Top 10 Mejores Estudiantes</h1>";
    out << "<table border=\"1\"><tr><th>Pos</th><th>Carnet</th><th>Nombre</th><th>Carrera</th><th>Semestre</th><th>Promedio</th></tr>";
    for (size_t i=0;i<avgCarnet.size() && i<10;i++) {
        int carnet = avgCarnet[i].second;
        double avg = avgCarnet[i].first;
        auto it = find_if(students.begin(), students.end(), [&](const Student &st){ return st.carnet == carnet; });
        if (it!=students.end()) {
            out << "<tr><td>"<<(i+1)<<"</td><td>"<<it->carnet<<"</td><td>"<<it->nombre<<" "<<it->apellido<<"</td><td>"<<it->carrera<<"</td><td>"<<it->semestre<<"</td><td>"<<avg<<"</td></tr>";
        }
    }
    out << "</table></body></html>";
    cout << "Reporte generado: " << filename << "\n";
}

void reportCoursesReprobation(const vector<Student>& students, const vector<Course>& courses, const vector<Grade>& grades) {
    struct Stats { int total=0, apr=0, rep=0; };
    map<int,Stats> data;
    for (auto &g : grades) {
        auto &st = data[g.codigo_curso];
        st.total++;
        if (g.nota >= 61) st.apr++; else st.rep++;
    }
    vector<pair<double,int>> order;
    for (auto &p: data) {
        double perc = p.second.total>0 ? (100.0*p.second.rep/p.second.total) : 0;
        order.push_back({perc,p.first});
    }
    sort(order.begin(), order.end(), greater<>());
    string filename = "reporte_reprobacion.html";
    ofstream out(filename);
    out << "<html><head><meta charset=\"utf-8\"><title>Reprobación</title></head><body>";
    out << "<h1>Cursos con Mayor Índice de Reprobación</h1>";
    out << "<table border=\"1\"><tr><th>Código</th><th>Curso</th><th>Total</th><th>Aprobados</th><th>Reprobados</th><th>% Reprobación</th></tr>";
    for (auto &pr : order) {
        int code = pr.second;
        auto it = find_if(courses.begin(), courses.end(), [&](const Course &c){ return c.codigo==code; });
        if (it==courses.end()) continue;
        auto &st = data[code];
        double perc = st.total>0 ? (100.0*st.rep/st.total) : 0;
        out << "<tr><td>"<<code<<"</td><td>"<<it->nombre<<"</td><td>"<<st.total<<"</td><td>"<<st.apr<<"</td><td>"<<st.rep<<"</td><td>"<<perc<<"</td></tr>";
    }
    out << "</table></body></html>";
    cout << "Reporte generado: " << filename << "\n";
}

void reportAnalysisByCareer(const vector<Student>& students, const vector<Course>& courses, const vector<Grade>& grades) {
    map<string, vector<int>> studentsByCareer;
    map<string, vector<double>> careerGrades;
    map<string,set<int>> careerCourses;
    map<string,map<int,int>> distribution;
    for (auto &s: students) {
        studentsByCareer[s.carrera].push_back(s.carnet);
        distribution[s.carrera][s.semestre]++;
    }
    for (auto &g: grades) {
        auto it = find_if(students.begin(), students.end(), [&](const Student &s){ return s.carnet==g.carnet; });
        if (it!=students.end()) {
            careerGrades[it->carrera].push_back(g.nota);
        }
    }
    for (auto &c : courses) {
        careerCourses[c.carrera].insert(c.codigo);
    }
    string filename = "reporte_carrera.html";
    ofstream out(filename);
    out << "<html><head><meta charset=\"utf-8\"><title>Análisis por Carrera</title></head><body>";
    out << "<h1>Análisis por Carrera</h1>";
    out << "<table border=\"1\"><tr><th>Carrera</th><th>Estudiantes</th><th>Promedio</th><th>Cursos</th><th>Distribución por semestre</th></tr>";
    for (auto &p : studentsByCareer) {
        string carrera = p.first;
        int total = p.second.size();
        double avg = average(careerGrades[carrera]);
        int cursosCount = careerCourses[carrera].size();
        string dist="";
        for (auto &d : distribution[carrera]) {
            dist += to_string(d.first) + ":" + to_string(d.second) + " ";
        }
        out << "<tr><td>"<<carrera<<"</td><td>"<<total<<"</td><td>"<<avg<<"</td><td>"<<cursosCount<<"</td><td>"<<dist<<"</td></tr>";
    }
    out << "</table></body></html>";
    cout << "Reporte generado: " << filename << "\n";
}

int main() {
    vector<Student> students;
    vector<Course> courses;
    vector<Grade> grades;
    int option;
    do {
        cout << "==========================================\n";
        cout << "SISTEMA DE ANALISIS ACADEMICO\n";
        cout << "==========================================\n";
        cout << "1. Cargar archivo de estudiantes\n";
        cout << "2. Cargar archivo de cursos\n";
        cout << "3. Cargar archivo de notas\n";
        cout << "4. Generar Reporte: Estadísticas por Curso\n";
        cout << "5. Generar Reporte: Rendimiento por Estudiante\n";
        cout << "6. Generar Reporte: Top 10 Mejores Estudiantes\n";
        cout << "7. Generar Reporte: Cursos con Mayor Reprobaciలn\n";
        cout << "8. Generar Reporte: Análisis por Carrera\n";
        cout << "9. Salir\n";
        cout << "Seleccione una opciలn: ";
        cin >> option;
        switch(option) {
            case 1: {
                string path;
                cout << "Ruta del archivo estudantes: ";
                cin >> path;
                loadStudents(path, students);
                break;
            }
            case 2: {
                string path;
                cout << "Ruta del archivo cursos: ";
                cin >> path;
                loadCourses(path, courses);
                break;
            }
            case 3: {
                string path;
                cout << "Ruta del archivo notas: ";
                cin >> path;
                loadGrades(path, grades);
                break;
            }
            case 4:
                reportStatsByCourse(students, courses, grades);
                break;
            case 5:
                reportPerformanceByStudent(students, courses, grades);
                break;
            case 6:
                reportTop10(students, courses, grades);
                break;
            case 7:
                reportCoursesReprobation(students, courses, grades);
                break;
            case 8:
                reportAnalysisByCareer(students, courses, grades);
                break;
            case 9:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opciలn invలlida\n";
        }
    } while (option != 9);
    return 0;
}