#include <fstream>
#include <iostream>
#include <string>
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


int main() {
	string content;
  readfile(content);
  cout<<content<<endl;
  return 0;
}
