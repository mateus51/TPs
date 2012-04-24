#include "StringUtils.h"

vector<string> StringUtils::TokenizeLine(string line, char delimiter) {
	//cout << "  tokenizing(" << delimiter << ") " << line << " -> ";
	vector<string> tokens;

	size_t delim, prev_delim;
	string str;

	delim = prev_delim = line.find(delimiter);
	str = line.substr(0, delim);
	tokens.push_back(str);
	//cout << "str = '" << str << "'" << endl;

	while ((delim = line.find(delimiter, ++delim)) != string::npos) {
		str = line.substr(prev_delim + 1, delim - prev_delim);
		tokens.push_back(str);
		prev_delim = delim;
	}

	str = line.substr(prev_delim + 1, delim - prev_delim);
	if (!str.empty())
		tokens.push_back(str);

	unsigned int i;
//	for (i = 0; i < tokens.size(); i++) {
//		cout << "    [" << tokens[i] << "] ";
//	}
//	cout << endl;
	for (i = 0; i < tokens.size(); i++) {
		//cout << "  will remove spaces " << tokens[i] << endl;
		//cout << "   ";
		RemoveSpaces(tokens[i]);
	}

	return tokens;
}

void StringUtils::RemoveSpaces(string& str) {
	//cout << "  -Removing spaces: '" << str << "' -> '";

	size_t start, end;

	start = str.find_first_not_of(" ");
	if (start != string::npos)
		str = str.substr(start);

	//cout << str << "' -> '";

	end = str.find_last_not_of(" ");
	if (end != string::npos)
		str = str.substr(0, end + 1);

//	if (str[str.size() - 1] == ';')
//		str[str.size() - 1] = '\0';

	//cout << str << "'" << endl;
}
