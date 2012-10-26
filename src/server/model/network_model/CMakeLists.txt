add_library (servernetworkmodel ServerNetworkModel.cpp)

target_link_libraries (servernetworkmodel thriftnb event thrift_c_glib)