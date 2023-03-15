// Spring'22
// Instructor: Diba Mirza
// Student name: 
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include "movies.h"
using namespace std;

//Part 1:
//use set data structure
//define Movie struct


bool parseLine(string &line, string &movieName, double &movieRating);
bool hasPrefix(const string &prefix, const string &movieName);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " filename prefix1 prefix2 ... prefix n " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
  // Create an object of a STL data-structure to store all the movies
  std::set<Movie> movies;

  string line, movieName;
  double movieRating;
  // Read each file and store the name and rating
  while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
        // Use std::string movieName and double movieRating
        movies.insert(Movie(movieName,movieRating));
        // to construct your Movie objects
        //cout << movieName << " has rating " << movieRating << endl;
        // insert elements into your data structure
  }

  movieFile.close();


  if (argc == 2){
    for (auto it = movies.begin(); it != movies.end(); ++it) {
        cout << (*it).name << ", " << (*it).rating << endl;
    }
    return 0;
  }
    //specifies the prefixes
  
  if (argc >=3) {
    stringstream highestRatedMovies;

    for (int i = 2; i < argc; i++) {  
        std::priority_queue<Movie,std::vector<Movie>,ComparisonClass> prefixList;
        //cout << endl << "Movies starting with: " << argv[i] << " " << endl;
        for (auto it = movies.begin(); it != movies.end(); ++it) {
            if (hasPrefix(string(argv[i]),(*it).name)) {
                //cout << (*it).name << " " << (*it).rating << endl;
                prefixList.push(*it);
            }
        }
        
        //priority queue (if greater than the left, insert at the left)
        //  For each prefix,
        //  Find all movies that have that prefix and store them in an appropriate data structure
        //  If no movie with that prefix exists print the following message

        
        if (prefixList.empty()) {
            cout << "No movies found with prefix "<< argv[i] << endl; 
        } else {
            //  For each prefix,
            //  Print the highest rated movie with that prefix if it exists.
            highestRatedMovies << "Best movie with prefix " << argv[i] << " is: " << prefixList.top().name << " with rating " << std::fixed << std::setprecision(1) << prefixList.top().rating << endl;
        
            while (!prefixList.empty()) {
                cout << prefixList.top().name << ", " << std::fixed << std::setprecision(1) << prefixList.top().rating << endl;
                prefixList.pop();
            }
        }
        cout << endl;
    }

    cout << highestRatedMovies.str();
  }

  return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    if (line.length() <= 0) return false;
    string tempRating = "";

    bool flag = false;
    movieName = tempRating = "", movieRating = 0.0, flag = false;

    for (int i = 0; i < line.length(); i++){
        if(flag) tempRating += line[i];
        else if(line[i]==','&& line[0]!='"') flag = true;
        else {
            if(i==0 && line[0]=='"') continue;
            if(line[i]=='"'){ i++; flag=true; continue;}
            movieName += line[i];
        }
    }
    
    movieRating = stod(tempRating);
    return true;
}

bool hasPrefix(const string &prefix, const string &movieName) {
    if (prefix.length() > movieName.length()) {
        return false;
    }
    for (int i = 0; i < prefix.length(); i++) {
        if (prefix[i]!=movieName[i]) {
            return false;
        }
    }
    return true;
}
