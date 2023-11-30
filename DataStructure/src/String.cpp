#ifndef STRING_CPP
#define STRING_CPP

#include "List.cpp"
#include <cstring>
#include <iostream>
#include <string>

using std::string;

List<string> split(const string &s, char ch) {
  List<string> res;
  string tmp = "";
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == ch) {
      res.append(tmp);
      tmp = "";
    } else {
      tmp += s[i];
    }
  }
  res.append(tmp);
  return res;
}

std::string strip(const std::string &str) {
  /**
   * @brief This function removes all leading and trailing whitespace characters
   * from the given string.
   *
   * @return Another string. It doesn't change the original string.
   */
  std::string whitespace = " \t\n\r\f\v";
  std::size_t start = str.find_first_not_of(whitespace);
  std::size_t end = str.find_last_not_of(whitespace);

  if (start == std::string::npos) { // 如果全部都是空白字符
    return "";
  }

  return str.substr(start, end - start + 1);
}

string cleanAndReduceWhitespace(const string &input) {
  string result;
  bool lastWasSpace = false;

  for (char c : input) {
    // 检查字符是否为空格或其他特定字符
    if (c == ' ' || c == '\r' || c == '\n' || c == '\t') {
      if (!lastWasSpace) { // 如果上一个字符不是空格，则添加一个空格到结果中
        result += ' ';
        lastWasSpace = true;
      }
    } else {
      result += c;
      lastWasSpace = false;
    }
  }

  return result;
}

string toLowerCase(const string &input) {
  string result = input;
  for (char &c : result) {
    if (isalpha(c) && isupper(c)) {
      c = tolower(c);
    }
  }
  return result;
}

string mergeSpaces(const string &input) {
  string result;
  bool lastWasSpace = false;

  for (char c : input) {
    if (c == ' ') {
      if (!lastWasSpace) {
        result.push_back(c);
      }
      lastWasSpace = true;
    } else {
      result.push_back(c);
      lastWasSpace = false;
    }
  }

  return result;
}

bool contain(const string &s1, const string &s2){
  /**
   * @brief Check if s1 contains s2
   * 
   * @param s1 
   * @param s2 
   * @return true 
   * @return false 
   */
  // Use KMP algorithm
  int n = s1.size(), m = s2.size();
  int *next = new int[m];
  next[0] = -1;
  int i = 0, j = -1;
  while (i < m) {
    if (j == -1 || s2[i] == s2[j]) {
      i++;
      j++;
      next[i] = j;
    } else {
      j = next[j];
    }
  }
  i = 0, j = 0;
  while (i < n && j < m) {
    if (j == -1 || s1[i] == s2[j]) {
      i++;
      j++;
    } else {
      j = next[j];
    }
  }
  delete[] next;
  return j == m;
}

bool begin_with(const string &s1, const string &s2) {
  /**
   * @brief Check if s1 begins with s2
   * 
   * @param s1 
   * @param s2 
   * @return true 
   * @return false 
   */
  if (s1.size() < s2.size()) {
    return false;
  }
  for (int i = 0; i < s2.size(); i++) {
    if (s1[i] != s2[i]) {
      return false;
    }
  }
  return true;
}

bool end_with(const string &s1, const string &s2) {
  /**
   * @brief Check if s1 ends with s2
   * 
   * @param s1 
   * @param s2 
   * @return true 
   * @return false 
   */
  if (s1.size() < s2.size()) {
    return false;
  }
  int i = s1.size() - 1, j = s2.size() - 1;
  while (j >= 0) {
    if (s1[i] != s2[j]) {
      return false;
    }
    i--;
    j--;
  }
  return true;
}

#endif