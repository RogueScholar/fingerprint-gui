SET(CMAKE_AUTORCC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
SET(AUTOUIC_SEARCH_PATHS "${AUTOUIC_SEARCH_PATHS} ${CMAKE_CURRENT_SOURCE_DIR}")

QT5_WRAP_CPP(COMMON_OBJS_MOC "${CMAKE_CURRENT_SOURCE_DIR}/../include/FingerprintDevice.h")
add_library(COMMON_OBJS OBJECT
  ${COMMON_OBJS_MOC}
  drivers/UpekDevice.cpp
  drivers/GenericDevice.cpp
  GlobalsImg.cpp
  DeviceHandler.cpp
  UsbDevice.cpp
)

add_library(WDRES OBJECT widget-res.qrc)

# fingerprint-gui: main GUI
set(QRC_OBJS GUI-res.qrc
             About-res.qrc)
qt5_wrap_ui(GUI_OBJS About.ui
            ExistDialog.ui
            FingerprintGUI.ui
            SavedDialog.ui
            Message.ui)
add_definitions("-DLIBEXECDIR=\"${CMAKE_PREFIX_PATH}/lib/fingerprint-gui\"")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing")
add_executable(fingerprint-gui
   ${GUI_OBJS}
   ${QRC_OBJS}
   $<TARGET_OBJECTS:COMMON_OBJS>
   AboutImpl.cpp
   ExistDialogImpl.cpp
   Fingerprint.cpp
   FingerprintData.cpp
   FingerprintGUI.cpp
   MainWindowImpl.cpp
   SavedDialogImpl.cpp
   MessageDialogImpl.cpp
   PamTester.cpp
   xmlwriter.cpp
   UserSettings.cpp
)

target_link_libraries(fingerprint-gui
${LIBUSB_LINK_LIBRARIES} ${LIBFPRINT_LINK_LIBRARIES} pam dl ${QT_LIBRARIES} qca-qt5)

# fingerprint-identifier
add_executable(fingerprint-identifier
  $<TARGET_OBJECTS:COMMON_OBJS>
  $<TARGET_OBJECTS:WDRES>
  FingerprintIdentifier.ui

  FingerprintData.cpp
  FingerprintDiscoverer.cpp
  IdentifierGUI.cpp
  FingerprintIdentifier.cpp
)
target_link_libraries(fingerprint-identifier
${LIBUSB_LINK_LIBRARIES} ${LIBFPRINT_LINK_LIBRARIES} pam dl ${QT_LIBRARIES})

# fingerprint-polkit-agent
qt5_wrap_ui(POLKIT_UI_OBJS
  FingerprintPlugin.ui
  PolkitDialog.ui
  PolkitDetails.ui)
add_executable(fingerprint-polkit-agent
  ${POLKIT_UI_OBJS}
  $<TARGET_OBJECTS:WDRES>

  GlobalsImg.cpp
  PluginDialog.cpp
  PolkitListener.cpp
  PolkitDialogImpl.cpp
  FingerprintPolkit.cpp
)
target_include_directories(fingerprint-polkit-agent PRIVATE ${POLKITQT-1_INCLUDE_DIRS})
target_link_libraries(fingerprint-polkit-agent
  ${LIBUSB_LINK_LIBRARIES}
  ${LIBFPRINT_LINK_LIBRARIES}
  ${POLKITQT-1_CORE_LIBRARY}
  ${POLKITQT-1_AGENT_LIBRARY}
  ${QT_LIBRARIES}
)

# fingerprint-helper
add_executable(fingerprint-helper
  $<TARGET_OBJECTS:COMMON_OBJS>
  FingerprintPlugin.ui

  FingerprintData.cpp
  FingerprintDiscoverer.cpp
  xmlwriter.cpp
  UserSettings.cpp
  PamGUI.cpp
  PamNonGUI.cpp
  FingerprintHelper.cpp
  $<TARGET_OBJECTS:WDRES>
)
target_link_libraries(fingerprint-helper
  ${LIBUSB_LINK_LIBRARIES}
  ${LIBFPRINT_LINK_LIBRARIES}
  ${QT_LIBRARIES}
  ${FAKEKEY_LINK_LIBRARIES}
  Qt5::X11Extras
  dl qca-qt5
)
