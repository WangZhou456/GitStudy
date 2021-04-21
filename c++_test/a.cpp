#include <iostream>
#include <string>
using namespace std;
int main() {
string s = "你好";
string sub = s.substr(0, 3);
cout << "s: " << s << " size: " << s.size() << endl;
cout << "sub: " << sub << "       size: " << sub.size() << endl;
char* cc = "你好";
*cc = s.c_str();
cout << "cc: " << cc << "    size: " << sizeof(cc) << endl;
return 0;
}
