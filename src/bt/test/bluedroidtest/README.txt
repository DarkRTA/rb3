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
>dut_mode_configure 1
BT DUT MODE CONFIGURE
HAL REQUEST SUCCESS
>

Disabling Test Mode
===================
>dut_mode_configure 0
BT DUT MODE CONFIGURE
HAL REQUEST SUCCESS
>

Running BLE Test commands (Bluetooth must be enabled)
=====================================================
NOTE: Unlike BR/EDR, there is no explicit DUT mode to run these BLE tests.

> le_test_mode 1 <rx_freq>

> le_test_mode 2 <tx_freq> <test_data_len> <payload_pattern>

> le_test_mode 3 <no_args>
Please refer to the BT Core spec pages-1099 to 1102 for possible values for
the above parameters. These values need to be provided in Decimal format.

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
dut_mode_configure :: DUT mode - 1 to enter,0 to exit
le_test_mode :: LE Test Mode - RxTest - 1 <rx_freq>,
	                           TxTest - 2 <tx_freq> <test_data_len> <payload_pattern>,
	                           End Test - 3 <no_args>

