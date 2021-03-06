#ifndef BINARY_OP_AST_NODE_H
#define BINARY_OP_AST_NODE_H

#include "query/Token.h"
#include "query/ast/ASTNode.h"
#include "query/ast/NodeVisitor.h"

class BinaryOpASTNode : public ASTNode {
private:
  ASTNode *Left;
  Token Op;
  ASTNode *Right;

public:
  BinaryOpASTNode(ASTNode *Left, Token Op, ASTNode *Right);
  ASTNode *left();
  Token op();
  ASTNode *right();
  void accept(NodeVisitor &Visitor) override;
  ~BinaryOpASTNode();
};

#endif
