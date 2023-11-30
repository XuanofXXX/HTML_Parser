#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <fstream>

#include "CssSelector.h"
#include "HtmlElement.h"
#include "utils.h"

using std::cout;
using std::endl;

class HtmlParser {
public:
  HtmlParser(){};

  HtmlParser(string s) { this->doc = strip(s); };

  void parse();

  void readHTML(string &html);

  void readfile(const string &filename);

  Node<HtmlElem *>* css(const string &s, HtmlElem *root);

  // List<HtmlElem*> XPathSelect(const string& path);

  void debug(HtmlElem *ele);

  HtmlElem *getRoot();

  string getDoc();

private:
  HtmlElem *root;

  string doc;

  HtmlElem *_isComment(int i);

  HtmlElem *_isJavaScript(int i);

  HtmlElem *_isCSS(int i);

  int _isSelfClosing(const string &tag);

  int _isInline(const string &tag);

  HtmlElem *_parseTag(int i);

  bool _checkNested(HtmlElem *child);

  HtmlElem *_parseContent(int i);

  void _parseHtml();

  Node<HtmlElem *>* _traverse(HtmlElem* root, SelectorInfo* info);

  map<string, string> _parseAttribute(const string &attr);

};

#endif