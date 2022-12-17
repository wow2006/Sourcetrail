if(WIN32)
  get_filename_component(QT_BINARY_DIR "${QT_MOC_EXECUTABLE}" PATH)
  set(QT_PLUGINS_DIR "${QT_BINARY_DIR}/../plugins")

  function(COPY_QT_BINARIES IS_DEBUG IS_APP)
    set(SUFFIX "")
    if(IS_DEBUG)
      set(SUFFIX "d")
    endif()

    set(CONFIGURATION "Release")
    if(IS_DEBUG)
      set(CONFIGURATION "Debug")
    endif()

    if(CMAKE_CL_64)
      set(BITS "64")
    else()
      set(BITS "32")
    endif()

    set(TARGET "test")
    if(IS_APP)
      set(TARGET "app")

      file(GLOB MY_PUBLIC_HEADERS "${CMAKE_SOURCE_DIR}/setup/dynamic_libraries/win${BITS}/app/*")
      file(COPY ${MY_PUBLIC_HEADERS} DESTINATION "${CMAKE_BINARY_DIR}/${TARGET}/")
    endif()

    configure_file("${QT_BINARY_DIR}/Qt5Core${SUFFIX}.dll"
                   "${CMAKE_BINARY_DIR}/${TARGET}/Qt5Core${SUFFIX}.dll" COPYONLY)
    configure_file("${QT_BINARY_DIR}/Qt5Gui${SUFFIX}.dll"
                   "${CMAKE_BINARY_DIR}/${TARGET}/Qt5Gui${SUFFIX}.dll" COPYONLY)
    configure_file("${QT_BINARY_DIR}/Qt5Network${SUFFIX}.dll"
                   "${CMAKE_BINARY_DIR}/${TARGET}/Qt5Network${SUFFIX}.dll" COPYONLY)
    configure_file("${QT_BINARY_DIR}/Qt5Svg${SUFFIX}.dll"
                   "${CMAKE_BINARY_DIR}/${TARGET}/Qt5Svg${SUFFIX}.dll" COPYONLY)
    configure_file("${QT_BINARY_DIR}/Qt5Widgets${SUFFIX}.dll"
                   "${CMAKE_BINARY_DIR}/${TARGET}/Qt5Widgets${SUFFIX}.dll" COPYONLY)
    configure_file("${QT_BINARY_DIR}/Qt5WinExtras${SUFFIX}.dll"
                   "${CMAKE_BINARY_DIR}/${TARGET}/Qt5WinExtras${SUFFIX}.dll" COPYONLY)

    configure_file("${QT_PLUGINS_DIR}/platforms/qwindows${SUFFIX}.dll"
                   "${CMAKE_BINARY_DIR}/${TARGET}/platforms/qwindows${SUFFIX}.dll" COPYONLY)

    configure_file("${QT_PLUGINS_DIR}/styles/qwindowsvistastyle${SUFFIX}.dll"
                   "${CMAKE_BINARY_DIR}/${TARGET}/styles/qwindowsvistastyle${SUFFIX}.dll" COPYONLY)

    configure_file("${QT_PLUGINS_DIR}/imageformats/qgif${SUFFIX}.dll"
                   "${CMAKE_BINARY_DIR}/${TARGET}/imageformats/qgif${SUFFIX}.dll" COPYONLY)
    configure_file("${QT_PLUGINS_DIR}/imageformats/qicns${SUFFIX}.dll"
                   "${CMAKE_BINARY_DIR}/${TARGET}/imageformats/qicns${SUFFIX}.dll" COPYONLY)
    configure_file("${QT_PLUGINS_DIR}/imageformats/qico${SUFFIX}.dll"
                   "${CMAKE_BINARY_DIR}/${TARGET}/imageformats/qico${SUFFIX}.dll" COPYONLY)
    configure_file("${QT_PLUGINS_DIR}/imageformats/qjpeg${SUFFIX}.dll"
                   "${CMAKE_BINARY_DIR}/${TARGET}/imageformats/qjpeg${SUFFIX}.dll" COPYONLY)
    configure_file("${QT_PLUGINS_DIR}/imageformats/qsvg${SUFFIX}.dll"
                   "${CMAKE_BINARY_DIR}/${TARGET}/imageformats/qsvg${SUFFIX}.dll" COPYONLY)
    configure_file("${QT_PLUGINS_DIR}/imageformats/qtga${SUFFIX}.dll"
                   "${CMAKE_BINARY_DIR}/${TARGET}/imageformats/qtga${SUFFIX}.dll" COPYONLY)
    configure_file("${QT_PLUGINS_DIR}/imageformats/qtiff${SUFFIX}.dll"
                   "${CMAKE_BINARY_DIR}/${TARGET}/imageformats/qtiff${SUFFIX}.dll" COPYONLY)
    configure_file("${QT_PLUGINS_DIR}/imageformats/qwbmp${SUFFIX}.dll"
                   "${CMAKE_BINARY_DIR}/${TARGET}/imageformats/qwbmp${SUFFIX}.dll" COPYONLY)
    configure_file("${QT_PLUGINS_DIR}/imageformats/qwebp${SUFFIX}.dll"
                   "${CMAKE_BINARY_DIR}/${TARGET}/imageformats/qwebp${SUFFIX}.dll" COPYONLY)
  endfunction()

  copy_qt_binaries(True True)
  copy_qt_binaries(True False)
  copy_qt_binaries(False True)
  copy_qt_binaries(False False)

  configure_file("${CMAKE_SOURCE_DIR}/setup/icon/windows/sourcetrail.ico"
                 "${CMAKE_BINARY_DIR}/sourcetrail.ico" COPYONLY)
endif()