#include <iostream>
#include "tree_for_words.h"
using namespace std;

int main()
{
	tree_for_words tree{};
	tree.plus_word("a raccoon, a badger and a deer come into a bar, and a drunkard comes out  drunkard .");
	tree.print_words();
}