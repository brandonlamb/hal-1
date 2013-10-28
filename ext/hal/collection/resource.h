
extern zend_class_entry *hal_collection_resource_ce;

ZEPHIR_INIT_CLASS(Hal_Collection_Resource);

PHP_METHOD(Hal_Collection_Resource, __construct);
PHP_METHOD(Hal_Collection_Resource, getData);
PHP_METHOD(Hal_Collection_Resource, get);
PHP_METHOD(Hal_Collection_Resource, add);
PHP_METHOD(Hal_Collection_Resource, count);

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_collection_resource_get, 0, 0, 1)
	ZEND_ARG_INFO(0, rel)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_collection_resource_add, 0, 0, 2)
	ZEND_ARG_INFO(0, rel)
	ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(hal_collection_resource_method_entry) {
	PHP_ME(Hal_Collection_Resource, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Hal_Collection_Resource, getData, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Hal_Collection_Resource, get, arginfo_hal_collection_resource_get, ZEND_ACC_PUBLIC)
	PHP_ME(Hal_Collection_Resource, add, arginfo_hal_collection_resource_add, ZEND_ACC_PUBLIC)
	PHP_ME(Hal_Collection_Resource, count, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
