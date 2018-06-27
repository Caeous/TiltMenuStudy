# Tilt-menu Study

Users would benefit from one-handed menu interactions with a wrist-worn computer. This prototype allows to study this interaction via two model variants (four-zone and two-zone). At the end of the trials, a Likert 7-point scale is presented to the user to rate the performance of the model variant.

## Study Instructions
1. At the start of the study, please enter the desired Id for the participant. Any string values are allowed.
2. Explain to the user that the goal is to select the menu option displayed at the top.
3. Explain that there are two model variants to test.
4. Note that the user has to press on the screen to navigate.
5. Inform the user that a 7-point Likert scale will be presented once 8 menu options have been selected.
6. Each model variant trial will have a JSON file created in the Documents directory. i.e. "<USER>/Documents/TiltMenu/"
7. Once each model variant has been shown, the initial screen will be shown allowing for another unique Id to be entered, or to continue with the same Id for another trial attempt.

## Build Instructions
1. Clone this repository
2. Download and install the lastest version of Android studio (https://developer.android.com/studio/index.html).
3. Ensure the latest Android SDK is downloaded during installation.
4. Download and uncompress the Android NDK r10e on your computer.
5. Download and install the Java SE 1.8.0.
6. Download and install Qt 5.10.1 with Qt Creator.
7. The Qt Creator IDE that came with the Qt 5 installation on your development host, must be configured to enable developing applications for Android. Launch Qt Creator and select Tools > Options > Devices > Android to add the Android NDK and SDK paths.
8. Build the project against the Android ABI.
9. Deploy the project to the connected Android device.
