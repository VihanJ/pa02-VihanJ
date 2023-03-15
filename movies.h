#include <string>

struct Movie { 
    std::string name;
    double rating;
    Movie(std::string n, double r) : name(n), rating(r) {}
    bool operator<(const Movie m2) const {
        return (name < m2.name);
    }
    bool operator== (const Movie m2) const {
        return (name==m2.name && rating==m2.rating);
    }
};

class ComparisonClass {
    public: 
        bool operator() (Movie m1, Movie m2) {
            if (m1.rating==m2.rating) {
                return (m1.name > m2.name);
            } else {
                return m1.rating < m2.rating;
            }
            
        }
};