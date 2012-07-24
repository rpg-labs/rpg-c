#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "rpg_csv_to_list.c"


void testTwoValues(void)
{
	int ret;
	struct _rpg_string_list *l=NULL;
	char *line = "one,two";

	ret = rpg_csv_to_list_run( line, &l );

	CU_ASSERT(2 == l->count);
}

void testThreeValues(void)
{
	int ret;
	struct _rpg_string_list *l=NULL;
	char *line = "one,two,three";

	ret = rpg_csv_to_list_run( line, &l );

	CU_ASSERT(3 == l->count);
}


void testThreeValuesGetFirstValue(void)
{
	int ret;
	struct _rpg_string_list *l=NULL;
	char *line = "one,two,three";

	ret = rpg_csv_to_list_run( line, &l );
	CU_ASSERT(3 == l->count);
	
	{
		char *v=NULL;
		ret = rpg_string_list_get( l, 1, &v );
		CU_ASSERT_STRING_EQUAL("one",v);
	}
}


void testThreeValuesGetSecondValue(void)
{
	int ret;
	struct _rpg_string_list *l=NULL;
	char *line = "one,two,three";

	ret = rpg_csv_to_list_run( line, &l );
	CU_ASSERT(3 == l->count);
	
	{
		char *v=NULL;
		ret = rpg_string_list_get( l, 2, &v );
		CU_ASSERT_STRING_EQUAL("two",v);
	}
}


void testThreeValuesGetThirdValue(void)
{
	int ret;
	struct _rpg_string_list *l=NULL;
	char *line = "one,two,three";

	ret = rpg_csv_to_list_run( line, &l );
	CU_ASSERT(3 == l->count);
	
	{
		char *v=NULL;
		ret = rpg_string_list_get( l, 3, &v );
		CU_ASSERT_STRING_EQUAL("three",v);
	}
}


void testThreeValuesGetFourthValue(void)
{
	int ret;
	struct _rpg_string_list *l=NULL;
	char *line = "one,two,three";

	ret = rpg_csv_to_list_run( line, &l );
	CU_ASSERT(3 == l->count);

	{
		char *v=NULL;
		ret = rpg_string_list_get( l, 4, &v );
		CU_ASSERT_PTR_NULL(v);

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

   pSuite = CU_add_suite("Suite_RPG_CSV_TO_LIST", NULL, NULL);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }


   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if ((NULL == CU_add_test(pSuite, "test two values", testTwoValues)) ||
       (NULL == CU_add_test(pSuite, "test three values", testThreeValues)) ||
       (NULL == CU_add_test(pSuite, "test three values, get first", testThreeValuesGetFirstValue)) ||
       (NULL == CU_add_test(pSuite, "test three values, get second", testThreeValuesGetSecondValue)) ||
       (NULL == CU_add_test(pSuite, "test three values, get third", testThreeValuesGetThirdValue)) ||
       (NULL == CU_add_test(pSuite, "test three values, get fourth", testThreeValuesGetFourthValue))
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
