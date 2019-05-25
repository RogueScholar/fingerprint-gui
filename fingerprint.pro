TEMPLATE = subdirs
SUBDIRS = bin

isEmpty(PREFIX) {
        PREFIX = /usr
}
isEmpty(LIB) {
	LIB = lib
}

LIBDIR = $${PREFIX}/$${LIB}

upek-lib.commands     = install -d $(INSTALL_ROOT)$${LIBDIR}; \
                        if uname -a | grep -q x86_64; then \
                            install -m 644 ./upek/lib64/libbsapi.so.4.0 ./upek/lib64/libbsapi.so.4.3 $(INSTALL_ROOT)$${LIBDIR}; \
                        else \
                            install -m 644 ./upek/lib/libbsapi.so.4.0 ./upek/lib/libbsapi.so.4.3 $(INSTALL_ROOT)$${LIBDIR}; \
                        fi; \
                        ldconfig
upek-rules.commands   = install -d $(INSTALL_ROOT)/etc/udev/rules.d; \
                        install -m 644 ./upek/91-fingerprint-gui-upek.rules $(INSTALL_ROOT)/etc/udev/rules.d
upek-cfg.commands     = install -d $(INSTALL_ROOT)/etc; \
                        install -m 644 ./upek/upek.cfg $(INSTALL_ROOT)/etc/upek.cfg
upek-dir.commands     = install -d $(INSTALL_ROOT)/var/upek_data; \
                        groupadd -f -r plugdev; \
                        chown root:plugdev $(INSTALL_ROOT)/var/upek_data; \
                        chmod 0775 $(INSTALL_ROOT)/var/upek_data
upek-udevadm.commands = if command -v udevadm >/dev/null; then \
                            for ID in 2015 2016; do \
                                udevadm trigger --subsystem-match=usb --attr-match=idVendor=0483 --attr-match=idProduct=$ID; \
                            done; \
                            for ID in 2015 2016 2020 1000 1001 1002 1003 3000 3001 5002 5003; do \
                                udevadm trigger --subsystem-match=usb --attr-match=idVendor=147e --attr-match=idProduct=$ID; \
                            done; \
                        fi
install-upek.commands =
install-upek.depends  = upek-lib upek-rules upek-cfg upek-dir upek-udevadm
uninstall-upek.commands = rm -f $(INSTALL_ROOT)$${LIBDIR}/libbsapi.so.4.0; \
                          rm -f $(INSTALL_ROOT)$${LIBDIR}/libbsapi.so.4.3; \
                          rm -rf $(INSTALL_ROOT)/var/upek_data; \
                          rm -f $(INSTALL_ROOT)/etc/udev/rules.d/91-fingerprint-gui-upek.rules; \
                          ldconfig

# for version 1.07 change ownership and permissions of data directories and files
user-data.commands = find /var/lib/fingerprint-gui -exec chown root:root {} +; find /var/lib/fingerprint-gui -type d -exec chmod 755 {} +; find /var/lib/fingerprint-gui -type f -exec chmod 600 {} +; rm -f $(INSTALL_ROOT)$${target.path}/fingerprint-suid

QMAKE_EXTRA_TARGETS += upek-lib upek-rules upek-cfg upek-dir upek-udevadm install-upek uninstall-upek user-data

