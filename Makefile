CC : = gcc CFLAGS : = -std = c11 - Wall - Wextra SRC : = src BUILD_DIR
    : = build TARGET_STRLEN : = $(BUILD_DIR) / Quest_1 TARGET_STRCMP
    : = $(BUILD_DIR) / Quest_2 TARGET_STRCPY : = $(BUILD_DIR) /
                                                 Quest_3 TARGET_STRCAT
    : = $(BUILD_DIR) / Quest_4 TARGET_STRCHR : = $(BUILD_DIR) /
                                                 Quest_5 TARGET_STRSTR
    : = $(BUILD_DIR) / Quest_6 TARGET_STRTOK
    : = $(BUILD_DIR) / Quest_7 TARGET_TEXTPROC : = $(BUILD_DIR) / Quest_8

#Add a portable mkdir helper : use mkdir - p on Unix, fallback for Windows cmd
                                                                      MKDIR
    : = mkdir - p $(BUILD_DIR) ifeq($(OS), Windows_NT) MKDIR
    : = if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)" endif

                .PHONY
    : all strlen_tests strcmp_tests strcpy_tests strcat_tests strchr_tests
          strstr_tests strtok_tests text_processor clean

              all : strlen_tests

                        strlen_tests : $(TARGET_STRLEN)

                                           strcmp_tests : $(TARGET_STRCMP)

                                                              strcpy_tests
    : $(TARGET_STRCPY)

          strcat_tests : $(TARGET_STRCAT)

                             strchr_tests : $(TARGET_STRCHR)

                                                strstr_tests : $(TARGET_STRSTR)

                                                                   strtok_tests
    : $(TARGET_STRTOK)

          text_processor : $(TARGET_TEXTPROC)

                               $(TARGET_STRLEN)
    : $(SRC) /
            s21_string.c $(SRC) / s21_string_test.c $(SRC) /
            s21_string.h @$(MKDIR) $(CC) $(CFLAGS) $(SRC) /
            s21_string.c $(SRC) / s21_string_test.c -
        I$(SRC) -
        o $(TARGET_STRLEN)

                $(TARGET_STRCMP)
    : $(SRC) / s21_string.c $(SRC) / s21_string_test.c $(SRC) /
      s21_string.h @$(MKDIR) $(CC) $(CFLAGS) $(SRC) / s21_string.c $(SRC) /
      s21_string_test.c -
        I$(SRC) -
        o $(TARGET_STRCMP)

                $(TARGET_STRCPY)
    : $(SRC) / s21_string.c $(SRC) / s21_string_test.c $(SRC) /
      s21_string.h @$(MKDIR) $(CC) $(CFLAGS) $(SRC) / s21_string.c $(SRC) /
      s21_string_test.c -
        I$(SRC) -
        o $(TARGET_STRCPY)

                $(TARGET_STRCAT)
    : $(SRC) / s21_string.c $(SRC) / s21_string_test.c $(SRC) /
      s21_string.h @$(MKDIR) $(CC) $(CFLAGS) $(SRC) / s21_string.c $(SRC) /
      s21_string_test.c -
        I$(SRC) -
        o $(TARGET_STRCAT)

                $(TARGET_STRCHR)
    : $(SRC) / s21_string.c $(SRC) / s21_string_test.c $(SRC) /
      s21_string.h @$(MKDIR) $(CC) $(CFLAGS) $(SRC) / s21_string.c $(SRC) /
      s21_string_test.c -
        I$(SRC) -
        o $(TARGET_STRCHR)

                $(TARGET_STRSTR)
    : $(SRC) / s21_string.c $(SRC) / s21_string_test.c $(SRC) /
      s21_string.h @$(MKDIR) $(CC) $(CFLAGS) $(SRC) / s21_string.c $(SRC) /
      s21_string_test.c -
        I$(SRC) -
        o $(TARGET_STRSTR)

                $(TARGET_STRTOK)
    : $(SRC) / s21_string.c $(SRC) / s21_string_test.c $(SRC) /
      s21_string.h @$(MKDIR) $(CC) $(CFLAGS) $(SRC) / s21_string.c $(SRC) /
      s21_string_test.c -
        I$(SRC) -
        o $(TARGET_STRTOK)

                $(TARGET_TEXTPROC)
    : $(SRC) / text_processor.c @$(MKDIR) $(CC) $(CFLAGS) $(SRC) /
      text_processor.c -
        I$(SRC) -
        o $(TARGET_TEXTPROC)

            clean : -rm -
                    rf $(BUILD_DIR)
