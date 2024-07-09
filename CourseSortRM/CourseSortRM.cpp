#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Course {
    string code;
    string title;

    Course(const string& c, const string& t) : code(c), title(t) {}
};

// Parse course data from a line
Course parseCourse(const string& line) {
    istringstream iss(line);
    string code, title;
    iss >> code;
    getline(iss, title);
    
    title.erase(0, title.find_first_not_of(" \t"));
    title.erase(title.find_last_not_of(" \t") + 1);
    return Course(code, title);
}

// Used to compare courses by title for sorting
bool compareByTitle(const Course& c1, const Course& c2) {
    return c1.title < c2.title;
}

int main() {
    char choice;
    do {
        string filename;
        cout << "Enter the name of the data file: ";
        cin >> filename;

        ifstream file(filename);
        if (!file) {
            cerr << "Error: Unable to open file " << filename << endl;
            continue;
        }

        vector<Course> courses;

        // inputFile 
        string line;
        while (getline(file, line)) {
            if (line.empty())
                continue;
            Course course = parseCourse(line);
            courses.push_back(course);
        }

        // Sorting by titles
        sort(courses.begin(), courses.end(), compareByTitle);

       
        //Output for sort
        for (const Course& course : courses) {
            cout << course.title << " (" << course.code << ")" << endl;
        }

        cout << "\nRun Again(Y/N): ";
        cin >> choice;
    } while (toupper(choice) == 'Y');

    return 0;
}
