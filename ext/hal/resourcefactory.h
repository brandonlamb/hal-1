
extern zend_class_entry *hal_resourcefactory_ce;

ZEPHIR_INIT_CLASS(Hal_ResourceFactory);

PHP_METHOD(Hal_ResourceFactory, fromJson);
PHP_METHOD(Hal_ResourceFactory, fromXml);

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_resourcefactory_fromjson, 0, 0, 1)
	ZEND_ARG_INFO(0, text)
	ZEND_ARG_INFO(0, maxDepth)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_resourcefactory_fromxml, 0, 0, 1)
	ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(hal_resourcefactory_method_entry) {
	PHP_ME(Hal_ResourceFactory, fromJson, arginfo_hal_resourcefactory_fromjson, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Hal_ResourceFactory, fromXml, arginfo_hal_resourcefactory_fromxml, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
