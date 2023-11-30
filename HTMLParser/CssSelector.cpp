#ifndef CSSSELECTOR_CPP
#define CSSSELECTOR_CPP

#include "CssSelector.h"

bool _matchTag(HtmlElem *element, const string &tagName) {
  if (element == nullptr)
    return false;
  if (element->tag == tagName)
    return true;
  if (tagName == "*" || tagName == "") {
    if (element->endTag == true || element->tag == "ROOT" ||
        element->tag == CONTENT || element->tag == COMMENT ||
        element->tag == JAVASCRIPT || element->tag == CSS ||
        element->tag == NONE) {
      return false;
    } else {
      return true;
    }
  }
  return false;
}

bool _matchClass(HtmlElem *element, const string &className) {
  if (element == nullptr)
    return false;
  string classValue = element->attrs["class"];
  List<string> classes = split(classValue, ' ');
  for (int i = 0; i < classes.size(); i++) {
    if (classes[i] == className)
      return true;
  }
  return false;
}

bool _matchID(HtmlElem *element, const string &idName) {
  if (element == nullptr)
    return false;
  if (element->attrs["id"] == idName)
    return true;
  return false;
}

bool _matchAttribute(HtmlElem *element, const string &attributeName,
                     const string &attributeValue, AttrType type) {

  if (element == nullptr)
    return false;
  auto it = element->attrs.find(attributeName);
  if (it != element->attrs.end()) {
    if (type == NORMAL) {
      if (attributeValue == "" || it->second == attributeValue)
        return true;
    } else if (type == CONTAIN) {
      if (contain(element->attrs[attributeName], attributeValue))
        return true;
    } else if (type == BEGIN) {
      if (begin_with(element->attrs[attributeName], attributeValue))
        return true;
    } else if (type == END) {
      if (end_with(element->attrs[attributeName], attributeValue))
        return true;
    }
  }
  return false;
}

bool match(HtmlElem *ele, SelectorInfo *info) {
  if (ele == nullptr){
    return false;
  }
  for (int i = 0; i < info->parts.size(); i++) {
    if (info->parts[i]->type == ID) {
      if (!_matchID(ele, info->parts[i]->value))
        return false;
    } else if (info->parts[i]->type == CLASS) {
      if (!_matchClass(ele, info->parts[i]->value))
        return false;
    } else if (info->parts[i]->type == TAG) {
      if (!_matchTag(ele, info->parts[i]->value))
        return false;
    } else if (info->parts[i]->type == ATTRIBUTE) {
      if (!_matchAttribute(ele, info->parts[i]->value,
                           info->parts[i]->attributeValue,
                           info->parts[i]->attrType))
        return false;
    } else {
      return false;
    }
  }
  return true;
}

SelectorInfo *CssSelector::_parseNode(const string &simple_part) {
  /**
   * @brief Parse one node with some restraints
   * pass test 1~5
   */
  SelectorInfo *info = new SelectorInfo();
  SelectorPart *part = new SelectorPart();

  bool inClass = false, inID = false, inAttr = false, inAttrValue = false,
       inAttrName = false, inName = true;

  string attrName = "", attrValue = "", className = "", tagName = "";

  if (simple_part[0] == '.' || simple_part[0] == '#' || simple_part[0] == '[') {
    inName = false;
  }

  for (int i = 0; i < simple_part.size(); i++) {
    if (inClass) {
      if (simple_part[i] == '.' || simple_part[i] == '#' ||
          simple_part[i] == ' ' || simple_part[i] == '[') {
        part->type = CLASS;
        part->value = className;
        info->parts.append(part);
        className = "";
        part = new SelectorPart();
        inClass = false;
        i--;
      } else {
        className += simple_part[i];
      }
    } else if (inAttr) {
      if (simple_part[i] == '~') {
        part->attrType = CONTAIN;
        continue;
      } else if (simple_part[i] == '|') {
        part->attrType = BEGIN;
        continue;
      } else if (simple_part[i] == '$') {
        part->attrType = END;
        continue;
      }

      if (simple_part[i] == '=') {
        inAttrName = false;
        inAttrValue = true;
        continue;
      } else if (simple_part[i] == ']') {
        inAttr = false;
        inAttrName = false;
        inAttrValue = false;
        part->type = ATTRIBUTE;
        part->value = attrName;
        part->attributeValue = attrValue;
        info->parts.append(part);
        attrName = "";
        attrValue = "";
        part = new SelectorPart();
        continue;
      }
      if (inAttrName) {
        attrName += simple_part[i];
      }
      if (inAttrValue) {
        attrValue += simple_part[i];
      }
    } else if (inID) {
      if (simple_part[i] == '.' || simple_part[i] == '#' ||
          simple_part[i] == ' ' || simple_part[i] == '[') {
        part->type = ID;
        part->value = tagName;
        info->parts.append(part);
        tagName = "";
        part = new SelectorPart();
        inID = false;
        i--;
      } else {
        tagName += simple_part[i];
      }
    } else if (inName) {
      if (simple_part[i] == '.' || simple_part[i] == '#' ||
          simple_part[i] == ' ' || simple_part[i] == '[') {
        part->type = TAG;
        part->value = tagName;
        info->parts.append(part);
        tagName = "";
        part = new SelectorPart();
        inName = false;
        i--;
      } else {
        tagName += simple_part[i];
      }
    }
    if (simple_part[i] == '.') {
      inClass = true;
      continue;
    } else if (simple_part[i] == '#') {
      inID = true;
      continue;
    } else if (simple_part[i] == '[') {
      inAttr = true;
      inAttrName = true;
      continue;
    }
  }
  if (part->type == CSS_NONE) {
    if (inClass) {
      part->type = CLASS;
      part->value = className;
      info->parts.append(part);
    } else if (inAttr) {
      part->type = ATTRIBUTE;
      part->value = attrName;
      part->attributeValue = attrValue;
      info->parts.append(part);
    } else if (inID) {
      part->type = ID;
      part->value = tagName;
      info->parts.append(part);
    } else if (inName) {
      part->type = TAG;
      part->value = tagName;
      info->parts.append(part);
    }
  }
  return info;
}

LinkList<SelectorInfo *> CssSelector::parseSelector(const string &selector) {
  LinkList<SelectorInfo *> Info; // 使用列表存储解析后的选择器部分
  int begin_index = 0;
  int end_index = 0;
  SelectorInfo *relation = new SelectorInfo();
  bool isQuote = false;
  for (int i = 0; i < selector.size(); i++) {
    if (selector[i] == '[') {
      isQuote = true;
    } else if (selector[i] == ']') {
      isQuote = false;
    } else if (selector[i] == ' ') {
      relation->type = DESCENDANT;
    } else if (selector[i] == '>') {
      relation->type = CHILD;
    } else if (selector[i] == ',') {
      relation->type = GROUP;
    } else if (selector[i] == '~') {
      if (!isQuote)
        relation->type = BROTHER;
    } else if (selector[i] == '+') {
      relation->type = FIRST_BROTHER;
    } else {
      end_index = i;
    }
    if (relation->type != CSS_NONE) {
      SelectorInfo *node =
          _parseNode(selector.substr(begin_index, end_index - begin_index + 1));
      begin_index = i + 1;
      Info.append(node);
      Info.append(relation);
      relation = new SelectorInfo();
    }
  }
  if (begin_index < selector.size()) {
    Info.append(_parseNode(
        selector.substr(begin_index, selector.size() - begin_index)));
  }
  return Info;
}

#endif
