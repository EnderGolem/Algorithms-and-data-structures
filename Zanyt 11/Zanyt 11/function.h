#pragma once
#include <string>
#include <vector>

std::vector<int> prefix_function(const std::string& sub, const std::string& s) {
	std::vector<int> ans(s.length());
	int j = 0;
	for (int i = 1; i < static_cast<int>(s.length()); i++) {

		if (j == static_cast<int>(sub.size()))
			j = ans[j - 1];
		while (j > 0 && s[i] != sub[j])
			j = ans[j - 1];
		if (s[i] == sub[j])  j++;
		ans[i] = j;
	}
	j = 0;
	for (int i = 0; i < sub.size(); i++)
	{
		if (j == static_cast<int>(sub.size()))
			j = ans[j - 1];
		while (j > 0 && s[i] != sub[j])
			j = ans[j - 1];
		if (s[i] == sub[j])  j++;
		ans[i] = j;
	}
	return ans;
}
