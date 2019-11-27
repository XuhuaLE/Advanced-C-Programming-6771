
// This part is for the constructors

// 2nd constructor
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::vector<N>::const_iterator start,
                         typename std::vector<N>::const_iterator end) {
  for (auto it = start; it != end; ++it) {
    nodes[*it] = std::make_shared<Node>(*it);
    N temp{};
    E tempE{};
    graphVector.push_back(std::tuple<N, N, E>(*it, temp, tempE));
  }
}

// 3rd constructor
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator start,
typename std::vector<std::tuple<N, N, E>>::const_iterator end) {
  for (auto tupleIterator = start; tupleIterator != end; ++tupleIterator) {
    auto constructorTuple{*tupleIterator};
    auto constructorSrc = std::get<0>(constructorTuple);  // get source node
    auto constructorDst = std::get<1>(constructorTuple);  // get destinition node

    if (!IsNode(constructorSrc)) {  // create node
      this->InsertNode(constructorSrc);
    }
    if (!IsNode(constructorDst)) {  // create node
      this->InsertNode(constructorDst);
    }

    auto constructorWeight = std::get<2>(constructorTuple);  // get weight
    this->InsertEdge(constructorSrc, constructorDst, constructorWeight);
  }
}

// 4th constructor
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::initializer_list<N> list) {
  for (auto listIterator = list.begin(); listIterator != list.end(); ++listIterator) {
    this->InsertNode(*listIterator);
  }
}


// 5th constructor copy
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(const gdwg::Graph<N, E>& old_g):Graph(old_g.graphVector.begin(),old_g.graphVector.end()) {}


// 6th constructor move
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(gdwg::Graph<N, E>&& old_g):Graph(old_g.graphVector.begin(),old_g.graphVector.end()) {
  old_g.Clear();
}


// Methods

template <typename N, typename E>
bool gdwg::Graph<N, E>::InsertNode(const N& val) noexcept {
  if (IsNode(val)) {
    return false;
  } else {
    nodes[val] = std::make_shared<Node>(val);
    N temp{};
    E tempE{};
    graphVector.push_back(std::tuple<N, N, E>(val, temp, tempE));
    return true;
  }
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::InsertEdge(const N& src, const N& dst, const E& w) {
  if (IsNode(src) && IsNode(dst)) {
    auto srcPtr = nodes[src];
    auto dstPtr = nodes[dst];
    for (auto e: dstPtr->inEdges) {
      auto edge_src = e->src_.lock();
      if ((e->weight_ == w) && (edge_src->val_ == src)) {
        return false;
      }
    }
    Edge e = Edge(srcPtr, dstPtr, w);
    auto ePtr = std::make_shared<Edge>(e);
    srcPtr->outEdges.insert(ePtr);
    dstPtr->inEdges.insert(ePtr);

    E temp{};
    graphVector.push_back(std::tuple<N, N, E>(src, dst, w));
    for (auto iter = graphVector.begin(); iter != graphVector.end(); ++iter) {
      if (std::get<0>(*iter) == src && std::get<2>(*iter) == temp) {
        graphVector.erase(iter);
        break;
      }
    }

    return true;
  } else {
    throw std::runtime_error("Cannot call Graph::InsertEdge when either src or dst node does not exist");
  }
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::DeleteNode(const N& val) noexcept {
  if (IsNode(val)) {
    nodes.erase(val);

    for (auto iter = graphVector.begin(); iter != graphVector.end();) {
      if (std::get<0>(*iter) == val || std::get<1>(*iter) == val) {
        iter = graphVector.erase(iter);
      } else {
        ++iter;
      }
    }

    return true;
  }
  return false;
}


template <typename N, typename E>
bool gdwg::Graph<N, E>::Replace(const N& oldData, const N& newData) {
  if (!IsNode(oldData)) {
    throw std::runtime_error("Cannot call Graph::Replace on a node that doesn't exist");
  }
  if (IsNode(newData)) {
    return false;
  } else {
    nodes[newData] = nodes[oldData];
    nodes[newData]->val_ = newData;
    nodes.erase(oldData);

    for (auto iter = graphVector.begin(); iter != graphVector.end();) {
      if(std::get<0>(*iter) == oldData) {
        std::get<0>(*iter) = newData;
      } else if (std::get<1>(*iter) == oldData) {
        std::get<1>(*iter) = newData;
      } else {
        ++iter;
      }
    }

    return true;
  }
}


template <typename N, typename E>
void gdwg::Graph<N, E>::Clear() noexcept {
  nodes.clear();
  graphVector.clear();
}


template <typename N, typename E>
bool gdwg::Graph<N, E>::IsNode(const N& val) const {
  if (nodes.find(val) == nodes.end()) {
    return false;
  } else {
    return true;
  }
}


template <typename N, typename E>
bool gdwg::Graph<N, E>::IsConnected(const N& src, const N& dst){
  if (!IsNode(src) || !IsNode(dst)) {
    throw std::runtime_error("Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
  }
  auto dstPtr = nodes[dst];
  for (auto e: dstPtr->inEdges) {
    auto edge_src = e->src_.lock();
    if (edge_src->val_ == src) {
      return true;
    }
  }
  return false;
}


template <typename N, typename E>
std::vector<N> gdwg::Graph<N, E>::GetNodes() const noexcept{
  std::vector<N> nodesVector{};
  for (auto getNodesIter = nodes.begin(); getNodesIter != nodes.end(); ++getNodesIter) {
    nodesVector.push_back(getNodesIter->first);
  }
  std::sort(nodesVector.begin(), nodesVector.end());
  return nodesVector;
}

template <typename N, typename E>
std::vector<N> gdwg::Graph<N, E>::GetConnected(const N& src){
  if (!IsNode(src)) {
    throw std::out_of_range("Cannot call Graph::GetConnected if src doesn't exist in the graph");
  }
  std::vector<N> connectVector{};
  auto connectPtr = nodes[src];
  for (auto e: connectPtr->outEdges) {
    auto edge_dst = e->dst_.lock();
    connectVector.push_back(edge_dst->val_);
  }
  std::sort(connectVector.begin(), connectVector.end());
  return connectVector;
}


template <typename N, typename E>
std::vector<E> gdwg::Graph<N, E>::GetWeights(const N& src, const N& dst) {
  if (!IsNode(src) || !IsNode(dst)) {
    throw std::out_of_range("Cannot call Graph::GetWeights if src or dst node don't exist in the graph");
  }
  std::vector<E> weightsVector{};
  auto weightPtr = nodes[dst];
  for (auto e: weightPtr->inEdges) {
    auto edge_src = e->src_.lock();
    if (edge_src->val_ == src) {
      weightsVector.push_back(e->weight_);
    }
  }
  std::sort(weightsVector.begin(), weightsVector.end());
  return weightsVector;
}


template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N, E>::find(const N& src, const N& dst, const E& w) noexcept{
  for(auto findIt=this->begin(); findIt!=this->end();++findIt){
    if (*findIt== std::make_tuple(src,dst,w)){
      return findIt;
    }

  }
  return this->end();
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N, E>::erase(typename gdwg::Graph<N, E>::const_iterator it){
  auto copyIt=it;
  if(it == this->end()){
    return it;
  }else{
    copyIt++;
    auto src = std::get<0>(*it);
    auto dst = std::get<1>(*it);
    auto w = std::get<2>(*it);
    auto yOn = this->erase(src,dst,w);
    if(yOn){
      return this->end();
    }else{
      return this->end();
    }
  }
}




template <typename N, typename E>
bool gdwg::Graph<N, E>::erase(const N& src, const N& dst, const E& w) {
  //std::cout<<"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"<<w<<"\n";
  auto srcPtr = nodes[src];
  auto dstPtr = nodes[dst];
  bool flag = false;
  std::shared_ptr<Edge> aaa{}, bbb{};

  for (auto e: dstPtr->inEdges) {
    auto edge_src = e->src_.lock();
    if ((e->weight_ == w) && (edge_src->val_ == src)) {
      aaa = e;
      flag = true;
    }
  }

  for (auto e: srcPtr->outEdges) {
    auto edge_dst = e->dst_.lock();
    if ((e->weight_ == w) && (edge_dst->val_ == dst)) {
      bbb = e;
    }
  }

  if (flag) {
    dstPtr->inEdges.erase(aaa);
    srcPtr->outEdges.erase(bbb);
  }
  //tuple code
  for (auto iter = graphVector.begin(); iter != graphVector.end();) {
    if (std::get<0>(*iter) == src && std::get<1>(*iter) == dst && std::get<2>(*iter) == w) {
      //std::cout<<"erase src\n";
      //std::cout<<std::get<0>(*iter)<<"\n";
      //std::cout<<"erase weight\n";
      //std::cout<<std::get<2>(*iter)<<"\n";
      graphVector.erase(iter);
      return  flag;
    } else {
      ++iter;
    }
  }
  //tuple code
  return flag;
}



