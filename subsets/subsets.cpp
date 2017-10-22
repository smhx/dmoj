#include <iostream>
#include <set>
#include <algorithm>
#include <string>
using namespace std;

const string ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

class Node {
public:
    Node(char c) {
        letter = c;
        isActive = false;
    }
    ~Node() {}
    set<Node*> getParents() {return parents;}

    void addElement(char c) {
        elements.insert(c);
        for (auto node : parents) {
            set<char> e = node->getElements();
            if ( e.find(c) == e.end() ) {
                node->addElement(c);
            } 
        }
    }

    
    set<char> getElements() {return elements;}
    
    void addChild(Node* child) {
        for (auto c: child->getElements()) {
            addElement(c);
        }
    }
    
    void addParent(Node* par) {
        parents.insert(par);
    }
    bool isActive;
    char getLetter() {return letter;}
private:
    set<Node*> parents;
    char letter;
    set<char> elements;
};


int main () {

    Node* nodes[26];

    for (int i = 0; i < 26; i++) {
        nodes[i] = new Node(ALPHA[i]);
    }

    int N;
    cin >> N;
    char left, right;
    string input;
    for (int i = -1; i < N; i++) {

        getline(cin, input);
        if (i==-1) continue;
        left = input[0];
        right = input[input.size()-1];
        int index = left-'A';
        nodes[index]->isActive = true;
        if ( islower(right) ) {
            nodes[index]->addElement(right);
        } else {
            int ri = right-'A';
            nodes[ri]->isActive = true;
            nodes[index]->addChild(nodes[ri]);
            nodes[ri]->addParent(nodes[index]);
        }
    }

    for (int i = 0; i < 26; i++) {
        Node* node = nodes[i];
        if (node->isActive) {
            cout << node->getLetter() << " = {";
            set<char> elements = node->getElements();
            int j=0;
            for (auto c: elements) {
                j++;
                cout << c;
                if (j < (int)elements.size()) {
                    cout << ",";
                } 
            }
            cout << "}" << endl;
        }
    }

    for (int i = 0; i < 26; i++) {
        delete nodes[i];
    }
    
}