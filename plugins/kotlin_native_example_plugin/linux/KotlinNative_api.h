#ifndef KONAN_KOTLINNATIVE_H
#define KONAN_KOTLINNATIVE_H
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
typedef bool            KotlinNative_KBoolean;
#else
typedef _Bool           KotlinNative_KBoolean;
#endif
typedef unsigned short     KotlinNative_KChar;
typedef signed char        KotlinNative_KByte;
typedef short              KotlinNative_KShort;
typedef int                KotlinNative_KInt;
typedef long long          KotlinNative_KLong;
typedef unsigned char      KotlinNative_KUByte;
typedef unsigned short     KotlinNative_KUShort;
typedef unsigned int       KotlinNative_KUInt;
typedef unsigned long long KotlinNative_KULong;
typedef float              KotlinNative_KFloat;
typedef double             KotlinNative_KDouble;
typedef void*              KotlinNative_KNativePtr;
struct KotlinNative_KType;
typedef struct KotlinNative_KType KotlinNative_KType;

typedef struct {
  KotlinNative_KNativePtr pinned;
} KotlinNative_kref_kotlin_Byte;
typedef struct {
  KotlinNative_KNativePtr pinned;
} KotlinNative_kref_kotlin_Short;
typedef struct {
  KotlinNative_KNativePtr pinned;
} KotlinNative_kref_kotlin_Int;
typedef struct {
  KotlinNative_KNativePtr pinned;
} KotlinNative_kref_kotlin_Long;
typedef struct {
  KotlinNative_KNativePtr pinned;
} KotlinNative_kref_kotlin_Float;
typedef struct {
  KotlinNative_KNativePtr pinned;
} KotlinNative_kref_kotlin_Double;
typedef struct {
  KotlinNative_KNativePtr pinned;
} KotlinNative_kref_kotlin_Char;
typedef struct {
  KotlinNative_KNativePtr pinned;
} KotlinNative_kref_kotlin_Boolean;
typedef struct {
  KotlinNative_KNativePtr pinned;
} KotlinNative_kref_kotlin_Unit;
typedef struct {
  KotlinNative_KNativePtr pinned;
} KotlinNative_kref_KotlinNative_Object;
typedef struct {
  KotlinNative_KNativePtr pinned;
} KotlinNative_kref_KotlinNative_Rational;


typedef struct {
  /* Service functions. */
  void (*DisposeStablePointer)(KotlinNative_KNativePtr ptr);
  void (*DisposeString)(const char* string);
  KotlinNative_KBoolean (*IsInstance)(KotlinNative_KNativePtr ref, const KotlinNative_KType* type);
  KotlinNative_kref_kotlin_Byte (*createNullableByte)(KotlinNative_KByte);
  KotlinNative_kref_kotlin_Short (*createNullableShort)(KotlinNative_KShort);
  KotlinNative_kref_kotlin_Int (*createNullableInt)(KotlinNative_KInt);
  KotlinNative_kref_kotlin_Long (*createNullableLong)(KotlinNative_KLong);
  KotlinNative_kref_kotlin_Float (*createNullableFloat)(KotlinNative_KFloat);
  KotlinNative_kref_kotlin_Double (*createNullableDouble)(KotlinNative_KDouble);
  KotlinNative_kref_kotlin_Char (*createNullableChar)(KotlinNative_KChar);
  KotlinNative_kref_kotlin_Boolean (*createNullableBoolean)(KotlinNative_KBoolean);
  KotlinNative_kref_kotlin_Unit (*createNullableUnit)(void);

  /* User functions. */
  struct {
    struct {
      struct {
        const char* (*get_globalString)();
        const char* (*echo)(const char* str);
        struct {
          KotlinNative_KType* (*_type)(void);
          KotlinNative_kref_KotlinNative_Object (*_instance)();
          const char* (*get_pluginName)(KotlinNative_kref_KotlinNative_Object thiz);
        } Object;
        struct {
          KotlinNative_KType* (*_type)(void);
          KotlinNative_kref_KotlinNative_Rational (*Rational)(KotlinNative_KInt numerator, KotlinNative_KInt denominator);
          const char* (*toString)(KotlinNative_kref_KotlinNative_Rational thiz);
          KotlinNative_KInt (*result)(KotlinNative_kref_KotlinNative_Rational thiz);
          KotlinNative_KInt (*get_numerator)(KotlinNative_kref_KotlinNative_Rational thiz);
          KotlinNative_KInt (*get_denominator)(KotlinNative_kref_KotlinNative_Rational thiz);
        } Rational;
      } KotlinNative;
    } root;
  } kotlin;
} KotlinNative_ExportedSymbols;
extern KotlinNative_ExportedSymbols* KotlinNative_symbols(void);
#ifdef __cplusplus
}  /* extern "C" */
#endif
#endif  /* KONAN_KOTLINNATIVE_H */
