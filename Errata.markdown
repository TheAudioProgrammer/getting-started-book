# Errata

This is a list of known mistakes and bugs in the book *The Complete Beginner's Guide to Audio Plug-in Development* and/or the accompanying source code.

## EPUB issues

Chapters 8 and 11 of the EPUB version of the book may show an error message in Apple Books and other e-readers. The text of these chapters is incomplete due to this error.

On certain e-readers (such as the Kindle app), reading in dark mode used low-contrast colors.

These issues have been fixed and an updated EPUB file is available. Please go to [your Lemon Squeezy order page](https://app.lemonsqueezy.com/my-orders) to download the latest version of the EPUB file. (The PDF version does not have these errors.)

## Chapter 6: AUAudioFilePlayer not listed in AudioPluginHost

The section *Playing audio files (Mac)* says, "Right-click inside the AudioPluginHost window again and from the pop-up choose Apple > AUAudioFilePlayer." It's possible AUAudioFilePlayer is not listed as a plug-in that you can choose.

To fix this, in AudioPluginHost go to the **Options** menu in the menu bar and select **Edit the List of Available Plug-Ins**. In the window that appears, click on **Options...** at the bottom and choose **Scan for new or updated AudioUnit plug-ins**. After a short while, AUAudioFilePlayer should appear in the list.

Additionally, you can follow the instructions from the next section, *Playing audio files (Windows)*, and use the AudioFilePlayer project to play sounds.

## Xcode error: A build only device cannot be used to run this target

You may get the following error message from Xcode:

![](Images/BuildOnlyDeviceError.png)

This happens when the run destination at the top of the Xcode window is set to **Any Mac**. When Any Mac is selected, Xcode only lets you build the project but not run it. To fix this, click on Any Mac and change this setting to **My Mac**.
