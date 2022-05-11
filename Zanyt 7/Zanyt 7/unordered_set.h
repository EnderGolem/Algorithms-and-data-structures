#pragma once
#include<iostream>
#include<cassert>

namespace my
{

	class hash_mod
	{
		const int MOD = 701;
	public:
		int operator() (const int& k) const
		{
			return k % MOD;
		}
	};

	template<class T = hash_mod>
	class line_hash
	{
	public:
		T h = T();
		int operator() (const int& k, const int& i, const int& size) const
		{
			return (h(k) + i) % size;
		}
	};

	template <class _Kty, class _Hasher = line_hash<hash_mod>, class _Keyeq = std::equal_to<_Kty>, class _Alloc = std::allocator<_Kty>>
	class unordered_set
	{
		int capasity;
		_Kty* tabl;
		bool* empty;
		int size;

	public:
		using hasher = _Hasher;
		using value_type = _Kty;
		_Hasher get_hash = _Hasher();
		int get_size()
		{
			return size;
		}
		unordered_set(int capasity = 2000) : capasity(capasity)
		{
			size = 0;
			tabl = new value_type[capasity];
			empty = new bool[capasity];
			for(int i = 0;i<capasity;i++)
			{
				tabl[i] = NULL;
				empty[i] = true;
			}

		}
		unordered_set(std::initializer_list<value_type> lst, int capasity = 2000) : capasity(capasity)
		{
			size = 0;
			tabl = new value_type[capasity];
			empty = new bool[capasity];
			for (int i = 0; i < capasity; i++)
			{
				tabl[i] = NULL;
				empty[i] = true;
			}
			for each (auto x in lst)
			{
				insert(x);
			}
		}
		/// <summary>
		/// Insert element, return count of collision
		/// </summary>
		void insert(value_type value)
		{
			hash_insert(value);
		}

		bool has(value_type value)
		{

			for (int i = 0; i < capasity; i++)
			{
				int j = get_hash(value, i, capasity);
				if (tabl[j] == NULL)
					return  false;
				if (tabl[j] == value)				
					return true;
			}
			return false;
		}
		bool erase(value_type value)
		{
			for (int i = 0; i < capasity; i++)
			{
				int j = get_hash(value, i, capasity);
				if(tabl[j] != NULL)
				{
					if(tabl[j] == value && !empty[j])
					{
						empty[j] = true;
						size--;
						return  true;
					}
				}
				else
					return  false;		

			}
			return false;
		}
		~unordered_set()
		{
			delete[] tabl;
			delete[] empty;
		}
		void print()
		{
			for (int i = 0; i < capasity; i++)
			{
				if (tabl[i] > 0)
					std::cout << i << " " << empty[i] << " " << get_hash(tabl[i], 0, capasity) << " " << tabl[i] << '\n';
			}
		}
	private:
		void hash_insert(value_type k)
		{
			for (int i = 0; i < capasity; i++)
			{
				int j = get_hash(k, i, capasity);
				if(!empty[j] && tabl[j] == k)
					return;
				if (tabl[j] == NULL || empty[j])
				{
					size++;
					empty[j] = false;
					tabl[j] = k;
				//	std::cout << size << ' ' << tabl[j] << '\n';
					return;
				}
			}
			assert(true);
		}
	};
}