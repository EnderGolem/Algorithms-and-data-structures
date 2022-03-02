#pragma once

template<class  T>
class  binary_tree
{
private:
	struct  node
	{
		T data;
		node* parent, * left, * right;
	};
};
