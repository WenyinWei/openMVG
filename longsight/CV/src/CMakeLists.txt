
foreach(files blas1 blas2 blas3 blas3range )
  add_executable(${files} ${files}.cpp)
  set_target_properties(${files} PROPERTIES COMPILE_FLAGS "-DVIENNACL_WITH_OPENCL")
  target_link_libraries(${files} ${OPENCL_LIBRARIES})
endforeach()

include_directories("${include_dir}"/viennacv) # for "viennaCV.h"
message(${include_dir})
foreach(files image_test)
  # include_directories(${include_dir}/stb) # One may find this website useful https://stackoverflow.com/questions/2076475/reading-an-image-file-in-c-c
  add_executable(${files} ${files}.cpp)
  add_definitions( -DMAGICKCORE_QUANTUM_DEPTH=16 )
  add_definitions( -DMAGICKCORE_HDRI_ENABLE=0 )
  find_package(ImageMagick COMPONENTS Magick++) # TODO: sudo apt-get install libmagick++-dev
  message(${ImageMagick_INCLUDE_DIRS})
  include_directories(${ImageMagick_INCLUDE_DIRS})
  target_link_libraries(${files} ${ImageMagick_LIBRARIES})
  set_target_properties(${files} PROPERTIES COMPILE_FLAGS "-DVIENNACL_WITH_OPENCL")
  target_link_libraries(${files} ${OPENCL_LIBRARIES})
endforeach()