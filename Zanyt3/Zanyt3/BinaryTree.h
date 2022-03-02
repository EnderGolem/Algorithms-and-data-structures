#pragma once

template<class  T>
class  BinaryTree
{
private:
	struct  Node
	{
		T data;
		Node* parent, * left, * right;
	};
public:
	Node* m_root;
	BinaryTree(): m_root(nullptr)
	{
	}
	void insert(T data)
	{
		if(m_root->data  == nullptr)
		{
			m_root = Node{ data,nullptr,nullptr,nullptr };
			return;
		}
		auto current = m_root;
		while(current != nullptr)
		{
			if (current->data < data) {
				if (current->left == nullptr) {
					current->left = Node{ data,current,nullptr,nullptr };
					return;
				}
				current = current->left;
			}			
			else
			{
				if (current->right == nullptr) {
					current->right = Node{ data,current,nullptr,nullptr };
					return;
				}
				current = current->right;
			}
		}
	}
	bool contains(T data)
	{
		if (m_root->data == nullptr)
		{
			m_root = Node{ data,nullptr,nullptr,nullptr };
			return  false;
		}
		auto current = m_root;
		while (current != nullptr)
		{
			if (current->data == data)
				return true;
			if (current->data < data) 
			{			
				current = current->left;
			}
			else
			{
				current = current->right;
			}
		}
		return false;
	}
	
};
