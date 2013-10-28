
extern zend_class_entry *hal_resource_ce;

ZEPHIR_INIT_CLASS(Hal_Resource);

PHP_METHOD(Hal_Resource, __construct);
PHP_METHOD(Hal_Resource, getUri);
PHP_METHOD(Hal_Resource, getData);
PHP_METHOD(Hal_Resource, getResources);
PHP_METHOD(Hal_Resource, getLinks);
PHP_METHOD(Hal_Resource, addResource);
PHP_METHOD(Hal_Resource, getResource);
PHP_METHOD(Hal_Resource, addLink);
PHP_METHOD(Hal_Resource, getLink);
PHP_METHOD(Hal_Resource, addCurie);
PHP_METHOD(Hal_Resource, setRenderer);
PHP_METHOD(Hal_Resource, render);

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_resource___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, uri)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_resource_addresource, 0, 0, 1)
	ZEND_ARG_INFO(0, rel)
	ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_resource_getresource, 0, 0, 1)
	ZEND_ARG_INFO(0, rel)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_resource_addlink, 0, 0, 2)
	ZEND_ARG_INFO(0, rel)
	ZEND_ARG_INFO(0, uri)
	ZEND_ARG_INFO(0, attributes)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_resource_getlink, 0, 0, 1)
	ZEND_ARG_INFO(0, rel)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_resource_addcurie, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, uri)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_resource_setrenderer, 0, 0, 1)
	ZEND_ARG_INFO(0, renderer)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_resource_render, 0, 0, 0)
	ZEND_ARG_INFO(0, pretty)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(hal_resource_method_entry) {
	PHP_ME(Hal_Resource, __construct, arginfo_hal_resource___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Hal_Resource, getUri, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Hal_Resource, getData, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Hal_Resource, getResources, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Hal_Resource, getLinks, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Hal_Resource, addResource, arginfo_hal_resource_addresource, ZEND_ACC_PUBLIC)
	PHP_ME(Hal_Resource, getResource, arginfo_hal_resource_getresource, ZEND_ACC_PUBLIC)
	PHP_ME(Hal_Resource, addLink, arginfo_hal_resource_addlink, ZEND_ACC_PUBLIC)
	PHP_ME(Hal_Resource, getLink, arginfo_hal_resource_getlink, ZEND_ACC_PUBLIC)
	PHP_ME(Hal_Resource, addCurie, arginfo_hal_resource_addcurie, ZEND_ACC_PUBLIC)
	PHP_ME(Hal_Resource, setRenderer, arginfo_hal_resource_setrenderer, ZEND_ACC_PUBLIC)
	PHP_ME(Hal_Resource, render, arginfo_hal_resource_render, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
