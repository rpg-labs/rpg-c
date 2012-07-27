#ifndef RPG_CUNIT
#define RPG_CUNIT

#define RPG_CU_ENSURE_SUCCEEDED CU_ASSERT_TRUE_FATAL ( ret == SUCCESS );
#define RPG_CU_FNC_CHECK RPG_CU_ENSURE_SUCCEEDED;
#define RPG_CU_FNC_A_PTR_CHECK(p) RPG_CU_ENSURE_SUCCEEDED; CU_ASSERT_PTR_NOT_NULL_FATAL(p);

#include "CUnit/Basic.h"

#endif
