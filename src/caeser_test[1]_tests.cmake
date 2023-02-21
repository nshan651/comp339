add_test([=[CaeserTest.Encoder]=]  /home/nick/git/comp339/bin/caeser_test [==[--gtest_filter=CaeserTest.Encoder]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CaeserTest.Encoder]=]  PROPERTIES WORKING_DIRECTORY /home/nick/git/comp339/src SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  caeser_test_TESTS CaeserTest.Encoder)
