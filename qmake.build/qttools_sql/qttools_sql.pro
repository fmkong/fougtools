include(../config.pri)
CONFIG *= dll
include(../../src/qttools/sql/build_qttools_sql.pri)

qttools_sql_include.path  = $$QTTOOLS_INC_PATH/qttools/sql
qttools_sql_include.files = ../../src/qttools/sql/*.h
INSTALLS += qttools_sql_include
