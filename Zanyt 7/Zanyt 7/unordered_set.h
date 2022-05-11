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
		int size;
		_Kty* tabl;
		bool* empty;

	public:
		using hasher = _Hasher;
		using value_type = _Kty;
		_Hasher get_hash = _Hasher();

		unordered_set(int size = 2000) : size(size)
		{
			tabl = new value_type[size];
			empty = new bool[size];
		}
		unordered_set(std::initializer_list<value_type> lst, int size = 2000) : size(size)
		{
			for each (auto x in lst)
			{
				insert(x);
			}
		}
		/// <summary>
		/// Insert element, return count of collision
		/// </summary>
		int insert(value_type value)
		{
			return hash_insert(value);
		}

		bool has(value_type value)
		{

			for (int i = 0; i < size; i++)
			{
				int j = get_hash(value, i, size);
				if (empty[j])
					return false;
				if (tabl[j] == value)
				{
					return true;
				}
			}
			return false;
		}
		bool erase(value_type value)
		{
			for (int i = 0; i < size; i++)
			{
				int j = get_hash(value, i, size);
				if (empty[j])
					return false;
				if (tabl[j] == value)
				{
					empty[j] = false;
				}
			}
			return false;
		}
		~unordered_set()
		{
			delete[] tabl;
		}
		void print()
		{
			for (int i = 0; i < size; i++)
			{
				if (tabl[i] > 0)
					std::cout << i << " " << empty[i] << " " << get_hash(tabl[i], 0, size) << " " << tabl[i] << '\n';
			}
		}
	private:
		void hash_insert(value_type k)
		{
			for (int i = 0; i < size; i++)
			{
				int j = get_hash(k, i, size);
				if (empty[j])
				{
					empty[j] = false;
					tabl[j] = k;
					return;
				}
			}
			assert(true);
		}
	};
}