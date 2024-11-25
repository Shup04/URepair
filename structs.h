#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
#include <vector>
#include <queue>

// Define Contractor struct
struct Contractor {
    int id = 0;
    std::string name = "";
    int rate = 0;
    std::string skillset = "";

    // Define operator==
    bool operator==(const Contractor& other) const {
        return id == other.id; // Compare based on ID
    }
};

// Define Job struct
struct Job {
    int id = 0;
    std::string description = "";
    std::string requiredSkill = "";
    float price = 0.0;
    int urgency = 0; // Lower value = higher urgency
};

// Define a comparator for Job priority
struct JobComparator {
    bool operator()(const Job& a, const Job& b) {
        if (a.urgency == b.urgency) {
            return a.price < b.price; // Lower price comes last if urgency is equal
        }
        return a.urgency > b.urgency; // Higher urgency comes first
    }
};

struct ContractorComparator {
    bool operator()(const Contractor& a, const Contractor& b) {
        return a.rate < b.rate; // Sort by rate in ascending order
    }
};

struct JobPriceComparator {
    bool operator()(const Job& a, const Job& b) const {
        return a.price < b.price; // Sort by price in ascending order
    }
};

template <typename T>
struct BSTNode {
    T data;               // Store the data (Job, Contractor, etc.)
    BSTNode* left;        // Pointer to the left child
    BSTNode* right;       // Pointer to the right child

    BSTNode(const T& value) : data(value), left(nullptr), right(nullptr) {} // Constructor
};

template <typename T, typename Compare>
class BST {
private:
    BSTNode<T>* root;
    Compare comparator;

    BSTNode<T>* insert(BSTNode<T>* node, const T& value) {
        if (node == nullptr) return new BSTNode<T>(value);
        if (comparator(value, node->data)) {
            node->left = insert(node->left, value);
        } else {
            node->right = insert(node->right, value);
        }
        return node;
    }

    BSTNode<T>* search(BSTNode<T>* node, const T& value) {
        if (node == nullptr || node->data == value) return node;
        if (comparator(value, node->data)) {
            return search(node->left, value);
        } else {
            return search(node->right, value);
        }
    }

    void inOrderTraversal(BSTNode<T>* node, std::vector<T>& result) {
        if (node != nullptr) {
            inOrderTraversal(node->left, result);
            result.push_back(node->data);
            inOrderTraversal(node->right, result);
        }
    }

public:
    BST() : root(nullptr) {}

    void insert(const T& value) {
        root = insert(root, value);
    }

    BSTNode<T>* search(const T& value) {
        return search(root, value);
    }

    std::vector<T> inOrder() {
        std::vector<T> result;
        inOrderTraversal(root, result);
        return result;
    }
};

#endif // STRUCTS_H
