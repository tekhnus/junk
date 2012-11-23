add_library (logger Logger.cpp)
add_library (loggersettings Settings.cpp)

target_link_libraries (logger loggersettings)