/** @file */

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#if defined(__GNUC__) && __GNUC__ >= 4 && __GNUC_MINOR__ > 7
/**
 * An atomic fetch-and-add.
 */
#define FAA(ptr, val) __atomic_fetch_add(ptr, val, __ATOMIC_RELAXED)
/**
 * An atomic fetch-and-add that also ensures sequential consistency.
 */
#define FAAcs(ptr, val) __atomic_fetch_add(ptr, val, __ATOMIC_SEQ_CST)

/**
 * An atomic compare-and-swap.
 */
#define CAS(ptr, cmp, val) __atomic_compare_exchange_n(ptr, cmp, val, 0, \
    __ATOMIC_RELAXED, __ATOMIC_RELAXED)
/**
 * An atomic compare-and-swap that also ensures sequential consistency.
 */
#define CAScs(ptr, cmp, val) __atomic_compare_exchange_n(ptr, cmp, val, 0, \
    __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
/**
 * An atomic compare-and-swap that ensures release semantic when succeed
 * or acquire semantic when failed.
 */
#define CASra(ptr, cmp, val) __atomic_compare_exchange_n(ptr, cmp, val, 0, \
    __ATOMIC_RELEASE, __ATOMIC_ACQUIRE)
/**
 * An atomic compare-and-swap that ensures acquire semantic when succeed
 * or relaxed semantic when failed.
 */
#define CASar(ptr, cmp, val) __atomic_compare_exchange_n(ptr, cmp, val, 0, \
    __ATOMIC_ACQUIRE, __ATOMIC_RELAXED)

/**
 * An atomic store.
 */
#define STORE(ptr, val) __atomic_store_n(ptr, val, __ATOMIC_RELAXED)

/**
 * A store with a preceding release fence to ensure all previous load
 * and stores completes before the current store is visiable.
 */
#define RELEASE(ptr, val) __atomic_store_n(ptr, val, __ATOMIC_RELEASE)

/**
 * A load with a following acquire fence to ensure no following load and
 * stores can start before the current load completes.
 */
#define ACQUIRE(ptr) __atomic_load_n(ptr, __ATOMIC_ACQUIRE)

#else /** Non-GCC or old GCC. */
#if defined(__x86_64__) || defined(_M_X64_)

#define FAA __sync_fetch_and_add
#define FAAcs __sync_fetch_and_add

static inline int
_compare_and_swap(void ** ptr, void ** expected, void * desired) {
  void * oldval = *expected;
  void * newval = __sync_val_compare_and_swap(ptr, oldval, desired);

  if (newval == oldval) {
    return 1;
  } else {
    *expected = newval;
    return 0;
  }
}
#define CAS(ptr, expected, desired) \
  _compare_and_swap((void **) ptr, (void **) expected, (void *) desired)
#define CAScs CAS
#define CASra CAS
#define CASar CAS

static inline void * _acquire(void * volatile * p) {
  void * v = *p;
  __asm__("":::"memory");
  return v;
}
#define ACQUIRE(p) (__typeof__(*p))_acquire((void * volatile *)p)
#define RELEASE(p, v) do {\
  __asm__("":::"memory"); \
  *p = v; \
} while (0)

#endif
#endif

#if defined(__x86_64__) || defined(_M_X64_)
#define PAUSE() __asm__ ("pause")
#else
#define PAUSE()
#endif

#endif /* end of include guard: PRIMITIVES_H */
