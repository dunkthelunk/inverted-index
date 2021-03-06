#ifndef AST_NODE_H
#define AST_NODE_H

#include "TermRecord.h"
#include "compare/TermRecordCompare.h"
#include "query/ast/NodeVisitor.h"
#include <set>

class ASTNode {
private:
  bool IsEvaluated;
  std::set<TermRecord, TermRecordCompare> Result;

public:
  ASTNode();
  virtual void accept(NodeVisitor &Visitor) = 0;
  bool evaluated();
  void isEvaluated();
  std::set<TermRecord, TermRecordCompare> &result();
  std::set<TermRecord, TermRecordCompare> evaluatedResult();
  virtual ~ASTNode() = 0;
};
#endif
