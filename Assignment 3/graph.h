#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_

#include <memory>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <map>
#include <tuple>
#include <initializer_list>
#include <utility>

namespace gdwg {
template <typename N, typename E>
class Graph {
 public:
  class const_iterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::tuple<N, N, E>;
    using reference = std::tuple<const N&, const N&, const E&>;
    using pointer = std::tuple<N, N, E>*;
    using difference_type = std::tuple<N, N, E>;
    const_iterator operator--() {
      vtPtr_--;
      this->vtPtr_ = vtPtr_;
      return *this;
    }
    reference operator* () {
      return {std::get<0>(*this->vtPtr_), std::get<1>(*this->vtPtr_), std::get<2>(*this->vtPtr_)};
    }

    const_iterator operator++() {
      vtPtr_++;
      this->vtPtr_ = vtPtr_;
      return *this;
    }
    const_iterator operator++(int) {
      auto copy(*this);
      this->vtPtr_++;
      return copy;
    }

    const_iterator operator--(int) {
      auto copy(*this);
      this->vtPtr_--;
      return copy;
    }
    bool operator==(const const_iterator &rValue) {
      auto thisValue = *this;
      return std::get<0>(*rValue.vtPtr_) == std::get<0>(*thisValue)
          && std::get<1>(*rValue.vtPtr_) == std::get<1>(*thisValue)
          && std::get<2>(*rValue.vtPtr_) == std::get<2>(*thisValue);
    }

    bool operator!=(const const_iterator &rValue) {
      auto thisValue = *this;
      return !(std::get<0>(*rValue.vtPtr_) == std::get<0>(*thisValue)
          && std::get<1>(*rValue.vtPtr_) == std::get<1>(*thisValue)
          && std::get<2>(*rValue.vtPtr_) == std::get<2>(*thisValue));
    }

   private:
    friend class Graph;
    explicit const_iterator(typename std::vector<std::tuple<N, N, E>>
    ::iterator inIter): vtPtr_{inIter} {};
    typename std::vector<std::tuple<N, N, E>>::const_iterator vtPtr_;
  };
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  const_iterator cbegin() noexcept {
    return const_iterator{graphVector.begin()};
  }
  const_iterator cend() noexcept {
    return const_iterator{graphVector.end()};
  }
  const_reverse_iterator crbegin() noexcept {
    return const_reverse_iterator{cend()};
  }
  const_reverse_iterator crend() noexcept {
    return const_reverse_iterator{cbegin()};
  }
  const_iterator begin() noexcept {
    return cbegin();
  }
  const_iterator end() noexcept {
    return cend();
  }
  const_reverse_iterator rbegin() const noexcept {
    return crbegin();
  }
  const_reverse_iterator rend() const noexcept { return crend();}

  // Constructors
  // 1st
  Graph() = default;

  // 2nd
  Graph(typename std::vector<N>::const_iterator start, typename std::vector<N>::const_iterator end);

  // 3rd
  Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator start,
  typename std::vector<std::tuple<N, N, E>>::const_iterator end);

  // 4th
  Graph(typename std::initializer_list<N> list);

  // 5th
  Graph(const Graph<N, E>& old_g);

  // 6th
  explicit Graph(gdwg::Graph<N, E>&& old_g);

  // destructorF
  ~Graph() = default;

  // Operations
  Graph<N, E>& operator=(const Graph<N, E>&);
  Graph<N, E>& operator=(Graph<N, E>&&);

  bool InsertNode(const N& val) noexcept;
  bool InsertEdge(const N& src, const N& dst, const E& w);
  bool DeleteNode(const N&) noexcept;
  bool Replace(const N& oldData, const N& newData);
  // void MergeReplace(const N& oldData, const N& newData);
  void Clear() noexcept;
  bool IsNode(const N& val) const;
  bool IsConnected(const N& src, const N& dst);

  bool erase(const N& src, const N& dst, const E& w);
  typename gdwg::Graph<N, E>::const_iterator find(const N& src, const N& dst, const E& w) noexcept;
  typename gdwg::Graph<N, E>::const_iterator erase(typename gdwg::Graph<N, E>::const_iterator it);
  std::vector<N> GetNodes() const noexcept;
  std::vector<N> GetConnected(const N& src);
  std::vector<E> GetWeights(const N& src, const N& dst);

  friend std::ostream& operator<<(std::ostream& os, Graph<N, E>& g) {
    std::vector<std::tuple<N, N, E>> empty{};
    if (g.graphVector == empty) {
      return os;
    }

    std::sort(g.graphVector.begin(), g.graphVector.end());
    N null{};
    N srcInit{};
    auto lastSrc = srcInit;
    for (auto it = g.graphVector.begin(); it != g.graphVector.end(); ++it) {
      auto src = std::get<0>(*it);
      if (src == lastSrc) {
        os << "  " << std::get<1>(*it) << " | " << std::get<2>(*it) << "\n";
      } else if (lastSrc != srcInit) {
        os << ")\n";
        os << src << " (\n";
        if (std::get<1>(*it) != null) {
          os << "  " << std::get<1>(*it) << " | " << std::get<2>(*it) << "\n";
        }
      } else {
        os << src << " (\n";
        if (std::get<1>(*it) != null) {
          os << "  " << std::get<1>(*it) << " | " << std::get<2>(*it) << "\n";
        }
      }
      lastSrc = src;
    }
    os <<")\n";
    return os;
  }


 private:
  struct Node;
  struct Edge;
  struct Node {
    explicit Node(const N& val): val_{val} {}
    N val_;
    std::set<std::shared_ptr<Edge>> inEdges;
    std::set<std::shared_ptr<Edge>> outEdges;
  };
  struct Edge {
    Edge(std::shared_ptr<Node> src,
     std::shared_ptr<Node> dst, const E& weight): src_{src}, dst_{dst}, weight_{weight} {}
    std::weak_ptr<Node> src_;
    std::weak_ptr<Node> dst_;
    E weight_;
  };

  std::map<N, std::shared_ptr<Node>> nodes;
  std::vector<std::tuple<N, N, E>> graphVector;
};
}  // namespace gdwg
// #include "assignments/dg/graph.tpp"
#include "graph.tpp"
#endif  // ASSIGNMENTS_DG_GRAPH_H_
