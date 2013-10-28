
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
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
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
 * Hal\Resource
 * The Hal resource document class
 *
 * @package Hal
 * @author Ben Longden <ben@nocarrier.co.uk>
 * @author Brandon Lamb <brandon@brandonlamb.com>
 */
ZEPHIR_INIT_CLASS(Hal_Resource) {

	ZEPHIR_REGISTER_CLASS(Hal, Resource, hal, resource, hal_resource_method_entry, 0);

/**
     * The uri represented by this representation.
     *
     * @var string
     */
	zend_declare_property_null(hal_resource_ce, SL("uri"), ZEND_ACC_PROTECTED TSRMLS_CC);
/**
     * The data for this resource. An associative array of key value pairs.
     *
     * ["price" => 30.00, "colour" => "blue"]
     *
     * @var array
     */
	zend_declare_property_null(hal_resource_ce, SL("data"), ZEND_ACC_PROTECTED TSRMLS_CC);
/**
     * An array of embedded Hal objects representing embedded resources.
     *
     * @var array
     */
	zend_declare_property_null(hal_resource_ce, SL("resources"), ZEND_ACC_PROTECTED TSRMLS_CC);
/**
     * A collection of Hal\Link objects keyed by the link relation to this resource.
     *
     * ["next" => [Hal\Link]]
     *
     * @var Hal\Collection\Link
     */
	zend_declare_property_null(hal_resource_ce, SL("links"), ZEND_ACC_PROTECTED TSRMLS_CC);
/**
     * The Hal\Resource renderer
     *
     * @var Hal\RenderInterface
     */
	zend_declare_property_null(hal_resource_ce, SL("renderer"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * Construct a new Hal\Resource object from an array of data. You can markup the
 * $data array with certain keys and values in order to affect the
 * generated JSON or XML documents if required to do so.
 *
 * "@" prefix on any array key will cause the value to be set as an
 * attribute on the XML element generated by the parent. i.e, array("x" =>
 * array("@href" => "http://url")) will yield <x href="http://url"></x> in
 * the XML representation. The @ prefix will be stripped from the JSON
 * representation.
 *
 * Specifying the key "value" will cause the value of this key to be set as
 * the value of the XML element instead of a child. i.e, array("x" =>
 * array("value" => "example")) will yield <x>example</x> in the XML
 * representation. This will not affect the JSON representation.
 *
 * @param string uri
 * @param array data
 */
PHP_METHOD(Hal_Resource, __construct) {

	zval *uri_param = NULL, *data = NULL, *_0 = NULL, *_1, *_2;
	zval *uri = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &uri_param, &data);

	if (!uri_param) {
		ZEPHIR_INIT_VAR(uri);
		ZVAL_EMPTY_STRING(uri);
	} else {
		zephir_get_strval(uri, uri_param);
	}
	if (!data) {
		data = ZEPHIR_GLOBAL(global_null);
	}


	if ((Z_TYPE_P(data) == IS_ARRAY)) {
		zephir_update_property_this(this_ptr, SL("data"), data TSRMLS_CC);
	} else {
		ZEPHIR_INIT_VAR(_0);
		array_init(_0);
		zephir_update_property_this(this_ptr, SL("data"), _0 TSRMLS_CC);
	}
	zephir_update_property_this(this_ptr, SL("uri"), uri TSRMLS_CC);
	ZEPHIR_INIT_NVAR(_0);
	object_init_ex(_0, hal_collection_resource_ce);
	zephir_call_method_noret(_0, "__construct");
	zephir_update_property_this(this_ptr, SL("resources"), _0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, hal_collection_link_ce);
	zephir_call_method_noret(_1, "__construct");
	zephir_update_property_this(this_ptr, SL("links"), _1 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_2);
	object_init_ex(_2, hal_render_json_ce);
	zephir_update_property_this(this_ptr, SL("renderer"), _2 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Get resource"s URI.
 *
 * @return string
 */
PHP_METHOD(Hal_Resource, getUri) {


	RETURN_MEMBER(this_ptr, "uri");

}

/**
 * Return an array of data (key => value pairs) representing this resource.
 *
 * @return array
 */
PHP_METHOD(Hal_Resource, getData) {


	RETURN_MEMBER(this_ptr, "data");

}

/**
 * Return an array of Hal\Resource objected embedded in this one.
 *
 * @return Hal\Collection\Resource A collection of Hal\Resource
 */
PHP_METHOD(Hal_Resource, getResources) {


	RETURN_MEMBER(this_ptr, "resources");

}

/**
 * Return an array of Hal\Link objects representing resources related to this one.
 *
 * @return Hal\Collection\Link A collection of Hal\Link
 */
PHP_METHOD(Hal_Resource, getLinks) {


	RETURN_MEMBER(this_ptr, "links");

}

/**
 * Add an embedded resource, identified by $rel and represented by $resource.
 *
 * @param string rel
 * @param Hal\Resource resource
 * @return Hal\Resource
 */
PHP_METHOD(Hal_Resource, addResource) {

	zval *rel_param = NULL, *resource = NULL, *_0;
	zval *rel = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &rel_param, &resource);

		if (Z_TYPE_P(rel_param) != IS_STRING) {
				zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'rel' must be a string") TSRMLS_CC);
				RETURN_MM_NULL();
		}

		rel = rel_param;

	if (!resource) {
		ZEPHIR_CPY_WRT(resource, ZEPHIR_GLOBAL(global_null));
	}
	ZEPHIR_SEPARATE_PARAM(resource);


	if ((Z_TYPE_P(resource) == IS_NULL)) {
		ZEPHIR_INIT_NVAR(resource);
		object_init_ex(resource, hal_resource_ce);
		zephir_call_method_noret(resource, "__construct");
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("resources"), PH_NOISY_CC);
	zephir_call_method_p2_noret(_0, "add", rel, resource);
	RETURN_THIS();

}

/**
 * Add a link to the resource, identified by rel, located at uri.
 *
 * @param string rel
 * @param string uri
 * @param array attributes Other attributes, as defined by HAL spec and RFC 5988.
 * @return Hal\Resource
 */
PHP_METHOD(Hal_Resource, addLink) {

	zval *rel_param = NULL, *uri_param = NULL, *attributes = NULL, *link, *_0;
	zval *rel = NULL, *uri = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &rel_param, &uri_param, &attributes);

		if (Z_TYPE_P(rel_param) != IS_STRING) {
				zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'rel' must be a string") TSRMLS_CC);
				RETURN_MM_NULL();
		}

		rel = rel_param;

		if (Z_TYPE_P(uri_param) != IS_STRING) {
				zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'uri' must be a string") TSRMLS_CC);
				RETURN_MM_NULL();
		}

		uri = uri_param;

	if (!attributes) {
		attributes = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_INIT_VAR(link);
	object_init_ex(link, hal_link_ce);
	zephir_call_method_p2_noret(link, "__construct", uri, attributes);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("links"), PH_NOISY_CC);
	zephir_call_method_p2_noret(_0, "add", rel, link);
	RETURN_THIS();

}

/**
 * Lookup and return an array of Hal\Link objects for a given relation.  Will also resolve CURIE rels if required.
 *
 * @param string rel The link relation required
 * @return array|bool Array of Hal\Link objects if found. Otherwise false.
 */
PHP_METHOD(Hal_Resource, getLink) {

	zval *rel_param = NULL, *_0;
	zval *rel = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &rel_param);

		if (Z_TYPE_P(rel_param) != IS_STRING) {
				zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'rel' must be a string") TSRMLS_CC);
				RETURN_MM_NULL();
		}

		rel = rel_param;



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("links"), PH_NOISY_CC);
	zephir_call_method_p1(return_value, _0, "get", rel);
	RETURN_MM();

}

/**
 * Create a CURIE link template, used for abbreviating custom link relations.
 *
 * $hal->addCurie("acme", "http://.../rels/{rel}");
 * $hal->addLink("acme:test", "http://.../test");
 *
 * @param string $name
 * @param string $uri
 * @return Hal\Resource
 */
PHP_METHOD(Hal_Resource, addCurie) {

	zval *name_param = NULL, *uri_param = NULL, *_0, *_1;
	zval *name = NULL, *uri = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &uri_param);

		if (Z_TYPE_P(name_param) != IS_STRING) {
				zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
				RETURN_MM_NULL();
		}

		name = name_param;

		if (Z_TYPE_P(uri_param) != IS_STRING) {
				zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'uri' must be a string") TSRMLS_CC);
				RETURN_MM_NULL();
		}

		uri = uri_param;



	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_array_update_string(&_0, SL("name"), &name, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_0, SL("templated"), &ZEPHIR_GLOBAL(global_true), PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "curies", 1);
	zephir_call_method_p3_noret(this_ptr, "addlink", _1, uri, _0);
	RETURN_THIS();

}

/**
 * Set the renderer object
 *
 * @param Hal\RenderInterface renderer
 * @return Hal\Resource
 */
PHP_METHOD(Hal_Resource, setRenderer) {

	zval *renderer;

	zephir_fetch_params(0, 1, 0, &renderer);



	zephir_update_property_this(this_ptr, SL("renderer"), renderer TSRMLS_CC);
	RETURN_THISW();

}

/**
 * Return the current object in a application/hal+json format (links and resources).
 *
 * @param bool pretty Enable pretty-printing.
 * @return string
 */
PHP_METHOD(Hal_Resource, render) {

	zval *pretty_param = NULL, *_0;
	zend_bool pretty;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &pretty_param);

	if (!pretty_param) {
		pretty = 0;
	} else {
		pretty = zephir_get_boolval(pretty_param);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("renderer"), PH_NOISY_CC);
	zephir_call_method_p2(return_value, _0, "render", this_ptr, (pretty ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
	RETURN_MM();

}

/**
 * Decode a application/hal+json document into a Hal\Resource object.
 *
 * @param string text
 * @param int maxDepth
 * @return Hal\Resource
 */
PHP_METHOD(Hal_Resource, fromJson) {

	zend_function *_16 = NULL, *_23 = NULL, *_27 = NULL;
	HashTable *_5, *_8, *_11, *_14, *_18, *_25;
	HashPosition _4, _7, _10, _13, _17, _24;
	int maxDepth;
	zval *text, *maxDepth_param = NULL, *data, *uri = NULL, *link = NULL, *rel = NULL, *links = NULL, *embed = NULL, *href = NULL, *childResource = NULL, *hal, *value, *_data, *_links, *_embedded = NULL, *_0, *_1, *_2, *_3, **_6, **_9, **_12, **_15, **_19, *_20 = NULL, *_21 = NULL, *_22 = NULL, **_26;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &text, &maxDepth_param);

	if (!maxDepth_param) {
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

/**
 * Decode a application/hal+xml document into a Hal\Resource object.
 *
 * @param string text
 * @return Hal\Resource
 */
PHP_METHOD(Hal_Resource, fromXml) {

	zend_function *_13 = NULL, *_14 = NULL, *_15 = NULL;
	HashTable *_7, *_10;
	HashPosition _6, _9;
	zend_class_entry *_0;
	zval *text, *data, *children, *link = NULL, *links, *links2 = NULL, *embedded, *rel, *hal, *attributes = NULL, *href, *_1, *_2, *_3, *_4, *_5, **_8, **_11, *_12 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &text);



	ZEPHIR_INIT_VAR(data);
	_0 = zend_fetch_class(SL("SimpleXMLElement"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
	object_init_ex(data, _0);
	zephir_call_method_p1_noret(data, "__construct", text);
	ZEPHIR_INIT_VAR(children);
	zephir_call_method(children, data, "children");
	ZEPHIR_OBS_VAR(_1);
	zephir_read_property(&_1, children, SL("link"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(links);
	if (zephir_clone(links, _1 TSRMLS_CC) == FAILURE) {
		RETURN_MM();
	}
	ZEPHIR_OBS_VAR(_2);
	zephir_read_property(&_2, children, SL("resource"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(embedded);
	if (zephir_clone(embedded, _2 TSRMLS_CC) == FAILURE) {
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(hal);
	object_init_ex(hal, hal_resource_ce);
	ZEPHIR_INIT_VAR(_3);
	zephir_call_method(_3, data, "attributes");
	ZEPHIR_OBS_VAR(_4);
	zephir_read_property(&_4, _3, SL("href"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_5);
	zephir_call_method(_5, children, "asxml");
	zephir_call_method_p2_noret(hal, "__construct", _4, _5);
	zephir_is_iterable(links, &_7, &_6, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_7, (void**) &_8, &_6) == SUCCESS
		; zend_hash_move_forward_ex(_7, &_6)
	) {
		ZEPHIR_GET_HVALUE(links2, _8);
		if ((Z_TYPE_P(links2) != IS_ARRAY)) {
			ZEPHIR_INIT_NVAR(links2);
			array_init(links2);
			zephir_array_fast_append(links2, links2);
		}
		zephir_is_iterable(links, &_10, &_9, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_10, (void**) &_11, &_9) == SUCCESS
			; zend_hash_move_forward_ex(_10, &_9)
		) {
			ZEPHIR_GET_HVALUE(link, _11);
			ZEPHIR_INIT_NVAR(_12);
			zephir_call_method_cache(_12, link, "attributes", &_13);
			ZEPHIR_INIT_NVAR(attributes);
			zephir_call_method_cache(attributes, _12, "asxml", &_14);
			ZEPHIR_OBS_NVAR(attributes);
			zephir_array_fetch_string(&attributes, attributes, SL("@attributes"), PH_NOISY TSRMLS_CC);
			zephir_array_fetch_string(&rel, attributes, SL("rel"), PH_NOISY | PH_READONLY TSRMLS_CC);
			zephir_array_fetch_string(&href, attributes, SL("href"), PH_NOISY | PH_READONLY TSRMLS_CC);
			zephir_call_method_p3_cache_noret(hal, "addlink", &_15, rel, href, attributes);
		}
	}
	RETURN_CCTOR(hal);

}

