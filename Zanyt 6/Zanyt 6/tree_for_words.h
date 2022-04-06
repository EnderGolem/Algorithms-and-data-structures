#pragma once
#include <queue>
#include <set>

class tree_for_words
{
private:
	struct  node
	{
		node* parent;
		node* children[28]{};
		int count_word;
		node() : count_word(0)
		{
			parent = nullptr;
			for (auto& i : children)
			{
				i = nullptr;
			}
		}
		node(node* parent) : parent(parent), count_word(0)
		{
			for (auto& i : children)
			{
				i = nullptr;
			}
		}
	};
	node* root;
	node* current;
public:
	tree_for_words()
	{
		root = new node();
		current = root;

	}
	void plus_word(std::string s)
	{
		for (auto x : s)
		{
			plus_word(x);
		}
	}
	void plus_word(const char& c)
	{

		if( c < 'a' || 'z' < c)
		{
			count_word();
			return;
		}
		if (current->children[c - 97] == nullptr)
		{
			current->children[c - 97] = new node(current);
		}
		current = current->children[c - 97];



	}
	void print_words(int length = 0)
	{
		int ans = 0;
		for (std::queue<std::pair<node*, int>> queue({ std::pair<node*, int>(root, 1) }); !queue.empty(); queue.pop())
		{
			for (auto& i : queue.front().first->children)
			{
				if (i != nullptr)
				{
					queue.push(std::pair<node*, int>(i, queue.front().second + 1));
				}
			}
			if (queue.front().first->count_word > 0 && queue.front().second >= length)
			{
				ans++;
				print_word(queue.front().first, queue.front().second);
			}
		}
		std::cout << ans << '\n';
	}
	void find_max(int length = 0)
	{
		int ans = 0;
		
		std::set<std::string> set;
		for (std::queue<std::pair<node*, int>> queue({ std::pair<node*, int>(root, 1) }); !queue.empty(); queue.pop())
		{
			for (auto& i : queue.front().first->children)
			{
				if (i != nullptr)
				{
					queue.push(std::pair<node*, int>(i, queue.front().second + 1));
				}
			}
			if (queue.front().first->count_word > 0 && queue.front().second >= length)
			{
				ans++;				
				set.insert(word(queue.front().first, queue.front().second));
			}
		}
		std::cout << ans << '\n';
	}
private:
	void print_word(node* nd, const int& size)
	{
		std::string s(size - 1, 'a');
		const int ans = nd->count_word;

		for (int y = 0; nd->parent != nullptr; y++, nd = nd->parent)
			for (unsigned char i = 0; i < 28; i++)
			{
				if (nd->parent->children[i] == nd)
				{
					s[size - y - 2] = static_cast<char>(i + 97);
				}
			}
		std::cout << s << ' ' << ans << '\n';
	}

	std::string word(node* nd, const int& size)
	{
		std::string s(size - 1, 'a');
		for (int y = 0; nd->parent != nullptr; y++, nd = nd->parent)
			for (unsigned char i = 0; i < 28; i++)
			{
				if (nd->parent->children[i] == nd)
				{
					s[size - y - 2] = static_cast<char>(i + 97);
				}
			}
		
		return  s;
	}
	void count_word()
	{
		current->count_word++;
		current = root;
	}
};
