add_test([=[CaeserTest.Full]=]  /home/nick/git/comp339/caeser-cipher/bin/caeser_test [==[--gtest_filter=CaeserTest.Full]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CaeserTest.Full]=]  PROPERTIES WORKING_DIRECTORY /home/nick/git/comp339/caeser-cipher/src SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  caeser_test_TESTS CaeserTest.Full)
