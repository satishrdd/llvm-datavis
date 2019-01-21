#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "llvm/Support/CommandLine.h"
#include "clang/Tooling/Tooling.h"
#include <iostream>

using namespace clang::tooling;
using namespace llvm;
using namespace clang;


class FindNamedClassVisitor
  : public RecursiveASTVisitor<FindNamedClassVisitor> {
public:
  explicit FindNamedClassVisitor(ASTContext *Context)
    : Context(Context) {}

  bool VisitCXXRecordDecl(CXXRecordDecl *Declaration) {
    if (Declaration->isStruct()) {
      clang::TagDecl *t = Declaration;
      clang::RecordDecl *r =  Declaration;
      clang::RecordDecl::field_iterator jt;
      std::cout<<Declaration->getNameAsString()<<std::endl;
      for(jt = r->field_begin(); jt != r->field_end();++jt)
      {
          std::cout <<"\t-----"<< jt->getType().getAsString() << " " << jt->getNameAsString() << std::endl;
      }
      std::cout<<std::endl;
    }
    return true;
  }

private:
  ASTContext *Context;
};

class FindNamedClassConsumer : public clang::ASTConsumer {
public:
  explicit FindNamedClassConsumer(ASTContext *Context)
    : Visitor(Context) {}

  virtual void HandleTranslationUnit(clang::ASTContext &Context) {
    Visitor.TraverseDecl(Context.getTranslationUnitDecl());
  }
private:
  FindNamedClassVisitor Visitor;
};

class FindNamedClassAction : public clang::ASTFrontendAction {
public:
  virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
    clang::CompilerInstance &Compiler, llvm::StringRef InFile) {
    return std::unique_ptr<clang::ASTConsumer>(
        new FindNamedClassConsumer(&Compiler.getASTContext()));
  }
};

static llvm::cl::OptionCategory MyToolCategory("My tool options");
int main(int argc, const char **argv) {
      CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
      ClangTool Tool(OptionsParser.getCompilations(),
                 OptionsParser.getSourcePathList());
      return Tool.run(newFrontendActionFactory<FindNamedClassAction>().get());
}