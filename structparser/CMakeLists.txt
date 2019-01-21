set(LLVM_LINK_COMPONENTS support)

add_clang_executable(structparser
  StructParser.cpp
)
target_link_libraries(structparser PRIVATE 
  clangTooling
  clangBasic
  clangASTMatchers
)