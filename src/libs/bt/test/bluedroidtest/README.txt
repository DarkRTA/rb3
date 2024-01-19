Bluedroid Test Application
==========================
The test application provides a small console shell interface that allows
access to the Bluetooth HAL API library though ASCII commands. This is similar
to how the real JNI service would operate. The primary objective of this
application is to allow Bluetooth to be put in DUT Mode for RF/BB BQB test purposes.

This application is mutually exclusive with the Java based Bluetooth.apk. Hence
before launching the application, it should be ensured that the Settings->Bluetooth is OFF.

This application is built as 'bdt' and shall be available in '/system/bin/bdt'

Limitations
===========
1.) Settings->Bluetooth must be OFF for this application to work
2.) Currently, only the SIG 'HCI Test Mode' commands are supported. The vendor
specific HCI test mode commands to be added.

Usage instructions
==================
The following section describes the various commands and their usage

Launching the test application
==============================
$ adb shell
root@android:/ # /system/bin/bdt
set_aid_and_cap : pid 1183, uid 0 gid 0
:::::::::::::::::::::::::::::::::::::::::::::::::::
:: Bluedroid test app starting
Loading HAL lib + extensions
HAL library loaded (Success)
INIT BT
HAL REQUEST SUCCESS

Enabling Bluetooth
==================
>enable
ENABLE BT
HAL REQUEST SUCCESS
>ADAPTER STATE UPDATED : ON

Enabling Test Mode (Bluetooth must be enabled for this command to work)
======================================================================
>enable_test_mode
ENABLE BT TEST MODE
HAL REQUEST SUCCESS
>

Disabling Test Mode
===================
>disable_test_mode
DISABLE BT TEST MODE
HAL REQUEST SUCCESS

Exit the test application
=========================
>quit
shutdown bdroid test app
Unloading HAL lib
HAL library unloaded (Success)
:: Bluedroid test app terminating

Help (Lists the available commands)
===================================
>help
help lists all available console commands

quit
enable :: enables bluetooth
disable :: disables bluetooth
enable_test_mode :: enters bluedroid test mode
disable_test_mode :: exits bluedroid test mode

