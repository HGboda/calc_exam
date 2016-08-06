#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <check.h>
#include <calc.h>

#define SUITE_NAME "Calc_UnitTest"

// char testbuf[][10] = {"XIV","LX","XX","II","II","II","D","D"};
// char resultbuf[][10] = {"LXXIV","XXII","IV","M"};
    
START_TEST (test_case1)
{
    char * retout;
    char testbuf[][10] = {"XIV","LX"};
    char *resultbuf = "LXXIV";
    retout = testcase(testbuf,resultbuf);

    fail_unless ( !strcmp(retout,resultbuf), "test case1 error!!" );
}
END_TEST

START_TEST (test_case2)
{
    char * retout;
    char testbuf[][10] = {"XX","II"};
    char *resultbuf = "XXII";
    retout = testcase(testbuf,resultbuf);

    fail_unless ( !strcmp(retout,resultbuf), "test case2 error!!" );
}
END_TEST

START_TEST (test_case3)
{
    char * retout;
    char testbuf[][10] = {"II","II"};
    char *resultbuf = "IV";
    retout = testcase(testbuf,resultbuf);

    fail_unless ( !strcmp(retout,resultbuf), "test case3 error!!" );
}
END_TEST

START_TEST (test_case4)
{
    char * retout;
    char testbuf[][10] = {"D","D"};
    char *resultbuf = "M";
    retout = testcase(testbuf,resultbuf);

    fail_unless ( !strcmp(retout,resultbuf), "test case4 error!!" );
}
END_TEST


Suite * create_suite(void) {
    Suite *s = suite_create( SUITE_NAME );

    
    TCase *tc_core = tcase_create ("Test_Create");
    tcase_add_test(tc_core, test_case1);
    tcase_add_test(tc_core, test_case2);
    tcase_add_test(tc_core, test_case3);
    tcase_add_test(tc_core, test_case4);
    suite_add_tcase(s, tc_core);

    
    return s;
}


int main( void ) {
    int num_fail;
    Suite *s = create_suite();
    SRunner *sr = srunner_create(s);
    srunner_run_all (sr, CK_NORMAL);
    num_fail = srunner_ntests_failed (sr);
    srunner_free (sr);
    return (num_fail == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}