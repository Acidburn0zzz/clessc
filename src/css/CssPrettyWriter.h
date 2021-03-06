
#ifndef __CssPrettyWriter_h__
#define __CssPrettyWriter_h__

#include "CssWriter.h"
#include "../TokenList.h"
#include "../Token.h"
#include <iostream>

class CssPrettyWriter: public CssWriter {
private:
  int indent_size;

protected:
  void indent();
  void newline();

  virtual void writeSelector(const TokenList &selector);
    
public:
  CssPrettyWriter(std::ostream &out): CssWriter(out) {
    indent_size = 0;
  };
  CssPrettyWriter(std::ostream &out, SourceMapWriter &sourcemap):
    CssWriter(out, sourcemap) {
    indent_size = 0;
  }

  virtual void writeAtRule(const Token &keyword, const TokenList &rule);
  virtual void writeRulesetStart(const TokenList &selector);
  virtual void writeRulesetEnd();
  virtual void writeDeclaration(const Token &property, const TokenList &value);
  virtual void writeDeclarationDeliminator();
  virtual void writeComment(const Token &comment);
  virtual void writeMediaQueryStart(const TokenList &selector);
  virtual void writeMediaQueryEnd();
};

#endif
