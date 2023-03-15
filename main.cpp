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
        cout << (*it).name << ", " << std::fixed << std::setprecision(1) << (*it).rating << endl;
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
/*
for loop runs m times (for every prefix)
    for loop runs n times (for every movie)
        n comparisons
            k priority queue insertions -- insertion time is O(logk)
    O(n)

    concatenate to highestRatedMovies
    while loop runs k times (for each movie with the prefix)
        priority queue removal - worst case is O(logk)
    O(k)

worst-case time complexity is O(m)*O(n+k)
=>O(mn)

space-complexity:

creating the priority queue is the dominant operation: 
has space complexity O(k)
destroys priority queue at the end of each prefix loop

also concatenating m strings for highestRatedMovies string O(k)


worst-case space-complexity is O(k+m)

Reflection: 
I designed my algorithm mainly to optimize space complexity
without much consideration for time complexity

I used a priority queue to store the movies that had the desired prefix,
Even though this method has only O(k) space complexity, I needed the custom sorting
capability of a priority queue to change the order the movies are printed out,
as the movies set data structure stores the movies in alphabetical order while
the lab called for the movies with prefixes to be printed out in rating order.

While using this priority queue method, if I had wanted to optimize my time complexity to be less than
O(mn), I could perhaps use a processing function while iterating through movies
to make subsequent prefix operations faster. There are many possible methods.
For example, in the first pass, I could construct a tree of movies ordered lexicographically,
When I wanted to find all movies with a prefix, I would search for the first node that has the desired prefix, 
so that all of its children also have that prefix, thus lessening search times. 

Overall, I chose this implementation for its simplicity, 
but I could significantly improve the time complexity. I believe my space complexity is 
adequate given the constraints of the problem

*/







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
