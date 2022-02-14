# mc500ui
This is on-going Tickingbot Matsuura project for mc500 built with Qt5. CMake build system is chosen so that it is more compatible to future Qt6 release. However, Qt6 is not widely supported everywhere at the moment so that it is not yet selected for the current progress of the project. 

## Compilation
After installing Qt and CMake, the project can be compile directly with Qt Creator or CMake command.
Instruction on setting up Qt from Ubuntu's repositories: https://wiki.qt.io/Install_Qt_5_on_Ubuntu.

If you want to have other version than default version from ubuntu repo you can download Qt Online installer and install all the packages from there. The same method is applied to Window environment.

## Packaging
Create an Release build version of the project and copy the binary to a desired folder.
I recommend using linuxdeployqt (https://github.com/probonopd/linuxdeployqt) for quickly getting all the necessary Qt package copied to your desired folder.
Instruction for using linuxdeployqt https://medium.com/swlh/how-to-deploy-your-qt-applications-to-linux-operating-system-with-linuxdeployqt-3c004a43c67a.

If the tool cannot find Qt library, you may need to add a config file (<QT.version>.config) to path "/etc/ld.so.conf.d". The file includes the path to where your Qt library is installed, for example: "/opt/Qt/5.12.2/gcc_64/lib". Then run "sudo ldconfig" to update the configuration.

#TO-DO: It is best to create an installer for the application. Qt also provides Qt Installer Framework for this purpose.

## Running
The package created in the previous step should be enough for running the application in another Ubuntu/Debian machine. If not, you may need to do some of the following steps on the target device depending on the situation:

1. sudo apt-get install '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev

For more information, see https://wiki.qt.io/Building_Qt_5_from_Git

2. export LD_LIBRARY_PATH=<path_to_Qt_library_folder>
3. export QT_PLUGIN_PATH=<path_to_Qt_plugin_folder>

## TCP connection
The application finds server IP address and port number from environment variable MC_HOSTNAME and MC_PORT. If not specified, default values are localhost (or 127.0.0.1) for host name and 2535 for port number.

