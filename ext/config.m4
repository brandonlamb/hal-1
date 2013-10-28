PHP_ARG_ENABLE(hal, whether to enable hal, [ --enable-hal   Enable Hal])

if test "$PHP_HAL" = "yes"; then
	AC_DEFINE(HAVE_HAL, 1, [Whether you have Hal])
	hal_sources="hal.c kernel/main.c kernel/memory.c kernel/exception.c kernel/hash.c kernel/debug.c kernel/backtrace.c kernel/object.c kernel/array.c kernel/string.c kernel/fcall.c kernel/alternative/fcall.c kernel/operators.c kernel/concat.c hal/collection/link.c hal/collection/resource.c hal/link.c hal/render/json.c hal/render/xml.c hal/renderinterface.c hal/resource.c hal/resourcefactory.c"
	PHP_NEW_EXTENSION(hal, $hal_sources, $ext_shared)
fi
