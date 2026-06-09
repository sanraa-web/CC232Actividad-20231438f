#pragma once

#include <cstdint>
#include <functional>
#include <random>
#include <stdexcept>
#include <utility>

namespace ods {

template <class T, class Compare = std::less<T>>
class Treap {
 public:
  struct Node {
    T key{};
    std::uint64_t priority{0};
    Node* parent{nullptr};
    Node* left{nullptr};
    Node* right{nullptr};
    std::size_t subtreeSize{1};


    Node() = default;
    Node(const T& value, std::uint64_t p, Node* par = nullptr)
        : key(value), priority(p), parent(par) {}

    bool isLeftChild() const { return parent != nullptr && parent->left == this; }
    bool isRightChild() const { return parent != nullptr && parent->right == this; }
  };

  Treap() : rng_(232) {}
  explicit Treap(std::uint64_t seed) : rng_(seed) {}
  explicit Treap(Compare comp, std::uint64_t seed = 232) : comp_(std::move(comp)), rng_(seed) {}

  Treap(const Treap&) = delete;
  Treap& operator=(const Treap&) = delete;

  Treap(Treap&& other) noexcept { swap(other); }
  Treap& operator=(Treap&& other) noexcept {
    if (this != &other) { clear(); swap(other); }
    return *this;
  }

  ~Treap() { clear(); }

  void clear() {
    destroy(root_);
    root_ = nullptr;
    size_ = 0;
  }

  void swap(Treap& other) noexcept {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    std::swap(comp_, other.comp_);
    std::swap(rng_, other.rng_);
    std::swap(priorityCounter_, other.priorityCounter_);
  }

  Node* root() const noexcept { return root_; }
  std::size_t size() const noexcept { return size_; }
  bool empty() const noexcept { return size_ == 0; }

  bool add(const T& x) { return addWithPriority(x, nextPriority()); }

  bool addWithPriority(const T& x, std::uint64_t priority) {
    Node* u = new Node(x, priority);
    if (!addNode(u)) {
      delete u;
      return false;
    }
    bubbleUp(u);
    return true;
  }

  bool remove(const T& x) {
    Node* u = findEQ(x);
    if (!u) return false;
    trickleDown(u);
    splice(u);
    delete u;
    return true;
  }

  const T& kth(std::size_t k) const {
    Node* u = root_;
    while (u) {
      std::size_t leftSize = sz(u->left);
      std::size_t rank     = leftSize + 1;

      if (k == rank) {
        return u->key;
      } else if (k < rank) {
        u = u->left;
      } else {
        k -= rank;
        u = u->right;
      }
    }
  }

 private:
  Node* root_{nullptr};
  std::size_t size_{0};
  Compare comp_{};
  std::mt19937_64 rng_;
  std::uint64_t priorityCounter_{0};

  static std::size_t sz(const Node* u) noexcept {
    return u ? u->subtreeSize : 0;
  }

  std::uint64_t nextPriority() {
    std::uint64_t raw = rng_();
    return (raw << 16) ^ (++priorityCounter_);
  }

  static void updateSize(Node* u) noexcept {
    if (u) u->subtreeSize = 1 + sz(u->left) + sz(u->right);
  }

  Node* findLast(const T& x) const {
    Node* w = root_;
    Node* prev = nullptr;
    while (w != nullptr) {
      prev = w;
      if (comp_(x, w->key)) {
        w = w->left;
      } else if (comp_(w->key, x)) {
        w = w->right;
      } else {
        return w;
      }
    }
    return prev;
  }

  Node* findEQ(const T& x) const {
    Node* w = root_;
    while (w != nullptr) {
      if (comp_(x, w->key)) {
        w = w->left;
      } else if (comp_(w->key, x)) {
        w = w->right;
      } else {
        return w;
      }
    }
    return nullptr;
  }

  bool addNode(Node* u) {
    u->left = u->right = nullptr;
    u->subtreeSize = 1;
    Node* p = findLast(u->key);
    if (!p) {
      root_ = u;
      u->parent = nullptr;
      ++size_;
      return true;
    }
    if (comp_(u->key, p->key)) {
      if (p->left) return false;
      p->left = u;
    } else if (comp_(p->key, u->key)) {
      if (p->right) return false;
      p->right = u;
    } else {
      return false;
    }
    u->parent = p;
    ++size_;
    for (Node* anc = p; anc; anc = anc->parent) 
      updateSize(anc);
    return true;
  }

  void splice(Node* u) {
    Node* s = u->left ? u->left : u->right;
    if (u == root_) {
      root_ = s;
    } else if (u->isLeftChild()) {
      u->parent->left = s;
    } else {
      u->parent->right = s;
    }
    if (s) s->parent = u->parent;
    for (Node* anc = u->parent; anc; anc = anc->parent) 
      updateSize(anc);
    --size_;
  }

  void rotateLeft(Node* u) {
    if (!u || !u->right) return;
    Node* w = u->right;
    w->parent = u->parent;
    if (!u->parent) {
      root_ = w;
    } else if (u->isLeftChild()) {
      u->parent->left = w;
    } else {
      u->parent->right = w;
    }
    u->right = w->left;
    if (u->right) 
      u->right->parent = u;
    w->left = u;
    u->parent = w;
    updateSize(u);
    updateSize(w);
  }

  void rotateRight(Node* u) {
    if (!u || !u->left) return;
    Node* w = u->left;
    w->parent = u->parent;
    if (!u->parent) {
      root_ = w;
    } else if (u->isLeftChild()) {
      u->parent->left = w;
    } else {
      u->parent->right = w;
    }
    u->left = w->right;
    if (u->left) u->left->parent = u;
    w->right = u;
    u->parent = w;
    updateSize(u);
    updateSize(w);
  }

  void bubbleUp(Node* u) {
    while (u->parent && u->parent->priority > u->priority) {
      if (u->isRightChild()) {
        rotateLeft(u->parent);
      } else {
        rotateRight(u->parent);
      }
    }
    if (!u->parent) root_ = u;
  }

  void trickleDown(Node* u) {
    while (u->left || u->right) {
      if (!u->left) {
        rotateLeft(u);
      } else if (!u->right) {
        rotateRight(u);
      } else if (u->left->priority < u->right->priority) {
        rotateRight(u);
      } else {
        rotateLeft(u);
      }
      if (root_ == u) root_ = u->parent;
    }
  }

  static void destroy(Node* u) {
    if (!u) return;
    destroy(u->left);
    destroy(u->right);
    delete u;
  }
};

}  // namespace ods