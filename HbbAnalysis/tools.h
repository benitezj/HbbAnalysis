#include <stdlib.h>
#include <string.h>
#include <vector>
using namespace std;

namespace HbbAnalysis {
  
  ///////////////////////////////////////////////
  ///Split a string into its parts defined by "sep"
  vector<string> split(const string &text, char sep) {
    vector<string> tokens;
    int start = 0, end = 0;
    while ((end = text.find(sep, start)) != int(string::npos) ) {
      string tok=text.substr(start, end - start);
      //cout<<tok<<endl;
      tokens.push_back(tok);
      start = end + 1;
    }
    tokens.push_back(text.substr(start));
    return tokens;
  }



}
