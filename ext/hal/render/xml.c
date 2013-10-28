
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
#include "kernel/hash.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/concat.h"
#include "kernel/array.h"


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
 * Hal\Render\Xml
 * Renders a Hal\Resource into an xml string that is valid for application/xml+hal
 *
 * @package Hal\Render
 * @author Ben Longden <ben@nocarrier.co.uk>
 * @author Brandon Lamb <brandon@brandonlamb.com>
 */
ZEPHIR_INIT_CLASS(Hal_Render_Xml) {

	ZEPHIR_REGISTER_CLASS(Hal\\Render, Xml, hal, render_xml, hal_render_xml_method_entry, 0);

	zend_class_implements(hal_render_xml_ce TSRMLS_CC, 1, hal_renderinterface_ce);

	return SUCCESS;

}

/**
 * Render.
 *
 * @param Hal\Resource resource
 * @param bool pretty
 * @return string
 */
PHP_METHOD(Hal_Render_Xml, render) {

	zend_function *_8 = NULL;
	HashTable *_6;
	HashPosition _5;
	zend_class_entry *_0;
	zend_bool pretty;
	zval *resource, *pretty_param = NULL, *doc, *dom, *ownerDocument, *uri, *rel = NULL, *resources = NULL, *_1, *_2 = NULL, *_3, *_4, **_7, *_9;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &resource, &pretty_param);

		pretty = zephir_get_boolval(pretty_param);


	ZEPHIR_INIT_VAR(doc);
	_0 = zend_fetch_class(SL("SimpleXMLElement"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
	object_init_ex(doc, _0);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "<resource></resource>", 1);
	zephir_call_method_p1_noret(doc, "__construct", _1);
	ZEPHIR_INIT_VAR(uri);
	zephir_call_method(uri, resource, "geturi");
	if ((Z_TYPE_P(uri) != IS_NULL)) {
		ZEPHIR_INIT_BNVAR(_1);
		zephir_call_method(_1, resource, "geturi");
		ZEPHIR_INIT_VAR(_2);
		ZVAL_STRING(_2, "href", 1);
		zephir_call_method_p2_noret(doc, "addattribute", _2, _1);
	}
	ZEPHIR_INIT_NVAR(_2);
	zephir_call_method(_2, resource, "getlinks");
	zephir_call_method_p2_noret(this_ptr, "parselinks", doc, _2);
	ZEPHIR_INIT_VAR(_3);
	zephir_call_method(_3, resource, "getdata");
	zephir_call_method_p2_noret(this_ptr, "arraytoxml", _3, doc);
	ZEPHIR_INIT_VAR(_4);
	zephir_call_method(_4, resource, "getresources");
	zephir_is_iterable(_4, &_6, &_5, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_6, (void**) &_7, &_5) == SUCCESS
		; zend_hash_move_forward_ex(_6, &_5)
	) {
		ZEPHIR_GET_HMKEY(rel, _6, _5);
		ZEPHIR_GET_HVALUE(resources, _7);
		zephir_call_method_p3_cache_noret(this_ptr, "resourcesforxml", &_8, doc, rel, resources);
	}
	ZEPHIR_INIT_VAR(dom);
	zephir_call_func_p1(dom, "dom_import_simplexml", doc);
	if (pretty) {
		ZEPHIR_OBS_VAR(ownerDocument);
		zephir_read_property(&ownerDocument, dom, SL("ownerDocument"), PH_NOISY_CC);
		zephir_update_property_zval(ownerDocument, SL("preserveWhiteSpace"), (0) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
		zephir_update_property_zval(ownerDocument, SL("formatOutput"), (1) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	}
	ZEPHIR_OBS_VAR(_9);
	zephir_read_property(&_9, dom, SL("ownerDocument"), PH_NOISY_CC);
	zephir_call_method(return_value, _9, "savexml");
	RETURN_MM();

}

/**
 * parseLinks
 *
 * Add links in hal+xml format to a SimpleXmlElement object.
 *
 * @param \SimpleXmlElement doc
 * @param Hal\Collection\Link links
 * @return void
 */
PHP_METHOD(Hal_Render_Xml, parseLinks) {

	zend_function *_9 = NULL, *_10 = NULL, *_11 = NULL, *_13 = NULL, *_14 = NULL, *_18 = NULL;
	HashTable *_2, *_6, *_16;
	HashPosition _1, _5, _15;
	zval *doc, *collection, *rel = NULL, *link = NULL, *links = NULL, *element = NULL, *attribute = NULL, *value = NULL, *_0, **_3, *_4 = NULL, **_7, *_8 = NULL, *_12 = NULL, **_17;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &doc, &collection);



	ZEPHIR_INIT_VAR(_0);
	zephir_call_method(_0, collection, "getdata");
	zephir_is_iterable(_0, &_2, &_1, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
		; zend_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HMKEY(rel, _2, _1);
		ZEPHIR_GET_HVALUE(links, _3);
		ZEPHIR_INIT_LNVAR(_4);
		ZEPHIR_CONCAT_SVS(_4, "rel: ", rel, "\n");
		zend_print_zval(_4, 0);
		zephir_is_iterable(links, &_6, &_5, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_6, (void**) &_7, &_5) == SUCCESS
			; zend_hash_move_forward_ex(_6, &_5)
		) {
			ZEPHIR_GET_HVALUE(link, _7);
			zephir_call_func_p1_noret("print_r", link);
			ZEPHIR_INIT_NVAR(_8);
			ZVAL_STRING(_8, "link", 1);
			ZEPHIR_INIT_NVAR(element);
			zephir_call_method_p1_cache(element, doc, "addchild", &_9, _8);
			ZEPHIR_INIT_NVAR(_8);
			ZVAL_STRING(_8, "rel", 1);
			zephir_call_method_p2_cache_noret(element, "addattribute", &_10, _8, rel);
			ZEPHIR_INIT_NVAR(_8);
			zephir_call_method_cache(_8, link, "geturi", &_11);
			ZEPHIR_INIT_NVAR(_12);
			ZVAL_STRING(_12, "href", 1);
			zephir_call_method_p2_cache_noret(element, "addattribute", &_13, _12, _8);
			ZEPHIR_INIT_NVAR(_12);
			zephir_call_method_cache(_12, link, "getattributes", &_14);
			zephir_is_iterable(_12, &_16, &_15, 0, 0);
			for (
				; zend_hash_get_current_data_ex(_16, (void**) &_17, &_15) == SUCCESS
				; zend_hash_move_forward_ex(_16, &_15)
			) {
				ZEPHIR_GET_HMKEY(attribute, _16, _15);
				ZEPHIR_GET_HVALUE(value, _17);
				zephir_call_method_p2_cache_noret(element, "addattribute", &_18, attribute, value);
			}
		}
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * arrayToXml
 *
 * @param array $data
 * @param \SimpleXmlElement element
 * @param mixed parent
 * @access protected
 * @return void
 */
PHP_METHOD(Hal_Render_Xml, arrayToXml) {

	zend_function *_3 = NULL, *_4 = NULL, *_5 = NULL, *_6 = NULL, *_7 = NULL, *_12 = NULL, *_14 = NULL, *_15 = NULL, *_16 = NULL;
	HashTable *_1;
	HashPosition _0;
	zval *data, *element, *parent = NULL, *key = NULL, *value = NULL, *subnode = NULL, **_2, _8 = zval_used_for_init, _9 = zval_used_for_init, *_10 = NULL, *_11 = NULL, *_13 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &data, &element, &parent);

	if (!parent) {
		parent = ZEPHIR_GLOBAL(global_null);
	}


	zephir_is_iterable(data, &_1, &_0, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
		; zend_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HMKEY(key, _1, _0);
		ZEPHIR_GET_HVALUE(value, _2);
		if ((Z_TYPE_P(value) == IS_ARRAY)) {
			if (!(zephir_is_numeric(key))) {
				if (((zephir_fast_count_int(value TSRMLS_CC) > 0) && zephir_array_isset_long(value, 0))) {
					zephir_call_method_p3_cache_noret(this_ptr, "arraytoxml", &_3, value, element, key);
				} else {
					ZEPHIR_INIT_NVAR(subnode);
					zephir_call_method_p1_cache(subnode, element, "addchild", &_4, key);
					zephir_call_method_p3_cache_noret(this_ptr, "arraytoxml", &_5, value, subnode, key);
				}
			} else {
				ZEPHIR_INIT_NVAR(subnode);
				zephir_call_method_p1_cache(subnode, element, "addchild", &_6, parent);
				zephir_call_method_p3_cache_noret(this_ptr, "arraytoxml", &_7, value, subnode, parent);
			}
		} else {
			if (!(zephir_is_numeric(key))) {
				ZEPHIR_SINIT_NVAR(_8);
				ZVAL_LONG(&_8, 0);
				ZEPHIR_SINIT_NVAR(_9);
				ZVAL_LONG(&_9, 1);
				ZEPHIR_INIT_NVAR(_10);
				zephir_call_func_p3(_10, "substr", key, &_8, &_9);
				if (ZEPHIR_IS_STRING(_10, "@")) {
					ZEPHIR_SINIT_NVAR(_8);
					ZVAL_LONG(&_8, 1);
					ZEPHIR_INIT_NVAR(_11);
					zephir_call_func_p2(_11, "substr", key, &_8);
					zephir_call_method_p2_cache_noret(element, "addattribute", &_12, _11, value);
				} else {
					if ((ZEPHIR_IS_STRING(key, "value") && (zephir_fast_count_int(data TSRMLS_CC) == 1))) {
					} else {
						ZEPHIR_INIT_NVAR(_11);
						zephir_call_func_p1(_11, "is_bool", value);
						if (zephir_is_true(_11)) {
							ZEPHIR_INIT_NVAR(_13);
							zephir_call_func_p1(_13, "intval", value);
							zephir_call_method_p2_cache_noret(element, "addchild", &_14, key, _13);
						} else {
							ZEPHIR_SINIT_NVAR(_8);
							ZVAL_LONG(&_8, 3);
							ZEPHIR_INIT_NVAR(_13);
							zephir_call_func_p2(_13, "htmlspecialchars", value, &_8);
							zephir_call_method_p2_cache_noret(element, "addchild", &_15, key, _13);
						}
					}
				}
			} else {
				ZEPHIR_SINIT_NVAR(_8);
				ZVAL_LONG(&_8, 3);
				ZEPHIR_INIT_NVAR(_10);
				zephir_call_func_p2(_10, "htmlspecialchars", value, &_8);
				zephir_call_method_p2_cache_noret(element, "addchild", &_16, parent, _10);
			}
		}
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * resourcesForXml
 *
 * Add resources in hal+xml format (identified by rel) to a
 * SimpleXmlElement object.
 *
 * @param \SimpleXmlElement doc
 * @param mixed rel
 * @param array resources
 */
PHP_METHOD(Hal_Render_Xml, resourcesForXml) {

	zend_function *_4 = NULL, *_5 = NULL, *_6 = NULL, *_7 = NULL, *_9 = NULL, *_10 = NULL, *_11 = NULL, *_13 = NULL, *_17 = NULL, *_18 = NULL, *_19 = NULL;
	HashTable *_1, *_15;
	HashPosition _0, _14;
	zval *doc, *rel, *resources, *resource = NULL, *innerRel = NULL, *innerRes = NULL, *uri = NULL, *element = NULL, **_2, *_3 = NULL, *_8 = NULL, *_12 = NULL, **_16;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &doc, &rel, &resources);



	zephir_is_iterable(resources, &_1, &_0, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
		; zend_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HVALUE(resource, _2);
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_STRING(_3, "resource", 1);
		ZEPHIR_INIT_NVAR(element);
		zephir_call_method_p1_cache(element, doc, "addchild", &_4, _3);
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_STRING(_3, "rel", 1);
		zephir_call_method_p2_cache_noret(element, "addattribute", &_5, _3, rel);
		if (zephir_is_true(resource)) {
			ZEPHIR_INIT_NVAR(uri);
			zephir_call_method_cache(uri, resource, "geturi", &_6);
			if ((Z_TYPE_P(uri) != IS_NULL)) {
				ZEPHIR_INIT_NVAR(_3);
				zephir_call_method_cache(_3, resource, "geturi", &_7);
				ZEPHIR_INIT_NVAR(_8);
				ZVAL_STRING(_8, "href", 1);
				zephir_call_method_p2_cache_noret(element, "addattribute", &_9, _8, _3);
			}
			ZEPHIR_INIT_NVAR(_8);
			zephir_call_method_cache(_8, resource, "getlinks", &_10);
			zephir_call_method_p2_cache_noret(this_ptr, "parselinks", &_11, element, _8);
			ZEPHIR_INIT_NVAR(_12);
			zephir_call_method_cache(_12, resource, "getresources", &_13);
			zephir_is_iterable(_12, &_15, &_14, 0, 0);
			for (
				; zend_hash_get_current_data_ex(_15, (void**) &_16, &_14) == SUCCESS
				; zend_hash_move_forward_ex(_15, &_14)
			) {
				ZEPHIR_GET_HMKEY(innerRel, _15, _14);
				ZEPHIR_GET_HVALUE(innerRes, _16);
				zephir_call_method_p3_cache_noret(this_ptr, "resourcesforxml", &_17, element, innerRel, innerRes);
			}
			ZEPHIR_INIT_NVAR(_8);
			zephir_call_method_cache(_8, resource, "getdata", &_18);
			zephir_call_method_p2_cache_noret(this_ptr, "arraytoxml", &_19, _8, element);
		}
	}
	ZEPHIR_MM_RESTORE();

}

