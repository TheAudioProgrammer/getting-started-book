# Errata

This is a list of known mistakes and bugs in the book *The Complete Beginner's Guide to Audio Plug-in Development* and/or the accompanying source code.

## Xcode error: A build only device cannot be used to run this target

You may get the following error message from Xcode:

![](Images/BuildOnlyDeviceError.png)

This happens when the run destination at the top of the Xcode window is set to **Any Mac**. When Any Mac is selected, Xcode only lets you build the project but not run it. To fix this, click on Any Mac and change this setting to **My Mac**.
