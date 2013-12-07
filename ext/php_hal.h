

#ifndef PHP_HAL_H
#define PHP_HAL_H 1

#include "kernel/globals.h"

#define PHP_HAL_VERSION "0.0.1"
#define PHP_HAL_EXTNAME "hal"



ZEND_BEGIN_MODULE_GLOBALS(hal)

	/* Memory */
	zephir_memory_entry *start_memory;
	zephir_memory_entry *active_memory;

	/* Virtual Symbol Tables */
	zephir_symbol_table *active_symbol_table;

	/* Function cache */
	HashTable *function_cache;

	/* Max recursion control */
	unsigned int recursive_lock;

	/* Global constants */
	zval *global_true;
	zval *global_false;
	zval *global_null;
	
ZEND_END_MODULE_GLOBALS(hal)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(hal)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) TSRMG(hal_globals_id, zend_hal_globals *, v)
#else
	#define ZEPHIR_GLOBAL(v) (hal_globals.v)
#endif

#ifdef ZTS
	#define ZEPHIR_VGLOBAL ((zend_hal_globals *) (*((void ***) tsrm_ls))[TSRM_UNSHUFFLE_RSRC_ID(hal_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(hal_globals)
#endif

#define zephir_globals hal_globals
#define zend_zephir_globals zend_hal_globals

extern zend_module_entry hal_module_entry;
#define phpext_hal_ptr &hal_module_entry

#endif
