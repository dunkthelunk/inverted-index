#ifndef NODE_PRINT_VISITOR_H
#define NODE_PRINT_VISITOR_H
#include "query/ast/ASTNode.h"
#include "query/ast/BinaryOpASTNode.h"
#include "query/ast/NodeVisitor.h"
#include "query/ast/WordASTNode.h"

class NodePrintVisitor : public NodeVisitor {
public:
  void visit(BinaryOpASTNode *Node) override;
  void visit(WordASTNode *Node) override;
};
#endif
