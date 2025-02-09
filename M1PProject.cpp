#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_STUDENTS = 100;
const int MAX_TESTS = 10;

// Function protoypes
int readData(ifstream& inFile, string names[], double scores[][MAX_TESTS], int& numTests);
void calculateAverages(const double scores[][MAX_TESTS], double averages[], int numStudents, int numTests);
char calculateLetterGrade(double average);
void displayReport(const string names[], const double averages[], int numStudents);

int main() {
    string names[MAX_STUDENTS];
    double scores[MAX_STUDENTS][MAX_TESTS];
    double averages[MAX_STUDENTS];
    int numStudents = 0, numTests = 0;

    ifstream inFile("StudentGrades.txt");

    if (!inFile) {
        cerr << "There was an error opening the StudentGrades.txt file. Please make sure a StudentGrades.txt file exists.";
        return 1;
    }

    numStudents = readData(inFile, names, scores, numTests);
    inFile.close();

    calculateAverages(scores, averages, numStudents, numTests);
    displayReport(names, averages, numStudents);

    return 0;
}

// Function to read student names and test scores from a file
int readData(ifstream& inFile, string names[], double scores[][MAX_TESTS], int& numTests) {
    int studentCount = 0;

    while (studentCount < MAX_STUDENTS && inFile >> names[studentCount]) {
        int testIndex = 0;
        double score;

        while (testIndex < MAX_TESTS && inFile >> score) {
            scores[studentCount][testIndex] = score;
            testIndex++;
        }

        if (studentCount == 0) {
            numTests = testIndex;
        }

        studentCount++;

        inFile.clear();
    }

    return studentCount;
}

// Calculates the average scores
void calculateAverages(const double scores[][MAX_TESTS], double averages[], int numStudents, int numTests) {
    for (int i = 0; i < numStudents; i++) {
        double sum = 0;
        for (int j = 0; j < numTests; j++) {
            sum += scores[i][j];
        }
        averages[i] = sum / numTests;
    }
}

// Function to get the letter grade based off score
char calculateLetterGrade(double average) {
    if (average >= 90) return 'A';
    if (average >= 80) return 'B';
    if (average >= 70) return 'C';
    if (average >= 60) return 'D';
    return 'F';
}

// Function to display the results
void displayReport(const string names[], const double averages[], int numStudents) {
    cout << "TEST GRADE REPORT\n";
    cout << left << setw(15) << "Name" << setw(10) << "Average" << setw(10) << "Grade" << endl;
    cout << "----------------------------------\n";

    for (int i = 0; i < numStudents; i++) {
        cout << left << setw(15) << names[i]
            << setw(10) << fixed << setprecision(2) << averages[i]
            << setw(10) << calculateLetterGrade(averages[i]) << endl;
    }
}
