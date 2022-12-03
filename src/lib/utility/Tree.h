#pragma once

template <typename T>
struct Tree
{
	Tree() {}
	Tree([[maybe_unused]] T data): data(data) {}
	T data;
	std::vector<Tree<T>> children;
};
