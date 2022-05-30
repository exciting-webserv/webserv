#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <strutil/strutil.hpp>

namespace util {

/**
 * ""           -> ""
 * ".\t..\t..." -> "" (. is whitespace)
 * " a  b  c"   -> "a", "b", "c"
 * "a b c"      -> "a", "b", "c"
 * "a"          -> "a"
 */
static vector<string> splitEmptySep(const string& str) {
  vector<string> result;
  std::istringstream iss(str);

  std::copy(std::istream_iterator<string>(iss), std::istream_iterator<string>(),
            back_inserter(result));
  if (result.empty())
    result.push_back("");
  return result;
}

static vector<string> splitSep(const string& text, const string& sep) {
  vector<string> result;
  string::size_type start = 0, end = text.find(sep);
  while (end != string::npos) {
    result.push_back(text.substr(start, end - start));
    start = end + sep.length();
    end = text.find(sep, start);
  }
  result.push_back(text.substr(start, end));
  return result;
}

/**
 * @brief Return a list of the words in the string, using sep as the delimiter
 * string.
 *
 * @param sep if "" (default), splits and removes all whitespaces.
 *
 * "a b c" " " -> "a", "b", "c"
 * "a,b,c" ","  -> "a", "b", "c"
 */
vector<string> split(const string& str, const string& sep) {
  if (sep == "")
    return splitEmptySep(str);
  else
    return splitSep(str, sep);
}

}  // namespace util

/*
// TODO: turn them into proper unit tests.
void test_splitEmptySep() {
  {
    std::vector<std::string> expected(1, "");
    assert(util::split("       ") == expected);
    assert(util::split("") == expected);
    assert(util::split(" 		  			") == expected);
  }
  {
    std::string tmp[3] = {"a", "b", "c"};
    std::vector<std::string> expected(tmp, tmp + 3);
    assert(util::split("a b c") == expected);
    assert(util::split("a   b    c") == expected);
  }
  {
    std::vector<std::string> expected(1, "a");
    assert(util::split("a") == expected);
  }
}

void test_splitSep() {
  {
    std::string tmp[3] = {"a", "b", "c"};
    std::vector<std::string> expected(tmp, tmp + 3);
    assert(util::split("a b c", " ") == expected);

    assert(util::split("a,b,c", ",") == expected);
    assert(util::split("a!!b!!c", "!!") == expected);
    assert(util::split("a->b->c", "->") == expected);
  }
  {
    std::string tmp = "a!!b!!c";
    assert(util::split(tmp, "->") == std::vector<std::string>(1, tmp));
  }
  {
    std::string tmp[4] = {"a", "", "b", "c"};
    std::vector<std::string> expected(tmp, tmp + 4);
    assert(util::split("a,,b,c", ",") == expected);
    assert(util::split("a->->b->c", "->") == expected);
  }
}
*/
