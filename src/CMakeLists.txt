project(win32_api) 

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE}) 

## Add source files ## 
	file (GLOB_RECURSE source_files ./*) 
## End of adding source files ## 

## Remove main.c files of modules ## 
## End of removing main.c files of modules ## 

## Add executables ## 
	add_executable (win32_api ${source_files}) 
## End of adding executables ##