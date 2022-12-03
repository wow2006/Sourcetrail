# Address Sanitizer
add_library(
  AddressSanaitizer
  INTERFACE
  IMPORTED
  GLOBAL
)

target_link_options(
  AddressSanaitizer
  INTERFACE
  $<$<CXX_COMPILER_ID:GNU,Clang>:-fsanitize=address>
)

target_compile_options(
  AddressSanaitizer
  INTERFACE
  $<$<CXX_COMPILER_ID:GNU,Clang>:-fsanitize=address;-fomit-frame-pointer>
)

# Memory Sanitizer
add_library(
  MemorySanaitizer
  INTERFACE
  IMPORTED
  GLOBAL
)

target_link_options(
  MemorySanaitizer
  INTERFACE
  $<$<CXX_COMPILER_ID:GNU,Clang>:-fsanitize=memory>
)

target_compile_options(
  MemorySanaitizer
  INTERFACE
  $<$<CXX_COMPILER_ID:GNU,Clang>:-fsanitize=memory;-fno-omit-frame-pointer>
)

add_library(
  Sanaitizer::Address
  ALIAS
  AddressSanaitizer
)

add_library(
  Sanaitizer::Memory
  ALIAS
  MemorySanaitizer
)

