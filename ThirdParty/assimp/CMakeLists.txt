message("-- Linking Assimp")
add_library(Assimp bin/assimp-vc142-mtd.dll)
set_target_properties(Assimp PROPERTIES LINKER_LANGUAGE CXX)