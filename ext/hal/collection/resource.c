
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/operators.h"


/**
 * This file is part of the Hal library
 *
 * (c) Ben Longden <ben@nocarrier.co.uk
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 *
 * @package Nocarrier
 */
/**
 * Hal\Collection\Resource
 * Provides storage of arrays of Hal\Resource objects
 *
 * @package Hal
 * @author Brandon Lamb <brandon@brandonlamb.com>
 */
ZEPHIR_INIT_CLASS(Hal_Collection_Resource) {

	ZEPHIR_REGISTER_CLASS(Hal\\Collection, Resource, hal, collection_resource, hal_collection_resource_method_entry, 0);

/**
     * @var array
     */
	zend_declare_property_null(hal_collection_resource_ce, SL("data"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(hal_collection_resource_ce TSRMLS_CC, 1, spl_ce_Countable);

	return SUCCESS;

}

/**
 * Constructor
 * @param array data
 */
PHP_METHOD(Hal_Collection_Resource, __construct) {

	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("data"), _0 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Return the array of links
 * @return array
 */
PHP_METHOD(Hal_Collection_Resource, getData) {


	RETURN_MEMBER(this_ptr, "data");

}

/**
 * Retrieve a collection of resources by rel.
 *
 * @param string rel The resource relation required
 * @return array|bool Array of resources if found, otherwise false
 */
PHP_METHOD(Hal_Collection_Resource, get) {

	zval *rel_param = NULL, *resources, *_0;
	zval *rel = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &rel_param);

		zephir_get_strval(rel, rel_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("data"), PH_NOISY_CC);
	if (zephir_array_isset_fetch(&resources, _0, rel, 1 TSRMLS_CC)) {
		RETURN_CTOR(resources);
	}
	RETURN_MM_BOOL(0);

}

/**
 * Add a resource to the collection of resources
 *
 * @param string rel
 * @param Hal\Resource resource
 * @param bool multi
 */
PHP_METHOD(Hal_Collection_Resource, add) {

	zend_bool multi;
	zval *rel_param = NULL, *resource, *multi_param = NULL, *value, *_0, *_1;
	zval *rel = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &rel_param, &resource, &multi_param);

		zephir_get_strval(rel, rel_param);
	if (!multi_param || Z_TYPE_P(multi_param) == IS_NULL) {
		multi = 1;
	} else {
		multi = zephir_get_boolval(multi_param);
	}


	ZEPHIR_OBS_VAR(value);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("data"), PH_NOISY_CC);
	if (((multi == 1) && zephir_array_isset_fetch(&value, _0, rel, 0 TSRMLS_CC))) {
		zephir_array_append(&value, resource, PH_SEPARATE);
		zephir_update_property_array(this_ptr, SL("data"), rel, value TSRMLS_CC);
	} else {
		if ((multi == 1)) {
			ZEPHIR_INIT_VAR(_1);
			array_init(_1);
			zephir_array_fast_append(_1, resource);
			zephir_update_property_array(this_ptr, SL("data"), rel, _1 TSRMLS_CC);
		} else {
			zephir_update_property_array(this_ptr, SL("data"), rel, resource TSRMLS_CC);
		}
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns the number of annotations in the collection
 *
 * @return int
 */
PHP_METHOD(Hal_Collection_Resource, count) {

	zval *_0;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("data"), PH_NOISY_CC);
	RETURN_LONG(zephir_fast_count_int(_0 TSRMLS_CC));

}

