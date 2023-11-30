#ifndef HTMLPARSER_CPP
#define HTMLPARSER_CPP

#include "HtmlParser.h"

HtmlElem *HtmlParser::_isComment(int i) {
  /**
   * \@brief
   * \@param: s: string
   * \@param: i: index of the '<'
   * \@return: return the position of Annotation '>', if not Annotation,
   * return i;
   */
  HtmlElem *res = new HtmlElem();
  res->tag = NONE;
  string comment = "";
  if (doc[i + 1] == '!' && doc[i + 2] == '-' && doc[i + 3] == '-') {
    res->tag = COMMENT;
    for (int j = i + 4; j + 2 < doc.size(); j++) {
      if (doc[j] == '-' && doc[j + 1] == '-' && doc[j + 2] == '>') {
        res->attribute = comment;
        res->start_index = i;
        res->end_index = j + 2;
        return res;
      }
      comment += doc[j];
    }
  }
  return res;
};

HtmlElem *HtmlParser::_isJavaScript(int i) {
  /**
   * @brief Determine whether the tag is a JavaScript or not
   * @param s: string
   * @param i: index of the '<'
   * @return : return the position of JavaScript '>', if not JavaScript,
   * return i;
   */
  HtmlElem *res = new HtmlElem();
  res->tag = NONE;
  if (doc[i + 1] == 's' && doc[i + 2] == 'c' && doc[i + 3] == 'r' &&
      doc[i + 4] == 'i' && doc[i + 5] == 'p' && doc[i + 6] == 't') {
    res->tag = JAVASCRIPT;
    string script = "";
    for (int j = i + 7; j + 8 < doc.size(); j++) {
      if (doc[j] == '<' && doc[j + 1] == '/' && doc[j + 2] == 's' &&
          doc[j + 3] == 'c' && doc[j + 4] == 'r' && doc[j + 5] == 'i' &&
          doc[j + 6] == 'p' && doc[j + 7] == 't' && doc[j + 8] == '>') {
        res->attribute = script;
        res->start_index = i;
        res->end_index = j + 8;
        return res;
      }
      script += doc[j];
    }
  }
  return res;
}

HtmlElem *HtmlParser::_isCSS(int i) {
  HtmlElem *res = new HtmlElem();
  res->tag = NONE;
  if (doc[i + 1] == 's' && doc[i + 2] == 't' && doc[i + 3] == 'y' &&
      doc[i + 4] == 'l' && doc[i + 5] == 'e') {
    res->tag = CSS;
    string script = "";
    for (int j = i + 6; j + 7 < doc.size(); j++) {
      if (doc[j] == '<' && doc[j + 1] == '/' && doc[j + 2] == 's' &&
          doc[j + 3] == 't' && doc[j + 4] == 'y' && doc[j + 5] == 'l' &&
          doc[j + 6] == 'e' && doc[j + 7] == '>') {
        res->attribute = script;
        res->start_index = i;
        res->end_index = j + 7;
        return res;
      }
      script += doc[j];
    }
  }
  return res;
}

int HtmlParser::_isSelfClosing(const string &tag) {
  /**
   * @brief Determine whether the tag is a closing tag or not
   * @param s: string
   * @return : 1 if it is a closing tag, 0 if it is a self-closing tag, -1 if
   * it is
   */
  string self_closing_tags[] = {
      "area",  "base",   "br",    "col",    "command", "embed",
      "hr",    "img",    "input", "keygen", "link",    "meta",
      "param", "source", "track", "wbr",    "!DOCTYPE"};

  string non_self_closing_tags[] = {
      "a",          "abbr",     "acronym", "address",  "article",    "aside",
      "audio",      "b",        "bdi",     "bdo",      "blockquote", "body",
      "button",     "canvas",   "caption", "cite",     "code",       "colgroup",
      "data",       "datalist", "dd",      "del",      "details",    "dfn",
      "dialog",     "div",      "dl",      "dt",       "em",         "fieldset",
      "figcaption", "figure",   "footer",  "form",     "h1",         "h2",
      "h3",         "h4",       "h5",      "h6",       "head",       "header",
      "html",       "i",        "iframe",  "ins",      "kbd",        "label",
      "legend",     "li",       "main",    "map",      "mark",       "nav",
      "noscript",   "object",   "ol",      "optgroup", "option",     "output",
      "p",          "picture",  "pre",     "progress", "q",          "rp",
      "rt",         "ruby",     "s",       "samp",     "script",     "section",
      "select",     "small",    "span",    "strong",   "style",      "sub",
      "summary",    "sup",      "table",   "tbody",    "td",         "textarea",
      "tfoot",      "th",       "thead",   "time",     "title",      "tr",
      "ul",         "var",      "video"};
  for (auto &e : self_closing_tags) {
    if (tag == e) {
      return 1;
    }
  }

  for (auto &e : non_self_closing_tags) {
    if (tag == e) {
      return 0;
    }
  }

  return -1;
}

int HtmlParser::_isInline(const string &tag) {
  /**
   * @brief 判断给定的 HTML 标签是否为内联元素
   *
   * @param s 给定的 HTML 标签
   * @return int 返回值为 0 表示不是内联元素，返回值为 1
   * 表示是普通内联元素，返回值为 2 表示是特殊内联元素
   */
  string inline_elements[] = {
      "a",        "abbr",   "acronym", "b",      "bdo",    "big",
      "br",       "button", "cite",    "code",   "data",   "datalist",
      "dfn",      "em",     "i",       "img",    "input",  "kbd",
      "label",    "map",    "mark",    "meter",  "object", "output",
      "progress", "q",      "ruby",    "rbc",    "rtc",    "rb",
      "rp",       "rt",     "samp",    "script", "select", "small",
      "span",     "strong", "sub",     "sup",    "svg",    "textarea",
      "time",     "tt",     "var",     "wbr"};

  string block_elements[] = {
      "address", "article", "aside", "audio", "blockquote", "canvas", "dd",
      "details", "div", "dl", "dt", "fieldset", "figcaption", "figure",
      "footer", "form", "h1", "h2", "h3", "h4", "h5", "h6", "header", "hgroup",
      "hr", "li", "main", "nav", "noscript", "ol", "output", "p", "pre",
      "section", "table", "tfoot", "ul", "video", "figcaption", "summary",
      "blockquote", "figure", "hr", "menu", "ol", "ul", "pre", "address",
      "dialog",

      // Table related block elements
      "caption", "colgroup", "thead", "tbody", "tr", "td", "th",

      // Others
      "template",

      // else
      "html"};

  for (const auto &e : block_elements) {
    if (tag == e) {
      if (tag == "h" or tag == "p" or tag == "dt") {
        return SPECIAL_BLOCK;
      } else {
        return NORMAL_BLOCK;
      }
    }
  }

  for (const auto &e : inline_elements) {
    if (tag == e) {
      if (tag == "a") {
        return SPECIAL_INLINE;
      } else {
        return NORMAL_INLINE;
      }
    }
  }
  return 0;
}

HtmlElem *HtmlParser::_parseTag(int i) {
  /**
   * @brief Given a string and the index of "<". Return the HtmlElem with
   * tagName and tagContent(if had)
   * @attention : Couldn't determine whether the tag is an annotation or not.
   * @param s: string
   * @param i: index of "<"
   * @return : Return the HtmlElem with tagName and Attr
   */
  HtmlElem *res = new HtmlElem();
  res->start_index = i;

  if (doc[i + 1] == '/') { // Eng Tag </head>
    res->endTag = true;
  }

  HtmlElem *temp = _isComment(i);
  if (temp->tag != NONE) {
    return temp;
  }

  temp = _isJavaScript(i);
  if (temp->tag != NONE) {
    return temp;
  }

  temp = _isCSS(i);
  if (temp->tag != NONE) {
    return temp;
  }

  Stack<char> st;
  string attribute = "";
  string tagname = "";
  int index = i;

  for (int j = index + 1; j < doc.length(); j++) // Get Tag Name
  {
    if (doc[j] == ' ' or doc[j] == '>' or doc[j] == '\r' or doc[j] == '\n' or
        doc[j] == '\t') {
      // cout << "tagname finish:" << doc[j];
      index = j;
      if (tagname == "!DOCTYPE") {
        res->tag = tagname;
      } else {
        res->tag = toLowerCase(tagname);
      }
      break;
    }
    tagname += doc[j];
  }

  for (int j = index; j < doc.size(); j++) {
    if (doc[j] == '"') { // class=""
      if (st.empty()) {
        st.push('"');
      } else {
        st.pop();
      }
    }

    if (st.empty() and doc[j] == '>') { // End of Tag
      res->attribute = cleanAndReduceWhitespace(attribute);
      res->end_index = j;
      break;
    }
    attribute += doc[j];
  }

  res->attrs = _parseAttribute(res->attribute);

  res->SelfType = _isInline(res->tag);

  if (_isSelfClosing(res->tag) == 1) { // Self Closing Tag
    res->selfClosing = true;
  }

  return res;
}

bool HtmlParser::_checkNested(HtmlElem *child) {
  if (child->fatherType == NORMAL_BLOCK) {
    return true;
  }

  if (child->fatherType == NORMAL_INLINE) {
    if (child->SelfType == NORMAL_INLINE or child->SelfType == SPECIAL_INLINE)
      return true;
    else
      return false;
  }

  if (child->fatherType == SPECIAL_BLOCK) {
    if (child->SelfType == NORMAL_INLINE or child->SelfType == SPECIAL_INLINE) {
      return true;
    } else {
      return false;
    }
  }

  if (child->fatherType == SPECIAL_INLINE) {
    if (child->tag == "a")
      return false;
    else
      return true;
  }
  return true;
}

HtmlElem *HtmlParser::_parseContent(int i) {
  HtmlElem *res = new HtmlElem();
  res->start_index = i;
  res->end_index = doc.size();
  res->tag = CONTENT;

  string content = "";

  // int index = i;
  for (int index = i; index < doc.size(); index++) {
    if (doc[index] == '<') {
      res->end_index = index - 1;
      break;
    }
    content += doc[index];
  }

  content = strip(content);
  res->attribute = mergeSpaces(content);
  return res;
}

void HtmlParser::_parseHtml() {
  /**
   * @brief Parse the whole HTML file
   * @param doc: string
   * @return : void
   */

  Stack<HtmlElem *> nodeStack;
  HtmlElem *dummyRoot = new HtmlElem;
  dummyRoot->tag = "ROOT";
  dummyRoot->SelfType = NORMAL_BLOCK;
  dummyRoot->fatherType = NORMAL_BLOCK;
  nodeStack.push(dummyRoot);

  int index = 0;
  while (!nodeStack.empty() && index + 1 < doc.length()) {
    HtmlElem *cur = nodeStack.top();

    if (doc[index] == '<') {
      HtmlElem *newEle = _parseTag(index); // <node>
      newEle->fatherType = cur->SelfType;
      newEle->father = cur;

      if (newEle->endTag) { // </node>
        string endtag = newEle->tag.substr(1, newEle->tag.length() - 1);
        if (endtag == cur->tag) {
          nodeStack.pop();
          cur = nodeStack.top();
          cur->append(newEle);
          index = newEle->end_index + 1;
          continue;
        } else { // parse error
          this->root = nullptr;
          return;
        }
      }

      if (!newEle->selfClosing) {
        if (!_checkNested(newEle)) {
          this->root = nullptr;
          return;
        }
      }

      if (!newEle->selfClosing && newEle->tag != COMMENT &&
          newEle->tag != JAVASCRIPT && newEle->tag != CSS) { // normal node
        nodeStack.push(newEle);
      }
      cur->append(newEle);
      index = newEle->end_index + 1;
    } else {
      HtmlElem *newEle = _parseContent(index); // content
      newEle->fatherType = cur->SelfType;
      if (newEle->attribute != "")
        cur->append(newEle);
      index = newEle->end_index + 1;
    }
  }

  Queue<HtmlElem *> que;
  que.enqueue(dummyRoot);
  while (!que.empty()) {
    HtmlElem *cur = que.peek();
    que.dequeue();
    Node<HtmlElem *> *child = cur->children->next;
    List<Node<HtmlElem *> *> l;
    while (child) {
      l.append(child);
      if (child->next == nullptr) {
        child->data->brother = nullptr;
      } else {
        child->data->brother = child->next->data;
      }
      child = child->next;
    }
    for (int i = l.size() - 1; i >= 0; i--) {
      que.enqueue(l[i]->data);
    }
  }
  this->root = dummyRoot;
}

map<string, string> HtmlParser::_parseAttribute(const string &attr) {
  map<string, string> res;
  string key = "";
  string value = "";
  bool isKey = true;
  bool isValue = false;
  bool isQuote = false;

  for (int i = 0; i < attr.size(); i++) {
    if (isQuote) {
      if (attr[i] == '"') {
        isQuote = false;
        res[key] = value;
        key = "";
        value = "";
        isKey = true;
        isValue = false;
        continue;
      } else {
        value += attr[i];
        continue;
      }
    }
    if (attr[i] == '"') {
      isQuote = true;
      continue;
    } else if (attr[i] == ' ') {
      continue;
    } else if (attr[i] == '=') {
      isKey = false;
      isValue = true;
      continue;
    }
    if (isKey) {
      key += attr[i];
    }
    if (isValue) {
      value += attr[i];
    }
  }
  return res;
}

void HtmlParser::parse() { _parseHtml(); }

void HtmlParser::readHTML(string &html) { this->doc = html; }

void HtmlParser::readfile(const string &filename) {
  /**
   * @brief Reading a file using its filename
   */
  std::fstream file(filename);
  if (!file) {
    std::cerr << "Cannot open file!" << std::endl;
    exit(1);
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  file.close();
  string s = buffer.str();
  this->doc = s;
  parse();
}

Node<HtmlElem *> *HtmlParser::_traverse(HtmlElem *root, SelectorInfo *info) {
  /**
   * @brief Traverse the root, return a list contains all the elements that
   * fit the selector info.
   * @return a list contains target
   */
  if (root == nullptr) {
    return nullptr;
  }
  LinkList<HtmlElem *> *res = new LinkList<HtmlElem *>();
  Stack<HtmlElem *> st;
  Node<HtmlElem *> *node = root->children->next;
  List<Node<HtmlElem *> *> l;
  while (node) {
    l.append(node);
    node = node->next;
  }
  for (int i = l.size() - 1; i >= 0; i--) {
    st.push(l[i]->data);
  }
  // st.push(root);
  HtmlElem *cur = nullptr;
  while (!st.empty()) {
    cur = st.top();
    st.pop();
    if (match(cur, info)) {
      res->append(cur);
    }
    Node<HtmlElem *> *node = cur->children->next;
    List<Node<HtmlElem *> *> l;
    while (node) {
      l.append(node);
      node = node->next;
    }
    for (int i = l.size() - 1; i >= 0; i--) {
      st.push(l[i]->data);
    }
  }
  return res->head;
}

Node<HtmlElem *> *HtmlParser::css(const string &s, HtmlElem *root) {
  if (root == nullptr) {
    return nullptr;
  }

  Queue<HtmlElem *> tempNode;
  LinkList<SelectorInfo *> selectors = CssSelector::parseSelector(s);

  if (selectors.size() == 1) {
    return _traverse(root, selectors[0]);
  }
  Stack<HtmlElem *> st;
  st.push(root);

  SelectorInfo *first = selectors[0];

  while (!st.empty()) {
    HtmlElem *cur = st.top();
    st.pop();
    if (match(cur, first)) {
      tempNode.enqueue(cur);
    }
    Node<HtmlElem *> *node = cur->children->next;
    List<Node<HtmlElem *> *> l;
    while (node) {
      l.append(node);
      node = node->next;
    }
    for (int i = l.size() - 1; i >= 0; i--) {
      st.push(l[i]->data);
    }
  }

  for (int i = 1; i < selectors.size() - 1; i += 2) {
    SelectorInfo *relation = selectors[i];
    SelectorInfo *second = selectors[i + 1];
    while (!st.empty()) {
      st.pop();
    }
    int queue_size = tempNode.getSize();
    for (int j = 0; j < queue_size; j++) {
      HtmlElem *boss = tempNode.peek();
      tempNode.dequeue();
      if (relation->type == DESCENDANT) {
        Node<HtmlElem *> *traverse_node = _traverse(boss, second);
        Node<HtmlElem *> *cur = traverse_node->next;
        while (cur) {
          if (exist(tempNode, cur->data)) {
            cur = cur->next;
            continue;
          } else {
            tempNode.enqueue(cur->data);
          }
          cur = cur->next;
        }
      } else if (relation->type == BROTHER) {
        HtmlElem *bro = boss->brother;
        while (bro != nullptr) {
          if (match(bro, second)) {
            tempNode.enqueue(bro);
          }
          bro = bro->brother;
        }
      } else if (relation->type == FIRST_BROTHER) {
        if (boss->brother != nullptr) {
          bool isValid = true;
          while (isValid && boss->brother) {
            boss = boss->brother;
            if (boss->endTag == true || boss->tag == "ROOT" ||
                boss->tag == CONTENT || boss->tag == COMMENT ||
                boss->tag == JAVASCRIPT || boss->tag == CSS ||
                boss->tag == NONE)
              continue;
            else {
              break;
            }
          }
          if (match(boss, second)) {
            tempNode.enqueue(boss);
          }
        }
      } else if (relation->type == CHILD) {
        Node<HtmlElem *> *child = boss->children;
        child = child->next;
        while (child) {
          if (match(child->data, second)) {
            tempNode.enqueue(child->data);
          }
          child = child->next;
        }
      } else if (relation->type == GROUP) {
        tempNode.enqueue(boss);
        Node<HtmlElem *> *traverse_node = _traverse(root, second);
        Node<HtmlElem *> *cur = traverse_node->next;
        while (cur) {
          if (exist(tempNode, cur->data)) {
            cur = cur->next;
            continue;
          } else {
            tempNode.enqueue(cur->data);
          }
          cur = cur->next;
        }
      }
    }
  }
  Node<HtmlElem *> *dummyHead = new Node<HtmlElem *>();
  Node<HtmlElem *> *cur = dummyHead;
  while (!tempNode.empty()) {
    cur->next = new Node<HtmlElem *>(tempNode.peek());
    tempNode.dequeue();
    cur = cur->next;
  }
  return dummyHead;
}

/*
List<HtmlElem *> selectXPath(const string &path) {
  List<HtmlElem *> result;

  // Parse the XPath path into a list of element selectors and operators.
  List<string> selectors;
  List<string> operators;
  string selector = "";
  for (char c : path) {
    if (c == '/') {
      if (!selector.empty()) {
        selectors.append(selector);
        selector = "";
      }
      operators.append("/");
    } else if (c == '@') {
      operators.append("@");
    } else {
      selector += c;
    }
  }
  if (!selector.empty()) {
    selectors.append(selector);
  }

  // Start from the root element.
  Queue<HtmlElem *> queue;
  queue.enqueue(root);

  // Traverse the elements tree.
  for (int i = 0; i < selectors.size(); i++) {
    string selector = selectors[i];
    string op = operators[i];
    int size = queue.getSize();
    for (int j = 0; j < size; j++) {
      HtmlElem *elem = queue.peek();
      queue.dequeue();
      if (op == "/") {
        for (HtmlElem *child : elem->children) {
          if (child->tag == selector) {
            queue.enqueue(child);
          }
        }
      } else if (op == "//") {
        for (HtmlElem *child : elem->children) {
          if (child->tag == selector) {
            result.push_back(child);
          }
          queue.enqueue(child);
        }
      } else if (op == ".") {
        if (elem->tag == selector) {
          result.push_back(elem);
        }
      } else if (op == "..") {
        if (elem->parent && elem->parent->tag == selector) {
          result.push_back(elem->parent);
        }
      } else if (op == "@") {
        if (elem->attributes.count(selector)) {
          // Create a new HtmlElem to represent the attribute.
          HtmlElem *attr = new HtmlElem;
          attr->tag = selector;
          attr->text = elem->attributes[selector];
          result.push_back(attr);
        }
      }
    }
  }

  return result;
}
*/

void HtmlParser::debug(HtmlElem *ele) {
  cout << "ele.tag: " << ele->tag << endl;
  cout << "ele.attribute: " << ele->attribute << endl;
  cout << "ele.start_index: " << ele->start_index << endl;
  cout << "ele.end_index: " << ele->end_index << endl;
  cout << "ele.selfClosing: " << ele->selfClosing << endl;
  cout << "ele.endTag: " << ele->endTag << endl;
  // cout << "ele.children.size(): " << ele->children.size() << endl;
  cout << endl;
}

HtmlElem *HtmlParser::getRoot() { return this->root; }

string HtmlParser::getDoc() { return this->doc; }

#endif
