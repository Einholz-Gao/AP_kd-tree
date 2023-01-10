#include <iostream>
#include <vector>
#include <list>
#include <memory>

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
    std::vector<int> _ref_point;
    float _ref_dist = 10000000;
    std::shared_ptr<Node> minNode(std::shared_ptr<Node>, std::shared_ptr<Node>, std::shared_ptr<Node>, int);
    std::shared_ptr<Node> findMin(std::shared_ptr<Node>, unsigned, unsigned);
    std::shared_ptr<Node> kd_delete(std::shared_ptr<Node>, std::vector<int>, int);
    std::shared_ptr<Node> KNN(std::shared_ptr<Node> , std::vector<int> , unsigned );
    std::shared_ptr<Node> closest(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2, std::vector<int> point);
    float distance(std::vector<int>, std::vector<int>);
    void kd_insert(std::shared_ptr<Node> , const std::vector<int>& );
    void printKDTreeBranches(std::shared_ptr<Node>, bool, const std::string&);
    void printKDTree();

    KD_Tree(){};
    KD_Tree(std::shared_ptr<Node> root) : _root_node(root) {};
};


