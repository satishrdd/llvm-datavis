set(LLVM_LINK_COMPONENTS support)

add_clang_executable(commentparser
	CommentParser.cpp
)

target_link_libraries(commentparser PRIVATE  
	clangTooling
	clangBasic
	clangASTMatchers
)