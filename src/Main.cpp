#include <iostream>

#include "IndexFileBasedDocSupplier.h"
#include "InvertedIndex.h"
#include "TermRecordPrinter.h"
#include "query/Interpreter.h"
#include "query/Lexer.h"
#include "query/Parser.h"
#include "query/ast/ResultComputingNodeVisitor.h"
#include "util/DocumentIndexFileBasedStringSupplier.h"
#include "util/SimpleTokenizer.h"
#include "util/TermIDMapper.h"

int main() {
  std::string DocFilesRoot = "../resources/txts/";
  std::string IndexFileName = "index.txt";
  std::string MappingFileName = "TermIDMapping.txt";
  std::string MappingFilePath = DocFilesRoot + MappingFileName;

  DocumentIndexFileBasedStringSupplier SSupplier(DocFilesRoot, IndexFileName);
  TermIDMapper TermIDMapper(SSupplier);
  TermIDMapper.createMap();
  TermIDMapper.serializeMapTo(MappingFilePath);
  TermIDMapping TermIDMap;
  TermIDMap.loadMappingFromFile(MappingFilePath);

  IndexFileBasedDocSupplier IFBDocSupplier(DocFilesRoot, IndexFileName);
  SimpleTokenizer Tokenizer;
  InvertedIndex IIndex;
  IIndex.build(IFBDocSupplier, Tokenizer, TermIDMap);

  ResultComputingNodeVisitor RCNVisitor(IIndex, TermIDMap);

  TermRecordPrinter TRPrinter(DocFilesRoot, IndexFileName);

  std::string Query;
  std::cout << "Enter query string (Ctrl+D to exit) : ";
  while (getline(std::cin, Query)) {
    Lexer Lexer(Query);
    Parser Parser(Lexer);
    Interpreter Interpreter(Parser, RCNVisitor);
    auto Result = Interpreter.computeSearchResult();
    std::cout << Result.size() << " result";
    if (Result.size() == 1) {
      std::cout << ".\n";
    } else {
      std::cout << "s.\n";
    }
    for (auto TRecord : Result) {
      std::cout << TRecord.docID() << '\n';
      TRPrinter.print(TRecord);
    }
    std::cout << "Enter query string (Ctrl+D to exit) : ";
  }
  std::cout << '\n';
  return 0;
}
