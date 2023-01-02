#pragma once

namespace utility {

template <typename T>
struct Tree {
  Tree() = default;

  explicit Tree(T data_): data(std::move(data_)) {}

  T data;
  std::vector<Tree<T>> children;
};

}    // namespace utility