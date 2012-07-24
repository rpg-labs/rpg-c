#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "rpg_hash.c"


void testJsonExport(void)
{
	int ret;
	struct _rpg_hash *h;
	
	rpg_hash_init( &h );
	rpg_hash_set( h, "one", "1" );
	rpg_hash_set( h, "two", "2" );

	struct _rpg_string_list *sl;
	rpg_string_list_init(&sl);
	
	ret = rpg_hash_of_strings_to_json( h, sl );

	char *s;
	ret = rpg_string_list_to_string(sl, &s);

	CU_ASSERT_STRING_EQUAL( "{'one':'1','two':'2'}", s );

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
   if ((NULL == CU_add_test(pSuite, "test json export", testJsonExport))
       )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
