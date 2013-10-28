
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include "php_ext.h"
#include "hal.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/memory.h"

zend_class_entry *hal_renderinterface_ce;
zend_class_entry *hal_collection_link_ce;
zend_class_entry *hal_collection_resource_ce;
zend_class_entry *hal_link_ce;
zend_class_entry *hal_render_json_ce;
zend_class_entry *hal_render_xml_ce;
zend_class_entry *hal_resource_ce;
zend_class_entry *hal_resourcefactory_ce;

ZEND_DECLARE_MODULE_GLOBALS(hal)

PHP_MINIT_FUNCTION(hal){

	ZEPHIR_INIT(Hal_RenderInterface);
	ZEPHIR_INIT(Hal_Collection_Link);
	ZEPHIR_INIT(Hal_Collection_Resource);
	ZEPHIR_INIT(Hal_Link);
	ZEPHIR_INIT(Hal_Render_Json);
	ZEPHIR_INIT(Hal_Render_Xml);
	ZEPHIR_INIT(Hal_Resource);
	ZEPHIR_INIT(Hal_ResourceFactory);
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(hal){

	assert(ZEPHIR_GLOBAL(function_cache) == NULL);
	//assert(ZEPHIR_GLOBAL(orm).parser_cache == NULL);
	//assert(ZEPHIR_GLOBAL(orm).ast_cache == NULL);

	return SUCCESS;
}
#endif

static PHP_RINIT_FUNCTION(hal){

	php_zephir_init_globals(ZEPHIR_VGLOBAL TSRMLS_CC);
	//hal_init_interned_strings(TSRMLS_C);

	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(hal){

	if (ZEPHIR_GLOBAL(start_memory) != NULL) {
		zephir_clean_restore_stack(TSRMLS_C);
	}

	if (ZEPHIR_GLOBAL(function_cache) != NULL) {
		zend_hash_destroy(ZEPHIR_GLOBAL(function_cache));
		FREE_HASHTABLE(ZEPHIR_GLOBAL(function_cache));
		ZEPHIR_GLOBAL(function_cache) = NULL;
	}

	return SUCCESS;
}

static PHP_MINFO_FUNCTION(hal)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "Version", PHP_HAL_VERSION);
	php_info_print_table_end();
}

static PHP_GINIT_FUNCTION(hal)
{
	zephir_memory_entry *start;

	php_zephir_init_globals(hal_globals TSRMLS_CC);

	/* Start Memory Frame */
	start = (zephir_memory_entry *) pecalloc(1, sizeof(zephir_memory_entry), 1);
	start->addresses       = pecalloc(24, sizeof(zval*), 1);
	start->capacity        = 24;
	start->hash_addresses  = pecalloc(8, sizeof(zval*), 1);
	start->hash_capacity   = 8;

	hal_globals->start_memory = start;

	/* Global Constants */
	ALLOC_PERMANENT_ZVAL(hal_globals->global_false);
	INIT_PZVAL(hal_globals->global_false);
	ZVAL_FALSE(hal_globals->global_false);
	Z_ADDREF_P(hal_globals->global_false);

	ALLOC_PERMANENT_ZVAL(hal_globals->global_true);
	INIT_PZVAL(hal_globals->global_true);
	ZVAL_TRUE(hal_globals->global_true);
	Z_ADDREF_P(hal_globals->global_true);

	ALLOC_PERMANENT_ZVAL(hal_globals->global_null);
	INIT_PZVAL(hal_globals->global_null);
	ZVAL_NULL(hal_globals->global_null);
	Z_ADDREF_P(hal_globals->global_null);
}

static PHP_GSHUTDOWN_FUNCTION(hal)
{
	assert(hal_globals->start_memory != NULL);

	pefree(hal_globals->start_memory->hash_addresses, 1);
	pefree(hal_globals->start_memory->addresses, 1);
	pefree(hal_globals->start_memory, 1);
	hal_globals->start_memory = NULL;
}

zend_module_entry hal_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	NULL,
	PHP_HAL_EXTNAME,
	NULL,
	PHP_MINIT(hal),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(hal),
#else
	NULL,
#endif
	PHP_RINIT(hal),
	PHP_RSHUTDOWN(hal),
	PHP_MINFO(hal),
	PHP_HAL_VERSION,
	ZEND_MODULE_GLOBALS(hal),
	PHP_GINIT(hal),
	PHP_GSHUTDOWN(hal),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_HAL
ZEND_GET_MODULE(hal)
#endif
