// To create ADT that implements the "set" concept.a. Add (new Element) -Place a value into
// the set, b. Remove (element) Remove the value c. Contains (element) Return true if
// element is in collection,d. Size () Return number of values in collection Iterator () Return
// an iterator used to loop over collection, e. Intersection of two sets , f. Union of two sets,g.
// Difference between two sets,h. Subset
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Set {
private:
    vector<int> data;

public:
    // a. Add (new Element)
    void add(int element) {
        if (!contains(element)) {
            data.push_back(element);
        }
    }

    // b. Remove (element)
    void remove(int element) {
        for (int i = 0; i < data.size(); i++) {
            if (data[i] == element) {
                data.erase(data.begin() + i);
                return;
            }
        }
    }

    // c. Contains (element)
    bool contains(int element) {
        for (int x : data) {
            if (x == element) return true;
        }
        return false;
    }

    // d. Size ()
    int size() {
        return data.size();
    }

    // Iterator/Display helper
    void display() {
        cout << "{ ";
        for (int i = 0; i < data.size(); i++) {
            cout << data[i] << (i == data.size() - 1 ? "" : ", ");
        }
        cout << " }";
    }

    // e. Intersection
    Set intersection(Set other) {
        Set result;
        for (int x : data) {
            if (other.contains(x)) {
                result.add(x);
            }
        }
        return result;
    }

    // f. Union
    Set unionSet(Set other) {
        Set result = *this; // Start with all elements from this set
        for (int x : other.data) {
            result.add(x); // add() handles duplicates automatically
        }
        return result;
    }

    // g. Difference (Elements in A but not in B)
    Set difference(Set other) {
        Set result;
        for (int x : data) {
            if (!other.contains(x)) {
                result.add(x);
            }
        }
        return result;
    }

    // h. Subset (Is this set a subset of 'other'?)
    bool isSubsetOf(Set other) {
        for (int x : data) {
            if (!other.contains(x)) return false;
        }
        return true;
    }
};

int main() {
    Set setA, setB;

    // Adding elements
    setA.add(1); setA.add(2); setA.add(3); setA.add(4);
    setB.add(3); setB.add(4); setB.add(5); setB.add(6);

    cout << "Set A: "; setA.display(); cout << endl;
    cout << "Set B: "; setB.display(); cout << endl;

    // Union
    Set resUnion = setA.unionSet(setB);
    cout << "Union: "; resUnion.display(); cout << endl;

    // Intersection
    Set resInter = setA.intersection(setB);
    cout << "Intersection: "; resInter.display(); cout << endl;

    // Difference (A - B)
    Set resDiff = setA.difference(setB);
    cout << "Difference (A-B): "; resDiff.display(); cout << endl;

    // Subset Check
    Set setC; setC.add(3); setC.add(4);
    cout << "Is {3, 4} a subset of Set A? " << (setC.isSubsetOf(setA) ? "Yes" : "No") << endl;

    return 0;
}