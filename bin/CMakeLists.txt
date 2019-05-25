configure_file("fingerprint-rw/cc.ullrich-online.fingerprint-gui.policy.in" "fingerprint-rw/cc.ullrich-online.fingerprint-gui.policy" @ONLY)
configure_file("fingerprint-polkit-agent/fingerprint-polkit-agent.desktop.in" "fingerprint-polkit-agent/fingerprint-polkit-agent.desktop" @ONLY)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../doc/fingerprint-gui" DESTINATION "share/doc" PATTERN "*.xml" EXCLUDE)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/fingerprint-gui/fingerprint-gui.desktop" DESTINATION "share/applications")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/fingerprint-rw/cc.ullrich-online.fingerprint-gui.policy" DESTINATION "share/polkit-1/actions")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/fingerprint-polkit-agent/fingerprint-polkit-agent.desktop" DESTINATION "/etc/xdg/autostart/")
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/fingerprint-helper/92-fingerprint-gui-uinput.rules" DESTINATION "lib/udev/rules.d")

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/../man/fingerprint-gui.1" "../man/fingerprint-identifier.1" DESTINATION "share/man/man1")
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/../man/pam_fingerprint-gui.8" DESTINATION "share/man/man8")
