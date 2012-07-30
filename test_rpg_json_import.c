#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rpg_cunit.h"

#include "rpg_string_list.c"
#include "rpg_hash.c"
#include "rpg_json_import.c"


void test_find_index_of_char(void)
{
	int ret;
	struct _rpg_hash *h;
	
	int i;
	char *s = "  A  B  C  D  E  F  G";

	i=0;
	ret = chrpos( s, strlen( s ), 'A', &i );RPG_CU_FNC_CHECK
	CU_ASSERT_EQUAL( 2, i );

	i=3;
	ret = chrpos( s, strlen( s ), 'B', &i );RPG_CU_FNC_CHECK
	CU_ASSERT_TRUE( i == 5 );

	i=0;
	ret = chrpos( s, strlen( s ), 'B', &i );RPG_CU_FNC_CHECK
	CU_ASSERT_TRUE( i == -1 );

	i=0;
	ret = chrpos( s, strlen( s ), 'H', &i );RPG_CU_FNC_CHECK
	CU_ASSERT_TRUE( i == -1 );
}

int test_find_index_of_starting_points_mrv() { //mask_return_value
	int ret;
	char *s = " {\"hid\":\"198\",\"name\":\"Mangatewai\",\"psm\":\"16 Oct 2012\",\"psc\":\"25 Jul 2012\",\"mapref\":\"\"}";
	int i;

	i=0;
	ATTRIBUTE_LIST(s,strlen(s),i);RPG_CU_FNC_CHECK
	CU_ASSERT_EQUAL( 2, i );

	i=3;
	ATTRIBUTE_LIST(s,strlen(s),i);RPG_CU_FNC_CHECK
	CU_ASSERT_EQUAL( -1, i );

	i=2;
	START_OF_ATTR(s,strlen(s),i);RPG_CU_FNC_CHECK
	CU_ASSERT_EQUAL( 3, i );

	i=0;
	START_OF_ATTR(s,strlen(s),i);RPG_CU_FNC_CHECK
	CU_ASSERT_EQUAL( -1, i );

	return SUCCESS;
}

void test_find_index_of_starting_points(void)
{
	int ret = test_find_index_of_starting_points_mrv();
	CU_ASSERT_EQUAL( SUCCESS, ret );
}

int test_find_index_of_attibutes_mrv() { //mask_return_value
	int ret;
	char *s = " {\"hid\":\"198\",\"name\":\"Mangatewai\",\"psm\":\"16 Oct 2012\",\"psc\":\"25 Jul 2012\",\"mapref\":\"\"}";
	int i;

	i=3;
	END_OF_NAME(s,strlen(s),i);RPG_CU_FNC_CHECK
	CU_ASSERT_EQUAL( 5, i );

	i=9;
	END_OF_VALUE(s,strlen(s),i);RPG_CU_FNC_CHECK
	CU_ASSERT_EQUAL( 11, i );

	return SUCCESS;
}

void test_find_index_of_attibutes(void)
{
	int ret = test_find_index_of_attibutes_mrv();
	CU_ASSERT_EQUAL( SUCCESS, ret );
}


int test_read_attibute_to_hash_mrv() { //mask_return_value
	int ret;
	char *s = " {\"hid\":\"198\",\"name\":\"Mangatewai\",\"psm\":\"16 Oct 2012\",\"psc\":\"25 Jul 2012\",\"mapref\":\"\"}";
	int i;
	struct _rpg_hash *r;

	RPG_HASH_INIT(r);

	i=3;
	READ_ATTR_TO_HASH(s,strlen(s),i,r);
	CU_ASSERT_NOT_EQUAL_FATAL( -1, i );
	{
		void *data;
		RPG_HASH_GET(r,"hid",data);
		char *value = (char *)data;
		CU_ASSERT_STRING_EQUAL( "198", value );
		
	}
	CU_ASSERT_EQUAL( 13, i );

	i=15;
	READ_ATTR_TO_HASH(s,strlen(s),i,r);
	CU_ASSERT_NOT_EQUAL_FATAL( -1, i );
	{
		void *data;
		RPG_HASH_GET(r,"name",data);RPG_CU_FNC_A_PTR_CHECK( data );
		char *value = (char *)data;
		CU_ASSERT_STRING_EQUAL( "Mangatewai", value );
		
	}
	CU_ASSERT_EQUAL( 33, i );

	return SUCCESS;
}

void test_read_attibute_to_hash(void)
{
	int ret = test_read_attibute_to_hash_mrv();
	CU_ASSERT_EQUAL( SUCCESS, ret );
}


int test_read_null_attibute_to_hash_mrv() { //mask_return_value
	int ret;
	char *s = " {\"hid\":null,\"name\":\"Mangatewai\"}";
	int i;
	struct _rpg_hash *r;

	RPG_HASH_INIT(r);

	i=3;
	READ_ATTR_TO_HASH(s,strlen(s),i,r);
	CU_ASSERT_NOT_EQUAL_FATAL( -1, i );
	{
		void *data;
//		RPG_HASH_GET(r,"hid",data);
//		CU_ASSERT_EQUAL_FATAL( NULL, data );

	}
	CU_ASSERT_EQUAL( 12, i );

	i=14;
	READ_ATTR_TO_HASH(s,strlen(s),i,r);
	CU_ASSERT_NOT_EQUAL_FATAL( -1, i );
	{
		void *data;
		RPG_HASH_GET(r,"name",data);RPG_CU_FNC_A_PTR_CHECK( data );
		char *value = (char *)data;
		CU_ASSERT_STRING_EQUAL( "Mangatewai", value );

	}
	CU_ASSERT_EQUAL( 32, i );

	return SUCCESS;
}

void test_read_null_attibute_to_hash(void)
{
	int ret = test_read_null_attibute_to_hash_mrv();
	CU_ASSERT_EQUAL( SUCCESS, ret );
}

void test_json_import(void)
{
	int ret;
	struct _rpg_hash *r;
	

	char *s = "{\"hid\":\"198\",\"name\":\"Mangatewai\",\"psm\":\"16 Oct 2012\",\"psc\":\"25 Jul 2012\",\"mapref\":\"\"}";

	ret = rpg_json_import( s, &r );RPG_CU_FNC_A_PTR_CHECK(r);

	{
		void *data;
		ret = rpg_hash_get(r,"hid",&data);RPG_CU_FNC_A_PTR_CHECK(data)
		CU_ASSERT_STRING_EQUAL( "198", (char *)data );
	}

	{
		void *data;
		ret = rpg_hash_get(r,"name",&data);RPG_CU_FNC_A_PTR_CHECK(data)
		CU_ASSERT_STRING_EQUAL( "Mangatewai", (char *)data );
	}

	{
		void *data;
		ret = rpg_hash_get(r,"psm",&data);RPG_CU_FNC_A_PTR_CHECK(data)
		CU_ASSERT_STRING_EQUAL( "16 Oct 2012", (char *)data );
	}

	{
		void *data;
		ret = rpg_hash_get(r,"psc",&data);RPG_CU_FNC_A_PTR_CHECK(data)
		CU_ASSERT_STRING_EQUAL( "25 Jul 2012", (char *)data );
	}

	{
		void *data;
		ret = rpg_hash_get(r,"mapref",&data);RPG_CU_FNC_A_PTR_CHECK(data)
		CU_ASSERT_STRING_EQUAL( "", (char *)data );
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

   pSuite = CU_add_suite("Suite_RPG_JSON_IMPORT", NULL, NULL);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if ( 
   		//(NULL == CU_add_test(pSuite, "test json import", testJsonImport)) ||
   		(NULL == CU_add_test(pSuite, "test_find_index_of_starting_points", test_find_index_of_starting_points)) ||
   		(NULL == CU_add_test(pSuite, "test_find_index_of_starting_points", test_find_index_of_attibutes)) ||
   		(NULL == CU_add_test(pSuite, "test_read_attibute_to_hash", test_read_attibute_to_hash)) ||
   		(NULL == CU_add_test(pSuite, "test_find_index_of_char", test_find_index_of_char)) ||
   		(NULL == CU_add_test(pSuite, "test_json_import", test_json_import)) ||
   		(NULL == CU_add_test(pSuite, "test_read_null_attibute_to_hash", test_read_null_attibute_to_hash))
   		

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
