# rpg

rpg is a common library for the Rapid Prototyping Group

It offers simple conventions and helper libraries that have been found to be useful.

##Conventions

* All functions calls are defined to return int
	* These values indicate, and are referred to as 'status'
	* Function return either SUCCESS, or FAILED - as defined in rpg.h
	* Callers of these functions can append the macro, ENSURE_SUCCEEDED, after the call

* Return values are defined as out parameters
	* Naming convention - **out_
	* Memory is allocated in the calling function
		* If memory is allocated in the calling function, this is not an out parameter

