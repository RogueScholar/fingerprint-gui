SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

qt5_wrap_ui(UI_OBJS About.ui
         ExistDialog.ui
         FingerprintGUI.ui
         SavedDialog.ui
         Message.ui)

set(QRC_OBJS GUI-res.qrc
             About-res.qrc)
add_definitions("-DLIBEXECDIR=\"${CMAKE_PREFIX_PATH}/lib/fingerprint-gui\"")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing")

add_executable(fingerprint-gui
   ${UI_OBJS}
   ${QRC_OBJS}
   GlobalsImg.cpp
   DeviceHandler.cpp
   AboutImpl.cpp
   ExistDialogImpl.cpp
   Fingerprint.cpp
   FingerprintData.cpp
   drivers/UpekDevice.cpp
   drivers/GenericDevice.cpp
   FingerprintGUI.cpp
   MainWindowImpl.cpp
   SavedDialogImpl.cpp
   MessageDialogImpl.cpp
   PamTester.cpp
   xmlwriter.cpp
   UserSettings.cpp
   UsbDevice.cpp)

target_link_libraries(fingerprint-gui
${LIBUSB_LINK_LIBRARIES} ${LIBFPRINT_LINK_LIBRARIES} pam dl ${QT_LIBRARIES} qca-qt5)
