SRC_LIBJSONCPP_SRC = \
    $(top_srcdir)/lib/jsoncpp/src/lib_json/json_reader.cpp \
    $(top_srcdir)/lib/jsoncpp/src/lib_json/json_writer.cpp \
    $(top_srcdir)/lib/jsoncpp/src/lib_json/json_value.cpp

SRC_LIBSONCPP_INCLUDE = \
    -I$(top_srcdir)/lib/jsoncpp/include \
    -I$(top_srcdir)/lib/jsoncpp/src/lib_json
    