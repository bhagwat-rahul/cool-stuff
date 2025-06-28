#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
using namespace std;

void readfile(string& content) {
  ifstream file("sample.txt");
  if (!file.is_open()) {
    cout << "Error opening file\n";
  }
  string line;
  while (getline(file, line)) {
    content += line + "\n";
  }
  file.close();
}

vector<pair<int, int>> loadpairs(string)
{
	vector<pair<int,int>> pairs;
	return pairs;
}

vector<int> genorder (const vector<pair<int, int>>& pairs)
{
	vector<int> res;
	return res;
}

int checklines(vector<int> order, vector<vector<int>> line)
{
	int count = 0;
	return count;
}

vector<vector<int>> parsep2(const string& p2) {
    vector<vector<int>> res;
    istringstream stream(p2);
    for (string line; getline(stream, line); ) {
        istringstream linestream(line);
        vector<int> row;
        for (string token; getline(linestream, token, ','); )
            if (!token.empty())
                row.push_back(stoi(token));
        if (!row.empty())
            res.push_back(std::move(row));
    }
    return res;
}

int main() {
	string content;
  readfile(content);
  int pos = content.find("\n\n");
  string p1 = content.substr(0, pos);
  string p2 = (pos == string::npos) ? "" : content.substr(pos + 2);
  vector<pair<int,int>> p1data = loadpairs(content);
  vector<int> sorder = genorder(p1data);
  vector<vector<int>> p2data = parsep2(p2);
  cout<<"Valid count is: "<<checklines(sorder, p2data)<<endl;
  return 0;
}
