#include <fstream>
#include <iostream>
#include <string>
#include <vector>
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

vector<int> genorder (const vector<pair<int, int>>& pairs)
{
	vector<int> res;
	return res;
}

vector<pair<int, int>> loadpairs(string)
{
	vector<pair<int,int>> pairs;
	return pairs;
}

int checkline(vector<pair<int, int>> order, vector<int> line)
{
	return 0;
}

int main() {
	string content;
  readfile(content);
  cout<<content<<endl;
  vector<pair<int,int>> pairs = loadpairs(content);
  // vector<pair<int,int>> vp = {{20,3},{24,8},{12,9},{1,3}};
  int count = 0;
  vector<int> sortorder = genorder(pairs);
  return 0;
}
