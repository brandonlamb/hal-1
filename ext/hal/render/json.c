
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
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/hash.h"


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
 * Hal\Render\Json
 * Renders a Hal\Resource into an array that is valid for application/json+hal
 *
 * @package Hal
 * @author Ben Longden <ben@nocarrier.co.uk>
 * @author Brandon Lamb <brandon@brandonlamb.com>
 */
ZEPHIR_INIT_CLASS(Hal_Render_Json) {

	ZEPHIR_REGISTER_CLASS(Hal\\Render, Json, hal, render_json, hal_render_json_method_entry, 0);

	zend_class_implements(hal_render_json_ce TSRMLS_CC, 1, hal_renderinterface_ce);

	return SUCCESS;

}

/**
 * Render.
 *
 * @param Hal\Resource $resource
 * @param bool pretty
 * @return string
 */
PHP_METHOD(Hal_Render_Json, render) {

	int options = 0;
	zend_bool pretty;
	zval *resource, *pretty_param = NULL, *data, _0 = zval_used_for_init, _1, *_2, *_3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &resource, &pretty_param);

		pretty = zephir_get_boolval(pretty_param);


	ZEPHIR_SINIT_VAR(_0);
	ZVAL_STRING(&_0, "5.5.7-1+sury.org~precise+1", 0);
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "5.4.0", 0);
	ZEPHIR_INIT_VAR(_2);
	zephir_call_func_p2(_2, "version_compare", &_0, &_1);
	if ((ZEPHIR_GE_LONG(_2, 0) && pretty)) {
		options = 128;
	}
	ZEPHIR_INIT_VAR(_3);
	zephir_call_method_p1(_3, this_ptr, "parseresource", resource);
	ZEPHIR_SINIT_NVAR(_0);
	ZVAL_LONG(&_0, options);
	ZEPHIR_INIT_VAR(data);
	zephir_call_func_p2(data, "json_encode", _3, &_0);
	RETURN_CCTOR(data);

}

/**
 * Return an array (compatible with the hal+json format) representing the
 * complete response.
 *
 * @param Hal\Resource resource
 * @return array
 */
PHP_METHOD(Hal_Render_Json, parseResource) {

	zval *resource, *data, *links, *resources, *_0, *_1, *_2, *_3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &resource);



	if ((Z_TYPE_P(resource) != IS_OBJECT)) {
		array_init(return_value);
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(_0);
	zephir_call_method(_0, resource, "getdata");
	ZEPHIR_INIT_VAR(data);
	zephir_call_method_p1(data, this_ptr, "stripattributemarker", _0);
	ZEPHIR_INIT_VAR(_1);
	zephir_call_method(_1, resource, "geturi");
	ZEPHIR_INIT_VAR(_2);
	zephir_call_method(_2, resource, "getlinks");
	ZEPHIR_INIT_VAR(links);
	zephir_call_method_p2(links, this_ptr, "parselinks", _1, _2);
	if ((zephir_fast_count_int(links TSRMLS_CC) > 0)) {
		zephir_array_update_string(&data, SL("_links"), &links, PH_COPY | PH_SEPARATE);
	}
	ZEPHIR_INIT_VAR(_3);
	zephir_call_method(_3, resource, "getresources");
	ZEPHIR_INIT_VAR(resources);
	zephir_call_method_p1(resources, this_ptr, "parseresources", _3);
	if ((zephir_fast_count_int(resources TSRMLS_CC) > 0)) {
		zephir_array_update_string(&data, SL("_embedded"), &resources, PH_COPY | PH_SEPARATE);
	}
	RETURN_CCTOR(data);

}

/**
 * Return an array (compatible with the hal+json format) representing
 * associated links.
 *
 * @param string uri
 * @param array links
 * @return array
 */
PHP_METHOD(Hal_Render_Json, parseLinks) {

	zend_function *_7 = NULL, *_9 = NULL, *_16 = NULL, *_17 = NULL;
	HashTable *_2, *_11, *_14, *_19;
	HashPosition _1, _10, _13, _18;
	zval *uri_param = NULL, *collection, *data, *rel = NULL, *link = NULL, *links = NULL, *attribute = NULL, *attributes = NULL, *item = NULL, *value = NULL, *_0 = NULL, **_3, *_4 = NULL, *_5, *_6 = NULL, *_8, **_12, **_15, **_20, *_21 = NULL;
	zval *uri = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &uri_param, &collection);

		zephir_get_strval(uri, uri_param);


	ZEPHIR_INIT_VAR(data);
	array_init(data);
	if (!ZEPHIR_IS_STRING(uri, "")) {
		ZEPHIR_INIT_VAR(_0);
		array_init(_0);
		zephir_array_update_string(&_0, SL("href"), &uri, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&data, SL("self"), &_0, PH_COPY | PH_SEPARATE);
	}
	ZEPHIR_INIT_NVAR(_0);
	zephir_call_method(_0, collection, "getdata");
	zephir_is_iterable(_0, &_2, &_1, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
		; zend_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HMKEY(rel, _2, _1);
		ZEPHIR_GET_HVALUE(links, _3);
		if (((zephir_fast_count_int(links TSRMLS_CC) == 1) && !ZEPHIR_IS_STRING(rel, "curies"))) {
			ZEPHIR_INIT_NVAR(_4);
			array_init(_4);
			zephir_array_fetch_long(&_5, links, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
			ZEPHIR_INIT_NVAR(_6);
			zephir_call_method_cache(_6, _5, "geturi", &_7);
			zephir_array_update_string(&_4, SL("href"), &_6, PH_COPY | PH_SEPARATE);
			zephir_array_update_zval(&data, rel, &_4, PH_COPY | PH_SEPARATE);
			zephir_array_fetch_long(&_8, links, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
			ZEPHIR_INIT_NVAR(_6);
			zephir_call_method_cache(_6, _8, "getattributes", &_9);
			zephir_is_iterable(_6, &_11, &_10, 0, 0);
			for (
				; zend_hash_get_current_data_ex(_11, (void**) &_12, &_10) == SUCCESS
				; zend_hash_move_forward_ex(_11, &_10)
			) {
				ZEPHIR_GET_HMKEY(attribute, _11, _10);
				ZEPHIR_GET_HVALUE(value, _12);
				ZEPHIR_OBS_NVAR(attributes);
				zephir_array_fetch(&attributes, data, rel, PH_NOISY TSRMLS_CC);
				zephir_array_update_zval(&attributes, attribute, &value, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&data, rel, &attributes, PH_COPY | PH_SEPARATE);
			}
		} else {
			ZEPHIR_INIT_NVAR(_4);
			array_init(_4);
			zephir_array_update_zval(&data, rel, &_4, PH_COPY | PH_SEPARATE);
			zephir_is_iterable(links, &_14, &_13, 0, 0);
			for (
				; zend_hash_get_current_data_ex(_14, (void**) &_15, &_13) == SUCCESS
				; zend_hash_move_forward_ex(_14, &_13)
			) {
				ZEPHIR_GET_HVALUE(link, _15);
				ZEPHIR_INIT_NVAR(item);
				array_init(item);
				ZEPHIR_INIT_NVAR(_6);
				zephir_call_method_cache(_6, link, "geturi", &_16);
				zephir_array_update_string(&item, SL("href"), &_6, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(_6);
				zephir_call_method_cache(_6, link, "getattributes", &_17);
				zephir_is_iterable(_6, &_19, &_18, 0, 0);
				for (
					; zend_hash_get_current_data_ex(_19, (void**) &_20, &_18) == SUCCESS
					; zend_hash_move_forward_ex(_19, &_18)
				) {
					ZEPHIR_GET_HMKEY(attribute, _19, _18);
					ZEPHIR_GET_HVALUE(value, _20);
					zephir_array_update_zval(&item, attribute, &value, PH_COPY | PH_SEPARATE);
				}
				ZEPHIR_OBS_NVAR(value);
				if (zephir_array_isset_fetch(&value, data, rel, 0 TSRMLS_CC)) {
					zephir_array_append(&value, item, PH_SEPARATE);
					zephir_array_update_zval(&data, rel, &value, PH_COPY | PH_SEPARATE);
				} else {
					ZEPHIR_INIT_NVAR(_21);
					array_init(_21);
					zephir_array_fast_append(_21, item);
					zephir_array_update_zval(&data, rel, &_21, PH_COPY | PH_SEPARATE);
				}
			}
		}
	}
	RETURN_CCTOR(data);

}

/**
 * Return an array (compatible with the hal+json format) representing associated resources.
 *
 * [
 *   'rel1' => [res1, res2],
 *   'rel2' => [res1, res2],
 * ]
 *
 * @param mixed resources
 * @return array
 */
PHP_METHOD(Hal_Render_Json, parseResources) {

	zend_function *_4 = NULL;
	HashTable *_2;
	HashPosition _1;
	zval *resources = NULL, *data, *rel = NULL, *resource = NULL, *_0, **_3, *_5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &resources);

	ZEPHIR_SEPARATE_PARAM(resources);


	ZEPHIR_INIT_VAR(data);
	array_init(data);
	ZEPHIR_INIT_VAR(_0);
	zephir_call_method(_0, resources, "getdata");
	zephir_is_iterable(_0, &_2, &_1, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
		; zend_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HMKEY(rel, _2, _1);
		ZEPHIR_GET_HVALUE(resources, _3);
		ZEPHIR_INIT_NVAR(resource);
		zephir_call_method_p1_cache(resource, this_ptr, "arrayfromresources", &_4, resources);
		if ((zephir_fast_count_int(resource TSRMLS_CC) == 1)) {
			zephir_array_fetch_long(&_5, resource, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
			zephir_array_update_zval(&data, rel, &_5, PH_COPY | PH_SEPARATE);
		} else {
			zephir_array_update_zval(&data, rel, &resource, PH_COPY | PH_SEPARATE);
		}
	}
	RETURN_CCTOR(data);

}

/**
 * Loop through array of resources and pase into array
 *
 * @param array resources
 * @return array
 */
PHP_METHOD(Hal_Render_Json, arrayFromResources) {

	zend_function *_3 = NULL;
	HashTable *_1;
	HashPosition _0;
	zval *resources, *data, *resource = NULL, *res = NULL, **_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &resources);



	ZEPHIR_INIT_VAR(data);
	array_init(data);
	zephir_is_iterable(resources, &_1, &_0, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
		; zend_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HVALUE(resource, _2);
		ZEPHIR_INIT_NVAR(res);
		zephir_call_method_p1_cache(res, this_ptr, "parseresource", &_3, resource);
		if ((zephir_fast_count_int(res TSRMLS_CC) > 0)) {
			zephir_array_append(&data, res, PH_SEPARATE);
		}
	}
	RETURN_CCTOR(data);

}

/**
 * Remove the @ prefix from keys that denotes an attribute in XML. This
 * cannot be represented in JSON, so it's effectively ignored.
 *
 * @param array data The array to strip @ from the keys.
 * @return array
 */
PHP_METHOD(Hal_Render_Json, stripAttributeMarker) {

	zend_function *_8 = NULL;
	HashTable *_1;
	HashPosition _0;
	zval *data = NULL, *key = NULL, *value = NULL, **_2, _3 = zval_used_for_init, _4 = zval_used_for_init, *_5 = NULL, *_6 = NULL, *_7 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &data);

	ZEPHIR_SEPARATE_PARAM(data);


	if ((Z_TYPE_P(data) != IS_ARRAY)) {
		ZEPHIR_INIT_NVAR(data);
		array_init(data);
	}
	zephir_is_iterable(data, &_1, &_0, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
		; zend_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HMKEY(key, _1, _0);
		ZEPHIR_GET_HVALUE(value, _2);
		ZEPHIR_SINIT_NVAR(_3);
		ZVAL_LONG(&_3, 0);
		ZEPHIR_SINIT_NVAR(_4);
		ZVAL_LONG(&_4, 5);
		ZEPHIR_INIT_NVAR(_5);
		zephir_call_func_p3(_5, "substr", key, &_3, &_4);
		if (ZEPHIR_IS_STRING(_5, "@xml:")) {
			ZEPHIR_SINIT_NVAR(_3);
			ZVAL_LONG(&_3, 5);
			ZEPHIR_INIT_NVAR(_6);
			zephir_call_func_p2(_6, "substr", key, &_3);
			zephir_array_update_zval(&data, _6, &value, PH_COPY | PH_SEPARATE);
			zephir_array_unset(&data, key, PH_SEPARATE);
		} else {
			ZEPHIR_SINIT_NVAR(_3);
			ZVAL_LONG(&_3, 0);
			ZEPHIR_SINIT_NVAR(_4);
			ZVAL_LONG(&_4, 1);
			ZEPHIR_INIT_NVAR(_6);
			zephir_call_func_p3(_6, "substr", key, &_3, &_4);
			if (ZEPHIR_IS_STRING(_6, "@")) {
				ZEPHIR_SINIT_NVAR(_3);
				ZVAL_LONG(&_3, 1);
				ZEPHIR_INIT_NVAR(_7);
				zephir_call_func_p2(_7, "substr", key, &_3);
				zephir_array_update_zval(&data, _7, &value, PH_COPY | PH_SEPARATE);
				zephir_array_unset(&data, key, PH_SEPARATE);
			}
		}
		if ((Z_TYPE_P(value) == IS_ARRAY)) {
			ZEPHIR_INIT_NVAR(_6);
			zephir_call_method_p1_cache(_6, this_ptr, "stripattributemarker", &_8, value);
			zephir_array_update_zval(&data, key, &_6, PH_COPY | PH_SEPARATE);
		}
	}
	RETURN_CCTOR(data);

}

