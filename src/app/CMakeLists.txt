add_files(
  APP

  main.cpp
)

if(BUILD_EXPORT_UML)
  add_subdirectory(export_UML)
endif()

