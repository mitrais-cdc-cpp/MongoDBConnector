file(REMOVE_RECURSE
  "libMongoDaoLib.pdb"
  "libMongoDaoLib.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/MongoDaoLib.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
