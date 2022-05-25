#pragma once
#include <string>
#include <vector>

inline std::vector<int> prefix_function(const std::string& sub, const std::string& s) {
	std::vector<int> ans(s.length());
	int j = 0;
	if (sub.length() < s.length()) {
		for (int i = 1; i < static_cast<int>(s.length()); i++) {

			if (j == static_cast<int>(sub.size()))
				j = ans[j - 1];
			while (j > 0 && s[i] != sub[j])
				j = ans[j - 1];
			if (s[i] == sub[j])  j++;
			ans[i] = j;
		}
	}
	j = 0;
	for (int i = 0; i < std::min(sub.length(), s.length()); i++)
	{
		if (j == static_cast<int>(sub.size()))
			j = ans[j - 1];
		while (j > 0 && s[i] != sub[j])
			j = ans[j - 1] - 1;
		if (j == -1)
			j++;
		if (s[i] == sub[j])  j++;
		ans[i] = j;
	}
	return ans;
}

std::vector<int> find_subs(const std::string& sub, const std::string& s)
{
	auto vec = prefix_function(sub, s);
	std::vector<int> ans;
	for(int i = 0;i < vec.size();i++)
	{
		if(vec[i] == sub.length())
		{
			ans.push_back(i - sub.length() + 1);
		}
	}
	return  ans;
}