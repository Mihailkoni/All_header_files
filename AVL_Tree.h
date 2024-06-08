#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Circular_Doubly_Linked_List.h"
using namespace std;

struct Node {
    int bal;
    Node* left;
    Node* right;
    Circle* head;
    struct group {
        char l;
        int s;
    }g;
};


bool add_to_tree(char l, int s, Node*& p, bool& h, int num) {
    Node* p1;
    Node* p2;

    if (p == nullptr) {
        p = new Node();
        p->g.l = l;
        p->g.s = s;
        p->left = nullptr;
        p->right = nullptr;
        p->bal = 0;
        add_to_list(p->head, num);
        h = true;
        return true;
    }
    else if (p->g.l > l || (p->g.l == l && p->g.s > s)) {
        add_to_tree(l, s, p->left, h, num);
        if (h) {
            if (p->bal == 1) {
                p->bal = 0;
                h = false;
            }
            else if (p->bal == 0) {
                p->bal = -1;
            }
            else {
                p1 = p->left;
                if (p1->bal == -1) {
                    p->left = p1->right;
                    p1->right = p;
                    p->bal = 0;
                    p = p1;
                }
                else {
                    p2 = p1->right;
                    p1->right = p2->left;
                    p2->left = p1;
                    p->left = p2->right;
                    p2->right = p;
                    if (p2->bal == -1) {
                        p->bal = 1;
                    }
                    else {
                        p->bal = 0;
                    }
                    if (p2->bal == 1) {
                        p1->bal = -1;
                    }
                    else {
                        p1->bal = 0;
                    }
                    p = p2;
                }
                p->bal = 0;
                h = false;
            }
        }
    }
    else if (p->g.l < l || (p->g.l == l && p->g.s < s)) {
        add_to_tree(l, s, p->right, h, num);
        if (h) {
            if (p->bal == -1) {
                p->bal = 0;
                h = false;
            }
            else if (p->bal == 0) {
                p->bal = 1;
            }
            else {
                p1 = p->right;
                if (p1->bal == 1) {
                    p->right = p1->left;
                    p1->left = p;
                    p->bal = 0;
                    p = p1;
                }
                else {
                    p2 = p1->left;
                    p1->left = p2->right;
                    p2->right = p1;
                    p->right = p2->left;
                    p2->left = p;
                    if (p2->bal == 1) {
                        p->bal = -1;
                    }
                    else {
                        p->bal = 0;
                    }
                    if (p2->bal == -1) {
                        p1->bal = 1;
                    }
                    else {
                        p1->bal = 0;
                    }
                    p = p2;
                }
                p->bal = 0;
                h = false;
            }
        }
    }
    else {
        add_to_list(p->head, num);
    }
    return true;
}

void print_tree(Node* root, string indent, bool last) {
    if (root != nullptr) {
        cout << indent;
        if (last) {
            cout << "R----";
            indent += "   ";
        }
        else {
            cout << "L----";
            indent += "|  ";
        }
        cout << root->g.l << root->g.s << "(";
        print_list(root->head);
        cout << ")" << endl;
        print_tree(root->left, indent, false);
        print_tree(root->right, indent, true);
    }
}

void post_order(Node* p, ofstream& file) {
    if (p == nullptr) {
        return;
    }
    post_order(p->left, file);
    post_order(p->right, file);
    file << p->g.l << p->g.s << "\n";
}

bool search_node(Node* root, char l, int s) {
    if (root == nullptr) {
        return false;
    }
    else if (root->g.l == l && root->g.s == s) {
        return true;
    }
    else if (root->g.l < l || (root->g.l == l && root->g.s < s)) {
        return search_node(root->right, l, s);
    }
    else {
        return search_node(root->left, l, s);
    }
}

void delete_tree(Node*& root) {
    if (root != nullptr) {
        delete_tree(root->left);
        delete_tree(root->right);
        delete_list(root->head);
        delete root;
        root = nullptr;
    }
}

void balanceL(Node*& p, bool& h) {
    Node* p1;
    Node* p2;
    if (p->bal == -1) {
        p->bal = 0;
    }
    else if (p->bal == 0) {
        p->bal = 1;
        h = false;
    }
    else {
        p1 = p->right;
        if (p1->bal >= 0) { 
            p->right = p1->left;
            p1->left = p;
            if (p1->bal == 0) {
                p->bal = 1;
                p1->bal = -1;
                h = false;
            }
            else {
                p->bal = 0;
                p1->bal = 0;
            }
            p = p1;
        }
        else { 
            p2 = p1->left;
            p1->left = p2->right;
            p2->right = p1;
            p->right = p2->left;
            p2->left = p;
            if (p2->bal == 1) {
                p->bal = -1;
            }
            else {
                p->bal = 0;
            }
            if (p2->bal == -1) {
                p1->bal = 1;
            }
            else {
                p1->bal = 0;
            }
            p = p2;
            p2->bal = 0;
        }
    }
}


void balanceR(Node*& p, bool& h) {
    Node* p1;
    Node* p2;
    if (p->bal == 1) {
        p->bal = 0;
    }
    else if (p->bal == 0) {
        p->bal = -1;
        h = false;
    }
    else { 
        p1 = p->left;
        if (p1->bal <= 0) {
            p->left = p1->right;
            p1->right = p;
            if (p1->bal == 0) {
                p->bal = -1;
                p1->bal = 1;
                h = false;
            }
            else {
                p->bal = 0;
                p1->bal = 0;
            }
            p = p1;
        }
        else { 
            p2 = p1->right;
            p1->right = p2->left;
            p2->left = p1;
            p->left = p2->right;
            p2->right = p;
            if (p2->bal == -1) {
                p->bal = 1;
            }
            else {
                p->bal = 0;
            }
            if (p2->bal == 1) {
                p1->bal = -1;
            }
            else {
                p1->bal = 0;
            }
            p = p2;
            p2->bal = 0;
        }
    }
}

void del_Right(Node*& root, Node*& q, bool& h) {
    if (root->left != nullptr) {
        del_Right(root->left, q, h);
        if (h) {
            balanceL(root, h);
        }
    }
    else {
        q->g = root->g;
        q->head = root->head;
        q = root;
        root = root->right;
        h = true;
    }
}

bool DRL(char l, int s, Node*& root, bool& h, int num) {
    if (root == nullptr) {
        return true;
    }
    else if (root->g.l > l || (root->g.l == l && root->g.s > s)) {
        DRL(l, s, root->left, h, num);
        if (h) {
            balanceL(root, h);
        }
    }
    else if (root->g.l < l || (root->g.l == l && root->g.s < s)) {
        DRL(l, s, root->right, h, num);
        if (h) {
            balanceR(root, h);
        }
    }
    else {
        if (root->g.l == l && root->g.s == s) {
            if (((root->head)->next)->data != root->head->data) {
                delete_from_list(root->head, num);
                return true;
            }
            else {
                if (root->head->data == num) {
                    Node* q = root;
                    if (q->right == nullptr) {
                        root = q->left;
                        h = true;
                        return true;
                    }
                    else if (q->left == nullptr) {
                        root = q->right;
                        h = true;
                        return true;
                    }
                    else {
                        del_Right(q->right, q, h);
                        if (h) {
                            balanceR(root, h);
                        }
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void read_file(Node*& root, const string& filename) {
    string line;
    int num = 0, s;
    char l;
    bool h;

    ifstream in(filename);
    if (in.is_open()) {
        while (getline(in, line)) {
            num += 1;
            l = line[0];
            s = stoi(line.substr(1, 4));
            add_to_tree(l, s, root, h, num);
        }
        in.close();
    }
}

void write_to_file(Node*& root, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return;
    }
    post_order(root, file);
    file.close();
}