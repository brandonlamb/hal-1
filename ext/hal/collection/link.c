
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
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/string.h"
#include "kernel/concat.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"


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
 * Hal\Collection\Link
 * Provides storage of arrays of Hal\Link objects
 *
 * @package Hal
 * @author Ben Longden <ben@nocarrier.co.uk>
 * @author Brandon Lamb <brandon@brandonlamb.com>
 */
ZEPHIR_INIT_CLASS(Hal_Collection_Link) {

	ZEPHIR_REGISTER_CLASS(Hal\\Collection, Link, hal, collection_link, hal_collection_link_method_entry, 0);

/**
     * @var array
     */
	zend_declare_property_null(hal_collection_link_ce, SL("data"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(hal_collection_link_ce TSRMLS_CC, 1, spl_ce_Countable);

	return SUCCESS;

}

/**
 * Constructor
 * @param array data
 */
PHP_METHOD(Hal_Collection_Link, __construct) {

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
PHP_METHOD(Hal_Collection_Link, getData) {


	RETURN_MEMBER(this_ptr, "data");

}

/**
 * Retrieve a link from the container by rel. Also resolve any curie links if they are set.
 *
 * @param string rel The link relation required
 * @return array|bool Link if found, therwise false
 */
PHP_METHOD(Hal_Collection_Link, get) {

	zend_function *_8 = NULL, *_11 = NULL;
	HashTable *_5;
	HashPosition _4;
	zval *rel_param = NULL, *prefix = NULL, *link = NULL, *shortRel = NULL, *attrs = NULL, *curie = NULL, *_0, *_1, *_2, *_3, **_6, *_7 = NULL, _9 = zval_used_for_init, *_10 = NULL, *_12, *_13, *_14, *_15;
	zval *rel = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &rel_param);

		if (Z_TYPE_P(rel_param) != IS_STRING) {
				zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'rel' must be a string") TSRMLS_CC);
				RETURN_MM_NULL();
		}

		rel = rel_param;



	ZEPHIR_OBS_VAR(link);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("data"), PH_NOISY_CC);
	if (zephir_array_isset_fetch(&link, _0, rel, 0 TSRMLS_CC)) {
		RETURN_CCTOR(link);
	}
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("data"), PH_NOISY_CC);
	if (zephir_array_isset_string(_1, SS("curies"))) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("data"), PH_NOISY_CC);
		zephir_array_fetch_string(&_3, _2, SL("curies"), PH_NOISY | PH_READONLY TSRMLS_CC);
		zephir_is_iterable(_3, &_5, &_4, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_5, (void**) &_6, &_4) == SUCCESS
			; zend_hash_move_forward_ex(_5, &_4)
		) {
			ZEPHIR_GET_HVALUE(link, _6);
			ZEPHIR_INIT_NVAR(_7);
			zephir_call_method_cache(_7, link, "geturi", &_8);
			ZEPHIR_SINIT_NVAR(_9);
			ZVAL_STRING(&_9, "{rel}", 0);
			ZEPHIR_INIT_NVAR(prefix);
			zephir_call_func_p3(prefix, "strstr", _7, &_9, ZEPHIR_GLOBAL(global_true));
			ZEPHIR_INIT_NVAR(_10);
			zephir_call_func_p2(_10, "strpos", rel, prefix);
			if (ZEPHIR_IS_LONG(_10, 0)) {
				ZEPHIR_SINIT_NVAR(_9);
				ZVAL_LONG(&_9, zephir_fast_strlen_ev(prefix));
				ZEPHIR_INIT_NVAR(shortRel);
				zephir_call_func_p2(shortRel, "substr", rel, &_9);
				ZEPHIR_INIT_NVAR(attrs);
				zephir_call_method_cache(attrs, link, "getattributes", &_11);
				if (zephir_array_isset_string(attrs, SS("name"))) {
					zephir_array_fetch_string(&_12, attrs, SL("name"), PH_NOISY | PH_READONLY TSRMLS_CC);
					ZEPHIR_INIT_NVAR(curie);
					ZEPHIR_CONCAT_VSV(curie, _12, ":", shortRel);
					_13 = zephir_fetch_nproperty_this(this_ptr, SL("data"), PH_NOISY_CC);
					if (zephir_array_isset(_13, curie)) {
						_14 = zephir_fetch_nproperty_this(this_ptr, SL("data"), PH_NOISY_CC);
						zephir_array_fetch(&_15, _14, curie, PH_NOISY | PH_READONLY TSRMLS_CC);
						RETURN_CTOR(_15);
					}
				}
			}
		}
	}
	RETURN_MM_BOOL(0);

}

/**
 * Add a value to an offset
 *
 * @param string rel
 * @param Hal\Link link
 */
PHP_METHOD(Hal_Collection_Link, add) {

	zval *rel_param = NULL, *link, *value, *_0, *_1;
	zval *rel = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &rel_param, &link);

		if (Z_TYPE_P(rel_param) != IS_STRING) {
				zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'rel' must be a string") TSRMLS_CC);
				RETURN_MM_NULL();
		}

		rel = rel_param;



	ZEPHIR_OBS_VAR(value);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("data"), PH_NOISY_CC);
	if (zephir_array_isset_fetch(&value, _0, rel, 0 TSRMLS_CC)) {
		zephir_array_append(&value, link, PH_SEPARATE);
		zephir_update_property_array(this_ptr, SL("data"), rel, value TSRMLS_CC);
	} else {
		ZEPHIR_INIT_VAR(_1);
		array_init(_1);
		zephir_array_fast_append(_1, link);
		zephir_update_property_array(this_ptr, SL("data"), rel, _1 TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns the number of annotations in the collection
 *
 * @return int
 */
PHP_METHOD(Hal_Collection_Link, count) {

	zval *_0;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("data"), PH_NOISY_CC);
	RETURN_LONG(zephir_fast_count_int(_0 TSRMLS_CC));

}

