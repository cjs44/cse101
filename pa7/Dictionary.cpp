/************************************************
 * Caitlin Smith - csmith44
 * 2023 Spring CSE101 PA7
 * Dictionary.cpp
 * Dictionary ADT
 *************************************************/

#include <string>
#include <iostream>
#include <stdexcept>
#include "Dictionary.h"

// private

// Node Constructor -------------------------------------------------------
// Creates Node in the empty state.
Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}
//---------------------------------------------------------------------------

// Helper Functions (Optional) ---------------------------------------------
// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string &s, Node *R) const{
    // left print right
    // check not nil
    if (R != nil){
        inOrderString(s, R->left);
        // "print"
        s += R->key + " : ";
        s += std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }

}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string &s, Node *R) const{
    // print left right
    if (R != nil){
        // "print"
        s += R->key + "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node *R, Node *N){
    // print left right
    if (R != nil && R != N){
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node *R){
    // left right print
    if (R != nil){
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node *Dictionary::search(Node *R, keyType k) const{
    // doesn't exist
    if (R == nil || k == R->key){
        return R;
    }
    // search and return address of node
    // search left
    else if (k < R->key){
        return search(R->left, k);
    }
    // k > R->key
    // search right
    else {
        return search(R->right, k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node *Dictionary::findMin(Node *R){
    // empty, return nil
    if (R == nil){
        return nil;
    }
    Node *N = R;
    // keep going down
    while (N->left != nil){
        N = N->left;
    }
    return N;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node *Dictionary::findMax(Node *R){
    // empty, return nil
    if (R == nil){
        return nil;
    }
    Node *N = R;
    // keep going down
    while (N->right != nil){
        N = N->right;
    }
    return N;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost
// Node, or is nil, returns nil.
Dictionary::Node *Dictionary::findNext(Node *N){
    // case 1
    // rightmost node
    if (N->right != nil){
        return findMin(N->right);
    }
    // case 2
    Node *P = N->parent;
    while (P != nil && N == P->right){
        N = P;
        P = P->parent;
    }
    return P;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost
// Node, or is nil, returns nil.
Dictionary::Node *Dictionary::findPrev(Node *N){
    // case 1
    // leftmost node
    if (N->left != nil){
        return findMax(N->left);
    }
    // case 2
    Node *P = N->parent;
    while (P != nil && N == P->left){
        N = P;
        P = P->parent;
    }
    return P;
}
//---------------------------------------------------------------------------

// public

// Class Constructors & Destructors ----------------------------------------
// Creates new Dictionary in the empty state.
Dictionary::Dictionary(){
    nil = new Node("/", -1);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary &D){
    nil = new Node("/", -1);
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary(){
    postOrderDelete(root);
    delete nil;
}
//---------------------------------------------------------------------------

// Access functions --------------------------------------------------------
// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
    // search for k
    Node *N = search(root, k);
    if (N != nil){
        return true;
    }
    // not found
    else {
        return false;
    }
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType &Dictionary::getValue(keyType k) const{
    // precondition
    if (contains(k)){
        Node *N = search(root, k);
        return N->val;
    }
    else {
        throw std::logic_error("Dictionary: getValue(): key does not exist");
    }
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false
// otherwise.
bool Dictionary::hasCurrent() const{
    if (current != nil){
        return true;
    }
    else {
        return false;
    }
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent()
keyType Dictionary::currentKey() const{
    // precondition
    if (hasCurrent()){
        return current->key;
    }
    else {
        throw std::logic_error("Dictionary: currentKey(): current is not defined");
    }
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType &Dictionary::currentVal() const{
    // precondition
    if (hasCurrent()){
        return current->val;
    }
    else {
        throw std::logic_error("Dictionary: currentKey(): current is not defined");
    }
}
//---------------------------------------------------------------------------

// Manipulation procedures -------------------------------------------------
// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v,
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
    // use compare funct
    Node *y = nil;
    Node *x = root;
    while (x != nil){
        y = x;
        if (k.compare(x->key) < 0){
            x = x->left;
        }
        // repeat
        else if (k.compare(x->key) == 0){
            x->val = v;
            return;
        }
        else {
            x = x->right;
        }
    }
    Node *z = new Node(k, v);
    z->left = z->right = nil;
    z->parent = y;
    if (y == nil){
        root = z;
    }
    else if (z->key.compare(y->key) < 0){
        y->left = z;
    }
    else {
        y->right = z;
    }
    // pair added
    num_pairs += 1;
}

// transplant()
// replace u with v
void Dictionary::transplant(Node *u, Node *v){
    if (u->parent == nil){
        root = v;
    }
    else if (u == u->parent->left){
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    if (v != nil){
        v->parent = u->parent;
    }
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
    // find k 
    if (!contains(k)){
        throw std::logic_error("Dictionary: remove(): k not in tree");
    }
    Node *z = search(root, k);
    // if current, make it nil
    if (z == current){
        current = nil;
    }
    // case 1 / 2.1
    if (z->left == nil){
        transplant(z, z->right);
    }
    // case 2.2
    else if (z->right == nil){
        transplant(z, z->left);
    }
    // case 3
    else {
        Node *y = findMin(z->right);
        if (y->parent != z){
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    // delete the node
    delete z;
    // pair removed
    num_pairs -= 1;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::begin(){
    if (num_pairs != 0){
        current = findMin(root);
    }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::end(){
    if (num_pairs != 0){
        current = findMax(root);
    }
}

// next()
// If the current iterator is not at the last pair, advances current
// to the next pair (as defined by the order operator < on keys). If
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
    if (hasCurrent()){
        // not at last pair
        if (current != findMax(root)){
            current = findNext(current);
        }
        else {
            current = nil;
        }
    }
    else {
        throw std::logic_error("Dictionary: next(): current is not defined");
    }
}

// prev()
// If the current iterator is not at the first pair, moves current to
// the previous pair (as defined by the order operator < on keys). If
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
    if (hasCurrent()){
        // not at first pair
        if (current != findMin(root)){
            current = findPrev(current);
        }
        else {
            current = nil;
        }
    }
    else {
        throw std::logic_error("Dictionary: prev(): current is not defined");
    }
}
//---------------------------------------------------------------------------

// Other Functions ---------------------------------------------------------
// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value
// are separated by the sequence space-colon-space " : ". The pairs are arranged
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
    std::string S;
    inOrderString(S, root);
    return S;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
    std::string S;
    preOrderString(S, root);
    return S;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary &D) const{
    if (to_string() == D.to_string()){
        return true;
    }
    else {
        return false;
    }
}
//---------------------------------------------------------------------------

// Overloaded Operators ----------------------------------------------------
// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream &operator<<(std::ostream &stream, Dictionary &D){
    return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals().
bool operator==(const Dictionary &A, const Dictionary &B){
    return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary &Dictionary::operator=(const Dictionary &D){
    if (this != &D){
        Dictionary temp = D;
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }
    return *this;
}
//---------------------------------------------------------------------------