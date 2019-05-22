#include <iostream>
#include <bits/stl_bvector.h>

using namespace std;

const auto STRIP_SIZE = 3;

struct Building {
public:
    Building(int s, int e, int h) : start(s), end(e), height(h) {}

    friend ostream & operator << (ostream &out, const Building& strip){
        out << "( " << strip.start << ", " << strip.end << " ," << strip.height << ") ";

        return out;
    }

    int start;
    int end;
    int height;
};

vector<Building> loadStrip() {
    int stripLength;
    cin >> stripLength;

    vector<Building> strip(stripLength);
    while(stripLength > 0){
        int start, end, height;
        cin >> start >> end >> height;

        strip.push_back(Building(start, end, height));

        stripLength -= STRIP_SIZE;
    }

    return strip;
};

void print(vector<Building> skyline){
    for(int i = 0; i < skyline.size(); i++){
        cout << skyline[i];
    }
}

int main() {
    int cases;
    cin >> cases;

    while(cases-- > 0){
        vector<Building> strip = loadStrip();

        //skyline

        //print skyline
        print(strip);
        cout << "\n";
    }

    return 0;
};
