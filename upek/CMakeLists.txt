IF(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
  install(FILES "lib64/libbsapi.so.4.0" "lib64/libbsapi.so.4.3"
  DESTINATION "lib/")
ELSEIF(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86")
  install(FILES "lib64/libbsapi.so.4.0" "lib64/libbsapi.so.4.3"
  DESTINATION "lib/")
ENDIF()

install(FILES 91-fingerprint-gui-upek.rules DESTINATION "lib/udev/rules.d")
install(FILES upek.cfg DESTINATION /etc)
