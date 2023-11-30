#ifndef HTMLELEMENT_H
#define HTMLELEMENT_H

#include "../DataStructure/src/LinkedList.cpp"
#include "../DataStructure/src/List.cpp"
#include "../DataStructure/src/String.cpp"
#include <map>
#include <string>

// #define List vector
#define NORMAL_BLOCK 1
#define NORMAL_INLINE 2
#define SPECIAL_BLOCK 3
#define SPECIAL_INLINE 4

#define CONTENT "CONTENT"
#define COMMENT "COMMENT"
#define JAVASCRIPT "JAVASCRIPT"
#define CSS "CSS"
#define NONE "NONE"

using std::map;
using std::string;

class HtmlElem {
public:
  string tag = "";
  string attribute = "";
  map<string, string> attrs;
  HtmlElem *father = nullptr;
  HtmlElem *brother = nullptr;
  int fatherType = -1;
  int SelfType = -1;
  bool selfClosing = false;
  bool endTag = false;
  int start_index = -1;
  int end_index = -1;

  Node<HtmlElem *> *children = new Node<HtmlElem *>();

  HtmlElem(){};

  HtmlElem(string tag) { this->tag = tag; }

  HtmlElem(string tag, string attribute) {
    this->tag = tag;
    this->attribute = attribute;
  }

  void append(HtmlElem *other) {
    Node<HtmlElem *> *dummyNode = children;
    while (dummyNode->next) {
      dummyNode = dummyNode->next;
    }
    dummyNode->next = new Node<HtmlElem *>(other);
  }
  bool operator==(const HtmlElem &other) const {
    return tag == other.tag && attribute == other.attribute &&
           attrs == other.attrs && father == other.father &&
           brother == other.brother && fatherType == other.fatherType &&
           SelfType == other.SelfType && selfClosing == other.selfClosing &&
           endTag == other.endTag && start_index == other.start_index &&
           end_index == other.end_index;
  }
};

#endif