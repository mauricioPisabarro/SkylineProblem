#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>

using namespace std;

const auto STRIP_SIZE = 3;

struct Building {
    Building() {}
    Building(int s, int e, int h) : start(s), end(e), height(h) {}

    friend ostream & operator << (ostream &out, const Building& strip){
        out << "( " << strip.start << ", " << strip.end << " ," << strip.height << ") ";

        return out;
    }

    bool operator<(const Building& otherBuilding) const {
        return start < otherBuilding.start;
    }

    int start;
    int end;
    int height;
};

struct Skyline {
    Skyline(Building b, Skyline* n) : building(b), next(n) {}

    Building building;
    unique_ptr<Skyline> next;
};

unique_ptr<vector<Building>> loadStrip() {
    int stripLength;
    cin >> stripLength;

    auto strip = new vector<Building>();
    while(stripLength > 0){
        int start, end, height;
        cin >> start >> end >> height;

        strip->push_back(Building(start, end, height));

        stripLength -= STRIP_SIZE;
    }

    // IMPORTANT STEP O(log(n)) <<<<<<<<<<<<<<<<<<<<<<<<<<<<===================================
    sort(strip->begin(), strip->end());

    return unique_ptr<vector<Building>>(strip);
}

unique_ptr<Skyline> merge(unique_ptr<Skyline>& left, unique_ptr<Skyline>& right) {
    return NULL;
}

unique_ptr<Skyline> find_skyline(unique_ptr<vector<Building>>& strip, int from, int to){
    if(from == to){
        return make_unique<Skyline>(strip->at(from), NULL);
    }

    int middle = (to - from)/2 + from/2; //to avoid overflow

    auto left = find_skyline(strip, from, middle);
    auto right = find_skyline(strip, middle + 1, to);

    return merge(left, right);
}


template <class T>
void print(unique_ptr<vector<T>>& v){
    for(T t : v.operator*()){
        cout << t;
    }
}

int main() {
    int cases = 1;
    //cin >> cases;

    while(cases-- > 0){
        auto strip = loadStrip();

        unique_ptr<Skyline> skyline = find_skyline(strip, 0, strip->size());

        //print skyline
        print(strip);
        cout << "\n";
    }

    return 0;
}
