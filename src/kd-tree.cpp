#include "kd-tree.h"
#include "helper.h"
#include <cmath>

/*
  Finds the smallest node of three nodes
  @param x the 1st node
  @param y the 2nd node
  @param z the 3rd node
  @param d the dimension of the smallest value you want to find(d'th dimension in KD tree)
  @returns a shared_ptr to the smallest node of three nodes
*/
std::shared_ptr<Node> KD_Tree::minNode(std::shared_ptr<Node> x, std::shared_ptr<Node> y, std::shared_ptr<Node> z, int d)
{
    std::shared_ptr<Node> res = x;
    if (y != nullptr && y->data[d] < res->data[d])
       res = y;
    if (z != nullptr && z->data[d] < res->data[d])
       res = z;
    return res;
}

/*
  Recursively finds minimum of d'th dimension in KD tree
  @param node the root node of the tree or sub-tree
  @param d the dimension of the smallest value you want to find(d'th dimension in KD tree)
  @param depth the current depth(x,y,or z...) of the tree
  @returns a share_ptr to the minimum of the d'th dimensioin in KD tree
*/
std::shared_ptr<Node> KD_Tree::findMin(std::shared_ptr<Node> node, unsigned d, unsigned depth)
{
    if (node == nullptr)
        return nullptr;

    // cd -> current dimention
    unsigned cd = depth % K;

    // Compare point with node with respect to cd (Current dimension)
    if (cd == d)
    {
        if (node->left == nullptr)
            return node;
        return findMin(node->left, d, depth+1);
    }
    else
    return minNode(node,
               findMin(node->left, d, depth+1),
               findMin(node->right, d, depth+1), d);
}

/*
  calculate the distance between two points
  @param a point
  @param b point
  @returns the distance between two points
*/
double distance(std::vector<int> a, std::vector<int> b) {
  double sum = 0.0;
  for (int i = 0; i < K; i++) {
    sum += (a[i] - b[i]) * (a[i] - b[i]);
  }
  return std::sqrt(sum);
}
std::vector<int> best_point;
int best_dist = 20;
/*
  Recursively Nearest Neighbor Searching
  @param node the root node of the tree or sub-tree
  @param point to find the nearest point to this.
  @param cd the current dimension(x,y,z...)
  @returns a nearest point to the parameter point
*/
std::vector<int> KNN(std::shared_ptr<Node> node, std::vector<int> point,
                     unsigned cd) {

  if (node == nullptr ||
      distance(point, node->data) >
          best_dist) { // this point must be in a base range. cant be too far.
  } else {
    auto dist = distance(point, node->data);
    if (dist < best_dist) {
      best_point = node->data;
      best_dist = dist;
    }
    if (point[cd] < node->data[cd]) {
      KNN(node->left, point, (cd + 1) % K);
      KNN(node->right, point, (cd + 1) % K);
    } else {
      KNN(node->right, point, (cd + 1) % K);
      KNN(node->left, point, (cd + 1) % K);
    }
  }
  return best_point;
}

/*delete point to a kd-tree
  @param node the root node of the tree or sub-tree
  @param point the point to be deleted
  @param depth the current depth of the tree
  @returns a shared_ptr to the root of the trimmed KD tree
*/
std::shared_ptr<Node> KD_Tree::kd_delete(std::shared_ptr<Node> node, std::vector<int> point, int depth=0)
{
    // Given point is not present
    if (node == nullptr)
        return nullptr;

    // Find dimension of current node
    int cd = depth % K;

    // If the point to be deleted is present at root
    if (node->data == point)
    {
        // If right subtree is not nullptr
        if (node->right != nullptr)
        {
            // Find minimum of root's dimension in right subtree
            std::shared_ptr<Node> min = findMin(node->right, cd, 0);

            // Copy the minimum to node
            for (int i=0; i<K; i++)
                node->data[i] = min->data[i];

            // swap subtrees and use min(cd) from new right tree.
            node->right = kd_delete(node->right, min->data, depth+1);
        }
        // If the left is not nullptr
        else if (node->left != nullptr)
        {
            std::shared_ptr<Node> min = findMin(node->left, cd, 0);
            for (int i=0; i<K; i++)
                node->data[i] = min->data[i];
            node->left = kd_delete(node->left, min->data, depth+1);
        }
        else // If node to be deleted is leaf node
        {
            // delete node;
            return nullptr;
        }
        return node;
    }

    // This is not the point:
    if (point[cd] < node->data[cd])
        node->left = kd_delete(node->left, point, depth+1);
    else
        node->right = kd_delete(node->right, point, depth+1);
    return node;
}

/*insert point to a kd-tree
  @param node the root node of the tree or sub-tree
  @param point the point to be inserted
*/
void KD_Tree::kd_insert(std::shared_ptr<Node> node, const std::vector<int>& point) {
  int cd = 0;  // cutting dimension
  bool inserted = false;  // a flag indicating if insertion is completed
  while (!inserted) {
    // left branch
    if (point[cd] < node->data[cd]) {
      // if the left branch of the node is empty
      // insert the point to that branch
      if (node->left == nullptr) {
        // node->left = new Node(point);
        node->left = std::make_shared<Node>(point);
        inserted = true;
      }
      // if not, then inspect the left branch in next iteration
      else {
        cd = (cd+1) % K;
        node = node->left;
      }
    }
    // right branch
    else if (point[cd] > node->data[cd]) {
      // if the right branch of the node is empty
      // insert the point to that branch
      if (node->right == nullptr) {
        // node->right = new Node(point);
        node->right = std::make_shared<Node>(point);
        inserted = true;
      }
      // if not, then inspect the right branch in next iteration
      else {
        cd = (cd+1) % K;
        node = node->right;
      }
    }
    // point lies on an existed edge
    else {
      std::cout << "point overlap at dimension " << cd << std::endl;
      break;
    }
  }
}

/* print-out example:
       /-----(8, 9)
/-----(3, 8)
|      \-----(6, 3)
(2, 5)
|             /-----(-2, 10)
|      /-----(-3, 5)
\-----(1, 4)
       \-----(0, 3)
*/
/*print KD Tree branches, auxiliary function for printing KD Tree,
  to be called inside printKDTree().
  @param node current node
  @param left tells whether the branch to be printed is a left branch
  @param prefix the accumulated prefix for formatting
*/
void KD_Tree::printKDTreeBranches(std::shared_ptr<Node> node, bool left, const std::string& prefix) {
  if (node->right) {
    printKDTreeBranches(node->right, false, prefix + (left? "|      " : "       "));
  }
  std::cout << prefix;
  std::cout << (left? '\\' : '/');
  std::cout << "-----";
  std::cout << node->data << std::endl;
  if (node->left) {
    printKDTreeBranches(node->left, true, prefix + (left? "       " : "|      "));
  }
}

/*print KD Tree
  @param root the root of KD Tree
*/
void KD_Tree::printKDTree() {
  if (_root_node->right) {
    printKDTreeBranches(_root_node->right, false, "");
  }
  std::cout << _root_node->data << std::endl;
  if (_root_node->left) {
    printKDTreeBranches(_root_node->left, true, "");
  }
}

/*TODO: another print-out example:
            (51,75)
       ________|________
       |               |
    (25,40)         (70,70)
   ____|____       ____|____
   |       |       |       |
(10,30) (35,90) (55,1) (60,80)
                   |____
                       |
                     (56, 30)
*/
