#ifndef CSSSELECTER_H
#define CSSSELECTER_H

#include "HtmlElement.h"
// #include "HtmlParser.h"
#include <fstream>
#include <iostream>
enum Type { TAG, CLASS, ID, ATTRIBUTE, DESCENDANT, GROUP, CHILD, BROTHER, FIRST_BROTHER, CSS_NONE };

enum AttrType {NORMAL, CONTAIN, BEGIN, END};
// CONTAIN: [attr ~= value]
// BEGIN:   [attr |= value]
// END:     [attr $= value]

struct SelectorPart {
  Type type = CSS_NONE;
  AttrType attrType = NORMAL;
  string value;
  string attributeValue; // 仅当 type == ATTRIBUTE 时使用
  SelectorPart(): type(CSS_NONE)  {}
  SelectorPart(Type type, string value) : type(type), value(value) {}
};

struct SelectorInfo {
  Type type = CSS_NONE;
  LinkList<SelectorPart*> parts; // 存储选择器的各个部分
  SelectorInfo(): type(CSS_NONE){}
  SelectorInfo(LinkList<SelectorPart*> parts) : parts(parts) {}
  SelectorInfo(Type type) : type(type) {}
};

bool _matchTag(HtmlElem *element, const string &tagName);
bool _matchClass(HtmlElem *element, const string &className);
bool _matchID(HtmlElem *element, const string &idName);
bool _matchAttribute(HtmlElem *element, const string &attributeName,
                    const string &attributeValue, AttrType type);

bool match(HtmlElem* ele, SelectorInfo* info);

namespace CssSelector {
  // 解析器辅助函数
  SelectorInfo* _parseNode(const string &selectorPart);
  
  LinkList<SelectorInfo*> parseSelector(const string &selector); // 解析选择器
};
#endif