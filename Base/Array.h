#ifndef NFLIB_ARRAY_H
#define NFLIB_ARRAY_H

// Array ///////////////////////////////////////////////////////////////////////
#define _Array(T, SIZE, ...) Array$_##T##_$$_##SIZE##_$##__VA_ARGS__
#define Array(T, SIZE, ...) _Array(T, SIZE, __VA_ARGS__)

// DEF /////////////////////////////////////////////////////////////////////////
#define _Array_DEF(T, SIZE)                                                     \
/* typedef */                                                                   \
typedef struct Array(T, SIZE)       Array(T, SIZE);                             \
typedef struct Array(T, SIZE, _ops) Array(T, SIZE, _ops);                       \
typedef T*                          Array(T, SIZE, _Iter);                      \
/* Array */                                                                     \
struct Array(T, SIZE) {                                                         \
    T data[SIZE];                                                               \
    SizeType size;                                                              \
    Array(T, SIZE, _ops)* ops;                                                  \
};                                                                              \
/* ops */                                                                       \
struct Array(T, SIZE, _ops) {                                                   \
    SizeType (*MaxSize   ) (void);                                              \
    Bool     (*PushBacks ) (Array(T, SIZE)* this, const T data[], SizeType count); \
    Bool     (*PushFronts) (Array(T, SIZE)* this, const T data[], SizeType count); \
    Bool     (*PushBack  ) (Array(T, SIZE)* this, T data);                      \
    Bool     (*PushFront ) (Array(T, SIZE)* this, T data);                      \
    Bool     (*PopBacks  ) (Array(T, SIZE)* this, T data[], SizeType count);    \
    Bool     (*PopFronts ) (Array(T, SIZE)* this, T data[], SizeType count);    \
    Bool     (*PopBack   ) (Array(T, SIZE)* this, T* data);                     \
    Bool     (*PopFront  ) (Array(T, SIZE)* this, T* data);                     \
    void     (*SetData   ) (Array(T, SIZE)* this, const T data[SIZE]);          \
    T*       (*Begin     ) (Array(T, SIZE)* this);                              \
    T*       (*End       ) (Array(T, SIZE)* this);                              \
    void     (*IterNext  ) (T** iter);                                          \
};                                                                              \
/* Init */                                                                      \
void Array(T, SIZE, _Init) (Array(T, SIZE)* this)
#define Array_DEF(T, SIZE) _Array_DEF(T, SIZE)

// IMPL ////////////////////////////////////////////////////////////////////////
#define _Array_IMPL(T, SIZE)                                                    \
/* static function */                                                           \
static inline SizeType Array(T, SIZE, _MaxSize) (void) {                        \
    return SIZE;                                                                \
}                                                                               \
static inline Bool Array(T, SIZE, _PushBacks) (Array(T, SIZE)* this, const T data[], SizeType count) { \
    SizeType i = 0;                                                             \
    if (this->size + count > SIZE) { return False; }                            \
    for (i = 0; i < count; ++i) { this->data[this->size++] = data[i]; }         \
    return True;                                                                \
}                                                                               \
static inline Bool Array(T, SIZE, _PushFronts) (Array(T, SIZE)* this, const T data[], SizeType count) { \
    SizeType i = 0;                                                             \
    if (this->size + count > SIZE) { return False; }                            \
    for (i = 0; i < this->size; ++i) {                                          \
        this->data[this->size - i + count - 1] = this->data[this->size - i - 1]; \
    }                                                                           \
    for (i = 0; i < count; ++i) { this->data[i] = data[i]; }                    \
    this->size += count;                                                        \
    return True;                                                                \
}                                                                               \
static Bool Array(T, SIZE, _PushBack) (Array(T, SIZE)* this, T data) {          \
    return Array(T, SIZE, _PushBacks) (this, &data, 1);                         \
}                                                                               \
static Bool Array(T, SIZE, _PushFront) (Array(T, SIZE)* this, T data) {         \
    return Array(T, SIZE, _PushFronts) (this, &data, 1);                        \
}                                                                               \
static inline Bool Array(T, SIZE, _PopBacks) (Array(T, SIZE)* this, T data[], SizeType count) { \
    SizeType i = 0;                                                             \
    if (this->size < count) { return False; }                                   \
    for (i = 0; i < count; ++i) { data[i] = this->data[--this->size]; }         \
    return True;                                                                \
}                                                                               \
static inline Bool Array(T, SIZE, _PopFronts) (Array(T, SIZE)* this, T data[], SizeType count) { \
    SizeType i = 0;                                                             \
    if (this->size < count) { return False; }                                   \
    for (i = 0; i < count; ++i) { data[i] = this->data[i]; }                    \
    for (i = 0; i < this->size; ++i) { this->data[i] = this->data[i + count]; } \
    this->size -= count;                                                        \
    return True;                                                                \
}                                                                               \
static Bool Array(T, SIZE, _PopBack) (Array(T, SIZE)* this, T* data) {          \
    return Array(T, SIZE, _PopBacks) (this, data, 1);                           \
}                                                                               \
static Bool Array(T, SIZE, _PopFront) (Array(T, SIZE)* this, T* data) {         \
    return Array(T, SIZE, _PopFronts) (this, data, 1);                          \
}                                                                               \
static inline void Array(T, SIZE, _SetData) (Array(T, SIZE)* this, const T data[SIZE]) { \
    SizeType i = 0;                                                             \
    for (i = 0; i < SIZE; ++i) { this->data[i] = data[i]; }                     \
    this->size = SIZE;                                                          \
}                                                                               \
static inline T* Array(T, SIZE, _Begin) (Array(T, SIZE)* this) { return &this->data[0]; } \
static inline T* Array(T, SIZE, _End) (Array(T, SIZE)* this) { return &this->data[this->size]; } \
static void Array(T, SIZE, _IterNext) (T** iter) { ++(*iter); }                 \
static Array(T, SIZE, _ops)* Array(T, SIZE, _Ops) (void) {                      \
    static Array(T, SIZE, _ops) ops;                                            \
    static Bool init = False;                                                   \
    if (init == False) {                                                        \
        init = True;                                                            \
        ops.MaxSize    = Array(T, SIZE, _MaxSize   );                           \
        ops.PushBacks  = Array(T, SIZE, _PushBacks );                           \
        ops.PushFronts = Array(T, SIZE, _PushFronts);                           \
        ops.PushBack   = Array(T, SIZE, _PushBack  );                           \
        ops.PushFront  = Array(T, SIZE, _PushFront );                           \
        ops.PopBacks   = Array(T, SIZE, _PopBacks  );                           \
        ops.PopFronts  = Array(T, SIZE, _PopFronts );                           \
        ops.PopBack    = Array(T, SIZE, _PopBack   );                           \
        ops.PopFront   = Array(T, SIZE, _PopFront  );                           \
        ops.SetData    = Array(T, SIZE, _SetData   );                           \
        ops.Begin      = Array(T, SIZE, _Begin     );                           \
        ops.End        = Array(T, SIZE, _End       );                           \
        ops.IterNext   = Array(T, SIZE, _IterNext  );                           \
    }                                                                           \
    return &ops;                                                                \
}                                                                               \
/* Init */                                                                      \
void Array(T, SIZE, _Init) (Array(T, SIZE)* this) {                             \
    this->size = 0;                                                             \
    this->ops = Array(T, SIZE, _Ops) ();                                        \
}
#define Array_IMPL(T, SIZE) _Array_IMPL(T, SIZE)

#endif // NFLIB_ARRAY_H
