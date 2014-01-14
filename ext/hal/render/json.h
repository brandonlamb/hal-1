
extern zend_class_entry *hal_render_json_ce;

ZEPHIR_INIT_CLASS(Hal_Render_Json);

PHP_METHOD(Hal_Render_Json, render);
PHP_METHOD(Hal_Render_Json, parseResource);
PHP_METHOD(Hal_Render_Json, parseLinks);
PHP_METHOD(Hal_Render_Json, parseResources);
PHP_METHOD(Hal_Render_Json, arrayFromResources);
PHP_METHOD(Hal_Render_Json, stripAttributeMarker);

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_render_json_render, 0, 0, 1)
	ZEND_ARG_INFO(0, resource)
	ZEND_ARG_INFO(0, pretty)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_render_json_parseresource, 0, 0, 1)
	ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_render_json_parselinks, 0, 0, 2)
	ZEND_ARG_INFO(0, uri)
	ZEND_ARG_INFO(0, collection)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_render_json_parseresources, 0, 0, 1)
	ZEND_ARG_INFO(0, resources)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_render_json_arrayfromresources, 0, 0, 1)
	ZEND_ARG_INFO(0, resources)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_render_json_stripattributemarker, 0, 0, 1)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(hal_render_json_method_entry) {
	PHP_ME(Hal_Render_Json, render, arginfo_hal_render_json_render, ZEND_ACC_PUBLIC)
	PHP_ME(Hal_Render_Json, parseResource, arginfo_hal_render_json_parseresource, ZEND_ACC_PROTECTED)
	PHP_ME(Hal_Render_Json, parseLinks, arginfo_hal_render_json_parselinks, ZEND_ACC_PROTECTED)
	PHP_ME(Hal_Render_Json, parseResources, arginfo_hal_render_json_parseresources, ZEND_ACC_PROTECTED)
	PHP_ME(Hal_Render_Json, arrayFromResources, arginfo_hal_render_json_arrayfromresources, ZEND_ACC_PROTECTED)
	PHP_ME(Hal_Render_Json, stripAttributeMarker, arginfo_hal_render_json_stripattributemarker, ZEND_ACC_PROTECTED)
	PHP_FE_END
};
