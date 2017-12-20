XSLT := xsltproc --param man.charmap.use.subset "0" \
	--param make.year.ranges "1" \
	--param make.single.year.ranges "1"
STYLESHEET := /usr/share/xml/docbook/stylesheet/nwalsh/manpages/docbook.xsl
XMLLINT    := xmllint --valid --noout
MANPAGES   := fingerprint-gui.1 fingerprint-identifier.1 pam_fingerprint-gui.8

all: $(MANPAGES)
fingerprint-gui.1: src/fingerprint-gui.xml
	$(XSLT) $(STYLESHEET) $<
fingerprint-identifier.1: src/fingerprint-identifier.xml
	$(XSLT) $(STYLESHEET) $<
pam_fingerprint-gui.8: src/pam_fingerprint-gui.xml
	$(XSLT) $(STYLESHEET) $<
clean:
	rm $(MANPAGES)
valid:
	$(XMLLINT) src/*.xml
.PHONY: all clean valid
