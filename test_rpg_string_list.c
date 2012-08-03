#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "rpg_string_list.c"


apr_pool_t *p;

void testRpgStringListToString(void)
{
	int ret;

	struct _rpg_string_list *sl;
	ret = rpg_string_list_init(p,&sl);
	ret = rpg_string_list_add(p,sl, "one" );
	ret = rpg_string_list_add(p,sl, "two" );
	
	char *s;
	ret = rpg_string_list_to_string( p, sl, &s );

	CU_ASSERT_STRING_EQUAL( "onetwo", s );

}

void testRpgStringListRemoveLast(void)
{
	int ret;
    
	struct _rpg_string_list *sl;
	ret = rpg_string_list_init(p,&sl);
	ret = rpg_string_list_add(p,sl, "one" );
	ret = rpg_string_list_add(p,sl, "two" );
	ret = rpg_string_list_add(p,sl, "three" );
	
    {
        char *s;
        ret = rpg_string_list_to_string( p, sl, &s );
        CU_ASSERT_STRING_EQUAL( "onetwothree", s );
    }

    ret = rpg_string_list_remove_last(p,sl );
    {
        char *s;
        ret = rpg_string_list_to_string( p, sl, &s );
        CU_ASSERT_STRING_EQUAL( "onetwo", s );
    }

}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */

   pSuite = CU_add_suite("Suite_RPG_HASH", NULL, NULL);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }


   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if ((NULL == CU_add_test(pSuite, "test string list to string", testRpgStringListToString)) ||
       (NULL == CU_add_test(pSuite, "test string list remove last", testRpgStringListRemoveLast))
       )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

	apr_initialize();
	if(( apr_pool_create( &p, NULL)) != APR_SUCCESS) {
		printf( "Could not create memory sub-pool\n");
		exit( -1);
	}

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
