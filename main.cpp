#include <cctype>
#include <iostream>
#include <string>
// 包含必要的头文件
#include "HTMLParser/CssSelector.cpp"
#include "HTMLParser/HtmlElement.h"
#include "HTMLParser/HtmlParser.cpp"
#include "HTMLParser/Layout.cpp"
#include <iostream>

bool isHttpURL(const string &str) {
  return str.substr(0, 7) == "http://" || str.substr(0, 8) == "https://";
}

void fetch_url_content(string &url) {
  cout << "Reading from URL: " << url << endl;
  string command =
      "wget -O "
      "/Users/xiachunxuan/Study/PlayGround/HTMLParser/cache/download.html " +
      url;
  int result = system(command.c_str());
  if (result != 0) {
    throw std::runtime_error("Failed to download the HTML file.");
  } else {
    cout << "Downloaded to local path: cache/download.html" << endl;
  }
}

int main() {
  HtmlParser parser;
  List<HtmlElem *> lastQueryResults;
  std::string command, argument;

  std::cout << "HTML/CSS 解析器交互界面" << std::endl;

  while (true) {
    std::cout << "> ";
    std::cin >> command;
    if (command == "read") {
      cout << "请输入路径/网址: ";
      std::string argument; // Declare argument as a string variable
      std::cin >> argument;
      if (isHttpURL(argument)) {
        fetch_url_content(argument);
        argument = "/Users/xiachunxuan/Study/PlayGround/HTMLParser/cache/"
                   "download.html";
      }
      parser.readfile(argument);
    } else if (command == "query") {
      std::cin.ignore();
      std::getline(std::cin, argument);
      // 实现CSS选择器查询逻辑
      Node<HtmlElem *> *res = parser.css(argument, parser.getRoot());
      Node<HtmlElem *> *cur = res->next;
      lastQueryResults.clear();
      
      while (cur) {
        lastQueryResults.append(cur->data);
        cout << cur->data->tag << " " << cur->data->attribute << endl;
        cur = cur->next;
      }
      cout << "count is " << lastQueryResults.size() << endl;
      // 打印每个节点的标签类型，id，class
    } else if (command == "Out") {
      int index;
      std::cin >> index >> argument;
      if (index < 1 || index > lastQueryResults.size()) {
        std::cout << "索引超出范围" << std::endl;
        continue;
      }
      HtmlElem *element = lastQueryResults[index - 1];
      if (argument == "innerText") {
        cout << Layout::showText(element) << endl;
      } else if (argument == "outerHTML") {
        cout << Layout::show(element) << endl;
      } else if (argument == "query") {
        std::string subSelector;
        std::cin.ignore();
        std::getline(std::cin, subSelector);
        lastQueryResults.clear();
        Node<HtmlElem *> *res = parser.css(subSelector, element);
        Node<HtmlElem *> *cur = res->next;
        while (cur) {
          lastQueryResults.append(cur->data);
          cout << cur->data->tag << " " << cur->data->attribute << endl;
          cur = cur->next;
        }
        cout << "count is " << lastQueryResults.size() << endl;
      } else if (argument == "href") {
        if (element->attrs.find("href") != element->attrs.end()) {
          cout << element->attrs["href"] << endl;
        } else {
          cout << "未知属性" << endl;
        }
      } else if (argument == "src") {
        if (element->attrs.find("src") != element->attrs.end()) {
          cout << element->attrs["src"] << endl;
        } else {
          cout << "未知属性" << endl;
        }
      } else if (argument == "class") {
        cout << element->attrs["class"] << endl;
      } else if (argument == "id") {
        cout << element->attrs["id"] << endl;
      } else if (argument == "style") {
        cout << element->attrs["style"] << endl;
      } else if (argument == "tag") {
        cout << element->tag << endl;
      } else {
        std::cout << "未知属性" << std::endl;
      }
    } else if (command == "exit") {
      break;
    } else {
      std::cout << "未知命令" << std::endl;
    }
  }

  return 0;
}
