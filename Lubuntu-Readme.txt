The lxdm developers should read the PAM documentation. Specially the "Linux PAM Application Developers Guide" located here:
http://uw714doc.sco.com/en/SEC_pam/pam_appl.html
Because of the completely improper use of PAM authentication in lxdm it's not possible to use alternative authentication methods.

If you want to use fingerprint login for Lubuntu you should install lightdm and lightdm-gtk-greeter. This will work. 
