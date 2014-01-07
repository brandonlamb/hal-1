
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/array.h"
#include "kernel/hash.h"
#include "kernel/operators.h"


/**
 * This file is part of the Hal library
 *
 * (c) Ben Longden <ben@nocarrier.co.uk
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 *
 * @package Hal
 */
/**
 * Hal\Resource
 * The Hal resource document class
 *
 * @package Hal
 * @author Ben Longden <ben@nocarrier.co.uk>
 * @author Brandon Lamb <brandon@brandonlamb.com>
 */
ZEPHIR_INIT_CLASS(Hal_ResourceFactory) {

	ZEPHIR_REGISTER_CLASS(Hal, ResourceFactory, hal, resourcefactory, hal_resourcefactory_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);


	return SUCCESS;

}

/**
 * Decode a application/hal+json document into a Hal\Resource object.
 *
 * @param string text
 * @param int maxDepth
 * @return Hal\Resource
 */
PHP_METHOD(Hal_ResourceFactory, fromJson) {

	zend_function *_16 = NULL, *_23 = NULL, *_27 = NULL;
	HashTable *_5, *_8, *_11, *_14, *_18, *_25;
	HashPosition _4, _7, _10, _13, _17, _24;
	int maxDepth;
	zval *text, *maxDepth_param = NULL, *data, *uri = NULL, *link = NULL, *rel = NULL, *links = NULL, *embed = NULL, *href = NULL, *childResource = NULL, *hal, *value, *_data, *_links, *_embedded = NULL, *_0, *_1, *_2, *_3, **_6, **_9, **_12, **_15, **_19, *_20 = NULL, *_21 = NULL, *_22 = NULL, **_26;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &text, &maxDepth_param);

	if (!maxDepth_param || Z_TYPE_P(maxDepth_param) == IS_NULL) {
		maxDepth = 0;	} else {
		maxDepth = zephir_get_intval(maxDepth_param);
	}


	ZEPHIR_INIT_VAR(data);
	zephir_call_func_p2(data, "json_decode", text, ZEPHIR_GLOBAL(global_true));
	zephir_array_fetch_string(&_0, data, SL("_links"), PH_NOISY | PH_READONLY TSRMLS_CC);
	zephir_array_fetch_string(&_1, _0, SL("self"), PH_NOISY | PH_READONLY TSRMLS_CC);
	if (zephir_array_isset_string(_1, SS("href"))) {
		zephir_array_fetch_string(&_2, data, SL("_links"), PH_NOISY | PH_READONLY TSRMLS_CC);
		zephir_array_fetch_string(&_3, _2, SL("self"), PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_OBS_VAR(uri);
		zephir_array_fetch_string(&uri, _3, SL("href"), PH_NOISY TSRMLS_CC);
	} else {
		ZEPHIR_INIT_NVAR(uri);
		ZVAL_STRING(uri, "", 1);
	}
	ZEPHIR_INIT_VAR(_links);
	if (zephir_array_isset_string(data, SS("_links"))) {
		array_init(_links);
		zephir_array_fetch_string(&_2, data, SL("_links"), PH_NOISY | PH_READONLY TSRMLS_CC);
		zephir_is_iterable(_2, &_5, &_4, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_5, (void**) &_6, &_4) == SUCCESS
			; zend_hash_move_forward_ex(_5, &_4)
		) {
			ZEPHIR_GET_HMKEY(rel, _5, _4);
			ZEPHIR_GET_HVALUE(links, _6);
			if (!ZEPHIR_IS_STRING(rel, "self")) {
				zephir_array_update_zval(&_links, rel, &links, PH_COPY | PH_SEPARATE);
			}
		}
	} else {
		array_init(_links);
	}
	if (zephir_array_isset_string(data, SS("_embedded"))) {
		ZEPHIR_OBS_VAR(_embedded);
		zephir_array_fetch_string(&_embedded, data, SL("_embedded"), PH_NOISY TSRMLS_CC);
	} else {
		ZEPHIR_INIT_NVAR(_embedded);
		array_init(_embedded);
	}
	ZEPHIR_INIT_VAR(_data);
	array_init(_data);
	zephir_is_iterable(data, &_8, &_7, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_8, (void**) &_9, &_7) == SUCCESS
		; zend_hash_move_forward_ex(_8, &_7)
	) {
		ZEPHIR_GET_HMKEY(rel, _8, _7);
		ZEPHIR_GET_HVALUE(links, _9);
		if ((!ZEPHIR_IS_STRING(rel, "_links") && !ZEPHIR_IS_STRING(rel, "_embedded"))) {
			zephir_array_update_zval(&_data, rel, &links, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_VAR(hal);
	object_init_ex(hal, hal_resource_ce);
	zephir_call_method_p2_noret(hal, "__construct", uri, _data);
	zephir_is_iterable(_links, &_11, &_10, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_11, (void**) &_12, &_10) == SUCCESS
		; zend_hash_move_forward_ex(_11, &_10)
	) {
		ZEPHIR_GET_HMKEY(rel, _11, _10);
		ZEPHIR_GET_HVALUE(links, _12);
		if (!(zephir_array_isset_long(links, 0))) {
			ZEPHIR_INIT_NVAR(link);
			array_init(link);
			zephir_array_fast_append(link, links);
			ZEPHIR_CPY_WRT(links, link);
		}
		if (zephir_array_isset_long_fetch(&value, links, 0, 1 TSRMLS_CC)) {
			if ((Z_TYPE_P(value) != IS_ARRAY)) {
				ZEPHIR_INIT_NVAR(link);
				array_init(link);
				zephir_array_fast_append(link, links);
				ZEPHIR_CPY_WRT(links, link);
			}
		}
		zephir_is_iterable(links, &_14, &_13, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_14, (void**) &_15, &_13) == SUCCESS
			; zend_hash_move_forward_ex(_14, &_13)
		) {
			ZEPHIR_GET_HVALUE(link, _15);
			if (zephir_array_isset_string(link, SS("href"))) {
				ZEPHIR_OBS_NVAR(href);
				zephir_array_fetch_string(&href, link, SL("href"), PH_NOISY TSRMLS_CC);
				zephir_array_update_string(&link, SL("href"), &ZEPHIR_GLOBAL(global_null), PH_COPY | PH_SEPARATE);
			} else {
				ZEPHIR_INIT_NVAR(href);
				ZVAL_STRING(href, "", 1);
			}
			zephir_call_method_p3_cache_noret(hal, "addlink", &_16, rel, href, link);
		}
	}
	if ((maxDepth > 0)) {
		zephir_is_iterable(_embedded, &_18, &_17, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_18, (void**) &_19, &_17) == SUCCESS
			; zend_hash_move_forward_ex(_18, &_17)
		) {
			ZEPHIR_GET_HMKEY(rel, _18, _17);
			ZEPHIR_GET_HVALUE(embed, _19);
			if ((Z_TYPE_P(embed) != IS_ARRAY)) {
				ZEPHIR_INIT_NVAR(_20);
				ZEPHIR_INIT_NVAR(_21);
				zephir_call_func_p1(_21, "json_encode", embed);
				ZEPHIR_INIT_NVAR(_22);
				ZVAL_LONG(_22, (maxDepth - 1));
				zephir_call_self_p2(_20, this_ptr, "fromjson", _21, _22);
				zephir_call_method_p2_cache_noret(hal, "addresource", &_23, rel, _20);
			} else {
				zephir_is_iterable(embed, &_25, &_24, 0, 0);
				for (
					; zend_hash_get_current_data_ex(_25, (void**) &_26, &_24) == SUCCESS
					; zend_hash_move_forward_ex(_25, &_24)
				) {
					ZEPHIR_GET_HVALUE(childResource, _26);
					ZEPHIR_INIT_NVAR(_20);
					ZEPHIR_INIT_NVAR(_21);
					zephir_call_func_p1(_21, "json_encode", childResource);
					ZEPHIR_INIT_NVAR(_22);
					ZVAL_LONG(_22, (maxDepth - 1));
					zephir_call_self_p2(_20, this_ptr, "fromjson", _21, _22);
					zephir_call_method_p2_cache_noret(hal, "addresource", &_27, rel, _20);
				}
			}
		}
	}
	RETURN_CCTOR(hal);

}

