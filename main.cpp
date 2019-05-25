#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>

using namespace std;

const auto STRIP_SIZE = 3;

struct Building {
    Building() {}
    Building(const Building& b) : Building(b.start, b.end, b.height) {}
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
    Skyline() {}
    Skyline(int s, int h) : start(s), height(h) {}
    Skyline(const Building& building){
        start = building.start;
        height = building.height;

        next = make_shared<Skyline>(building.end, 0);
    }

    bool operator<(const shared_ptr<Skyline>& other) const {
        return height < other->height;
    }

    friend ostream & operator << (ostream &out, const Skyline& skyline){
        out << "( " << skyline.start << ", " << skyline.height << ") ";

        return out;
    }

    int start;
    int height;
    shared_ptr<Skyline> next;
};




unique_ptr<vector<Building>> loadStrip() {
    int stripLength;
    cin >> stripLength;

    auto strip = new vector<Building>();
    strip->resize(stripLength); //allocate memory to avoid resizing
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

shared_ptr<Skyline> getNextSkyline(shared_ptr<Skyline>& left, shared_ptr<Skyline>& right,
        int& leftHeight, int& rightHeight) {
    int maxHeight;
    shared_ptr<Skyline> toReturn;

    if(left < right){
        leftHeight = left->height;
        maxHeight = max(leftHeight, rightHeight);

        toReturn = make_shared<Skyline>(left->start, maxHeight);
        left = left->next;
    }else{
        rightHeight = right->height;
        maxHeight = max(leftHeight, rightHeight);

        toReturn = make_shared<Skyline>(right->start, maxHeight);
        right = right->next;
    }

    return toReturn;
}

shared_ptr<Skyline> merge(shared_ptr<Skyline>& leftSkyline, shared_ptr<Skyline>& rightSkyline) {
    auto left = leftSkyline < rightSkyline ? leftSkyline : rightSkyline;
    auto right = leftSkyline < rightSkyline ? rightSkyline : leftSkyline;

    int leftHeight = 0;
    int rightHeight = 0;

    shared_ptr<Skyline> mergedSkylines = getNextSkyline(left, right, leftHeight, rightHeight);
    shared_ptr<Skyline> whereToInsert = mergedSkylines;
    while(left && right){
        whereToInsert->next = getNextSkyline(left, right, leftHeight, rightHeight);
        whereToInsert = whereToInsert->next;
    }

    if(left){
        whereToInsert->next = left;
    }

    if(right){
        whereToInsert->next = right;
    }

    return mergedSkylines;
}

shared_ptr<Skyline> find_skyline(unique_ptr<vector<Building>>& strip, int from, int to){
    if(from == to){
        return make_shared<Skyline>(strip->at(from));
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

void print(shared_ptr<Skyline> skyLine) {
    shared_ptr<Skyline> toPrint = skyLine;

    while (toPrint){
        cout << toPrint.operator*() << " ";
        toPrint = toPrint->next;
    }
}

int main() {
    int cases = 1;
    //cin >> cases;

    while(cases-- > 0){
        auto strip = loadStrip();

        shared_ptr<Skyline> skyline = find_skyline(strip, 0, strip->size());

        print(skyline);
        cout << "\n";
    }

    return 0;
}
