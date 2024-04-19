add_custom_target(bundle)
add_custom_command(TARGET bundle
  DEPENDS ${PROJECT_NAME}
 
  COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/LTecher Adventure.app"
  COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/LTecher Adventure.app/Contents"
  COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/LTecher Adventure.app/Contents/MacOS"
  COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/LTecher Adventure.app/Contents/Resources"
  

  COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/bundle/Info.plist"
    "${CMAKE_CURRENT_BINARY_DIR}/LTecher Adventure.app/Contents/Info.plist"

  COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}" 
    "${CMAKE_CURRENT_BINARY_DIR}/LTecher Adventure.app/Contents/MacOS/"

  COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/bundle/run.sh" 
    "${CMAKE_CURRENT_BINARY_DIR}/LTecher Adventure.app/Contents/MacOS/run.sh"
  COMMAND chmod +x "${CMAKE_CURRENT_BINARY_DIR}/LTecher Adventure.app/Contents/MacOS/run.sh"


  COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCES_FILE}"
    "${CMAKE_CURRENT_BINARY_DIR}/LTecher Adventure.app/Contents/Resources/${RESOURCES_FILE}"

  COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/bundle/icon.icns" 
    "${CMAKE_CURRENT_BINARY_DIR}/LTecher Adventure.app/Contents/Resources/icon.icns"
)

