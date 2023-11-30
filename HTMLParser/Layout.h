#ifndef LAYOUT_H
#define LAYOUT_H

#include "HtmlParser.h"
#include "HtmlElement.h"

namespace Layout {
  string showSub(HtmlElem *const root);

  string show(HtmlElem *const root);

  string showText(HtmlElem *const root);

  string OutHTML(HtmlElem *const root, const string &s);

  string Text(HtmlElem *const root, const string &s);
};

#endif