#ifndef KD_TREE_H
#define KD_TREE_H

#include <iostream>
#include <vector>
#include <list>
#include <memory>

#define K 3

// define a Node struct
struct Node {
  std::vector<int> data;
  // Node *left = nullptr, *right = nullptr;
  std::shared_ptr<Node> left;
  std::shared_ptr<Node> right;

  Node(std::vector<int> vec) {
    data = vec;
  }

  Node() {}
};

class KD_Tree {
  private:
    std::shared_ptr<Node> _root_node;
  public:
    std::shared_ptr<Node> minNode(std::shared_ptr<Node> x, std::shared_ptr<Node> y, std::shared_ptr<Node> z, int d);
    std::shared_ptr<Node> findMin(std::shared_ptr<Node> node, unsigned d, unsigned depth);
    std::shared_ptr<Node> kd_delete(std::shared_ptr<Node> node, std::vector<int> point, int depth=0);
    std::shared_ptr<Node> KNN(std::shared_ptr<Node> node, std::vector<int> point, unsigned cd=0);
    std::shared_ptr<Node> closest(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2, std::vector<int> point);
    float distanceSquared(std::vector<int> a, std::vector<int> b);
    void kd_insert(std::shared_ptr<Node> node, const std::vector<int>& point);
    void printKDTreeBranches(std::shared_ptr<Node> node, bool left, const std::string& prefix);
    void printKDTree();

    KD_Tree(){};
    KD_Tree(std::shared_ptr<Node> root) : _root_node(root) {};
};

#endif